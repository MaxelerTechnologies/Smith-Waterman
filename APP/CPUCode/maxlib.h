
#ifndef MAXLIB_H
#define MAXLIB_H

#include <stdlib.h>
#include <MaxSLiCInterface.h>
#include "io.h"

#define MAX_NUM_DEVICE 8

//-------------------------------------------------------------------------
// \brief Maxeler card type.
//-------------------------------------------------------------------------
typedef enum{
	CARD_UNKNOWN,
    CARD_MAX3,
	CARD_FIRST = CARD_MAX3,
    CARD_MAX4CORIA,
    CARD_MAX4MAIA,
    CARD_SIM,
	CARD_LAST = CARD_SIM
} card_type;

const char* card_names[] = {
	"UNKNOWN",
    "MAX3424A", // must be in the same order as card_type for correct indexing
	"Coria",
	"Maia",
    "Simulation"
};


typedef struct{
	card_type maxcard;
	int linear;
	int dna;
	int simulation;

	int idx_first_device;
	int num_device;
	int loopLength;
	int num_pe;
	int lmem;

	int num_res;
	int useDnaMatrix;
	int match_score;
	int mismatch_score;
	int gap_open;
	int gap_extend;
	int maxVar;

	max_file_t    *maxfile;
	max_engine_t  *device [MAX_NUM_DEVICE];
	max_actions_t *actions[MAX_NUM_DEVICE];

	char *engine_pattern;
	int   size_bytes_S;
	int   size_bytes_flag;

} maxlib_context;



//-------------------------------------------------------------------------
// \brief Encapsulates a dynamically-loaded MaxLib instance.
//-------------------------------------------------------------------------
typedef struct {
	void *libhandle;	/**< @brief Handle to the dynamically loaded library. */

	// Use X-macros to declare function pointers
#define X(name,ret_type,arg_list) ret_type (*name)arg_list
#include "maxlib.x"
#undef X
} maxlib_t;



#endif
