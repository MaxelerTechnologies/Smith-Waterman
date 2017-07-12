/*********************************************************************
 * Maxeler Technologies: Smith Waterman Demo                         *
 *                                                                   *
 * Version: 1.3                                                      *
 * Date:    30 July 2013                                             *
 *                                                                   *
 * Backend application code source file                              *
 *                                                                   *
 *********************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <fcntl.h>

#include "cmdline.h"
#include "io.h"
#include "sw.h"
#include "timing.h"
#include "controlpipe.h"
#include "maxlib.h"

#define DESIGN_NAME SmithKernel

#define LINEAR			1
#define AFFINE			0

#define DNA				1
#define PROTEINS		0

#define DEFAULT_LINEAR	1
#define DEFAULT_DNA		1

#define MAX_LABEL_LENGTH	80


maxlib_t maxlib_load(card_type* p_card_type, int dna, int linear, int force_simulation, int* num_devices);


int main(int argc, char *argv[]) {
	// Query && database
	char *query_filename 	= NULL;
	char *lib_filename 		= NULL;
	query_stream *query		= NULL;
	data *lib 				= NULL;
	lib_stream *ls 			= NULL;
	int num_queries 		= 0;
	int lib_size 			= 0;

	// control and pipes
	struct gengetopt_args_info args_info;
	if (cmdline_parser(argc, argv, &args_info) != 0) {
		exit(EXIT_FAILURE);
	}
	msg_t msg;
	int control_pipe			= 0; /**< @brief File descriptor of the input control pipe. */
	int feedback_pipe			= 0; /**< @brief File descriptor of the output control pipe. */
	int toggle_compute 			= 0;
	int quit 					= 0;
	int compute_count 			= 0;
	int nb_display 				= 0;
	int LABEL_DISPLAY_LENGTH 	= 60;

	//Open pipes
	control_pipe = open_pipe(args_info.control_arg, O_RDONLY);
	feedback_pipe = open_pipe(args_info.feedback_arg, O_WRONLY);
	if( control_pipe==-1 || feedback_pipe==-1 ){
		return -1;
	}

	//Get the engine pattern to use, defaulting to "*" = any engine.
	const char *engine_pattern = args_info.engine_pattern_given ? args_info.engine_pattern_arg : "*";
	printf("\nUsing engine pattern \"%s\"\n\n", engine_pattern );

	//Initialisation
	int idx_first_device 	= args_info.first_device_given 	? args_info.first_device_arg 	: 0;
	int num_devices 		= args_info.num_device_given 	? args_info.num_device_arg 		: 1;

	// Detect the type of card and load the maxlib
	card_type type = CARD_UNKNOWN;
	if (args_info.dfe_given) {
	  if (strcmp(args_info.dfe_arg, "Vectis") == 0)
		type = CARD_MAX3;
	  else if (strcmp(args_info.dfe_arg, "Coria") == 0)
		type = CARD_MAX4CORIA;
	  else if (strcmp(args_info.dfe_arg, "Maia") == 0)
		type = CARD_MAX4MAIA;
	}
	int requested_num_devices = num_devices;
	maxlib_t maxlib = maxlib_load( &type, DNA /*PROTEINS*/, LINEAR, args_info.simulation_flag, &num_devices );
	if(num_devices < requested_num_devices) {
		printf("Server doesn't have %d devices, DFE run will use "
				"all %d devices found.\n", requested_num_devices, num_devices);
	} else {
		num_devices = requested_num_devices;
	}

	// Open devices and send configuration to GUI
	maxlib_context *context = maxlib.start(idx_first_device,num_devices,args_info.simulation_flag, type, feedback_pipe, engine_pattern);

	// Listening to the control pipe
	while (!quit) {
		if (has_message(control_pipe)) {
			msg = read_message(control_pipe);
		} else {
			msg = NONE;
		}

		if(msg == CONFIGURATION){
			// Load a different maxlib if required by the GUI (to switch from different algorithms)
			int dna 	= read_int(control_pipe);
			int linear 	= read_int(control_pipe);
			num_devices = requested_num_devices;
			maxlib 		= maxlib_load(&type,dna,linear,args_info.simulation_flag, &num_devices);
			if(num_devices < requested_num_devices) {
				printf("Server doesn't have %d devices, DFE run will use "
						"all %d devices found.\n", requested_num_devices, num_devices);
			} else {
				num_devices = requested_num_devices;
			}
			context 	= maxlib.restart(context, feedback_pipe);
		}
		if (msg == QUERY) {
			// Read the query file
			query = maxlib.load_queries(context, query, &num_queries, query_filename, control_pipe, feedback_pipe);
		}
		else if (msg == LIBRARY) {
			compute_count = 0;

			// Read the library file
			lib = maxlib.load_database(context, lib, &lib_size, lib_filename, control_pipe, feedback_pipe);

			// Divide the library into parts and interlace sequences
			ls = maxlib.prepare_database(context, ls, lib, lib_size, feedback_pipe);
		}
		else if (msg == STOP) {
			// Stop the compuation loop
			toggle_compute = 0;
			write_message(feedback_pipe, STOP);
		}
		else if (msg == COMPUTE || toggle_compute == 1) {
			if (toggle_compute == 0) {
				// First computation of the loop : read parameters from the pipe and set dfe parameter scalar inputs
				maxlib.set_sw(context, ls,control_pipe, lib_size, &nb_display, &LABEL_DISPLAY_LENGTH);
			}
			write_message(feedback_pipe, COMPUTE);
			toggle_compute = 1;

			// Set scalar inputs for the query sequence
			maxlib.set_query(context, query, compute_count);

			// Configure streams: for SLiC, this just sets the number of ticks
			maxlib.set_pcie_stream(context,(ls->cycles + (context->num_pe - 1)) * context->loopLength);

			// Run the alignment
			double startTime = gettime();
			ls = maxlib.run_alignment(context, ls);
			double dfeTime = gettime() - startTime;

			// Sort results and send to GUI
			maxlib.send_results(context, query, ls, lib, dfeTime, compute_count, nb_display, LABEL_DISPLAY_LENGTH, feedback_pipe, 0);

			// Control the computation loop
			compute_count++;
			if (!(compute_count < num_queries)) {
				toggle_compute = 0;
				compute_count = 0;
				write_message(feedback_pipe, STOP);
			}

		}
		else if (msg == QUIT) {
			quit = 1;
		}

	}

	// Shutting down
	printf("Shutting down\n");
	free(query_filename);
	free(lib_filename);

	// Close devices
	maxlib.end(context);

	// Free some memory
	if (lib) {
		for(int i=0;i<lib_size;i++){
	  		free(lib[i].label);
			free(lib[i].s);
		}
		free(lib);
	}
	if (ls) {
		for(int k=0;k<num_devices;k++){
			free(ls[k].inS);
			free(ls[k].label);
			free(ls[k].vflag);
			free(ls[k].Sflag);
			free(ls[k].twobitflag);
			free(ls[k].output);
			free(ls[k].which);
		}
		free(ls);

	}

	return 0;
}

typedef char filename_t[255];

static void *maxlib_load_library_for_card(card_type card, int dna, int linear, int *num_devices, filename_t filename) {
	snprintf(filename, sizeof(filename_t)-1, "libmaxlib_%s_%c_%s.so",
			card_names[card], dna==1 ? 'n' : 'p', linear==1 ? "lin" : "aff");
	void* libhandle = dlopen(filename, RTLD_NOW);
	if (!libhandle) {
		fprintf(stderr, "Error loading [%s]: %s\n", filename, dlerror());
		exit(1);
	}
	dlerror(); /* Clear any existing error */

	size_t (*count_engines_fn)() = dlsym(libhandle, "maxlib_count_engines");
	*num_devices = (*count_engines_fn)();

	return libhandle;
}

static void *maxlib_load_library(card_type *p_card_type, int dna, int linear, int force_simulation, int *num_devices, filename_t filename) {
	void *libhandle = NULL;
	if(!force_simulation) {
		for(card_type i=CARD_FIRST; i<CARD_LAST; ++i) {
			libhandle = maxlib_load_library_for_card(i, dna, linear, num_devices, filename);
			if(*num_devices > 0) {
				*p_card_type = i;
				break;
			} else {
				dlclose(libhandle);
			}
		}
	}

	// no card, load simulation
	if(libhandle == NULL) {
		snprintf(filename, sizeof(filename_t)-1, "libmaxlib_%s_%c_%s.so",
				card_names[CARD_SIM], dna==1 ? 'n' : 'p', linear==1 ? "lin" : "aff");
		libhandle = dlopen(filename, RTLD_NOW);
		if (!libhandle) {
			fprintf(stderr, "Error loading [%s]: %s\n", filename, dlerror());
			exit(1);
		}
		dlerror(); /* Clear any existing error */
		*p_card_type = CARD_SIM;
	}

	return libhandle;
}


/**********************************************************************
 * \brief Dynamically load the correct SO for the specified card type.
 **********************************************************************/
maxlib_t maxlib_load(card_type* p_card_type, int dna, int linear, int force_simulation, int* num_devices){
	maxlib_t maxlib;
	filename_t filename;
	if (*p_card_type == CARD_UNKNOWN)
		maxlib.libhandle = maxlib_load_library(p_card_type, dna, linear, force_simulation, num_devices, filename);
	else
		maxlib.libhandle = maxlib_load_library_for_card(*p_card_type, dna, linear, num_devices, filename);

	/* Use X-macros to load functions */
#define X(name,ret_type,arg_list) \
	maxlib.name = (ret_type (*)arg_list)dlsym(maxlib.libhandle, "maxlib_" #name); \
	if (maxlib.name == NULL) { \
		fprintf(stderr, "Could not load symbol \"%s\" from [%s] - %s\n", "maxlib_" #name, filename, dlerror()); \
		exit(1); \
	}
#include "maxlib.x"
#undef X

	printf("OK\n");
	return maxlib;
}

