#include <stdlib.h>
#include <string.h>
#include "maxlib.h"
#include "controlpipe.h"
#include "io.h"
#include "SmithWaterman.h"

#define SMITH_KERNEL "SmithKernel"


static void load_lmem(
		maxlib_context *context,
		lib_stream * ls);

static void run_and_reinitialise_actions(
		maxlib_context *context);

/******************************************
 * MaxLib functions
 ******************************************/


maxlib_context* maxlib_start(
		const int idx_first_device,
		const int num_device,
		const int simulation,
		card_type type,
		int feedback_pipe,
		const char *engine_pattern
		)
{
	maxlib_context *this_ 	= malloc(sizeof(*this_));

	printf("Opening %d device%s...", num_device, num_device==1 ? "" : "s");
	fflush(NULL);
	this_->idx_first_device = idx_first_device;
	this_->num_device 		= num_device;
	this_->simulation 		= simulation;
	this_->maxcard 			= type;

	//open maxfile
	this_->maxfile 		    = SmithWaterman_init();
	this_->engine_pattern   = strdup(engine_pattern);

	//read maxfile constants
	this_->num_pe 		    = max_get_constant_uint64t(this_->maxfile, "numPE");
	this_->lmem 		    = max_get_constant_uint64t(this_->maxfile, "lmem");
	this_->linear 		    = max_get_constant_uint64t(this_->maxfile, "linear");
	this_->dna 			    = max_get_constant_uint64t(this_->maxfile, "dna");
	this_->loopLength 	    = max_get_constant_uint64t(this_->maxfile, "loopLength");
	this_->useDnaMatrix     = max_get_constant_uint64t(this_->maxfile, "useDnaMatrix");
	this_->maxVar 		    = max_get_constant_uint64t(this_->maxfile, "maxVar");

	//open num_devices
	int dev 			    = 0;
	for (int i=idx_first_device;i<idx_first_device+num_device;i++){
		this_->device[dev]  = max_load(this_->maxfile, this_->engine_pattern );
		dev++;
	}
	this_->num_device       = dev;

	for ( int i = 0 ; i < num_device ; i++ ){
		this_->actions[i] = max_actions_init(this_->maxfile, NULL);
		max_disable_validation(this_->actions[i]);
	}

	printf("OK\n");
	printf("Smith Waterman Demo - Running on %d device%s\n", dev, dev==1 ? "" : "s");

	write_int(feedback_pipe, CONFIGURATION);
	write_int(feedback_pipe, this_->num_pe);
	write_int(feedback_pipe, this_->maxVar);
	write_int(feedback_pipe, this_->num_device);
	write_int(feedback_pipe, (int)type);

	return this_;

}

maxlib_context* maxlib_restart(
		maxlib_context* this_,
		int feedback_pipe)
{
	for(int i=0;i<this_->num_device;i++){
		max_unload(this_->device[i]);
	}
	max_file_free(this_->maxfile);

	//open maxfile
	this_->maxfile 		= SmithWaterman_init();

	//read maxfile constants
	this_->num_pe 		= max_get_constant_uint64t(this_->maxfile, "numPE");
	this_->lmem 		= max_get_constant_uint64t(this_->maxfile, "lmem");
	this_->linear 		= max_get_constant_uint64t(this_->maxfile, "linear");
	this_->dna 			= max_get_constant_uint64t(this_->maxfile, "dna");
	this_->loopLength 	= max_get_constant_uint64t(this_->maxfile, "loopLength");
	this_->useDnaMatrix = max_get_constant_uint64t(this_->maxfile, "useDnaMatrix");
	this_->maxVar 		= max_get_constant_uint64t(this_->maxfile, "maxVar");

	//open num_devices
	int dev=0;

	for(int i=this_->idx_first_device;i<this_->idx_first_device+this_->num_device;i++){
		this_->device[dev] = max_load(this_->maxfile, this_->engine_pattern );
		dev++;
	}

	write_int(feedback_pipe, CONFIGURATION);
	write_int(feedback_pipe, this_->num_pe);
	write_int(feedback_pipe, this_->maxVar);
	write_int(feedback_pipe, this_->num_device);
	write_int(feedback_pipe, (int)this_->maxcard);

	return this_;

}

void maxlib_end(
		maxlib_context *context)
{
	for(int i=0;i<context->num_device;i++){
		max_unload(context->device[i]);
	}
	max_file_free(context->maxfile);
	free(context->engine_pattern);
	free(context);
}

void maxlib_set_pcie_stream(
		maxlib_context *context,
		int num_cycles)
{
	for ( int i = 0 ; i < context->num_device ; i++ ) {
		max_set_ticks( context->actions[i], SMITH_KERNEL, num_cycles );
	}
}



lib_stream * maxlib_run_alignment(
		maxlib_context *context,
		lib_stream *ls)
{
	for ( int i = 0 ; i < context->num_device ; i++ ) {
		if (context->lmem == 0) {
			max_queue_input(context->actions[i], "inS",     ls[i].inS,        context->loopLength*ls[i].tn * sizeof(unsigned char));
			max_queue_input(context->actions[i], "inhflag", ls[i].twobitflag, context->loopLength*ls[i].ttn* sizeof(unsigned char));
		} else {
			max_lmem_linear(context->actions[i], "inS",     0,                     context->size_bytes_S   );
			max_lmem_linear(context->actions[i], "inhflag", context->size_bytes_S, context->size_bytes_flag);
		}

		max_queue_output(context->actions[i], "SW",    ls[i].output, (ls[i].number_of_output) * sizeof(int));
		max_queue_output(context->actions[i], "which", ls[i].which,  (ls[i].number_of_output) * sizeof(int));
	}

	run_and_reinitialise_actions( context );

	return ls;
}


void maxlib_send_results(
		maxlib_context *context,
		query_stream * query,
		lib_stream * ls,
		data * lib,
		double dfeTime,
		int compute_count,
		int nb_display,
		int LABEL_DISPLAY_LENGTH,
		int feedback_pipe,
		int check_results)
{
	int *index = NULL;
	int *sw = NULL;
	char *buffer = (char*) malloc(LABEL_DISPLAY_LENGTH * sizeof(char));

	int count = 0;
	int total_output = 0;
	for(int k=0;k<context->num_device;k++){
		for (int i = 0; i < context->loopLength; i++) {
			for (int j = 0; j < ls[k].number_of_output; j++) {
				if (ls[k].which[j] == i) {
					lib[count++].sw = ls[k].output[j];
				}
			}
		}
		total_output += ls[k].number_of_output;
	}
	get_higher_scores(nb_display, &index, &sw, lib, total_output);
	float cups = (float)((double)(query[compute_count].n) * (double) context->num_res / (double) dfeTime);

	//Writing results to the pipe
	//number of results
	write_int(feedback_pipe, nb_display);

	//GCUPS qs->m*nb_lib_residues/dfeTime
	write_float(feedback_pipe, cups);

	//query length + sequence
	write_int(feedback_pipe, query[compute_count].n);
	write_nchar(feedback_pipe, (char*) query[compute_count].s, query[compute_count].n);

	//query label
	buffer = strncpy(buffer, query[compute_count].label, LABEL_DISPLAY_LENGTH);
	for (int j = strlen(buffer); j < LABEL_DISPLAY_LENGTH; j++)
		buffer[j] = ' '; //<- not sure about that one
	write_nchar(feedback_pipe, buffer, LABEL_DISPLAY_LENGTH);

	//nb_display * (write 80 char + score + seqlen)
	for (int i = 0; i < nb_display; i++) {
		//label
		buffer = strncpy(buffer, lib[index[i]].label, LABEL_DISPLAY_LENGTH);

		for (int j = strlen(buffer); j < LABEL_DISPLAY_LENGTH; j++) {
			buffer[j] = ' ';
		}
		write_nchar(feedback_pipe, buffer, LABEL_DISPLAY_LENGTH);
		//seq length
		write_int(feedback_pipe, lib[index[i]].n);
		//score
		write_int(feedback_pipe, sw[i]);
	}
	//best match length + sequence
	write_int(feedback_pipe, lib[index[0]].n);
	write_nchar(feedback_pipe, (char*) lib[index[0]].s, lib[index[0]].n);
	if(check_results){
#ifdef CHECK_RESULTS
		int i,j;

		for(i=0;i<ls->number_of_output;i++) {
			fprintf(stderr,"sw0 %3d %5d %10d\n",i,ls->which[i],ls->output[i]);
		}

		/*smith waterman in C*/
		//sw right value
		data *lib;
		double cpuTime=0;
		lib = smithwaterman(query_filename,lib_filename,gap_open,gap_extend,&cpuTime,dna);

		//creating array "expected" : expected SW output
		int expected[(ls->number_of_output)];
		for(i=0;i<ls->number_of_output;i++) {
			expected[i] = lib[i].sw;
		}

		//creating array "out" : actual SW output from the DFE
		count = 0;
		int out[ls->number_of_output];
		for(i=0;i<loopLength;i++) {
			for(j=0;j<ls->number_of_output;j++) {
				if(ls->which[j]==i) {
					out[count] = ls->output[j];
					count++;
				}
			}
		}

		//print out for debug, see the difference of "expected" and "out"
		for(i=0;i<ls->number_of_output;i++) {
			fprintf(stderr,"sw final : %4d %10d %10d\n",i,expected[i],out[i]);
		}

		//checking the correspondence of "expected" and "out"
		printf("Checking data read from DFE.\n");
		for(i = 0; i < ls->number_of_output; i++)
		if(out[i] != expected[i]) {
			fprintf(stderr, "Output data @ %d = %d (expected %d)\n",
					i, out[i], expected[i]);
			status = 1;
		}

		if (status)
		printf("Test failed.\n");
		else
		printf("Test passed OK!\n");

		/**/
		printf("DFE time : %4.6f sec\n",dfeTime);
		printf("CPU  time : %4.6f sec\n",cpuTime);
#endif
	}

	free(index);
	free(sw);
	free(buffer);

}



data * maxlib_load_database(
		maxlib_context *context,
		data *lib,
		int *lib_size,
		char *lib_filename,
		int control_pipe,
		int feedback_pipe)
{
	// Get the database filename from the control pipe
	write_message(feedback_pipe, LIBRARY);
	context->linear = read_int(control_pipe);
	context->dna = read_int(control_pipe);
	int lib_filename_len = read_int(control_pipe);
	lib_filename = (char*) realloc(lib_filename, (1 + lib_filename_len) * sizeof(char));
	lib_filename = read_nchar(control_pipe, lib_filename, lib_filename_len);
	lib_filename[lib_filename_len] = '\0';

	// Load the database in a data structure
	int align = 0;
	switch(context->maxcard){
	//case CARD_MAX2C:
	//case CARD_MAX2B:
	case CARD_SIM:
		align=4*context->loopLength*context->num_device;
		break;
	case CARD_MAX4CORIA:
	case CARD_MAX4MAIA:
	case CARD_MAX3:
		align=8*context->loopLength*context->num_device;
		break;
	default :
		align=8*context->loopLength*context->num_device;
		break;
	}
	lib = allocate_database(lib, lib_filename, lib_size, align, context->dna);

	return lib;
}



/*
 * Divide the database into num_device*loopLength parts and interlace the data
 */
lib_stream * maxlib_prepare_database(
		maxlib_context *context,
		lib_stream *ls,
		data *lib,
		int lib_size,
		int feedback_pipe)
{
	// De-allocate the previous database
	if (ls != NULL) {
		for(int k=0;k<context->num_device;k++){
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
	// Divide the database into num_device*loopLength parts in temporary lls[num_device*loopLength]
	lib_stream *lls = NULL;
	context->num_res = max_create_library_stream(&lls, context->loopLength*context->num_device, lib, lib_size, context->dna);
	write_int(feedback_pipe, context->num_res);

	if (context->num_res>0) {
		// Interlace the database into ls
		ls = max_integrate_library_stream(ls, lls, context->loopLength, context->num_device, 1);
		write_int(feedback_pipe, lib_size);

		// Send the length of one part to the DFE
		for(int k=0;k<context->num_device;k++){
			max_set_uint64t(context->actions[k], SMITH_KERNEL, "n", (unsigned int) ls->cycles);
		}
	}

	// Free temporary lls
	if (lls != NULL) {
		for (int i = 0; i < context->loopLength*context->num_device; i++) {
			free(lls[i].twobitflag);
			free(lls[i].inS);
			free(lls[i].vflag);
			free(lls[i].Sflag);
			free(lls[i].output);
		}
		free(lls);
	}

	return ls;
}



query_stream * maxlib_load_queries(
		maxlib_context *context,
		query_stream *query,
		int *num_queries,
		char *query_filename,
		int control_pipe,
		int feedback_pipe)
{
	write_message(feedback_pipe, QUERY);
	context->linear = read_int(control_pipe);
	context->dna = read_int(control_pipe);
	int query_filename_len = read_int(control_pipe);
	query_filename = (char*)realloc(query_filename, (1+query_filename_len)*sizeof(char));
	query_filename = read_nchar(control_pipe,query_filename,query_filename_len);
	query_filename[query_filename_len] = '\0';

	//Use allocate_queries to load any queries with a length <= num_pe
	query = allocate_queries(query, query_filename, num_queries, context->num_pe, context->dna);
	write_int(feedback_pipe, *num_queries);

	if(*num_queries>0){
		int min_length = query[0].n;
		int max_length = query[0].n;
		for(int i=1;i<*num_queries;i++){
			min_length = min_length<query[i].n ? min_length : query[i].n ;
			max_length = max_length>query[i].n ? max_length : query[i].n ;
		}
		write_int(feedback_pipe, min_length);
		write_int(feedback_pipe, max_length);
	}

	return query;
}



void maxlib_set_query(
		maxlib_context * context,
		query_stream * query,
		int compute_count)
{
	char scalar_T[30];
	for(int dev=0;dev<context->num_device;dev++){
		for (int i = 0; i < context->num_pe; i++) {
			sprintf(scalar_T, "T%d", i);
			max_set_uint64t(context->actions[dev], SMITH_KERNEL, scalar_T, query[compute_count].inT[i]);
		}
	}
}




void maxlib_set_sw(
		maxlib_context *context,
		lib_stream *ls,
		int control_pipe,
		int lib_size,
		int *nb_display,
		int *display_len
		)
{
	context->linear 		= read_int(control_pipe);
	context->dna 			= read_int(control_pipe);
	*nb_display 			= read_int(control_pipe);
	*display_len 			= read_int(control_pipe);
	context->match_score 	= read_int(control_pipe);
	context->mismatch_score = read_int(control_pipe);
	context->gap_open 		= read_int(control_pipe);
	context->gap_extend 	= read_int(control_pipe);

	*nb_display = *nb_display < lib_size ? *nb_display : lib_size;
	context->gap_extend = context->linear == 0 ? context->gap_extend : context->gap_open;

	for(int i=0;i<context->num_device;i++){
		// gap_open
		max_set_uint64t(context->actions[i], SMITH_KERNEL, "open",
				context->linear == 1 ? context->gap_open : context->gap_open + context->gap_extend);

		// gap_extend in affine SW
		if (context->linear == 0){
			max_set_uint64t(context->actions[i], SMITH_KERNEL, "extend",context->gap_extend);
		}

		// match and mismatch scores for nucleotides SW if there is no nucleotides scoring matrix
		if (context->dna == 1 && context->useDnaMatrix == 0) {
			max_set_uint64t(context->actions[i], SMITH_KERNEL, "match",   context->match_score   );
			max_set_uint64t(context->actions[i], SMITH_KERNEL, "mismatch",context->mismatch_score);
		}
	}

	// Load the database into LMEM
	if (context->lmem == 1) {
		load_lmem(context, ls);
	}
}



static void load_lmem(
		maxlib_context *context,
		lib_stream * ls)
{
	int burst_len_in = max_get_burst_size(context->maxfile, NULL);

	context->size_bytes_S = context->loopLength * ls[0].tn* sizeof(unsigned char);
	while (context->size_bytes_S % burst_len_in != 0)
		context->size_bytes_S++;

	context->size_bytes_flag = context->loopLength * ls[0].ttn* sizeof(unsigned char);
	while (context->size_bytes_flag % burst_len_in != 0)
		context->size_bytes_flag++;

	for (int i=0;i<context->num_device;i++) {
		max_lmem_linear  (context->actions[i], "write_lmem",   0,         context->size_bytes_S);
		max_queue_input  (context->actions[i], "cpu_to_lmem", ls[i].inS, context->size_bytes_S);
	}
	run_and_reinitialise_actions(context);

	for(int i=0;i<context->num_device;i++){
		max_lmem_linear  (context->actions[i], "write_lmem",   context->size_bytes_S, context->size_bytes_flag);
		max_queue_input  (context->actions[i], "cpu_to_lmem", ls[i].twobitflag,      context->size_bytes_flag);
	}
	run_and_reinitialise_actions(context);
}



static void run_and_reinitialise_actions(
		maxlib_context *context)
{
	max_run_t* runs[MAX_NUM_DEVICE];
	for ( int i = 0 ; i < context->num_device ; i++ ){
		runs[i] = max_run_nonblock(context->device[i], context->actions[i]);
	}

	/*----- re-initialise actions for next time */
	for ( int i = 0 ; i < context->num_device ; i++ ){
		max_wait(runs[i]);
		max_actions_free(context->actions[i]);
		context->actions[i] = max_actions_init(context->maxfile, NULL);
		max_disable_validation(context->actions[i]);
	}
}


size_t maxlib_count_engines() {
	max_file_t* maxfile = SmithWaterman_init();
	const size_t engine_count = max_count_engines_present(maxfile, "*");
	max_file_free(maxfile);

	return engine_count;
}



/******************************************
 * Dummy function to sanity-check
 * X-macros match actual function types.
 ******************************************/
static void DUMMY_FUNCTION(void) __attribute__((unused));
static void DUMMY_FUNCTION(void)
{
    maxlib_t maxlib;
#define X(name,ret_type,arg_list) \
		maxlib.name = maxlib_##name;
#include "maxlib.x"
#undef X
}







