/**\file */
#ifndef SLIC_DECLARATIONS_SmithWaterman_H
#define SLIC_DECLARATIONS_SmithWaterman_H
#include "MaxSLiCInterface.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int SmithWaterman_has_errors(void);
const char* SmithWaterman_get_errors(void);
#define SmithWaterman_loopLength (6)
#define SmithWaterman_numPE (512)
#define SmithWaterman_lmem (1)
#define SmithWaterman_linear (1)
#define SmithWaterman_dna (1)
#define SmithWaterman_mismatch (1)
#define SmithWaterman_match (1)
#define SmithWaterman_useDnaMatrix (1)
#define SmithWaterman_tableWidth (24)
#define SmithWaterman_maxVar (5)


/*----------------------------------------------------------------------------*/
/*--------------------------- Interface writeLMem ----------------------------*/
/*----------------------------------------------------------------------------*/



/**
 * \brief Basic static function for the interface 'writeLMem'.
 * 
 * \param [in] param_address Interface Parameter "address".
 * \param [in] param_nbytes Interface Parameter "nbytes".
 * \param [in] instream_cpu_to_lmem The stream should be of size param_nbytes bytes.
 */
void SmithWaterman_writeLMem(
	int64_t param_address,
	int64_t param_nbytes,
	const void *instream_cpu_to_lmem);

/**
 * \brief Basic static non-blocking function for the interface 'writeLMem'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_address Interface Parameter "address".
 * \param [in] param_nbytes Interface Parameter "nbytes".
 * \param [in] instream_cpu_to_lmem The stream should be of size param_nbytes bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *SmithWaterman_writeLMem_nonblock(
	int64_t param_address,
	int64_t param_nbytes,
	const void *instream_cpu_to_lmem);

/**
 * \brief Advanced static interface, structure for the engine interface 'writeLMem'
 * 
 */
typedef struct { 
	int64_t param_address; /**<  [in] Interface Parameter "address". */
	int64_t param_nbytes; /**<  [in] Interface Parameter "nbytes". */
	const void *instream_cpu_to_lmem; /**<  [in] The stream should be of size param_nbytes bytes. */
} SmithWaterman_writeLMem_actions_t;

/**
 * \brief Advanced static function for the interface 'writeLMem'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void SmithWaterman_writeLMem_run(
	max_engine_t *engine,
	SmithWaterman_writeLMem_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'writeLMem'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *SmithWaterman_writeLMem_run_nonblock(
	max_engine_t *engine,
	SmithWaterman_writeLMem_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'writeLMem'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void SmithWaterman_writeLMem_run_group(max_group_t *group, SmithWaterman_writeLMem_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'writeLMem'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *SmithWaterman_writeLMem_run_group_nonblock(max_group_t *group, SmithWaterman_writeLMem_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'writeLMem'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void SmithWaterman_writeLMem_run_array(max_engarray_t *engarray, SmithWaterman_writeLMem_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'writeLMem'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *SmithWaterman_writeLMem_run_array_nonblock(max_engarray_t *engarray, SmithWaterman_writeLMem_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* SmithWaterman_writeLMem_convert(max_file_t *maxfile, SmithWaterman_writeLMem_actions_t *interface_actions);



/*----------------------------------------------------------------------------*/
/*---------------------------- Interface readLMem ----------------------------*/
/*----------------------------------------------------------------------------*/



/**
 * \brief Basic static function for the interface 'readLMem'.
 * 
 * \param [in] param_address Interface Parameter "address".
 * \param [in] param_nbytes Interface Parameter "nbytes".
 * \param [out] outstream_lmem_to_cpu The stream should be of size param_nbytes bytes.
 */
void SmithWaterman_readLMem(
	int64_t param_address,
	int64_t param_nbytes,
	void *outstream_lmem_to_cpu);

/**
 * \brief Basic static non-blocking function for the interface 'readLMem'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_address Interface Parameter "address".
 * \param [in] param_nbytes Interface Parameter "nbytes".
 * \param [out] outstream_lmem_to_cpu The stream should be of size param_nbytes bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *SmithWaterman_readLMem_nonblock(
	int64_t param_address,
	int64_t param_nbytes,
	void *outstream_lmem_to_cpu);

/**
 * \brief Advanced static interface, structure for the engine interface 'readLMem'
 * 
 */
typedef struct { 
	int64_t param_address; /**<  [in] Interface Parameter "address". */
	int64_t param_nbytes; /**<  [in] Interface Parameter "nbytes". */
	void *outstream_lmem_to_cpu; /**<  [out] The stream should be of size param_nbytes bytes. */
} SmithWaterman_readLMem_actions_t;

/**
 * \brief Advanced static function for the interface 'readLMem'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void SmithWaterman_readLMem_run(
	max_engine_t *engine,
	SmithWaterman_readLMem_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'readLMem'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *SmithWaterman_readLMem_run_nonblock(
	max_engine_t *engine,
	SmithWaterman_readLMem_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'readLMem'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void SmithWaterman_readLMem_run_group(max_group_t *group, SmithWaterman_readLMem_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'readLMem'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *SmithWaterman_readLMem_run_group_nonblock(max_group_t *group, SmithWaterman_readLMem_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'readLMem'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void SmithWaterman_readLMem_run_array(max_engarray_t *engarray, SmithWaterman_readLMem_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'readLMem'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *SmithWaterman_readLMem_run_array_nonblock(max_engarray_t *engarray, SmithWaterman_readLMem_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* SmithWaterman_readLMem_convert(max_file_t *maxfile, SmithWaterman_readLMem_actions_t *interface_actions);



/*----------------------------------------------------------------------------*/
/*---------------------------- Interface default -----------------------------*/
/*----------------------------------------------------------------------------*/



/**
 * \brief Basic static function for the interface 'default'.
 * 
 * \param [in] ticks_SmithKernel The number of ticks for which kernel "SmithKernel" will run.
 * \param [in] inscalar_SmithKernel_T0 Input scalar parameter "SmithKernel.T0".
 * \param [in] inscalar_SmithKernel_T1 Input scalar parameter "SmithKernel.T1".
 * \param [in] inscalar_SmithKernel_T10 Input scalar parameter "SmithKernel.T10".
 * \param [in] inscalar_SmithKernel_T100 Input scalar parameter "SmithKernel.T100".
 * \param [in] inscalar_SmithKernel_T101 Input scalar parameter "SmithKernel.T101".
 * \param [in] inscalar_SmithKernel_T102 Input scalar parameter "SmithKernel.T102".
 * \param [in] inscalar_SmithKernel_T103 Input scalar parameter "SmithKernel.T103".
 * \param [in] inscalar_SmithKernel_T104 Input scalar parameter "SmithKernel.T104".
 * \param [in] inscalar_SmithKernel_T105 Input scalar parameter "SmithKernel.T105".
 * \param [in] inscalar_SmithKernel_T106 Input scalar parameter "SmithKernel.T106".
 * \param [in] inscalar_SmithKernel_T107 Input scalar parameter "SmithKernel.T107".
 * \param [in] inscalar_SmithKernel_T108 Input scalar parameter "SmithKernel.T108".
 * \param [in] inscalar_SmithKernel_T109 Input scalar parameter "SmithKernel.T109".
 * \param [in] inscalar_SmithKernel_T11 Input scalar parameter "SmithKernel.T11".
 * \param [in] inscalar_SmithKernel_T110 Input scalar parameter "SmithKernel.T110".
 * \param [in] inscalar_SmithKernel_T111 Input scalar parameter "SmithKernel.T111".
 * \param [in] inscalar_SmithKernel_T112 Input scalar parameter "SmithKernel.T112".
 * \param [in] inscalar_SmithKernel_T113 Input scalar parameter "SmithKernel.T113".
 * \param [in] inscalar_SmithKernel_T114 Input scalar parameter "SmithKernel.T114".
 * \param [in] inscalar_SmithKernel_T115 Input scalar parameter "SmithKernel.T115".
 * \param [in] inscalar_SmithKernel_T116 Input scalar parameter "SmithKernel.T116".
 * \param [in] inscalar_SmithKernel_T117 Input scalar parameter "SmithKernel.T117".
 * \param [in] inscalar_SmithKernel_T118 Input scalar parameter "SmithKernel.T118".
 * \param [in] inscalar_SmithKernel_T119 Input scalar parameter "SmithKernel.T119".
 * \param [in] inscalar_SmithKernel_T12 Input scalar parameter "SmithKernel.T12".
 * \param [in] inscalar_SmithKernel_T120 Input scalar parameter "SmithKernel.T120".
 * \param [in] inscalar_SmithKernel_T121 Input scalar parameter "SmithKernel.T121".
 * \param [in] inscalar_SmithKernel_T122 Input scalar parameter "SmithKernel.T122".
 * \param [in] inscalar_SmithKernel_T123 Input scalar parameter "SmithKernel.T123".
 * \param [in] inscalar_SmithKernel_T124 Input scalar parameter "SmithKernel.T124".
 * \param [in] inscalar_SmithKernel_T125 Input scalar parameter "SmithKernel.T125".
 * \param [in] inscalar_SmithKernel_T126 Input scalar parameter "SmithKernel.T126".
 * \param [in] inscalar_SmithKernel_T127 Input scalar parameter "SmithKernel.T127".
 * \param [in] inscalar_SmithKernel_T128 Input scalar parameter "SmithKernel.T128".
 * \param [in] inscalar_SmithKernel_T129 Input scalar parameter "SmithKernel.T129".
 * \param [in] inscalar_SmithKernel_T13 Input scalar parameter "SmithKernel.T13".
 * \param [in] inscalar_SmithKernel_T130 Input scalar parameter "SmithKernel.T130".
 * \param [in] inscalar_SmithKernel_T131 Input scalar parameter "SmithKernel.T131".
 * \param [in] inscalar_SmithKernel_T132 Input scalar parameter "SmithKernel.T132".
 * \param [in] inscalar_SmithKernel_T133 Input scalar parameter "SmithKernel.T133".
 * \param [in] inscalar_SmithKernel_T134 Input scalar parameter "SmithKernel.T134".
 * \param [in] inscalar_SmithKernel_T135 Input scalar parameter "SmithKernel.T135".
 * \param [in] inscalar_SmithKernel_T136 Input scalar parameter "SmithKernel.T136".
 * \param [in] inscalar_SmithKernel_T137 Input scalar parameter "SmithKernel.T137".
 * \param [in] inscalar_SmithKernel_T138 Input scalar parameter "SmithKernel.T138".
 * \param [in] inscalar_SmithKernel_T139 Input scalar parameter "SmithKernel.T139".
 * \param [in] inscalar_SmithKernel_T14 Input scalar parameter "SmithKernel.T14".
 * \param [in] inscalar_SmithKernel_T140 Input scalar parameter "SmithKernel.T140".
 * \param [in] inscalar_SmithKernel_T141 Input scalar parameter "SmithKernel.T141".
 * \param [in] inscalar_SmithKernel_T142 Input scalar parameter "SmithKernel.T142".
 * \param [in] inscalar_SmithKernel_T143 Input scalar parameter "SmithKernel.T143".
 * \param [in] inscalar_SmithKernel_T144 Input scalar parameter "SmithKernel.T144".
 * \param [in] inscalar_SmithKernel_T145 Input scalar parameter "SmithKernel.T145".
 * \param [in] inscalar_SmithKernel_T146 Input scalar parameter "SmithKernel.T146".
 * \param [in] inscalar_SmithKernel_T147 Input scalar parameter "SmithKernel.T147".
 * \param [in] inscalar_SmithKernel_T148 Input scalar parameter "SmithKernel.T148".
 * \param [in] inscalar_SmithKernel_T149 Input scalar parameter "SmithKernel.T149".
 * \param [in] inscalar_SmithKernel_T15 Input scalar parameter "SmithKernel.T15".
 * \param [in] inscalar_SmithKernel_T150 Input scalar parameter "SmithKernel.T150".
 * \param [in] inscalar_SmithKernel_T151 Input scalar parameter "SmithKernel.T151".
 * \param [in] inscalar_SmithKernel_T152 Input scalar parameter "SmithKernel.T152".
 * \param [in] inscalar_SmithKernel_T153 Input scalar parameter "SmithKernel.T153".
 * \param [in] inscalar_SmithKernel_T154 Input scalar parameter "SmithKernel.T154".
 * \param [in] inscalar_SmithKernel_T155 Input scalar parameter "SmithKernel.T155".
 * \param [in] inscalar_SmithKernel_T156 Input scalar parameter "SmithKernel.T156".
 * \param [in] inscalar_SmithKernel_T157 Input scalar parameter "SmithKernel.T157".
 * \param [in] inscalar_SmithKernel_T158 Input scalar parameter "SmithKernel.T158".
 * \param [in] inscalar_SmithKernel_T159 Input scalar parameter "SmithKernel.T159".
 * \param [in] inscalar_SmithKernel_T16 Input scalar parameter "SmithKernel.T16".
 * \param [in] inscalar_SmithKernel_T160 Input scalar parameter "SmithKernel.T160".
 * \param [in] inscalar_SmithKernel_T161 Input scalar parameter "SmithKernel.T161".
 * \param [in] inscalar_SmithKernel_T162 Input scalar parameter "SmithKernel.T162".
 * \param [in] inscalar_SmithKernel_T163 Input scalar parameter "SmithKernel.T163".
 * \param [in] inscalar_SmithKernel_T164 Input scalar parameter "SmithKernel.T164".
 * \param [in] inscalar_SmithKernel_T165 Input scalar parameter "SmithKernel.T165".
 * \param [in] inscalar_SmithKernel_T166 Input scalar parameter "SmithKernel.T166".
 * \param [in] inscalar_SmithKernel_T167 Input scalar parameter "SmithKernel.T167".
 * \param [in] inscalar_SmithKernel_T168 Input scalar parameter "SmithKernel.T168".
 * \param [in] inscalar_SmithKernel_T169 Input scalar parameter "SmithKernel.T169".
 * \param [in] inscalar_SmithKernel_T17 Input scalar parameter "SmithKernel.T17".
 * \param [in] inscalar_SmithKernel_T170 Input scalar parameter "SmithKernel.T170".
 * \param [in] inscalar_SmithKernel_T171 Input scalar parameter "SmithKernel.T171".
 * \param [in] inscalar_SmithKernel_T172 Input scalar parameter "SmithKernel.T172".
 * \param [in] inscalar_SmithKernel_T173 Input scalar parameter "SmithKernel.T173".
 * \param [in] inscalar_SmithKernel_T174 Input scalar parameter "SmithKernel.T174".
 * \param [in] inscalar_SmithKernel_T175 Input scalar parameter "SmithKernel.T175".
 * \param [in] inscalar_SmithKernel_T176 Input scalar parameter "SmithKernel.T176".
 * \param [in] inscalar_SmithKernel_T177 Input scalar parameter "SmithKernel.T177".
 * \param [in] inscalar_SmithKernel_T178 Input scalar parameter "SmithKernel.T178".
 * \param [in] inscalar_SmithKernel_T179 Input scalar parameter "SmithKernel.T179".
 * \param [in] inscalar_SmithKernel_T18 Input scalar parameter "SmithKernel.T18".
 * \param [in] inscalar_SmithKernel_T180 Input scalar parameter "SmithKernel.T180".
 * \param [in] inscalar_SmithKernel_T181 Input scalar parameter "SmithKernel.T181".
 * \param [in] inscalar_SmithKernel_T182 Input scalar parameter "SmithKernel.T182".
 * \param [in] inscalar_SmithKernel_T183 Input scalar parameter "SmithKernel.T183".
 * \param [in] inscalar_SmithKernel_T184 Input scalar parameter "SmithKernel.T184".
 * \param [in] inscalar_SmithKernel_T185 Input scalar parameter "SmithKernel.T185".
 * \param [in] inscalar_SmithKernel_T186 Input scalar parameter "SmithKernel.T186".
 * \param [in] inscalar_SmithKernel_T187 Input scalar parameter "SmithKernel.T187".
 * \param [in] inscalar_SmithKernel_T188 Input scalar parameter "SmithKernel.T188".
 * \param [in] inscalar_SmithKernel_T189 Input scalar parameter "SmithKernel.T189".
 * \param [in] inscalar_SmithKernel_T19 Input scalar parameter "SmithKernel.T19".
 * \param [in] inscalar_SmithKernel_T190 Input scalar parameter "SmithKernel.T190".
 * \param [in] inscalar_SmithKernel_T191 Input scalar parameter "SmithKernel.T191".
 * \param [in] inscalar_SmithKernel_T192 Input scalar parameter "SmithKernel.T192".
 * \param [in] inscalar_SmithKernel_T193 Input scalar parameter "SmithKernel.T193".
 * \param [in] inscalar_SmithKernel_T194 Input scalar parameter "SmithKernel.T194".
 * \param [in] inscalar_SmithKernel_T195 Input scalar parameter "SmithKernel.T195".
 * \param [in] inscalar_SmithKernel_T196 Input scalar parameter "SmithKernel.T196".
 * \param [in] inscalar_SmithKernel_T197 Input scalar parameter "SmithKernel.T197".
 * \param [in] inscalar_SmithKernel_T198 Input scalar parameter "SmithKernel.T198".
 * \param [in] inscalar_SmithKernel_T199 Input scalar parameter "SmithKernel.T199".
 * \param [in] inscalar_SmithKernel_T2 Input scalar parameter "SmithKernel.T2".
 * \param [in] inscalar_SmithKernel_T20 Input scalar parameter "SmithKernel.T20".
 * \param [in] inscalar_SmithKernel_T200 Input scalar parameter "SmithKernel.T200".
 * \param [in] inscalar_SmithKernel_T201 Input scalar parameter "SmithKernel.T201".
 * \param [in] inscalar_SmithKernel_T202 Input scalar parameter "SmithKernel.T202".
 * \param [in] inscalar_SmithKernel_T203 Input scalar parameter "SmithKernel.T203".
 * \param [in] inscalar_SmithKernel_T204 Input scalar parameter "SmithKernel.T204".
 * \param [in] inscalar_SmithKernel_T205 Input scalar parameter "SmithKernel.T205".
 * \param [in] inscalar_SmithKernel_T206 Input scalar parameter "SmithKernel.T206".
 * \param [in] inscalar_SmithKernel_T207 Input scalar parameter "SmithKernel.T207".
 * \param [in] inscalar_SmithKernel_T208 Input scalar parameter "SmithKernel.T208".
 * \param [in] inscalar_SmithKernel_T209 Input scalar parameter "SmithKernel.T209".
 * \param [in] inscalar_SmithKernel_T21 Input scalar parameter "SmithKernel.T21".
 * \param [in] inscalar_SmithKernel_T210 Input scalar parameter "SmithKernel.T210".
 * \param [in] inscalar_SmithKernel_T211 Input scalar parameter "SmithKernel.T211".
 * \param [in] inscalar_SmithKernel_T212 Input scalar parameter "SmithKernel.T212".
 * \param [in] inscalar_SmithKernel_T213 Input scalar parameter "SmithKernel.T213".
 * \param [in] inscalar_SmithKernel_T214 Input scalar parameter "SmithKernel.T214".
 * \param [in] inscalar_SmithKernel_T215 Input scalar parameter "SmithKernel.T215".
 * \param [in] inscalar_SmithKernel_T216 Input scalar parameter "SmithKernel.T216".
 * \param [in] inscalar_SmithKernel_T217 Input scalar parameter "SmithKernel.T217".
 * \param [in] inscalar_SmithKernel_T218 Input scalar parameter "SmithKernel.T218".
 * \param [in] inscalar_SmithKernel_T219 Input scalar parameter "SmithKernel.T219".
 * \param [in] inscalar_SmithKernel_T22 Input scalar parameter "SmithKernel.T22".
 * \param [in] inscalar_SmithKernel_T220 Input scalar parameter "SmithKernel.T220".
 * \param [in] inscalar_SmithKernel_T221 Input scalar parameter "SmithKernel.T221".
 * \param [in] inscalar_SmithKernel_T222 Input scalar parameter "SmithKernel.T222".
 * \param [in] inscalar_SmithKernel_T223 Input scalar parameter "SmithKernel.T223".
 * \param [in] inscalar_SmithKernel_T224 Input scalar parameter "SmithKernel.T224".
 * \param [in] inscalar_SmithKernel_T225 Input scalar parameter "SmithKernel.T225".
 * \param [in] inscalar_SmithKernel_T226 Input scalar parameter "SmithKernel.T226".
 * \param [in] inscalar_SmithKernel_T227 Input scalar parameter "SmithKernel.T227".
 * \param [in] inscalar_SmithKernel_T228 Input scalar parameter "SmithKernel.T228".
 * \param [in] inscalar_SmithKernel_T229 Input scalar parameter "SmithKernel.T229".
 * \param [in] inscalar_SmithKernel_T23 Input scalar parameter "SmithKernel.T23".
 * \param [in] inscalar_SmithKernel_T230 Input scalar parameter "SmithKernel.T230".
 * \param [in] inscalar_SmithKernel_T231 Input scalar parameter "SmithKernel.T231".
 * \param [in] inscalar_SmithKernel_T232 Input scalar parameter "SmithKernel.T232".
 * \param [in] inscalar_SmithKernel_T233 Input scalar parameter "SmithKernel.T233".
 * \param [in] inscalar_SmithKernel_T234 Input scalar parameter "SmithKernel.T234".
 * \param [in] inscalar_SmithKernel_T235 Input scalar parameter "SmithKernel.T235".
 * \param [in] inscalar_SmithKernel_T236 Input scalar parameter "SmithKernel.T236".
 * \param [in] inscalar_SmithKernel_T237 Input scalar parameter "SmithKernel.T237".
 * \param [in] inscalar_SmithKernel_T238 Input scalar parameter "SmithKernel.T238".
 * \param [in] inscalar_SmithKernel_T239 Input scalar parameter "SmithKernel.T239".
 * \param [in] inscalar_SmithKernel_T24 Input scalar parameter "SmithKernel.T24".
 * \param [in] inscalar_SmithKernel_T240 Input scalar parameter "SmithKernel.T240".
 * \param [in] inscalar_SmithKernel_T241 Input scalar parameter "SmithKernel.T241".
 * \param [in] inscalar_SmithKernel_T242 Input scalar parameter "SmithKernel.T242".
 * \param [in] inscalar_SmithKernel_T243 Input scalar parameter "SmithKernel.T243".
 * \param [in] inscalar_SmithKernel_T244 Input scalar parameter "SmithKernel.T244".
 * \param [in] inscalar_SmithKernel_T245 Input scalar parameter "SmithKernel.T245".
 * \param [in] inscalar_SmithKernel_T246 Input scalar parameter "SmithKernel.T246".
 * \param [in] inscalar_SmithKernel_T247 Input scalar parameter "SmithKernel.T247".
 * \param [in] inscalar_SmithKernel_T248 Input scalar parameter "SmithKernel.T248".
 * \param [in] inscalar_SmithKernel_T249 Input scalar parameter "SmithKernel.T249".
 * \param [in] inscalar_SmithKernel_T25 Input scalar parameter "SmithKernel.T25".
 * \param [in] inscalar_SmithKernel_T250 Input scalar parameter "SmithKernel.T250".
 * \param [in] inscalar_SmithKernel_T251 Input scalar parameter "SmithKernel.T251".
 * \param [in] inscalar_SmithKernel_T252 Input scalar parameter "SmithKernel.T252".
 * \param [in] inscalar_SmithKernel_T253 Input scalar parameter "SmithKernel.T253".
 * \param [in] inscalar_SmithKernel_T254 Input scalar parameter "SmithKernel.T254".
 * \param [in] inscalar_SmithKernel_T255 Input scalar parameter "SmithKernel.T255".
 * \param [in] inscalar_SmithKernel_T256 Input scalar parameter "SmithKernel.T256".
 * \param [in] inscalar_SmithKernel_T257 Input scalar parameter "SmithKernel.T257".
 * \param [in] inscalar_SmithKernel_T258 Input scalar parameter "SmithKernel.T258".
 * \param [in] inscalar_SmithKernel_T259 Input scalar parameter "SmithKernel.T259".
 * \param [in] inscalar_SmithKernel_T26 Input scalar parameter "SmithKernel.T26".
 * \param [in] inscalar_SmithKernel_T260 Input scalar parameter "SmithKernel.T260".
 * \param [in] inscalar_SmithKernel_T261 Input scalar parameter "SmithKernel.T261".
 * \param [in] inscalar_SmithKernel_T262 Input scalar parameter "SmithKernel.T262".
 * \param [in] inscalar_SmithKernel_T263 Input scalar parameter "SmithKernel.T263".
 * \param [in] inscalar_SmithKernel_T264 Input scalar parameter "SmithKernel.T264".
 * \param [in] inscalar_SmithKernel_T265 Input scalar parameter "SmithKernel.T265".
 * \param [in] inscalar_SmithKernel_T266 Input scalar parameter "SmithKernel.T266".
 * \param [in] inscalar_SmithKernel_T267 Input scalar parameter "SmithKernel.T267".
 * \param [in] inscalar_SmithKernel_T268 Input scalar parameter "SmithKernel.T268".
 * \param [in] inscalar_SmithKernel_T269 Input scalar parameter "SmithKernel.T269".
 * \param [in] inscalar_SmithKernel_T27 Input scalar parameter "SmithKernel.T27".
 * \param [in] inscalar_SmithKernel_T270 Input scalar parameter "SmithKernel.T270".
 * \param [in] inscalar_SmithKernel_T271 Input scalar parameter "SmithKernel.T271".
 * \param [in] inscalar_SmithKernel_T272 Input scalar parameter "SmithKernel.T272".
 * \param [in] inscalar_SmithKernel_T273 Input scalar parameter "SmithKernel.T273".
 * \param [in] inscalar_SmithKernel_T274 Input scalar parameter "SmithKernel.T274".
 * \param [in] inscalar_SmithKernel_T275 Input scalar parameter "SmithKernel.T275".
 * \param [in] inscalar_SmithKernel_T276 Input scalar parameter "SmithKernel.T276".
 * \param [in] inscalar_SmithKernel_T277 Input scalar parameter "SmithKernel.T277".
 * \param [in] inscalar_SmithKernel_T278 Input scalar parameter "SmithKernel.T278".
 * \param [in] inscalar_SmithKernel_T279 Input scalar parameter "SmithKernel.T279".
 * \param [in] inscalar_SmithKernel_T28 Input scalar parameter "SmithKernel.T28".
 * \param [in] inscalar_SmithKernel_T280 Input scalar parameter "SmithKernel.T280".
 * \param [in] inscalar_SmithKernel_T281 Input scalar parameter "SmithKernel.T281".
 * \param [in] inscalar_SmithKernel_T282 Input scalar parameter "SmithKernel.T282".
 * \param [in] inscalar_SmithKernel_T283 Input scalar parameter "SmithKernel.T283".
 * \param [in] inscalar_SmithKernel_T284 Input scalar parameter "SmithKernel.T284".
 * \param [in] inscalar_SmithKernel_T285 Input scalar parameter "SmithKernel.T285".
 * \param [in] inscalar_SmithKernel_T286 Input scalar parameter "SmithKernel.T286".
 * \param [in] inscalar_SmithKernel_T287 Input scalar parameter "SmithKernel.T287".
 * \param [in] inscalar_SmithKernel_T288 Input scalar parameter "SmithKernel.T288".
 * \param [in] inscalar_SmithKernel_T289 Input scalar parameter "SmithKernel.T289".
 * \param [in] inscalar_SmithKernel_T29 Input scalar parameter "SmithKernel.T29".
 * \param [in] inscalar_SmithKernel_T290 Input scalar parameter "SmithKernel.T290".
 * \param [in] inscalar_SmithKernel_T291 Input scalar parameter "SmithKernel.T291".
 * \param [in] inscalar_SmithKernel_T292 Input scalar parameter "SmithKernel.T292".
 * \param [in] inscalar_SmithKernel_T293 Input scalar parameter "SmithKernel.T293".
 * \param [in] inscalar_SmithKernel_T294 Input scalar parameter "SmithKernel.T294".
 * \param [in] inscalar_SmithKernel_T295 Input scalar parameter "SmithKernel.T295".
 * \param [in] inscalar_SmithKernel_T296 Input scalar parameter "SmithKernel.T296".
 * \param [in] inscalar_SmithKernel_T297 Input scalar parameter "SmithKernel.T297".
 * \param [in] inscalar_SmithKernel_T298 Input scalar parameter "SmithKernel.T298".
 * \param [in] inscalar_SmithKernel_T299 Input scalar parameter "SmithKernel.T299".
 * \param [in] inscalar_SmithKernel_T3 Input scalar parameter "SmithKernel.T3".
 * \param [in] inscalar_SmithKernel_T30 Input scalar parameter "SmithKernel.T30".
 * \param [in] inscalar_SmithKernel_T300 Input scalar parameter "SmithKernel.T300".
 * \param [in] inscalar_SmithKernel_T301 Input scalar parameter "SmithKernel.T301".
 * \param [in] inscalar_SmithKernel_T302 Input scalar parameter "SmithKernel.T302".
 * \param [in] inscalar_SmithKernel_T303 Input scalar parameter "SmithKernel.T303".
 * \param [in] inscalar_SmithKernel_T304 Input scalar parameter "SmithKernel.T304".
 * \param [in] inscalar_SmithKernel_T305 Input scalar parameter "SmithKernel.T305".
 * \param [in] inscalar_SmithKernel_T306 Input scalar parameter "SmithKernel.T306".
 * \param [in] inscalar_SmithKernel_T307 Input scalar parameter "SmithKernel.T307".
 * \param [in] inscalar_SmithKernel_T308 Input scalar parameter "SmithKernel.T308".
 * \param [in] inscalar_SmithKernel_T309 Input scalar parameter "SmithKernel.T309".
 * \param [in] inscalar_SmithKernel_T31 Input scalar parameter "SmithKernel.T31".
 * \param [in] inscalar_SmithKernel_T310 Input scalar parameter "SmithKernel.T310".
 * \param [in] inscalar_SmithKernel_T311 Input scalar parameter "SmithKernel.T311".
 * \param [in] inscalar_SmithKernel_T312 Input scalar parameter "SmithKernel.T312".
 * \param [in] inscalar_SmithKernel_T313 Input scalar parameter "SmithKernel.T313".
 * \param [in] inscalar_SmithKernel_T314 Input scalar parameter "SmithKernel.T314".
 * \param [in] inscalar_SmithKernel_T315 Input scalar parameter "SmithKernel.T315".
 * \param [in] inscalar_SmithKernel_T316 Input scalar parameter "SmithKernel.T316".
 * \param [in] inscalar_SmithKernel_T317 Input scalar parameter "SmithKernel.T317".
 * \param [in] inscalar_SmithKernel_T318 Input scalar parameter "SmithKernel.T318".
 * \param [in] inscalar_SmithKernel_T319 Input scalar parameter "SmithKernel.T319".
 * \param [in] inscalar_SmithKernel_T32 Input scalar parameter "SmithKernel.T32".
 * \param [in] inscalar_SmithKernel_T320 Input scalar parameter "SmithKernel.T320".
 * \param [in] inscalar_SmithKernel_T321 Input scalar parameter "SmithKernel.T321".
 * \param [in] inscalar_SmithKernel_T322 Input scalar parameter "SmithKernel.T322".
 * \param [in] inscalar_SmithKernel_T323 Input scalar parameter "SmithKernel.T323".
 * \param [in] inscalar_SmithKernel_T324 Input scalar parameter "SmithKernel.T324".
 * \param [in] inscalar_SmithKernel_T325 Input scalar parameter "SmithKernel.T325".
 * \param [in] inscalar_SmithKernel_T326 Input scalar parameter "SmithKernel.T326".
 * \param [in] inscalar_SmithKernel_T327 Input scalar parameter "SmithKernel.T327".
 * \param [in] inscalar_SmithKernel_T328 Input scalar parameter "SmithKernel.T328".
 * \param [in] inscalar_SmithKernel_T329 Input scalar parameter "SmithKernel.T329".
 * \param [in] inscalar_SmithKernel_T33 Input scalar parameter "SmithKernel.T33".
 * \param [in] inscalar_SmithKernel_T330 Input scalar parameter "SmithKernel.T330".
 * \param [in] inscalar_SmithKernel_T331 Input scalar parameter "SmithKernel.T331".
 * \param [in] inscalar_SmithKernel_T332 Input scalar parameter "SmithKernel.T332".
 * \param [in] inscalar_SmithKernel_T333 Input scalar parameter "SmithKernel.T333".
 * \param [in] inscalar_SmithKernel_T334 Input scalar parameter "SmithKernel.T334".
 * \param [in] inscalar_SmithKernel_T335 Input scalar parameter "SmithKernel.T335".
 * \param [in] inscalar_SmithKernel_T336 Input scalar parameter "SmithKernel.T336".
 * \param [in] inscalar_SmithKernel_T337 Input scalar parameter "SmithKernel.T337".
 * \param [in] inscalar_SmithKernel_T338 Input scalar parameter "SmithKernel.T338".
 * \param [in] inscalar_SmithKernel_T339 Input scalar parameter "SmithKernel.T339".
 * \param [in] inscalar_SmithKernel_T34 Input scalar parameter "SmithKernel.T34".
 * \param [in] inscalar_SmithKernel_T340 Input scalar parameter "SmithKernel.T340".
 * \param [in] inscalar_SmithKernel_T341 Input scalar parameter "SmithKernel.T341".
 * \param [in] inscalar_SmithKernel_T342 Input scalar parameter "SmithKernel.T342".
 * \param [in] inscalar_SmithKernel_T343 Input scalar parameter "SmithKernel.T343".
 * \param [in] inscalar_SmithKernel_T344 Input scalar parameter "SmithKernel.T344".
 * \param [in] inscalar_SmithKernel_T345 Input scalar parameter "SmithKernel.T345".
 * \param [in] inscalar_SmithKernel_T346 Input scalar parameter "SmithKernel.T346".
 * \param [in] inscalar_SmithKernel_T347 Input scalar parameter "SmithKernel.T347".
 * \param [in] inscalar_SmithKernel_T348 Input scalar parameter "SmithKernel.T348".
 * \param [in] inscalar_SmithKernel_T349 Input scalar parameter "SmithKernel.T349".
 * \param [in] inscalar_SmithKernel_T35 Input scalar parameter "SmithKernel.T35".
 * \param [in] inscalar_SmithKernel_T350 Input scalar parameter "SmithKernel.T350".
 * \param [in] inscalar_SmithKernel_T351 Input scalar parameter "SmithKernel.T351".
 * \param [in] inscalar_SmithKernel_T352 Input scalar parameter "SmithKernel.T352".
 * \param [in] inscalar_SmithKernel_T353 Input scalar parameter "SmithKernel.T353".
 * \param [in] inscalar_SmithKernel_T354 Input scalar parameter "SmithKernel.T354".
 * \param [in] inscalar_SmithKernel_T355 Input scalar parameter "SmithKernel.T355".
 * \param [in] inscalar_SmithKernel_T356 Input scalar parameter "SmithKernel.T356".
 * \param [in] inscalar_SmithKernel_T357 Input scalar parameter "SmithKernel.T357".
 * \param [in] inscalar_SmithKernel_T358 Input scalar parameter "SmithKernel.T358".
 * \param [in] inscalar_SmithKernel_T359 Input scalar parameter "SmithKernel.T359".
 * \param [in] inscalar_SmithKernel_T36 Input scalar parameter "SmithKernel.T36".
 * \param [in] inscalar_SmithKernel_T360 Input scalar parameter "SmithKernel.T360".
 * \param [in] inscalar_SmithKernel_T361 Input scalar parameter "SmithKernel.T361".
 * \param [in] inscalar_SmithKernel_T362 Input scalar parameter "SmithKernel.T362".
 * \param [in] inscalar_SmithKernel_T363 Input scalar parameter "SmithKernel.T363".
 * \param [in] inscalar_SmithKernel_T364 Input scalar parameter "SmithKernel.T364".
 * \param [in] inscalar_SmithKernel_T365 Input scalar parameter "SmithKernel.T365".
 * \param [in] inscalar_SmithKernel_T366 Input scalar parameter "SmithKernel.T366".
 * \param [in] inscalar_SmithKernel_T367 Input scalar parameter "SmithKernel.T367".
 * \param [in] inscalar_SmithKernel_T368 Input scalar parameter "SmithKernel.T368".
 * \param [in] inscalar_SmithKernel_T369 Input scalar parameter "SmithKernel.T369".
 * \param [in] inscalar_SmithKernel_T37 Input scalar parameter "SmithKernel.T37".
 * \param [in] inscalar_SmithKernel_T370 Input scalar parameter "SmithKernel.T370".
 * \param [in] inscalar_SmithKernel_T371 Input scalar parameter "SmithKernel.T371".
 * \param [in] inscalar_SmithKernel_T372 Input scalar parameter "SmithKernel.T372".
 * \param [in] inscalar_SmithKernel_T373 Input scalar parameter "SmithKernel.T373".
 * \param [in] inscalar_SmithKernel_T374 Input scalar parameter "SmithKernel.T374".
 * \param [in] inscalar_SmithKernel_T375 Input scalar parameter "SmithKernel.T375".
 * \param [in] inscalar_SmithKernel_T376 Input scalar parameter "SmithKernel.T376".
 * \param [in] inscalar_SmithKernel_T377 Input scalar parameter "SmithKernel.T377".
 * \param [in] inscalar_SmithKernel_T378 Input scalar parameter "SmithKernel.T378".
 * \param [in] inscalar_SmithKernel_T379 Input scalar parameter "SmithKernel.T379".
 * \param [in] inscalar_SmithKernel_T38 Input scalar parameter "SmithKernel.T38".
 * \param [in] inscalar_SmithKernel_T380 Input scalar parameter "SmithKernel.T380".
 * \param [in] inscalar_SmithKernel_T381 Input scalar parameter "SmithKernel.T381".
 * \param [in] inscalar_SmithKernel_T382 Input scalar parameter "SmithKernel.T382".
 * \param [in] inscalar_SmithKernel_T383 Input scalar parameter "SmithKernel.T383".
 * \param [in] inscalar_SmithKernel_T384 Input scalar parameter "SmithKernel.T384".
 * \param [in] inscalar_SmithKernel_T385 Input scalar parameter "SmithKernel.T385".
 * \param [in] inscalar_SmithKernel_T386 Input scalar parameter "SmithKernel.T386".
 * \param [in] inscalar_SmithKernel_T387 Input scalar parameter "SmithKernel.T387".
 * \param [in] inscalar_SmithKernel_T388 Input scalar parameter "SmithKernel.T388".
 * \param [in] inscalar_SmithKernel_T389 Input scalar parameter "SmithKernel.T389".
 * \param [in] inscalar_SmithKernel_T39 Input scalar parameter "SmithKernel.T39".
 * \param [in] inscalar_SmithKernel_T390 Input scalar parameter "SmithKernel.T390".
 * \param [in] inscalar_SmithKernel_T391 Input scalar parameter "SmithKernel.T391".
 * \param [in] inscalar_SmithKernel_T392 Input scalar parameter "SmithKernel.T392".
 * \param [in] inscalar_SmithKernel_T393 Input scalar parameter "SmithKernel.T393".
 * \param [in] inscalar_SmithKernel_T394 Input scalar parameter "SmithKernel.T394".
 * \param [in] inscalar_SmithKernel_T395 Input scalar parameter "SmithKernel.T395".
 * \param [in] inscalar_SmithKernel_T396 Input scalar parameter "SmithKernel.T396".
 * \param [in] inscalar_SmithKernel_T397 Input scalar parameter "SmithKernel.T397".
 * \param [in] inscalar_SmithKernel_T398 Input scalar parameter "SmithKernel.T398".
 * \param [in] inscalar_SmithKernel_T399 Input scalar parameter "SmithKernel.T399".
 * \param [in] inscalar_SmithKernel_T4 Input scalar parameter "SmithKernel.T4".
 * \param [in] inscalar_SmithKernel_T40 Input scalar parameter "SmithKernel.T40".
 * \param [in] inscalar_SmithKernel_T400 Input scalar parameter "SmithKernel.T400".
 * \param [in] inscalar_SmithKernel_T401 Input scalar parameter "SmithKernel.T401".
 * \param [in] inscalar_SmithKernel_T402 Input scalar parameter "SmithKernel.T402".
 * \param [in] inscalar_SmithKernel_T403 Input scalar parameter "SmithKernel.T403".
 * \param [in] inscalar_SmithKernel_T404 Input scalar parameter "SmithKernel.T404".
 * \param [in] inscalar_SmithKernel_T405 Input scalar parameter "SmithKernel.T405".
 * \param [in] inscalar_SmithKernel_T406 Input scalar parameter "SmithKernel.T406".
 * \param [in] inscalar_SmithKernel_T407 Input scalar parameter "SmithKernel.T407".
 * \param [in] inscalar_SmithKernel_T408 Input scalar parameter "SmithKernel.T408".
 * \param [in] inscalar_SmithKernel_T409 Input scalar parameter "SmithKernel.T409".
 * \param [in] inscalar_SmithKernel_T41 Input scalar parameter "SmithKernel.T41".
 * \param [in] inscalar_SmithKernel_T410 Input scalar parameter "SmithKernel.T410".
 * \param [in] inscalar_SmithKernel_T411 Input scalar parameter "SmithKernel.T411".
 * \param [in] inscalar_SmithKernel_T412 Input scalar parameter "SmithKernel.T412".
 * \param [in] inscalar_SmithKernel_T413 Input scalar parameter "SmithKernel.T413".
 * \param [in] inscalar_SmithKernel_T414 Input scalar parameter "SmithKernel.T414".
 * \param [in] inscalar_SmithKernel_T415 Input scalar parameter "SmithKernel.T415".
 * \param [in] inscalar_SmithKernel_T416 Input scalar parameter "SmithKernel.T416".
 * \param [in] inscalar_SmithKernel_T417 Input scalar parameter "SmithKernel.T417".
 * \param [in] inscalar_SmithKernel_T418 Input scalar parameter "SmithKernel.T418".
 * \param [in] inscalar_SmithKernel_T419 Input scalar parameter "SmithKernel.T419".
 * \param [in] inscalar_SmithKernel_T42 Input scalar parameter "SmithKernel.T42".
 * \param [in] inscalar_SmithKernel_T420 Input scalar parameter "SmithKernel.T420".
 * \param [in] inscalar_SmithKernel_T421 Input scalar parameter "SmithKernel.T421".
 * \param [in] inscalar_SmithKernel_T422 Input scalar parameter "SmithKernel.T422".
 * \param [in] inscalar_SmithKernel_T423 Input scalar parameter "SmithKernel.T423".
 * \param [in] inscalar_SmithKernel_T424 Input scalar parameter "SmithKernel.T424".
 * \param [in] inscalar_SmithKernel_T425 Input scalar parameter "SmithKernel.T425".
 * \param [in] inscalar_SmithKernel_T426 Input scalar parameter "SmithKernel.T426".
 * \param [in] inscalar_SmithKernel_T427 Input scalar parameter "SmithKernel.T427".
 * \param [in] inscalar_SmithKernel_T428 Input scalar parameter "SmithKernel.T428".
 * \param [in] inscalar_SmithKernel_T429 Input scalar parameter "SmithKernel.T429".
 * \param [in] inscalar_SmithKernel_T43 Input scalar parameter "SmithKernel.T43".
 * \param [in] inscalar_SmithKernel_T430 Input scalar parameter "SmithKernel.T430".
 * \param [in] inscalar_SmithKernel_T431 Input scalar parameter "SmithKernel.T431".
 * \param [in] inscalar_SmithKernel_T432 Input scalar parameter "SmithKernel.T432".
 * \param [in] inscalar_SmithKernel_T433 Input scalar parameter "SmithKernel.T433".
 * \param [in] inscalar_SmithKernel_T434 Input scalar parameter "SmithKernel.T434".
 * \param [in] inscalar_SmithKernel_T435 Input scalar parameter "SmithKernel.T435".
 * \param [in] inscalar_SmithKernel_T436 Input scalar parameter "SmithKernel.T436".
 * \param [in] inscalar_SmithKernel_T437 Input scalar parameter "SmithKernel.T437".
 * \param [in] inscalar_SmithKernel_T438 Input scalar parameter "SmithKernel.T438".
 * \param [in] inscalar_SmithKernel_T439 Input scalar parameter "SmithKernel.T439".
 * \param [in] inscalar_SmithKernel_T44 Input scalar parameter "SmithKernel.T44".
 * \param [in] inscalar_SmithKernel_T440 Input scalar parameter "SmithKernel.T440".
 * \param [in] inscalar_SmithKernel_T441 Input scalar parameter "SmithKernel.T441".
 * \param [in] inscalar_SmithKernel_T442 Input scalar parameter "SmithKernel.T442".
 * \param [in] inscalar_SmithKernel_T443 Input scalar parameter "SmithKernel.T443".
 * \param [in] inscalar_SmithKernel_T444 Input scalar parameter "SmithKernel.T444".
 * \param [in] inscalar_SmithKernel_T445 Input scalar parameter "SmithKernel.T445".
 * \param [in] inscalar_SmithKernel_T446 Input scalar parameter "SmithKernel.T446".
 * \param [in] inscalar_SmithKernel_T447 Input scalar parameter "SmithKernel.T447".
 * \param [in] inscalar_SmithKernel_T448 Input scalar parameter "SmithKernel.T448".
 * \param [in] inscalar_SmithKernel_T449 Input scalar parameter "SmithKernel.T449".
 * \param [in] inscalar_SmithKernel_T45 Input scalar parameter "SmithKernel.T45".
 * \param [in] inscalar_SmithKernel_T450 Input scalar parameter "SmithKernel.T450".
 * \param [in] inscalar_SmithKernel_T451 Input scalar parameter "SmithKernel.T451".
 * \param [in] inscalar_SmithKernel_T452 Input scalar parameter "SmithKernel.T452".
 * \param [in] inscalar_SmithKernel_T453 Input scalar parameter "SmithKernel.T453".
 * \param [in] inscalar_SmithKernel_T454 Input scalar parameter "SmithKernel.T454".
 * \param [in] inscalar_SmithKernel_T455 Input scalar parameter "SmithKernel.T455".
 * \param [in] inscalar_SmithKernel_T456 Input scalar parameter "SmithKernel.T456".
 * \param [in] inscalar_SmithKernel_T457 Input scalar parameter "SmithKernel.T457".
 * \param [in] inscalar_SmithKernel_T458 Input scalar parameter "SmithKernel.T458".
 * \param [in] inscalar_SmithKernel_T459 Input scalar parameter "SmithKernel.T459".
 * \param [in] inscalar_SmithKernel_T46 Input scalar parameter "SmithKernel.T46".
 * \param [in] inscalar_SmithKernel_T460 Input scalar parameter "SmithKernel.T460".
 * \param [in] inscalar_SmithKernel_T461 Input scalar parameter "SmithKernel.T461".
 * \param [in] inscalar_SmithKernel_T462 Input scalar parameter "SmithKernel.T462".
 * \param [in] inscalar_SmithKernel_T463 Input scalar parameter "SmithKernel.T463".
 * \param [in] inscalar_SmithKernel_T464 Input scalar parameter "SmithKernel.T464".
 * \param [in] inscalar_SmithKernel_T465 Input scalar parameter "SmithKernel.T465".
 * \param [in] inscalar_SmithKernel_T466 Input scalar parameter "SmithKernel.T466".
 * \param [in] inscalar_SmithKernel_T467 Input scalar parameter "SmithKernel.T467".
 * \param [in] inscalar_SmithKernel_T468 Input scalar parameter "SmithKernel.T468".
 * \param [in] inscalar_SmithKernel_T469 Input scalar parameter "SmithKernel.T469".
 * \param [in] inscalar_SmithKernel_T47 Input scalar parameter "SmithKernel.T47".
 * \param [in] inscalar_SmithKernel_T470 Input scalar parameter "SmithKernel.T470".
 * \param [in] inscalar_SmithKernel_T471 Input scalar parameter "SmithKernel.T471".
 * \param [in] inscalar_SmithKernel_T472 Input scalar parameter "SmithKernel.T472".
 * \param [in] inscalar_SmithKernel_T473 Input scalar parameter "SmithKernel.T473".
 * \param [in] inscalar_SmithKernel_T474 Input scalar parameter "SmithKernel.T474".
 * \param [in] inscalar_SmithKernel_T475 Input scalar parameter "SmithKernel.T475".
 * \param [in] inscalar_SmithKernel_T476 Input scalar parameter "SmithKernel.T476".
 * \param [in] inscalar_SmithKernel_T477 Input scalar parameter "SmithKernel.T477".
 * \param [in] inscalar_SmithKernel_T478 Input scalar parameter "SmithKernel.T478".
 * \param [in] inscalar_SmithKernel_T479 Input scalar parameter "SmithKernel.T479".
 * \param [in] inscalar_SmithKernel_T48 Input scalar parameter "SmithKernel.T48".
 * \param [in] inscalar_SmithKernel_T480 Input scalar parameter "SmithKernel.T480".
 * \param [in] inscalar_SmithKernel_T481 Input scalar parameter "SmithKernel.T481".
 * \param [in] inscalar_SmithKernel_T482 Input scalar parameter "SmithKernel.T482".
 * \param [in] inscalar_SmithKernel_T483 Input scalar parameter "SmithKernel.T483".
 * \param [in] inscalar_SmithKernel_T484 Input scalar parameter "SmithKernel.T484".
 * \param [in] inscalar_SmithKernel_T485 Input scalar parameter "SmithKernel.T485".
 * \param [in] inscalar_SmithKernel_T486 Input scalar parameter "SmithKernel.T486".
 * \param [in] inscalar_SmithKernel_T487 Input scalar parameter "SmithKernel.T487".
 * \param [in] inscalar_SmithKernel_T488 Input scalar parameter "SmithKernel.T488".
 * \param [in] inscalar_SmithKernel_T489 Input scalar parameter "SmithKernel.T489".
 * \param [in] inscalar_SmithKernel_T49 Input scalar parameter "SmithKernel.T49".
 * \param [in] inscalar_SmithKernel_T490 Input scalar parameter "SmithKernel.T490".
 * \param [in] inscalar_SmithKernel_T491 Input scalar parameter "SmithKernel.T491".
 * \param [in] inscalar_SmithKernel_T492 Input scalar parameter "SmithKernel.T492".
 * \param [in] inscalar_SmithKernel_T493 Input scalar parameter "SmithKernel.T493".
 * \param [in] inscalar_SmithKernel_T494 Input scalar parameter "SmithKernel.T494".
 * \param [in] inscalar_SmithKernel_T495 Input scalar parameter "SmithKernel.T495".
 * \param [in] inscalar_SmithKernel_T496 Input scalar parameter "SmithKernel.T496".
 * \param [in] inscalar_SmithKernel_T497 Input scalar parameter "SmithKernel.T497".
 * \param [in] inscalar_SmithKernel_T498 Input scalar parameter "SmithKernel.T498".
 * \param [in] inscalar_SmithKernel_T499 Input scalar parameter "SmithKernel.T499".
 * \param [in] inscalar_SmithKernel_T5 Input scalar parameter "SmithKernel.T5".
 * \param [in] inscalar_SmithKernel_T50 Input scalar parameter "SmithKernel.T50".
 * \param [in] inscalar_SmithKernel_T500 Input scalar parameter "SmithKernel.T500".
 * \param [in] inscalar_SmithKernel_T501 Input scalar parameter "SmithKernel.T501".
 * \param [in] inscalar_SmithKernel_T502 Input scalar parameter "SmithKernel.T502".
 * \param [in] inscalar_SmithKernel_T503 Input scalar parameter "SmithKernel.T503".
 * \param [in] inscalar_SmithKernel_T504 Input scalar parameter "SmithKernel.T504".
 * \param [in] inscalar_SmithKernel_T505 Input scalar parameter "SmithKernel.T505".
 * \param [in] inscalar_SmithKernel_T506 Input scalar parameter "SmithKernel.T506".
 * \param [in] inscalar_SmithKernel_T507 Input scalar parameter "SmithKernel.T507".
 * \param [in] inscalar_SmithKernel_T508 Input scalar parameter "SmithKernel.T508".
 * \param [in] inscalar_SmithKernel_T509 Input scalar parameter "SmithKernel.T509".
 * \param [in] inscalar_SmithKernel_T51 Input scalar parameter "SmithKernel.T51".
 * \param [in] inscalar_SmithKernel_T510 Input scalar parameter "SmithKernel.T510".
 * \param [in] inscalar_SmithKernel_T511 Input scalar parameter "SmithKernel.T511".
 * \param [in] inscalar_SmithKernel_T52 Input scalar parameter "SmithKernel.T52".
 * \param [in] inscalar_SmithKernel_T53 Input scalar parameter "SmithKernel.T53".
 * \param [in] inscalar_SmithKernel_T54 Input scalar parameter "SmithKernel.T54".
 * \param [in] inscalar_SmithKernel_T55 Input scalar parameter "SmithKernel.T55".
 * \param [in] inscalar_SmithKernel_T56 Input scalar parameter "SmithKernel.T56".
 * \param [in] inscalar_SmithKernel_T57 Input scalar parameter "SmithKernel.T57".
 * \param [in] inscalar_SmithKernel_T58 Input scalar parameter "SmithKernel.T58".
 * \param [in] inscalar_SmithKernel_T59 Input scalar parameter "SmithKernel.T59".
 * \param [in] inscalar_SmithKernel_T6 Input scalar parameter "SmithKernel.T6".
 * \param [in] inscalar_SmithKernel_T60 Input scalar parameter "SmithKernel.T60".
 * \param [in] inscalar_SmithKernel_T61 Input scalar parameter "SmithKernel.T61".
 * \param [in] inscalar_SmithKernel_T62 Input scalar parameter "SmithKernel.T62".
 * \param [in] inscalar_SmithKernel_T63 Input scalar parameter "SmithKernel.T63".
 * \param [in] inscalar_SmithKernel_T64 Input scalar parameter "SmithKernel.T64".
 * \param [in] inscalar_SmithKernel_T65 Input scalar parameter "SmithKernel.T65".
 * \param [in] inscalar_SmithKernel_T66 Input scalar parameter "SmithKernel.T66".
 * \param [in] inscalar_SmithKernel_T67 Input scalar parameter "SmithKernel.T67".
 * \param [in] inscalar_SmithKernel_T68 Input scalar parameter "SmithKernel.T68".
 * \param [in] inscalar_SmithKernel_T69 Input scalar parameter "SmithKernel.T69".
 * \param [in] inscalar_SmithKernel_T7 Input scalar parameter "SmithKernel.T7".
 * \param [in] inscalar_SmithKernel_T70 Input scalar parameter "SmithKernel.T70".
 * \param [in] inscalar_SmithKernel_T71 Input scalar parameter "SmithKernel.T71".
 * \param [in] inscalar_SmithKernel_T72 Input scalar parameter "SmithKernel.T72".
 * \param [in] inscalar_SmithKernel_T73 Input scalar parameter "SmithKernel.T73".
 * \param [in] inscalar_SmithKernel_T74 Input scalar parameter "SmithKernel.T74".
 * \param [in] inscalar_SmithKernel_T75 Input scalar parameter "SmithKernel.T75".
 * \param [in] inscalar_SmithKernel_T76 Input scalar parameter "SmithKernel.T76".
 * \param [in] inscalar_SmithKernel_T77 Input scalar parameter "SmithKernel.T77".
 * \param [in] inscalar_SmithKernel_T78 Input scalar parameter "SmithKernel.T78".
 * \param [in] inscalar_SmithKernel_T79 Input scalar parameter "SmithKernel.T79".
 * \param [in] inscalar_SmithKernel_T8 Input scalar parameter "SmithKernel.T8".
 * \param [in] inscalar_SmithKernel_T80 Input scalar parameter "SmithKernel.T80".
 * \param [in] inscalar_SmithKernel_T81 Input scalar parameter "SmithKernel.T81".
 * \param [in] inscalar_SmithKernel_T82 Input scalar parameter "SmithKernel.T82".
 * \param [in] inscalar_SmithKernel_T83 Input scalar parameter "SmithKernel.T83".
 * \param [in] inscalar_SmithKernel_T84 Input scalar parameter "SmithKernel.T84".
 * \param [in] inscalar_SmithKernel_T85 Input scalar parameter "SmithKernel.T85".
 * \param [in] inscalar_SmithKernel_T86 Input scalar parameter "SmithKernel.T86".
 * \param [in] inscalar_SmithKernel_T87 Input scalar parameter "SmithKernel.T87".
 * \param [in] inscalar_SmithKernel_T88 Input scalar parameter "SmithKernel.T88".
 * \param [in] inscalar_SmithKernel_T89 Input scalar parameter "SmithKernel.T89".
 * \param [in] inscalar_SmithKernel_T9 Input scalar parameter "SmithKernel.T9".
 * \param [in] inscalar_SmithKernel_T90 Input scalar parameter "SmithKernel.T90".
 * \param [in] inscalar_SmithKernel_T91 Input scalar parameter "SmithKernel.T91".
 * \param [in] inscalar_SmithKernel_T92 Input scalar parameter "SmithKernel.T92".
 * \param [in] inscalar_SmithKernel_T93 Input scalar parameter "SmithKernel.T93".
 * \param [in] inscalar_SmithKernel_T94 Input scalar parameter "SmithKernel.T94".
 * \param [in] inscalar_SmithKernel_T95 Input scalar parameter "SmithKernel.T95".
 * \param [in] inscalar_SmithKernel_T96 Input scalar parameter "SmithKernel.T96".
 * \param [in] inscalar_SmithKernel_T97 Input scalar parameter "SmithKernel.T97".
 * \param [in] inscalar_SmithKernel_T98 Input scalar parameter "SmithKernel.T98".
 * \param [in] inscalar_SmithKernel_T99 Input scalar parameter "SmithKernel.T99".
 * \param [in] inscalar_SmithKernel_n Input scalar parameter "SmithKernel.n".
 * \param [in] inscalar_SmithKernel_open Input scalar parameter "SmithKernel.open".
 * \param [in] instream_cpu_to_lmem Stream "cpu_to_lmem".
 * \param [in] instream_size_cpu_to_lmem The size of the stream instream_cpu_to_lmem in bytes.
 * \param [out] outstream_SW Stream "SW".
 * \param [in] outstream_size_SW The size of the stream outstream_SW in bytes.
 * \param [out] outstream_lmem_to_cpu Stream "lmem_to_cpu".
 * \param [in] outstream_size_lmem_to_cpu The size of the stream outstream_lmem_to_cpu in bytes.
 * \param [out] outstream_which Stream "which".
 * \param [in] outstream_size_which The size of the stream outstream_which in bytes.
 * \param [in] lmem_address_write_lmem Linear LMem control for "write_lmem" stream: base address, in bytes.
 * \param [in] lmem_arr_size_write_lmem Linear LMem control for "write_lmem" stream: array size, in bytes.
 * \param [out] lmem_address_inS Linear LMem control for "inS" stream: base address, in bytes.
 * \param [out] lmem_arr_size_inS Linear LMem control for "inS" stream: array size, in bytes.
 * \param [out] lmem_address_inhflag Linear LMem control for "inhflag" stream: base address, in bytes.
 * \param [out] lmem_arr_size_inhflag Linear LMem control for "inhflag" stream: array size, in bytes.
 * \param [out] lmem_address_read_lmem Linear LMem control for "read_lmem" stream: base address, in bytes.
 * \param [out] lmem_arr_size_read_lmem Linear LMem control for "read_lmem" stream: array size, in bytes.
 */
void SmithWaterman(
	uint64_t ticks_SmithKernel,
	uint64_t inscalar_SmithKernel_T0,
	uint64_t inscalar_SmithKernel_T1,
	uint64_t inscalar_SmithKernel_T10,
	uint64_t inscalar_SmithKernel_T100,
	uint64_t inscalar_SmithKernel_T101,
	uint64_t inscalar_SmithKernel_T102,
	uint64_t inscalar_SmithKernel_T103,
	uint64_t inscalar_SmithKernel_T104,
	uint64_t inscalar_SmithKernel_T105,
	uint64_t inscalar_SmithKernel_T106,
	uint64_t inscalar_SmithKernel_T107,
	uint64_t inscalar_SmithKernel_T108,
	uint64_t inscalar_SmithKernel_T109,
	uint64_t inscalar_SmithKernel_T11,
	uint64_t inscalar_SmithKernel_T110,
	uint64_t inscalar_SmithKernel_T111,
	uint64_t inscalar_SmithKernel_T112,
	uint64_t inscalar_SmithKernel_T113,
	uint64_t inscalar_SmithKernel_T114,
	uint64_t inscalar_SmithKernel_T115,
	uint64_t inscalar_SmithKernel_T116,
	uint64_t inscalar_SmithKernel_T117,
	uint64_t inscalar_SmithKernel_T118,
	uint64_t inscalar_SmithKernel_T119,
	uint64_t inscalar_SmithKernel_T12,
	uint64_t inscalar_SmithKernel_T120,
	uint64_t inscalar_SmithKernel_T121,
	uint64_t inscalar_SmithKernel_T122,
	uint64_t inscalar_SmithKernel_T123,
	uint64_t inscalar_SmithKernel_T124,
	uint64_t inscalar_SmithKernel_T125,
	uint64_t inscalar_SmithKernel_T126,
	uint64_t inscalar_SmithKernel_T127,
	uint64_t inscalar_SmithKernel_T128,
	uint64_t inscalar_SmithKernel_T129,
	uint64_t inscalar_SmithKernel_T13,
	uint64_t inscalar_SmithKernel_T130,
	uint64_t inscalar_SmithKernel_T131,
	uint64_t inscalar_SmithKernel_T132,
	uint64_t inscalar_SmithKernel_T133,
	uint64_t inscalar_SmithKernel_T134,
	uint64_t inscalar_SmithKernel_T135,
	uint64_t inscalar_SmithKernel_T136,
	uint64_t inscalar_SmithKernel_T137,
	uint64_t inscalar_SmithKernel_T138,
	uint64_t inscalar_SmithKernel_T139,
	uint64_t inscalar_SmithKernel_T14,
	uint64_t inscalar_SmithKernel_T140,
	uint64_t inscalar_SmithKernel_T141,
	uint64_t inscalar_SmithKernel_T142,
	uint64_t inscalar_SmithKernel_T143,
	uint64_t inscalar_SmithKernel_T144,
	uint64_t inscalar_SmithKernel_T145,
	uint64_t inscalar_SmithKernel_T146,
	uint64_t inscalar_SmithKernel_T147,
	uint64_t inscalar_SmithKernel_T148,
	uint64_t inscalar_SmithKernel_T149,
	uint64_t inscalar_SmithKernel_T15,
	uint64_t inscalar_SmithKernel_T150,
	uint64_t inscalar_SmithKernel_T151,
	uint64_t inscalar_SmithKernel_T152,
	uint64_t inscalar_SmithKernel_T153,
	uint64_t inscalar_SmithKernel_T154,
	uint64_t inscalar_SmithKernel_T155,
	uint64_t inscalar_SmithKernel_T156,
	uint64_t inscalar_SmithKernel_T157,
	uint64_t inscalar_SmithKernel_T158,
	uint64_t inscalar_SmithKernel_T159,
	uint64_t inscalar_SmithKernel_T16,
	uint64_t inscalar_SmithKernel_T160,
	uint64_t inscalar_SmithKernel_T161,
	uint64_t inscalar_SmithKernel_T162,
	uint64_t inscalar_SmithKernel_T163,
	uint64_t inscalar_SmithKernel_T164,
	uint64_t inscalar_SmithKernel_T165,
	uint64_t inscalar_SmithKernel_T166,
	uint64_t inscalar_SmithKernel_T167,
	uint64_t inscalar_SmithKernel_T168,
	uint64_t inscalar_SmithKernel_T169,
	uint64_t inscalar_SmithKernel_T17,
	uint64_t inscalar_SmithKernel_T170,
	uint64_t inscalar_SmithKernel_T171,
	uint64_t inscalar_SmithKernel_T172,
	uint64_t inscalar_SmithKernel_T173,
	uint64_t inscalar_SmithKernel_T174,
	uint64_t inscalar_SmithKernel_T175,
	uint64_t inscalar_SmithKernel_T176,
	uint64_t inscalar_SmithKernel_T177,
	uint64_t inscalar_SmithKernel_T178,
	uint64_t inscalar_SmithKernel_T179,
	uint64_t inscalar_SmithKernel_T18,
	uint64_t inscalar_SmithKernel_T180,
	uint64_t inscalar_SmithKernel_T181,
	uint64_t inscalar_SmithKernel_T182,
	uint64_t inscalar_SmithKernel_T183,
	uint64_t inscalar_SmithKernel_T184,
	uint64_t inscalar_SmithKernel_T185,
	uint64_t inscalar_SmithKernel_T186,
	uint64_t inscalar_SmithKernel_T187,
	uint64_t inscalar_SmithKernel_T188,
	uint64_t inscalar_SmithKernel_T189,
	uint64_t inscalar_SmithKernel_T19,
	uint64_t inscalar_SmithKernel_T190,
	uint64_t inscalar_SmithKernel_T191,
	uint64_t inscalar_SmithKernel_T192,
	uint64_t inscalar_SmithKernel_T193,
	uint64_t inscalar_SmithKernel_T194,
	uint64_t inscalar_SmithKernel_T195,
	uint64_t inscalar_SmithKernel_T196,
	uint64_t inscalar_SmithKernel_T197,
	uint64_t inscalar_SmithKernel_T198,
	uint64_t inscalar_SmithKernel_T199,
	uint64_t inscalar_SmithKernel_T2,
	uint64_t inscalar_SmithKernel_T20,
	uint64_t inscalar_SmithKernel_T200,
	uint64_t inscalar_SmithKernel_T201,
	uint64_t inscalar_SmithKernel_T202,
	uint64_t inscalar_SmithKernel_T203,
	uint64_t inscalar_SmithKernel_T204,
	uint64_t inscalar_SmithKernel_T205,
	uint64_t inscalar_SmithKernel_T206,
	uint64_t inscalar_SmithKernel_T207,
	uint64_t inscalar_SmithKernel_T208,
	uint64_t inscalar_SmithKernel_T209,
	uint64_t inscalar_SmithKernel_T21,
	uint64_t inscalar_SmithKernel_T210,
	uint64_t inscalar_SmithKernel_T211,
	uint64_t inscalar_SmithKernel_T212,
	uint64_t inscalar_SmithKernel_T213,
	uint64_t inscalar_SmithKernel_T214,
	uint64_t inscalar_SmithKernel_T215,
	uint64_t inscalar_SmithKernel_T216,
	uint64_t inscalar_SmithKernel_T217,
	uint64_t inscalar_SmithKernel_T218,
	uint64_t inscalar_SmithKernel_T219,
	uint64_t inscalar_SmithKernel_T22,
	uint64_t inscalar_SmithKernel_T220,
	uint64_t inscalar_SmithKernel_T221,
	uint64_t inscalar_SmithKernel_T222,
	uint64_t inscalar_SmithKernel_T223,
	uint64_t inscalar_SmithKernel_T224,
	uint64_t inscalar_SmithKernel_T225,
	uint64_t inscalar_SmithKernel_T226,
	uint64_t inscalar_SmithKernel_T227,
	uint64_t inscalar_SmithKernel_T228,
	uint64_t inscalar_SmithKernel_T229,
	uint64_t inscalar_SmithKernel_T23,
	uint64_t inscalar_SmithKernel_T230,
	uint64_t inscalar_SmithKernel_T231,
	uint64_t inscalar_SmithKernel_T232,
	uint64_t inscalar_SmithKernel_T233,
	uint64_t inscalar_SmithKernel_T234,
	uint64_t inscalar_SmithKernel_T235,
	uint64_t inscalar_SmithKernel_T236,
	uint64_t inscalar_SmithKernel_T237,
	uint64_t inscalar_SmithKernel_T238,
	uint64_t inscalar_SmithKernel_T239,
	uint64_t inscalar_SmithKernel_T24,
	uint64_t inscalar_SmithKernel_T240,
	uint64_t inscalar_SmithKernel_T241,
	uint64_t inscalar_SmithKernel_T242,
	uint64_t inscalar_SmithKernel_T243,
	uint64_t inscalar_SmithKernel_T244,
	uint64_t inscalar_SmithKernel_T245,
	uint64_t inscalar_SmithKernel_T246,
	uint64_t inscalar_SmithKernel_T247,
	uint64_t inscalar_SmithKernel_T248,
	uint64_t inscalar_SmithKernel_T249,
	uint64_t inscalar_SmithKernel_T25,
	uint64_t inscalar_SmithKernel_T250,
	uint64_t inscalar_SmithKernel_T251,
	uint64_t inscalar_SmithKernel_T252,
	uint64_t inscalar_SmithKernel_T253,
	uint64_t inscalar_SmithKernel_T254,
	uint64_t inscalar_SmithKernel_T255,
	uint64_t inscalar_SmithKernel_T256,
	uint64_t inscalar_SmithKernel_T257,
	uint64_t inscalar_SmithKernel_T258,
	uint64_t inscalar_SmithKernel_T259,
	uint64_t inscalar_SmithKernel_T26,
	uint64_t inscalar_SmithKernel_T260,
	uint64_t inscalar_SmithKernel_T261,
	uint64_t inscalar_SmithKernel_T262,
	uint64_t inscalar_SmithKernel_T263,
	uint64_t inscalar_SmithKernel_T264,
	uint64_t inscalar_SmithKernel_T265,
	uint64_t inscalar_SmithKernel_T266,
	uint64_t inscalar_SmithKernel_T267,
	uint64_t inscalar_SmithKernel_T268,
	uint64_t inscalar_SmithKernel_T269,
	uint64_t inscalar_SmithKernel_T27,
	uint64_t inscalar_SmithKernel_T270,
	uint64_t inscalar_SmithKernel_T271,
	uint64_t inscalar_SmithKernel_T272,
	uint64_t inscalar_SmithKernel_T273,
	uint64_t inscalar_SmithKernel_T274,
	uint64_t inscalar_SmithKernel_T275,
	uint64_t inscalar_SmithKernel_T276,
	uint64_t inscalar_SmithKernel_T277,
	uint64_t inscalar_SmithKernel_T278,
	uint64_t inscalar_SmithKernel_T279,
	uint64_t inscalar_SmithKernel_T28,
	uint64_t inscalar_SmithKernel_T280,
	uint64_t inscalar_SmithKernel_T281,
	uint64_t inscalar_SmithKernel_T282,
	uint64_t inscalar_SmithKernel_T283,
	uint64_t inscalar_SmithKernel_T284,
	uint64_t inscalar_SmithKernel_T285,
	uint64_t inscalar_SmithKernel_T286,
	uint64_t inscalar_SmithKernel_T287,
	uint64_t inscalar_SmithKernel_T288,
	uint64_t inscalar_SmithKernel_T289,
	uint64_t inscalar_SmithKernel_T29,
	uint64_t inscalar_SmithKernel_T290,
	uint64_t inscalar_SmithKernel_T291,
	uint64_t inscalar_SmithKernel_T292,
	uint64_t inscalar_SmithKernel_T293,
	uint64_t inscalar_SmithKernel_T294,
	uint64_t inscalar_SmithKernel_T295,
	uint64_t inscalar_SmithKernel_T296,
	uint64_t inscalar_SmithKernel_T297,
	uint64_t inscalar_SmithKernel_T298,
	uint64_t inscalar_SmithKernel_T299,
	uint64_t inscalar_SmithKernel_T3,
	uint64_t inscalar_SmithKernel_T30,
	uint64_t inscalar_SmithKernel_T300,
	uint64_t inscalar_SmithKernel_T301,
	uint64_t inscalar_SmithKernel_T302,
	uint64_t inscalar_SmithKernel_T303,
	uint64_t inscalar_SmithKernel_T304,
	uint64_t inscalar_SmithKernel_T305,
	uint64_t inscalar_SmithKernel_T306,
	uint64_t inscalar_SmithKernel_T307,
	uint64_t inscalar_SmithKernel_T308,
	uint64_t inscalar_SmithKernel_T309,
	uint64_t inscalar_SmithKernel_T31,
	uint64_t inscalar_SmithKernel_T310,
	uint64_t inscalar_SmithKernel_T311,
	uint64_t inscalar_SmithKernel_T312,
	uint64_t inscalar_SmithKernel_T313,
	uint64_t inscalar_SmithKernel_T314,
	uint64_t inscalar_SmithKernel_T315,
	uint64_t inscalar_SmithKernel_T316,
	uint64_t inscalar_SmithKernel_T317,
	uint64_t inscalar_SmithKernel_T318,
	uint64_t inscalar_SmithKernel_T319,
	uint64_t inscalar_SmithKernel_T32,
	uint64_t inscalar_SmithKernel_T320,
	uint64_t inscalar_SmithKernel_T321,
	uint64_t inscalar_SmithKernel_T322,
	uint64_t inscalar_SmithKernel_T323,
	uint64_t inscalar_SmithKernel_T324,
	uint64_t inscalar_SmithKernel_T325,
	uint64_t inscalar_SmithKernel_T326,
	uint64_t inscalar_SmithKernel_T327,
	uint64_t inscalar_SmithKernel_T328,
	uint64_t inscalar_SmithKernel_T329,
	uint64_t inscalar_SmithKernel_T33,
	uint64_t inscalar_SmithKernel_T330,
	uint64_t inscalar_SmithKernel_T331,
	uint64_t inscalar_SmithKernel_T332,
	uint64_t inscalar_SmithKernel_T333,
	uint64_t inscalar_SmithKernel_T334,
	uint64_t inscalar_SmithKernel_T335,
	uint64_t inscalar_SmithKernel_T336,
	uint64_t inscalar_SmithKernel_T337,
	uint64_t inscalar_SmithKernel_T338,
	uint64_t inscalar_SmithKernel_T339,
	uint64_t inscalar_SmithKernel_T34,
	uint64_t inscalar_SmithKernel_T340,
	uint64_t inscalar_SmithKernel_T341,
	uint64_t inscalar_SmithKernel_T342,
	uint64_t inscalar_SmithKernel_T343,
	uint64_t inscalar_SmithKernel_T344,
	uint64_t inscalar_SmithKernel_T345,
	uint64_t inscalar_SmithKernel_T346,
	uint64_t inscalar_SmithKernel_T347,
	uint64_t inscalar_SmithKernel_T348,
	uint64_t inscalar_SmithKernel_T349,
	uint64_t inscalar_SmithKernel_T35,
	uint64_t inscalar_SmithKernel_T350,
	uint64_t inscalar_SmithKernel_T351,
	uint64_t inscalar_SmithKernel_T352,
	uint64_t inscalar_SmithKernel_T353,
	uint64_t inscalar_SmithKernel_T354,
	uint64_t inscalar_SmithKernel_T355,
	uint64_t inscalar_SmithKernel_T356,
	uint64_t inscalar_SmithKernel_T357,
	uint64_t inscalar_SmithKernel_T358,
	uint64_t inscalar_SmithKernel_T359,
	uint64_t inscalar_SmithKernel_T36,
	uint64_t inscalar_SmithKernel_T360,
	uint64_t inscalar_SmithKernel_T361,
	uint64_t inscalar_SmithKernel_T362,
	uint64_t inscalar_SmithKernel_T363,
	uint64_t inscalar_SmithKernel_T364,
	uint64_t inscalar_SmithKernel_T365,
	uint64_t inscalar_SmithKernel_T366,
	uint64_t inscalar_SmithKernel_T367,
	uint64_t inscalar_SmithKernel_T368,
	uint64_t inscalar_SmithKernel_T369,
	uint64_t inscalar_SmithKernel_T37,
	uint64_t inscalar_SmithKernel_T370,
	uint64_t inscalar_SmithKernel_T371,
	uint64_t inscalar_SmithKernel_T372,
	uint64_t inscalar_SmithKernel_T373,
	uint64_t inscalar_SmithKernel_T374,
	uint64_t inscalar_SmithKernel_T375,
	uint64_t inscalar_SmithKernel_T376,
	uint64_t inscalar_SmithKernel_T377,
	uint64_t inscalar_SmithKernel_T378,
	uint64_t inscalar_SmithKernel_T379,
	uint64_t inscalar_SmithKernel_T38,
	uint64_t inscalar_SmithKernel_T380,
	uint64_t inscalar_SmithKernel_T381,
	uint64_t inscalar_SmithKernel_T382,
	uint64_t inscalar_SmithKernel_T383,
	uint64_t inscalar_SmithKernel_T384,
	uint64_t inscalar_SmithKernel_T385,
	uint64_t inscalar_SmithKernel_T386,
	uint64_t inscalar_SmithKernel_T387,
	uint64_t inscalar_SmithKernel_T388,
	uint64_t inscalar_SmithKernel_T389,
	uint64_t inscalar_SmithKernel_T39,
	uint64_t inscalar_SmithKernel_T390,
	uint64_t inscalar_SmithKernel_T391,
	uint64_t inscalar_SmithKernel_T392,
	uint64_t inscalar_SmithKernel_T393,
	uint64_t inscalar_SmithKernel_T394,
	uint64_t inscalar_SmithKernel_T395,
	uint64_t inscalar_SmithKernel_T396,
	uint64_t inscalar_SmithKernel_T397,
	uint64_t inscalar_SmithKernel_T398,
	uint64_t inscalar_SmithKernel_T399,
	uint64_t inscalar_SmithKernel_T4,
	uint64_t inscalar_SmithKernel_T40,
	uint64_t inscalar_SmithKernel_T400,
	uint64_t inscalar_SmithKernel_T401,
	uint64_t inscalar_SmithKernel_T402,
	uint64_t inscalar_SmithKernel_T403,
	uint64_t inscalar_SmithKernel_T404,
	uint64_t inscalar_SmithKernel_T405,
	uint64_t inscalar_SmithKernel_T406,
	uint64_t inscalar_SmithKernel_T407,
	uint64_t inscalar_SmithKernel_T408,
	uint64_t inscalar_SmithKernel_T409,
	uint64_t inscalar_SmithKernel_T41,
	uint64_t inscalar_SmithKernel_T410,
	uint64_t inscalar_SmithKernel_T411,
	uint64_t inscalar_SmithKernel_T412,
	uint64_t inscalar_SmithKernel_T413,
	uint64_t inscalar_SmithKernel_T414,
	uint64_t inscalar_SmithKernel_T415,
	uint64_t inscalar_SmithKernel_T416,
	uint64_t inscalar_SmithKernel_T417,
	uint64_t inscalar_SmithKernel_T418,
	uint64_t inscalar_SmithKernel_T419,
	uint64_t inscalar_SmithKernel_T42,
	uint64_t inscalar_SmithKernel_T420,
	uint64_t inscalar_SmithKernel_T421,
	uint64_t inscalar_SmithKernel_T422,
	uint64_t inscalar_SmithKernel_T423,
	uint64_t inscalar_SmithKernel_T424,
	uint64_t inscalar_SmithKernel_T425,
	uint64_t inscalar_SmithKernel_T426,
	uint64_t inscalar_SmithKernel_T427,
	uint64_t inscalar_SmithKernel_T428,
	uint64_t inscalar_SmithKernel_T429,
	uint64_t inscalar_SmithKernel_T43,
	uint64_t inscalar_SmithKernel_T430,
	uint64_t inscalar_SmithKernel_T431,
	uint64_t inscalar_SmithKernel_T432,
	uint64_t inscalar_SmithKernel_T433,
	uint64_t inscalar_SmithKernel_T434,
	uint64_t inscalar_SmithKernel_T435,
	uint64_t inscalar_SmithKernel_T436,
	uint64_t inscalar_SmithKernel_T437,
	uint64_t inscalar_SmithKernel_T438,
	uint64_t inscalar_SmithKernel_T439,
	uint64_t inscalar_SmithKernel_T44,
	uint64_t inscalar_SmithKernel_T440,
	uint64_t inscalar_SmithKernel_T441,
	uint64_t inscalar_SmithKernel_T442,
	uint64_t inscalar_SmithKernel_T443,
	uint64_t inscalar_SmithKernel_T444,
	uint64_t inscalar_SmithKernel_T445,
	uint64_t inscalar_SmithKernel_T446,
	uint64_t inscalar_SmithKernel_T447,
	uint64_t inscalar_SmithKernel_T448,
	uint64_t inscalar_SmithKernel_T449,
	uint64_t inscalar_SmithKernel_T45,
	uint64_t inscalar_SmithKernel_T450,
	uint64_t inscalar_SmithKernel_T451,
	uint64_t inscalar_SmithKernel_T452,
	uint64_t inscalar_SmithKernel_T453,
	uint64_t inscalar_SmithKernel_T454,
	uint64_t inscalar_SmithKernel_T455,
	uint64_t inscalar_SmithKernel_T456,
	uint64_t inscalar_SmithKernel_T457,
	uint64_t inscalar_SmithKernel_T458,
	uint64_t inscalar_SmithKernel_T459,
	uint64_t inscalar_SmithKernel_T46,
	uint64_t inscalar_SmithKernel_T460,
	uint64_t inscalar_SmithKernel_T461,
	uint64_t inscalar_SmithKernel_T462,
	uint64_t inscalar_SmithKernel_T463,
	uint64_t inscalar_SmithKernel_T464,
	uint64_t inscalar_SmithKernel_T465,
	uint64_t inscalar_SmithKernel_T466,
	uint64_t inscalar_SmithKernel_T467,
	uint64_t inscalar_SmithKernel_T468,
	uint64_t inscalar_SmithKernel_T469,
	uint64_t inscalar_SmithKernel_T47,
	uint64_t inscalar_SmithKernel_T470,
	uint64_t inscalar_SmithKernel_T471,
	uint64_t inscalar_SmithKernel_T472,
	uint64_t inscalar_SmithKernel_T473,
	uint64_t inscalar_SmithKernel_T474,
	uint64_t inscalar_SmithKernel_T475,
	uint64_t inscalar_SmithKernel_T476,
	uint64_t inscalar_SmithKernel_T477,
	uint64_t inscalar_SmithKernel_T478,
	uint64_t inscalar_SmithKernel_T479,
	uint64_t inscalar_SmithKernel_T48,
	uint64_t inscalar_SmithKernel_T480,
	uint64_t inscalar_SmithKernel_T481,
	uint64_t inscalar_SmithKernel_T482,
	uint64_t inscalar_SmithKernel_T483,
	uint64_t inscalar_SmithKernel_T484,
	uint64_t inscalar_SmithKernel_T485,
	uint64_t inscalar_SmithKernel_T486,
	uint64_t inscalar_SmithKernel_T487,
	uint64_t inscalar_SmithKernel_T488,
	uint64_t inscalar_SmithKernel_T489,
	uint64_t inscalar_SmithKernel_T49,
	uint64_t inscalar_SmithKernel_T490,
	uint64_t inscalar_SmithKernel_T491,
	uint64_t inscalar_SmithKernel_T492,
	uint64_t inscalar_SmithKernel_T493,
	uint64_t inscalar_SmithKernel_T494,
	uint64_t inscalar_SmithKernel_T495,
	uint64_t inscalar_SmithKernel_T496,
	uint64_t inscalar_SmithKernel_T497,
	uint64_t inscalar_SmithKernel_T498,
	uint64_t inscalar_SmithKernel_T499,
	uint64_t inscalar_SmithKernel_T5,
	uint64_t inscalar_SmithKernel_T50,
	uint64_t inscalar_SmithKernel_T500,
	uint64_t inscalar_SmithKernel_T501,
	uint64_t inscalar_SmithKernel_T502,
	uint64_t inscalar_SmithKernel_T503,
	uint64_t inscalar_SmithKernel_T504,
	uint64_t inscalar_SmithKernel_T505,
	uint64_t inscalar_SmithKernel_T506,
	uint64_t inscalar_SmithKernel_T507,
	uint64_t inscalar_SmithKernel_T508,
	uint64_t inscalar_SmithKernel_T509,
	uint64_t inscalar_SmithKernel_T51,
	uint64_t inscalar_SmithKernel_T510,
	uint64_t inscalar_SmithKernel_T511,
	uint64_t inscalar_SmithKernel_T52,
	uint64_t inscalar_SmithKernel_T53,
	uint64_t inscalar_SmithKernel_T54,
	uint64_t inscalar_SmithKernel_T55,
	uint64_t inscalar_SmithKernel_T56,
	uint64_t inscalar_SmithKernel_T57,
	uint64_t inscalar_SmithKernel_T58,
	uint64_t inscalar_SmithKernel_T59,
	uint64_t inscalar_SmithKernel_T6,
	uint64_t inscalar_SmithKernel_T60,
	uint64_t inscalar_SmithKernel_T61,
	uint64_t inscalar_SmithKernel_T62,
	uint64_t inscalar_SmithKernel_T63,
	uint64_t inscalar_SmithKernel_T64,
	uint64_t inscalar_SmithKernel_T65,
	uint64_t inscalar_SmithKernel_T66,
	uint64_t inscalar_SmithKernel_T67,
	uint64_t inscalar_SmithKernel_T68,
	uint64_t inscalar_SmithKernel_T69,
	uint64_t inscalar_SmithKernel_T7,
	uint64_t inscalar_SmithKernel_T70,
	uint64_t inscalar_SmithKernel_T71,
	uint64_t inscalar_SmithKernel_T72,
	uint64_t inscalar_SmithKernel_T73,
	uint64_t inscalar_SmithKernel_T74,
	uint64_t inscalar_SmithKernel_T75,
	uint64_t inscalar_SmithKernel_T76,
	uint64_t inscalar_SmithKernel_T77,
	uint64_t inscalar_SmithKernel_T78,
	uint64_t inscalar_SmithKernel_T79,
	uint64_t inscalar_SmithKernel_T8,
	uint64_t inscalar_SmithKernel_T80,
	uint64_t inscalar_SmithKernel_T81,
	uint64_t inscalar_SmithKernel_T82,
	uint64_t inscalar_SmithKernel_T83,
	uint64_t inscalar_SmithKernel_T84,
	uint64_t inscalar_SmithKernel_T85,
	uint64_t inscalar_SmithKernel_T86,
	uint64_t inscalar_SmithKernel_T87,
	uint64_t inscalar_SmithKernel_T88,
	uint64_t inscalar_SmithKernel_T89,
	uint64_t inscalar_SmithKernel_T9,
	uint64_t inscalar_SmithKernel_T90,
	uint64_t inscalar_SmithKernel_T91,
	uint64_t inscalar_SmithKernel_T92,
	uint64_t inscalar_SmithKernel_T93,
	uint64_t inscalar_SmithKernel_T94,
	uint64_t inscalar_SmithKernel_T95,
	uint64_t inscalar_SmithKernel_T96,
	uint64_t inscalar_SmithKernel_T97,
	uint64_t inscalar_SmithKernel_T98,
	uint64_t inscalar_SmithKernel_T99,
	uint64_t inscalar_SmithKernel_n,
	uint64_t inscalar_SmithKernel_open,
	const void *instream_cpu_to_lmem,
	size_t instream_size_cpu_to_lmem,
	void *outstream_SW,
	size_t outstream_size_SW,
	void *outstream_lmem_to_cpu,
	size_t outstream_size_lmem_to_cpu,
	void *outstream_which,
	size_t outstream_size_which,
	size_t lmem_address_write_lmem,
	size_t lmem_arr_size_write_lmem,
	size_t lmem_address_inS,
	size_t lmem_arr_size_inS,
	size_t lmem_address_inhflag,
	size_t lmem_arr_size_inhflag,
	size_t lmem_address_read_lmem,
	size_t lmem_arr_size_read_lmem);

/**
 * \brief Basic static non-blocking function for the interface 'default'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] ticks_SmithKernel The number of ticks for which kernel "SmithKernel" will run.
 * \param [in] inscalar_SmithKernel_T0 Input scalar parameter "SmithKernel.T0".
 * \param [in] inscalar_SmithKernel_T1 Input scalar parameter "SmithKernel.T1".
 * \param [in] inscalar_SmithKernel_T10 Input scalar parameter "SmithKernel.T10".
 * \param [in] inscalar_SmithKernel_T100 Input scalar parameter "SmithKernel.T100".
 * \param [in] inscalar_SmithKernel_T101 Input scalar parameter "SmithKernel.T101".
 * \param [in] inscalar_SmithKernel_T102 Input scalar parameter "SmithKernel.T102".
 * \param [in] inscalar_SmithKernel_T103 Input scalar parameter "SmithKernel.T103".
 * \param [in] inscalar_SmithKernel_T104 Input scalar parameter "SmithKernel.T104".
 * \param [in] inscalar_SmithKernel_T105 Input scalar parameter "SmithKernel.T105".
 * \param [in] inscalar_SmithKernel_T106 Input scalar parameter "SmithKernel.T106".
 * \param [in] inscalar_SmithKernel_T107 Input scalar parameter "SmithKernel.T107".
 * \param [in] inscalar_SmithKernel_T108 Input scalar parameter "SmithKernel.T108".
 * \param [in] inscalar_SmithKernel_T109 Input scalar parameter "SmithKernel.T109".
 * \param [in] inscalar_SmithKernel_T11 Input scalar parameter "SmithKernel.T11".
 * \param [in] inscalar_SmithKernel_T110 Input scalar parameter "SmithKernel.T110".
 * \param [in] inscalar_SmithKernel_T111 Input scalar parameter "SmithKernel.T111".
 * \param [in] inscalar_SmithKernel_T112 Input scalar parameter "SmithKernel.T112".
 * \param [in] inscalar_SmithKernel_T113 Input scalar parameter "SmithKernel.T113".
 * \param [in] inscalar_SmithKernel_T114 Input scalar parameter "SmithKernel.T114".
 * \param [in] inscalar_SmithKernel_T115 Input scalar parameter "SmithKernel.T115".
 * \param [in] inscalar_SmithKernel_T116 Input scalar parameter "SmithKernel.T116".
 * \param [in] inscalar_SmithKernel_T117 Input scalar parameter "SmithKernel.T117".
 * \param [in] inscalar_SmithKernel_T118 Input scalar parameter "SmithKernel.T118".
 * \param [in] inscalar_SmithKernel_T119 Input scalar parameter "SmithKernel.T119".
 * \param [in] inscalar_SmithKernel_T12 Input scalar parameter "SmithKernel.T12".
 * \param [in] inscalar_SmithKernel_T120 Input scalar parameter "SmithKernel.T120".
 * \param [in] inscalar_SmithKernel_T121 Input scalar parameter "SmithKernel.T121".
 * \param [in] inscalar_SmithKernel_T122 Input scalar parameter "SmithKernel.T122".
 * \param [in] inscalar_SmithKernel_T123 Input scalar parameter "SmithKernel.T123".
 * \param [in] inscalar_SmithKernel_T124 Input scalar parameter "SmithKernel.T124".
 * \param [in] inscalar_SmithKernel_T125 Input scalar parameter "SmithKernel.T125".
 * \param [in] inscalar_SmithKernel_T126 Input scalar parameter "SmithKernel.T126".
 * \param [in] inscalar_SmithKernel_T127 Input scalar parameter "SmithKernel.T127".
 * \param [in] inscalar_SmithKernel_T128 Input scalar parameter "SmithKernel.T128".
 * \param [in] inscalar_SmithKernel_T129 Input scalar parameter "SmithKernel.T129".
 * \param [in] inscalar_SmithKernel_T13 Input scalar parameter "SmithKernel.T13".
 * \param [in] inscalar_SmithKernel_T130 Input scalar parameter "SmithKernel.T130".
 * \param [in] inscalar_SmithKernel_T131 Input scalar parameter "SmithKernel.T131".
 * \param [in] inscalar_SmithKernel_T132 Input scalar parameter "SmithKernel.T132".
 * \param [in] inscalar_SmithKernel_T133 Input scalar parameter "SmithKernel.T133".
 * \param [in] inscalar_SmithKernel_T134 Input scalar parameter "SmithKernel.T134".
 * \param [in] inscalar_SmithKernel_T135 Input scalar parameter "SmithKernel.T135".
 * \param [in] inscalar_SmithKernel_T136 Input scalar parameter "SmithKernel.T136".
 * \param [in] inscalar_SmithKernel_T137 Input scalar parameter "SmithKernel.T137".
 * \param [in] inscalar_SmithKernel_T138 Input scalar parameter "SmithKernel.T138".
 * \param [in] inscalar_SmithKernel_T139 Input scalar parameter "SmithKernel.T139".
 * \param [in] inscalar_SmithKernel_T14 Input scalar parameter "SmithKernel.T14".
 * \param [in] inscalar_SmithKernel_T140 Input scalar parameter "SmithKernel.T140".
 * \param [in] inscalar_SmithKernel_T141 Input scalar parameter "SmithKernel.T141".
 * \param [in] inscalar_SmithKernel_T142 Input scalar parameter "SmithKernel.T142".
 * \param [in] inscalar_SmithKernel_T143 Input scalar parameter "SmithKernel.T143".
 * \param [in] inscalar_SmithKernel_T144 Input scalar parameter "SmithKernel.T144".
 * \param [in] inscalar_SmithKernel_T145 Input scalar parameter "SmithKernel.T145".
 * \param [in] inscalar_SmithKernel_T146 Input scalar parameter "SmithKernel.T146".
 * \param [in] inscalar_SmithKernel_T147 Input scalar parameter "SmithKernel.T147".
 * \param [in] inscalar_SmithKernel_T148 Input scalar parameter "SmithKernel.T148".
 * \param [in] inscalar_SmithKernel_T149 Input scalar parameter "SmithKernel.T149".
 * \param [in] inscalar_SmithKernel_T15 Input scalar parameter "SmithKernel.T15".
 * \param [in] inscalar_SmithKernel_T150 Input scalar parameter "SmithKernel.T150".
 * \param [in] inscalar_SmithKernel_T151 Input scalar parameter "SmithKernel.T151".
 * \param [in] inscalar_SmithKernel_T152 Input scalar parameter "SmithKernel.T152".
 * \param [in] inscalar_SmithKernel_T153 Input scalar parameter "SmithKernel.T153".
 * \param [in] inscalar_SmithKernel_T154 Input scalar parameter "SmithKernel.T154".
 * \param [in] inscalar_SmithKernel_T155 Input scalar parameter "SmithKernel.T155".
 * \param [in] inscalar_SmithKernel_T156 Input scalar parameter "SmithKernel.T156".
 * \param [in] inscalar_SmithKernel_T157 Input scalar parameter "SmithKernel.T157".
 * \param [in] inscalar_SmithKernel_T158 Input scalar parameter "SmithKernel.T158".
 * \param [in] inscalar_SmithKernel_T159 Input scalar parameter "SmithKernel.T159".
 * \param [in] inscalar_SmithKernel_T16 Input scalar parameter "SmithKernel.T16".
 * \param [in] inscalar_SmithKernel_T160 Input scalar parameter "SmithKernel.T160".
 * \param [in] inscalar_SmithKernel_T161 Input scalar parameter "SmithKernel.T161".
 * \param [in] inscalar_SmithKernel_T162 Input scalar parameter "SmithKernel.T162".
 * \param [in] inscalar_SmithKernel_T163 Input scalar parameter "SmithKernel.T163".
 * \param [in] inscalar_SmithKernel_T164 Input scalar parameter "SmithKernel.T164".
 * \param [in] inscalar_SmithKernel_T165 Input scalar parameter "SmithKernel.T165".
 * \param [in] inscalar_SmithKernel_T166 Input scalar parameter "SmithKernel.T166".
 * \param [in] inscalar_SmithKernel_T167 Input scalar parameter "SmithKernel.T167".
 * \param [in] inscalar_SmithKernel_T168 Input scalar parameter "SmithKernel.T168".
 * \param [in] inscalar_SmithKernel_T169 Input scalar parameter "SmithKernel.T169".
 * \param [in] inscalar_SmithKernel_T17 Input scalar parameter "SmithKernel.T17".
 * \param [in] inscalar_SmithKernel_T170 Input scalar parameter "SmithKernel.T170".
 * \param [in] inscalar_SmithKernel_T171 Input scalar parameter "SmithKernel.T171".
 * \param [in] inscalar_SmithKernel_T172 Input scalar parameter "SmithKernel.T172".
 * \param [in] inscalar_SmithKernel_T173 Input scalar parameter "SmithKernel.T173".
 * \param [in] inscalar_SmithKernel_T174 Input scalar parameter "SmithKernel.T174".
 * \param [in] inscalar_SmithKernel_T175 Input scalar parameter "SmithKernel.T175".
 * \param [in] inscalar_SmithKernel_T176 Input scalar parameter "SmithKernel.T176".
 * \param [in] inscalar_SmithKernel_T177 Input scalar parameter "SmithKernel.T177".
 * \param [in] inscalar_SmithKernel_T178 Input scalar parameter "SmithKernel.T178".
 * \param [in] inscalar_SmithKernel_T179 Input scalar parameter "SmithKernel.T179".
 * \param [in] inscalar_SmithKernel_T18 Input scalar parameter "SmithKernel.T18".
 * \param [in] inscalar_SmithKernel_T180 Input scalar parameter "SmithKernel.T180".
 * \param [in] inscalar_SmithKernel_T181 Input scalar parameter "SmithKernel.T181".
 * \param [in] inscalar_SmithKernel_T182 Input scalar parameter "SmithKernel.T182".
 * \param [in] inscalar_SmithKernel_T183 Input scalar parameter "SmithKernel.T183".
 * \param [in] inscalar_SmithKernel_T184 Input scalar parameter "SmithKernel.T184".
 * \param [in] inscalar_SmithKernel_T185 Input scalar parameter "SmithKernel.T185".
 * \param [in] inscalar_SmithKernel_T186 Input scalar parameter "SmithKernel.T186".
 * \param [in] inscalar_SmithKernel_T187 Input scalar parameter "SmithKernel.T187".
 * \param [in] inscalar_SmithKernel_T188 Input scalar parameter "SmithKernel.T188".
 * \param [in] inscalar_SmithKernel_T189 Input scalar parameter "SmithKernel.T189".
 * \param [in] inscalar_SmithKernel_T19 Input scalar parameter "SmithKernel.T19".
 * \param [in] inscalar_SmithKernel_T190 Input scalar parameter "SmithKernel.T190".
 * \param [in] inscalar_SmithKernel_T191 Input scalar parameter "SmithKernel.T191".
 * \param [in] inscalar_SmithKernel_T192 Input scalar parameter "SmithKernel.T192".
 * \param [in] inscalar_SmithKernel_T193 Input scalar parameter "SmithKernel.T193".
 * \param [in] inscalar_SmithKernel_T194 Input scalar parameter "SmithKernel.T194".
 * \param [in] inscalar_SmithKernel_T195 Input scalar parameter "SmithKernel.T195".
 * \param [in] inscalar_SmithKernel_T196 Input scalar parameter "SmithKernel.T196".
 * \param [in] inscalar_SmithKernel_T197 Input scalar parameter "SmithKernel.T197".
 * \param [in] inscalar_SmithKernel_T198 Input scalar parameter "SmithKernel.T198".
 * \param [in] inscalar_SmithKernel_T199 Input scalar parameter "SmithKernel.T199".
 * \param [in] inscalar_SmithKernel_T2 Input scalar parameter "SmithKernel.T2".
 * \param [in] inscalar_SmithKernel_T20 Input scalar parameter "SmithKernel.T20".
 * \param [in] inscalar_SmithKernel_T200 Input scalar parameter "SmithKernel.T200".
 * \param [in] inscalar_SmithKernel_T201 Input scalar parameter "SmithKernel.T201".
 * \param [in] inscalar_SmithKernel_T202 Input scalar parameter "SmithKernel.T202".
 * \param [in] inscalar_SmithKernel_T203 Input scalar parameter "SmithKernel.T203".
 * \param [in] inscalar_SmithKernel_T204 Input scalar parameter "SmithKernel.T204".
 * \param [in] inscalar_SmithKernel_T205 Input scalar parameter "SmithKernel.T205".
 * \param [in] inscalar_SmithKernel_T206 Input scalar parameter "SmithKernel.T206".
 * \param [in] inscalar_SmithKernel_T207 Input scalar parameter "SmithKernel.T207".
 * \param [in] inscalar_SmithKernel_T208 Input scalar parameter "SmithKernel.T208".
 * \param [in] inscalar_SmithKernel_T209 Input scalar parameter "SmithKernel.T209".
 * \param [in] inscalar_SmithKernel_T21 Input scalar parameter "SmithKernel.T21".
 * \param [in] inscalar_SmithKernel_T210 Input scalar parameter "SmithKernel.T210".
 * \param [in] inscalar_SmithKernel_T211 Input scalar parameter "SmithKernel.T211".
 * \param [in] inscalar_SmithKernel_T212 Input scalar parameter "SmithKernel.T212".
 * \param [in] inscalar_SmithKernel_T213 Input scalar parameter "SmithKernel.T213".
 * \param [in] inscalar_SmithKernel_T214 Input scalar parameter "SmithKernel.T214".
 * \param [in] inscalar_SmithKernel_T215 Input scalar parameter "SmithKernel.T215".
 * \param [in] inscalar_SmithKernel_T216 Input scalar parameter "SmithKernel.T216".
 * \param [in] inscalar_SmithKernel_T217 Input scalar parameter "SmithKernel.T217".
 * \param [in] inscalar_SmithKernel_T218 Input scalar parameter "SmithKernel.T218".
 * \param [in] inscalar_SmithKernel_T219 Input scalar parameter "SmithKernel.T219".
 * \param [in] inscalar_SmithKernel_T22 Input scalar parameter "SmithKernel.T22".
 * \param [in] inscalar_SmithKernel_T220 Input scalar parameter "SmithKernel.T220".
 * \param [in] inscalar_SmithKernel_T221 Input scalar parameter "SmithKernel.T221".
 * \param [in] inscalar_SmithKernel_T222 Input scalar parameter "SmithKernel.T222".
 * \param [in] inscalar_SmithKernel_T223 Input scalar parameter "SmithKernel.T223".
 * \param [in] inscalar_SmithKernel_T224 Input scalar parameter "SmithKernel.T224".
 * \param [in] inscalar_SmithKernel_T225 Input scalar parameter "SmithKernel.T225".
 * \param [in] inscalar_SmithKernel_T226 Input scalar parameter "SmithKernel.T226".
 * \param [in] inscalar_SmithKernel_T227 Input scalar parameter "SmithKernel.T227".
 * \param [in] inscalar_SmithKernel_T228 Input scalar parameter "SmithKernel.T228".
 * \param [in] inscalar_SmithKernel_T229 Input scalar parameter "SmithKernel.T229".
 * \param [in] inscalar_SmithKernel_T23 Input scalar parameter "SmithKernel.T23".
 * \param [in] inscalar_SmithKernel_T230 Input scalar parameter "SmithKernel.T230".
 * \param [in] inscalar_SmithKernel_T231 Input scalar parameter "SmithKernel.T231".
 * \param [in] inscalar_SmithKernel_T232 Input scalar parameter "SmithKernel.T232".
 * \param [in] inscalar_SmithKernel_T233 Input scalar parameter "SmithKernel.T233".
 * \param [in] inscalar_SmithKernel_T234 Input scalar parameter "SmithKernel.T234".
 * \param [in] inscalar_SmithKernel_T235 Input scalar parameter "SmithKernel.T235".
 * \param [in] inscalar_SmithKernel_T236 Input scalar parameter "SmithKernel.T236".
 * \param [in] inscalar_SmithKernel_T237 Input scalar parameter "SmithKernel.T237".
 * \param [in] inscalar_SmithKernel_T238 Input scalar parameter "SmithKernel.T238".
 * \param [in] inscalar_SmithKernel_T239 Input scalar parameter "SmithKernel.T239".
 * \param [in] inscalar_SmithKernel_T24 Input scalar parameter "SmithKernel.T24".
 * \param [in] inscalar_SmithKernel_T240 Input scalar parameter "SmithKernel.T240".
 * \param [in] inscalar_SmithKernel_T241 Input scalar parameter "SmithKernel.T241".
 * \param [in] inscalar_SmithKernel_T242 Input scalar parameter "SmithKernel.T242".
 * \param [in] inscalar_SmithKernel_T243 Input scalar parameter "SmithKernel.T243".
 * \param [in] inscalar_SmithKernel_T244 Input scalar parameter "SmithKernel.T244".
 * \param [in] inscalar_SmithKernel_T245 Input scalar parameter "SmithKernel.T245".
 * \param [in] inscalar_SmithKernel_T246 Input scalar parameter "SmithKernel.T246".
 * \param [in] inscalar_SmithKernel_T247 Input scalar parameter "SmithKernel.T247".
 * \param [in] inscalar_SmithKernel_T248 Input scalar parameter "SmithKernel.T248".
 * \param [in] inscalar_SmithKernel_T249 Input scalar parameter "SmithKernel.T249".
 * \param [in] inscalar_SmithKernel_T25 Input scalar parameter "SmithKernel.T25".
 * \param [in] inscalar_SmithKernel_T250 Input scalar parameter "SmithKernel.T250".
 * \param [in] inscalar_SmithKernel_T251 Input scalar parameter "SmithKernel.T251".
 * \param [in] inscalar_SmithKernel_T252 Input scalar parameter "SmithKernel.T252".
 * \param [in] inscalar_SmithKernel_T253 Input scalar parameter "SmithKernel.T253".
 * \param [in] inscalar_SmithKernel_T254 Input scalar parameter "SmithKernel.T254".
 * \param [in] inscalar_SmithKernel_T255 Input scalar parameter "SmithKernel.T255".
 * \param [in] inscalar_SmithKernel_T256 Input scalar parameter "SmithKernel.T256".
 * \param [in] inscalar_SmithKernel_T257 Input scalar parameter "SmithKernel.T257".
 * \param [in] inscalar_SmithKernel_T258 Input scalar parameter "SmithKernel.T258".
 * \param [in] inscalar_SmithKernel_T259 Input scalar parameter "SmithKernel.T259".
 * \param [in] inscalar_SmithKernel_T26 Input scalar parameter "SmithKernel.T26".
 * \param [in] inscalar_SmithKernel_T260 Input scalar parameter "SmithKernel.T260".
 * \param [in] inscalar_SmithKernel_T261 Input scalar parameter "SmithKernel.T261".
 * \param [in] inscalar_SmithKernel_T262 Input scalar parameter "SmithKernel.T262".
 * \param [in] inscalar_SmithKernel_T263 Input scalar parameter "SmithKernel.T263".
 * \param [in] inscalar_SmithKernel_T264 Input scalar parameter "SmithKernel.T264".
 * \param [in] inscalar_SmithKernel_T265 Input scalar parameter "SmithKernel.T265".
 * \param [in] inscalar_SmithKernel_T266 Input scalar parameter "SmithKernel.T266".
 * \param [in] inscalar_SmithKernel_T267 Input scalar parameter "SmithKernel.T267".
 * \param [in] inscalar_SmithKernel_T268 Input scalar parameter "SmithKernel.T268".
 * \param [in] inscalar_SmithKernel_T269 Input scalar parameter "SmithKernel.T269".
 * \param [in] inscalar_SmithKernel_T27 Input scalar parameter "SmithKernel.T27".
 * \param [in] inscalar_SmithKernel_T270 Input scalar parameter "SmithKernel.T270".
 * \param [in] inscalar_SmithKernel_T271 Input scalar parameter "SmithKernel.T271".
 * \param [in] inscalar_SmithKernel_T272 Input scalar parameter "SmithKernel.T272".
 * \param [in] inscalar_SmithKernel_T273 Input scalar parameter "SmithKernel.T273".
 * \param [in] inscalar_SmithKernel_T274 Input scalar parameter "SmithKernel.T274".
 * \param [in] inscalar_SmithKernel_T275 Input scalar parameter "SmithKernel.T275".
 * \param [in] inscalar_SmithKernel_T276 Input scalar parameter "SmithKernel.T276".
 * \param [in] inscalar_SmithKernel_T277 Input scalar parameter "SmithKernel.T277".
 * \param [in] inscalar_SmithKernel_T278 Input scalar parameter "SmithKernel.T278".
 * \param [in] inscalar_SmithKernel_T279 Input scalar parameter "SmithKernel.T279".
 * \param [in] inscalar_SmithKernel_T28 Input scalar parameter "SmithKernel.T28".
 * \param [in] inscalar_SmithKernel_T280 Input scalar parameter "SmithKernel.T280".
 * \param [in] inscalar_SmithKernel_T281 Input scalar parameter "SmithKernel.T281".
 * \param [in] inscalar_SmithKernel_T282 Input scalar parameter "SmithKernel.T282".
 * \param [in] inscalar_SmithKernel_T283 Input scalar parameter "SmithKernel.T283".
 * \param [in] inscalar_SmithKernel_T284 Input scalar parameter "SmithKernel.T284".
 * \param [in] inscalar_SmithKernel_T285 Input scalar parameter "SmithKernel.T285".
 * \param [in] inscalar_SmithKernel_T286 Input scalar parameter "SmithKernel.T286".
 * \param [in] inscalar_SmithKernel_T287 Input scalar parameter "SmithKernel.T287".
 * \param [in] inscalar_SmithKernel_T288 Input scalar parameter "SmithKernel.T288".
 * \param [in] inscalar_SmithKernel_T289 Input scalar parameter "SmithKernel.T289".
 * \param [in] inscalar_SmithKernel_T29 Input scalar parameter "SmithKernel.T29".
 * \param [in] inscalar_SmithKernel_T290 Input scalar parameter "SmithKernel.T290".
 * \param [in] inscalar_SmithKernel_T291 Input scalar parameter "SmithKernel.T291".
 * \param [in] inscalar_SmithKernel_T292 Input scalar parameter "SmithKernel.T292".
 * \param [in] inscalar_SmithKernel_T293 Input scalar parameter "SmithKernel.T293".
 * \param [in] inscalar_SmithKernel_T294 Input scalar parameter "SmithKernel.T294".
 * \param [in] inscalar_SmithKernel_T295 Input scalar parameter "SmithKernel.T295".
 * \param [in] inscalar_SmithKernel_T296 Input scalar parameter "SmithKernel.T296".
 * \param [in] inscalar_SmithKernel_T297 Input scalar parameter "SmithKernel.T297".
 * \param [in] inscalar_SmithKernel_T298 Input scalar parameter "SmithKernel.T298".
 * \param [in] inscalar_SmithKernel_T299 Input scalar parameter "SmithKernel.T299".
 * \param [in] inscalar_SmithKernel_T3 Input scalar parameter "SmithKernel.T3".
 * \param [in] inscalar_SmithKernel_T30 Input scalar parameter "SmithKernel.T30".
 * \param [in] inscalar_SmithKernel_T300 Input scalar parameter "SmithKernel.T300".
 * \param [in] inscalar_SmithKernel_T301 Input scalar parameter "SmithKernel.T301".
 * \param [in] inscalar_SmithKernel_T302 Input scalar parameter "SmithKernel.T302".
 * \param [in] inscalar_SmithKernel_T303 Input scalar parameter "SmithKernel.T303".
 * \param [in] inscalar_SmithKernel_T304 Input scalar parameter "SmithKernel.T304".
 * \param [in] inscalar_SmithKernel_T305 Input scalar parameter "SmithKernel.T305".
 * \param [in] inscalar_SmithKernel_T306 Input scalar parameter "SmithKernel.T306".
 * \param [in] inscalar_SmithKernel_T307 Input scalar parameter "SmithKernel.T307".
 * \param [in] inscalar_SmithKernel_T308 Input scalar parameter "SmithKernel.T308".
 * \param [in] inscalar_SmithKernel_T309 Input scalar parameter "SmithKernel.T309".
 * \param [in] inscalar_SmithKernel_T31 Input scalar parameter "SmithKernel.T31".
 * \param [in] inscalar_SmithKernel_T310 Input scalar parameter "SmithKernel.T310".
 * \param [in] inscalar_SmithKernel_T311 Input scalar parameter "SmithKernel.T311".
 * \param [in] inscalar_SmithKernel_T312 Input scalar parameter "SmithKernel.T312".
 * \param [in] inscalar_SmithKernel_T313 Input scalar parameter "SmithKernel.T313".
 * \param [in] inscalar_SmithKernel_T314 Input scalar parameter "SmithKernel.T314".
 * \param [in] inscalar_SmithKernel_T315 Input scalar parameter "SmithKernel.T315".
 * \param [in] inscalar_SmithKernel_T316 Input scalar parameter "SmithKernel.T316".
 * \param [in] inscalar_SmithKernel_T317 Input scalar parameter "SmithKernel.T317".
 * \param [in] inscalar_SmithKernel_T318 Input scalar parameter "SmithKernel.T318".
 * \param [in] inscalar_SmithKernel_T319 Input scalar parameter "SmithKernel.T319".
 * \param [in] inscalar_SmithKernel_T32 Input scalar parameter "SmithKernel.T32".
 * \param [in] inscalar_SmithKernel_T320 Input scalar parameter "SmithKernel.T320".
 * \param [in] inscalar_SmithKernel_T321 Input scalar parameter "SmithKernel.T321".
 * \param [in] inscalar_SmithKernel_T322 Input scalar parameter "SmithKernel.T322".
 * \param [in] inscalar_SmithKernel_T323 Input scalar parameter "SmithKernel.T323".
 * \param [in] inscalar_SmithKernel_T324 Input scalar parameter "SmithKernel.T324".
 * \param [in] inscalar_SmithKernel_T325 Input scalar parameter "SmithKernel.T325".
 * \param [in] inscalar_SmithKernel_T326 Input scalar parameter "SmithKernel.T326".
 * \param [in] inscalar_SmithKernel_T327 Input scalar parameter "SmithKernel.T327".
 * \param [in] inscalar_SmithKernel_T328 Input scalar parameter "SmithKernel.T328".
 * \param [in] inscalar_SmithKernel_T329 Input scalar parameter "SmithKernel.T329".
 * \param [in] inscalar_SmithKernel_T33 Input scalar parameter "SmithKernel.T33".
 * \param [in] inscalar_SmithKernel_T330 Input scalar parameter "SmithKernel.T330".
 * \param [in] inscalar_SmithKernel_T331 Input scalar parameter "SmithKernel.T331".
 * \param [in] inscalar_SmithKernel_T332 Input scalar parameter "SmithKernel.T332".
 * \param [in] inscalar_SmithKernel_T333 Input scalar parameter "SmithKernel.T333".
 * \param [in] inscalar_SmithKernel_T334 Input scalar parameter "SmithKernel.T334".
 * \param [in] inscalar_SmithKernel_T335 Input scalar parameter "SmithKernel.T335".
 * \param [in] inscalar_SmithKernel_T336 Input scalar parameter "SmithKernel.T336".
 * \param [in] inscalar_SmithKernel_T337 Input scalar parameter "SmithKernel.T337".
 * \param [in] inscalar_SmithKernel_T338 Input scalar parameter "SmithKernel.T338".
 * \param [in] inscalar_SmithKernel_T339 Input scalar parameter "SmithKernel.T339".
 * \param [in] inscalar_SmithKernel_T34 Input scalar parameter "SmithKernel.T34".
 * \param [in] inscalar_SmithKernel_T340 Input scalar parameter "SmithKernel.T340".
 * \param [in] inscalar_SmithKernel_T341 Input scalar parameter "SmithKernel.T341".
 * \param [in] inscalar_SmithKernel_T342 Input scalar parameter "SmithKernel.T342".
 * \param [in] inscalar_SmithKernel_T343 Input scalar parameter "SmithKernel.T343".
 * \param [in] inscalar_SmithKernel_T344 Input scalar parameter "SmithKernel.T344".
 * \param [in] inscalar_SmithKernel_T345 Input scalar parameter "SmithKernel.T345".
 * \param [in] inscalar_SmithKernel_T346 Input scalar parameter "SmithKernel.T346".
 * \param [in] inscalar_SmithKernel_T347 Input scalar parameter "SmithKernel.T347".
 * \param [in] inscalar_SmithKernel_T348 Input scalar parameter "SmithKernel.T348".
 * \param [in] inscalar_SmithKernel_T349 Input scalar parameter "SmithKernel.T349".
 * \param [in] inscalar_SmithKernel_T35 Input scalar parameter "SmithKernel.T35".
 * \param [in] inscalar_SmithKernel_T350 Input scalar parameter "SmithKernel.T350".
 * \param [in] inscalar_SmithKernel_T351 Input scalar parameter "SmithKernel.T351".
 * \param [in] inscalar_SmithKernel_T352 Input scalar parameter "SmithKernel.T352".
 * \param [in] inscalar_SmithKernel_T353 Input scalar parameter "SmithKernel.T353".
 * \param [in] inscalar_SmithKernel_T354 Input scalar parameter "SmithKernel.T354".
 * \param [in] inscalar_SmithKernel_T355 Input scalar parameter "SmithKernel.T355".
 * \param [in] inscalar_SmithKernel_T356 Input scalar parameter "SmithKernel.T356".
 * \param [in] inscalar_SmithKernel_T357 Input scalar parameter "SmithKernel.T357".
 * \param [in] inscalar_SmithKernel_T358 Input scalar parameter "SmithKernel.T358".
 * \param [in] inscalar_SmithKernel_T359 Input scalar parameter "SmithKernel.T359".
 * \param [in] inscalar_SmithKernel_T36 Input scalar parameter "SmithKernel.T36".
 * \param [in] inscalar_SmithKernel_T360 Input scalar parameter "SmithKernel.T360".
 * \param [in] inscalar_SmithKernel_T361 Input scalar parameter "SmithKernel.T361".
 * \param [in] inscalar_SmithKernel_T362 Input scalar parameter "SmithKernel.T362".
 * \param [in] inscalar_SmithKernel_T363 Input scalar parameter "SmithKernel.T363".
 * \param [in] inscalar_SmithKernel_T364 Input scalar parameter "SmithKernel.T364".
 * \param [in] inscalar_SmithKernel_T365 Input scalar parameter "SmithKernel.T365".
 * \param [in] inscalar_SmithKernel_T366 Input scalar parameter "SmithKernel.T366".
 * \param [in] inscalar_SmithKernel_T367 Input scalar parameter "SmithKernel.T367".
 * \param [in] inscalar_SmithKernel_T368 Input scalar parameter "SmithKernel.T368".
 * \param [in] inscalar_SmithKernel_T369 Input scalar parameter "SmithKernel.T369".
 * \param [in] inscalar_SmithKernel_T37 Input scalar parameter "SmithKernel.T37".
 * \param [in] inscalar_SmithKernel_T370 Input scalar parameter "SmithKernel.T370".
 * \param [in] inscalar_SmithKernel_T371 Input scalar parameter "SmithKernel.T371".
 * \param [in] inscalar_SmithKernel_T372 Input scalar parameter "SmithKernel.T372".
 * \param [in] inscalar_SmithKernel_T373 Input scalar parameter "SmithKernel.T373".
 * \param [in] inscalar_SmithKernel_T374 Input scalar parameter "SmithKernel.T374".
 * \param [in] inscalar_SmithKernel_T375 Input scalar parameter "SmithKernel.T375".
 * \param [in] inscalar_SmithKernel_T376 Input scalar parameter "SmithKernel.T376".
 * \param [in] inscalar_SmithKernel_T377 Input scalar parameter "SmithKernel.T377".
 * \param [in] inscalar_SmithKernel_T378 Input scalar parameter "SmithKernel.T378".
 * \param [in] inscalar_SmithKernel_T379 Input scalar parameter "SmithKernel.T379".
 * \param [in] inscalar_SmithKernel_T38 Input scalar parameter "SmithKernel.T38".
 * \param [in] inscalar_SmithKernel_T380 Input scalar parameter "SmithKernel.T380".
 * \param [in] inscalar_SmithKernel_T381 Input scalar parameter "SmithKernel.T381".
 * \param [in] inscalar_SmithKernel_T382 Input scalar parameter "SmithKernel.T382".
 * \param [in] inscalar_SmithKernel_T383 Input scalar parameter "SmithKernel.T383".
 * \param [in] inscalar_SmithKernel_T384 Input scalar parameter "SmithKernel.T384".
 * \param [in] inscalar_SmithKernel_T385 Input scalar parameter "SmithKernel.T385".
 * \param [in] inscalar_SmithKernel_T386 Input scalar parameter "SmithKernel.T386".
 * \param [in] inscalar_SmithKernel_T387 Input scalar parameter "SmithKernel.T387".
 * \param [in] inscalar_SmithKernel_T388 Input scalar parameter "SmithKernel.T388".
 * \param [in] inscalar_SmithKernel_T389 Input scalar parameter "SmithKernel.T389".
 * \param [in] inscalar_SmithKernel_T39 Input scalar parameter "SmithKernel.T39".
 * \param [in] inscalar_SmithKernel_T390 Input scalar parameter "SmithKernel.T390".
 * \param [in] inscalar_SmithKernel_T391 Input scalar parameter "SmithKernel.T391".
 * \param [in] inscalar_SmithKernel_T392 Input scalar parameter "SmithKernel.T392".
 * \param [in] inscalar_SmithKernel_T393 Input scalar parameter "SmithKernel.T393".
 * \param [in] inscalar_SmithKernel_T394 Input scalar parameter "SmithKernel.T394".
 * \param [in] inscalar_SmithKernel_T395 Input scalar parameter "SmithKernel.T395".
 * \param [in] inscalar_SmithKernel_T396 Input scalar parameter "SmithKernel.T396".
 * \param [in] inscalar_SmithKernel_T397 Input scalar parameter "SmithKernel.T397".
 * \param [in] inscalar_SmithKernel_T398 Input scalar parameter "SmithKernel.T398".
 * \param [in] inscalar_SmithKernel_T399 Input scalar parameter "SmithKernel.T399".
 * \param [in] inscalar_SmithKernel_T4 Input scalar parameter "SmithKernel.T4".
 * \param [in] inscalar_SmithKernel_T40 Input scalar parameter "SmithKernel.T40".
 * \param [in] inscalar_SmithKernel_T400 Input scalar parameter "SmithKernel.T400".
 * \param [in] inscalar_SmithKernel_T401 Input scalar parameter "SmithKernel.T401".
 * \param [in] inscalar_SmithKernel_T402 Input scalar parameter "SmithKernel.T402".
 * \param [in] inscalar_SmithKernel_T403 Input scalar parameter "SmithKernel.T403".
 * \param [in] inscalar_SmithKernel_T404 Input scalar parameter "SmithKernel.T404".
 * \param [in] inscalar_SmithKernel_T405 Input scalar parameter "SmithKernel.T405".
 * \param [in] inscalar_SmithKernel_T406 Input scalar parameter "SmithKernel.T406".
 * \param [in] inscalar_SmithKernel_T407 Input scalar parameter "SmithKernel.T407".
 * \param [in] inscalar_SmithKernel_T408 Input scalar parameter "SmithKernel.T408".
 * \param [in] inscalar_SmithKernel_T409 Input scalar parameter "SmithKernel.T409".
 * \param [in] inscalar_SmithKernel_T41 Input scalar parameter "SmithKernel.T41".
 * \param [in] inscalar_SmithKernel_T410 Input scalar parameter "SmithKernel.T410".
 * \param [in] inscalar_SmithKernel_T411 Input scalar parameter "SmithKernel.T411".
 * \param [in] inscalar_SmithKernel_T412 Input scalar parameter "SmithKernel.T412".
 * \param [in] inscalar_SmithKernel_T413 Input scalar parameter "SmithKernel.T413".
 * \param [in] inscalar_SmithKernel_T414 Input scalar parameter "SmithKernel.T414".
 * \param [in] inscalar_SmithKernel_T415 Input scalar parameter "SmithKernel.T415".
 * \param [in] inscalar_SmithKernel_T416 Input scalar parameter "SmithKernel.T416".
 * \param [in] inscalar_SmithKernel_T417 Input scalar parameter "SmithKernel.T417".
 * \param [in] inscalar_SmithKernel_T418 Input scalar parameter "SmithKernel.T418".
 * \param [in] inscalar_SmithKernel_T419 Input scalar parameter "SmithKernel.T419".
 * \param [in] inscalar_SmithKernel_T42 Input scalar parameter "SmithKernel.T42".
 * \param [in] inscalar_SmithKernel_T420 Input scalar parameter "SmithKernel.T420".
 * \param [in] inscalar_SmithKernel_T421 Input scalar parameter "SmithKernel.T421".
 * \param [in] inscalar_SmithKernel_T422 Input scalar parameter "SmithKernel.T422".
 * \param [in] inscalar_SmithKernel_T423 Input scalar parameter "SmithKernel.T423".
 * \param [in] inscalar_SmithKernel_T424 Input scalar parameter "SmithKernel.T424".
 * \param [in] inscalar_SmithKernel_T425 Input scalar parameter "SmithKernel.T425".
 * \param [in] inscalar_SmithKernel_T426 Input scalar parameter "SmithKernel.T426".
 * \param [in] inscalar_SmithKernel_T427 Input scalar parameter "SmithKernel.T427".
 * \param [in] inscalar_SmithKernel_T428 Input scalar parameter "SmithKernel.T428".
 * \param [in] inscalar_SmithKernel_T429 Input scalar parameter "SmithKernel.T429".
 * \param [in] inscalar_SmithKernel_T43 Input scalar parameter "SmithKernel.T43".
 * \param [in] inscalar_SmithKernel_T430 Input scalar parameter "SmithKernel.T430".
 * \param [in] inscalar_SmithKernel_T431 Input scalar parameter "SmithKernel.T431".
 * \param [in] inscalar_SmithKernel_T432 Input scalar parameter "SmithKernel.T432".
 * \param [in] inscalar_SmithKernel_T433 Input scalar parameter "SmithKernel.T433".
 * \param [in] inscalar_SmithKernel_T434 Input scalar parameter "SmithKernel.T434".
 * \param [in] inscalar_SmithKernel_T435 Input scalar parameter "SmithKernel.T435".
 * \param [in] inscalar_SmithKernel_T436 Input scalar parameter "SmithKernel.T436".
 * \param [in] inscalar_SmithKernel_T437 Input scalar parameter "SmithKernel.T437".
 * \param [in] inscalar_SmithKernel_T438 Input scalar parameter "SmithKernel.T438".
 * \param [in] inscalar_SmithKernel_T439 Input scalar parameter "SmithKernel.T439".
 * \param [in] inscalar_SmithKernel_T44 Input scalar parameter "SmithKernel.T44".
 * \param [in] inscalar_SmithKernel_T440 Input scalar parameter "SmithKernel.T440".
 * \param [in] inscalar_SmithKernel_T441 Input scalar parameter "SmithKernel.T441".
 * \param [in] inscalar_SmithKernel_T442 Input scalar parameter "SmithKernel.T442".
 * \param [in] inscalar_SmithKernel_T443 Input scalar parameter "SmithKernel.T443".
 * \param [in] inscalar_SmithKernel_T444 Input scalar parameter "SmithKernel.T444".
 * \param [in] inscalar_SmithKernel_T445 Input scalar parameter "SmithKernel.T445".
 * \param [in] inscalar_SmithKernel_T446 Input scalar parameter "SmithKernel.T446".
 * \param [in] inscalar_SmithKernel_T447 Input scalar parameter "SmithKernel.T447".
 * \param [in] inscalar_SmithKernel_T448 Input scalar parameter "SmithKernel.T448".
 * \param [in] inscalar_SmithKernel_T449 Input scalar parameter "SmithKernel.T449".
 * \param [in] inscalar_SmithKernel_T45 Input scalar parameter "SmithKernel.T45".
 * \param [in] inscalar_SmithKernel_T450 Input scalar parameter "SmithKernel.T450".
 * \param [in] inscalar_SmithKernel_T451 Input scalar parameter "SmithKernel.T451".
 * \param [in] inscalar_SmithKernel_T452 Input scalar parameter "SmithKernel.T452".
 * \param [in] inscalar_SmithKernel_T453 Input scalar parameter "SmithKernel.T453".
 * \param [in] inscalar_SmithKernel_T454 Input scalar parameter "SmithKernel.T454".
 * \param [in] inscalar_SmithKernel_T455 Input scalar parameter "SmithKernel.T455".
 * \param [in] inscalar_SmithKernel_T456 Input scalar parameter "SmithKernel.T456".
 * \param [in] inscalar_SmithKernel_T457 Input scalar parameter "SmithKernel.T457".
 * \param [in] inscalar_SmithKernel_T458 Input scalar parameter "SmithKernel.T458".
 * \param [in] inscalar_SmithKernel_T459 Input scalar parameter "SmithKernel.T459".
 * \param [in] inscalar_SmithKernel_T46 Input scalar parameter "SmithKernel.T46".
 * \param [in] inscalar_SmithKernel_T460 Input scalar parameter "SmithKernel.T460".
 * \param [in] inscalar_SmithKernel_T461 Input scalar parameter "SmithKernel.T461".
 * \param [in] inscalar_SmithKernel_T462 Input scalar parameter "SmithKernel.T462".
 * \param [in] inscalar_SmithKernel_T463 Input scalar parameter "SmithKernel.T463".
 * \param [in] inscalar_SmithKernel_T464 Input scalar parameter "SmithKernel.T464".
 * \param [in] inscalar_SmithKernel_T465 Input scalar parameter "SmithKernel.T465".
 * \param [in] inscalar_SmithKernel_T466 Input scalar parameter "SmithKernel.T466".
 * \param [in] inscalar_SmithKernel_T467 Input scalar parameter "SmithKernel.T467".
 * \param [in] inscalar_SmithKernel_T468 Input scalar parameter "SmithKernel.T468".
 * \param [in] inscalar_SmithKernel_T469 Input scalar parameter "SmithKernel.T469".
 * \param [in] inscalar_SmithKernel_T47 Input scalar parameter "SmithKernel.T47".
 * \param [in] inscalar_SmithKernel_T470 Input scalar parameter "SmithKernel.T470".
 * \param [in] inscalar_SmithKernel_T471 Input scalar parameter "SmithKernel.T471".
 * \param [in] inscalar_SmithKernel_T472 Input scalar parameter "SmithKernel.T472".
 * \param [in] inscalar_SmithKernel_T473 Input scalar parameter "SmithKernel.T473".
 * \param [in] inscalar_SmithKernel_T474 Input scalar parameter "SmithKernel.T474".
 * \param [in] inscalar_SmithKernel_T475 Input scalar parameter "SmithKernel.T475".
 * \param [in] inscalar_SmithKernel_T476 Input scalar parameter "SmithKernel.T476".
 * \param [in] inscalar_SmithKernel_T477 Input scalar parameter "SmithKernel.T477".
 * \param [in] inscalar_SmithKernel_T478 Input scalar parameter "SmithKernel.T478".
 * \param [in] inscalar_SmithKernel_T479 Input scalar parameter "SmithKernel.T479".
 * \param [in] inscalar_SmithKernel_T48 Input scalar parameter "SmithKernel.T48".
 * \param [in] inscalar_SmithKernel_T480 Input scalar parameter "SmithKernel.T480".
 * \param [in] inscalar_SmithKernel_T481 Input scalar parameter "SmithKernel.T481".
 * \param [in] inscalar_SmithKernel_T482 Input scalar parameter "SmithKernel.T482".
 * \param [in] inscalar_SmithKernel_T483 Input scalar parameter "SmithKernel.T483".
 * \param [in] inscalar_SmithKernel_T484 Input scalar parameter "SmithKernel.T484".
 * \param [in] inscalar_SmithKernel_T485 Input scalar parameter "SmithKernel.T485".
 * \param [in] inscalar_SmithKernel_T486 Input scalar parameter "SmithKernel.T486".
 * \param [in] inscalar_SmithKernel_T487 Input scalar parameter "SmithKernel.T487".
 * \param [in] inscalar_SmithKernel_T488 Input scalar parameter "SmithKernel.T488".
 * \param [in] inscalar_SmithKernel_T489 Input scalar parameter "SmithKernel.T489".
 * \param [in] inscalar_SmithKernel_T49 Input scalar parameter "SmithKernel.T49".
 * \param [in] inscalar_SmithKernel_T490 Input scalar parameter "SmithKernel.T490".
 * \param [in] inscalar_SmithKernel_T491 Input scalar parameter "SmithKernel.T491".
 * \param [in] inscalar_SmithKernel_T492 Input scalar parameter "SmithKernel.T492".
 * \param [in] inscalar_SmithKernel_T493 Input scalar parameter "SmithKernel.T493".
 * \param [in] inscalar_SmithKernel_T494 Input scalar parameter "SmithKernel.T494".
 * \param [in] inscalar_SmithKernel_T495 Input scalar parameter "SmithKernel.T495".
 * \param [in] inscalar_SmithKernel_T496 Input scalar parameter "SmithKernel.T496".
 * \param [in] inscalar_SmithKernel_T497 Input scalar parameter "SmithKernel.T497".
 * \param [in] inscalar_SmithKernel_T498 Input scalar parameter "SmithKernel.T498".
 * \param [in] inscalar_SmithKernel_T499 Input scalar parameter "SmithKernel.T499".
 * \param [in] inscalar_SmithKernel_T5 Input scalar parameter "SmithKernel.T5".
 * \param [in] inscalar_SmithKernel_T50 Input scalar parameter "SmithKernel.T50".
 * \param [in] inscalar_SmithKernel_T500 Input scalar parameter "SmithKernel.T500".
 * \param [in] inscalar_SmithKernel_T501 Input scalar parameter "SmithKernel.T501".
 * \param [in] inscalar_SmithKernel_T502 Input scalar parameter "SmithKernel.T502".
 * \param [in] inscalar_SmithKernel_T503 Input scalar parameter "SmithKernel.T503".
 * \param [in] inscalar_SmithKernel_T504 Input scalar parameter "SmithKernel.T504".
 * \param [in] inscalar_SmithKernel_T505 Input scalar parameter "SmithKernel.T505".
 * \param [in] inscalar_SmithKernel_T506 Input scalar parameter "SmithKernel.T506".
 * \param [in] inscalar_SmithKernel_T507 Input scalar parameter "SmithKernel.T507".
 * \param [in] inscalar_SmithKernel_T508 Input scalar parameter "SmithKernel.T508".
 * \param [in] inscalar_SmithKernel_T509 Input scalar parameter "SmithKernel.T509".
 * \param [in] inscalar_SmithKernel_T51 Input scalar parameter "SmithKernel.T51".
 * \param [in] inscalar_SmithKernel_T510 Input scalar parameter "SmithKernel.T510".
 * \param [in] inscalar_SmithKernel_T511 Input scalar parameter "SmithKernel.T511".
 * \param [in] inscalar_SmithKernel_T52 Input scalar parameter "SmithKernel.T52".
 * \param [in] inscalar_SmithKernel_T53 Input scalar parameter "SmithKernel.T53".
 * \param [in] inscalar_SmithKernel_T54 Input scalar parameter "SmithKernel.T54".
 * \param [in] inscalar_SmithKernel_T55 Input scalar parameter "SmithKernel.T55".
 * \param [in] inscalar_SmithKernel_T56 Input scalar parameter "SmithKernel.T56".
 * \param [in] inscalar_SmithKernel_T57 Input scalar parameter "SmithKernel.T57".
 * \param [in] inscalar_SmithKernel_T58 Input scalar parameter "SmithKernel.T58".
 * \param [in] inscalar_SmithKernel_T59 Input scalar parameter "SmithKernel.T59".
 * \param [in] inscalar_SmithKernel_T6 Input scalar parameter "SmithKernel.T6".
 * \param [in] inscalar_SmithKernel_T60 Input scalar parameter "SmithKernel.T60".
 * \param [in] inscalar_SmithKernel_T61 Input scalar parameter "SmithKernel.T61".
 * \param [in] inscalar_SmithKernel_T62 Input scalar parameter "SmithKernel.T62".
 * \param [in] inscalar_SmithKernel_T63 Input scalar parameter "SmithKernel.T63".
 * \param [in] inscalar_SmithKernel_T64 Input scalar parameter "SmithKernel.T64".
 * \param [in] inscalar_SmithKernel_T65 Input scalar parameter "SmithKernel.T65".
 * \param [in] inscalar_SmithKernel_T66 Input scalar parameter "SmithKernel.T66".
 * \param [in] inscalar_SmithKernel_T67 Input scalar parameter "SmithKernel.T67".
 * \param [in] inscalar_SmithKernel_T68 Input scalar parameter "SmithKernel.T68".
 * \param [in] inscalar_SmithKernel_T69 Input scalar parameter "SmithKernel.T69".
 * \param [in] inscalar_SmithKernel_T7 Input scalar parameter "SmithKernel.T7".
 * \param [in] inscalar_SmithKernel_T70 Input scalar parameter "SmithKernel.T70".
 * \param [in] inscalar_SmithKernel_T71 Input scalar parameter "SmithKernel.T71".
 * \param [in] inscalar_SmithKernel_T72 Input scalar parameter "SmithKernel.T72".
 * \param [in] inscalar_SmithKernel_T73 Input scalar parameter "SmithKernel.T73".
 * \param [in] inscalar_SmithKernel_T74 Input scalar parameter "SmithKernel.T74".
 * \param [in] inscalar_SmithKernel_T75 Input scalar parameter "SmithKernel.T75".
 * \param [in] inscalar_SmithKernel_T76 Input scalar parameter "SmithKernel.T76".
 * \param [in] inscalar_SmithKernel_T77 Input scalar parameter "SmithKernel.T77".
 * \param [in] inscalar_SmithKernel_T78 Input scalar parameter "SmithKernel.T78".
 * \param [in] inscalar_SmithKernel_T79 Input scalar parameter "SmithKernel.T79".
 * \param [in] inscalar_SmithKernel_T8 Input scalar parameter "SmithKernel.T8".
 * \param [in] inscalar_SmithKernel_T80 Input scalar parameter "SmithKernel.T80".
 * \param [in] inscalar_SmithKernel_T81 Input scalar parameter "SmithKernel.T81".
 * \param [in] inscalar_SmithKernel_T82 Input scalar parameter "SmithKernel.T82".
 * \param [in] inscalar_SmithKernel_T83 Input scalar parameter "SmithKernel.T83".
 * \param [in] inscalar_SmithKernel_T84 Input scalar parameter "SmithKernel.T84".
 * \param [in] inscalar_SmithKernel_T85 Input scalar parameter "SmithKernel.T85".
 * \param [in] inscalar_SmithKernel_T86 Input scalar parameter "SmithKernel.T86".
 * \param [in] inscalar_SmithKernel_T87 Input scalar parameter "SmithKernel.T87".
 * \param [in] inscalar_SmithKernel_T88 Input scalar parameter "SmithKernel.T88".
 * \param [in] inscalar_SmithKernel_T89 Input scalar parameter "SmithKernel.T89".
 * \param [in] inscalar_SmithKernel_T9 Input scalar parameter "SmithKernel.T9".
 * \param [in] inscalar_SmithKernel_T90 Input scalar parameter "SmithKernel.T90".
 * \param [in] inscalar_SmithKernel_T91 Input scalar parameter "SmithKernel.T91".
 * \param [in] inscalar_SmithKernel_T92 Input scalar parameter "SmithKernel.T92".
 * \param [in] inscalar_SmithKernel_T93 Input scalar parameter "SmithKernel.T93".
 * \param [in] inscalar_SmithKernel_T94 Input scalar parameter "SmithKernel.T94".
 * \param [in] inscalar_SmithKernel_T95 Input scalar parameter "SmithKernel.T95".
 * \param [in] inscalar_SmithKernel_T96 Input scalar parameter "SmithKernel.T96".
 * \param [in] inscalar_SmithKernel_T97 Input scalar parameter "SmithKernel.T97".
 * \param [in] inscalar_SmithKernel_T98 Input scalar parameter "SmithKernel.T98".
 * \param [in] inscalar_SmithKernel_T99 Input scalar parameter "SmithKernel.T99".
 * \param [in] inscalar_SmithKernel_n Input scalar parameter "SmithKernel.n".
 * \param [in] inscalar_SmithKernel_open Input scalar parameter "SmithKernel.open".
 * \param [in] instream_cpu_to_lmem Stream "cpu_to_lmem".
 * \param [in] instream_size_cpu_to_lmem The size of the stream instream_cpu_to_lmem in bytes.
 * \param [out] outstream_SW Stream "SW".
 * \param [in] outstream_size_SW The size of the stream outstream_SW in bytes.
 * \param [out] outstream_lmem_to_cpu Stream "lmem_to_cpu".
 * \param [in] outstream_size_lmem_to_cpu The size of the stream outstream_lmem_to_cpu in bytes.
 * \param [out] outstream_which Stream "which".
 * \param [in] outstream_size_which The size of the stream outstream_which in bytes.
 * \param [in] lmem_address_write_lmem Linear LMem control for "write_lmem" stream: base address, in bytes.
 * \param [in] lmem_arr_size_write_lmem Linear LMem control for "write_lmem" stream: array size, in bytes.
 * \param [out] lmem_address_inS Linear LMem control for "inS" stream: base address, in bytes.
 * \param [out] lmem_arr_size_inS Linear LMem control for "inS" stream: array size, in bytes.
 * \param [out] lmem_address_inhflag Linear LMem control for "inhflag" stream: base address, in bytes.
 * \param [out] lmem_arr_size_inhflag Linear LMem control for "inhflag" stream: array size, in bytes.
 * \param [out] lmem_address_read_lmem Linear LMem control for "read_lmem" stream: base address, in bytes.
 * \param [out] lmem_arr_size_read_lmem Linear LMem control for "read_lmem" stream: array size, in bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *SmithWaterman_nonblock(
	uint64_t ticks_SmithKernel,
	uint64_t inscalar_SmithKernel_T0,
	uint64_t inscalar_SmithKernel_T1,
	uint64_t inscalar_SmithKernel_T10,
	uint64_t inscalar_SmithKernel_T100,
	uint64_t inscalar_SmithKernel_T101,
	uint64_t inscalar_SmithKernel_T102,
	uint64_t inscalar_SmithKernel_T103,
	uint64_t inscalar_SmithKernel_T104,
	uint64_t inscalar_SmithKernel_T105,
	uint64_t inscalar_SmithKernel_T106,
	uint64_t inscalar_SmithKernel_T107,
	uint64_t inscalar_SmithKernel_T108,
	uint64_t inscalar_SmithKernel_T109,
	uint64_t inscalar_SmithKernel_T11,
	uint64_t inscalar_SmithKernel_T110,
	uint64_t inscalar_SmithKernel_T111,
	uint64_t inscalar_SmithKernel_T112,
	uint64_t inscalar_SmithKernel_T113,
	uint64_t inscalar_SmithKernel_T114,
	uint64_t inscalar_SmithKernel_T115,
	uint64_t inscalar_SmithKernel_T116,
	uint64_t inscalar_SmithKernel_T117,
	uint64_t inscalar_SmithKernel_T118,
	uint64_t inscalar_SmithKernel_T119,
	uint64_t inscalar_SmithKernel_T12,
	uint64_t inscalar_SmithKernel_T120,
	uint64_t inscalar_SmithKernel_T121,
	uint64_t inscalar_SmithKernel_T122,
	uint64_t inscalar_SmithKernel_T123,
	uint64_t inscalar_SmithKernel_T124,
	uint64_t inscalar_SmithKernel_T125,
	uint64_t inscalar_SmithKernel_T126,
	uint64_t inscalar_SmithKernel_T127,
	uint64_t inscalar_SmithKernel_T128,
	uint64_t inscalar_SmithKernel_T129,
	uint64_t inscalar_SmithKernel_T13,
	uint64_t inscalar_SmithKernel_T130,
	uint64_t inscalar_SmithKernel_T131,
	uint64_t inscalar_SmithKernel_T132,
	uint64_t inscalar_SmithKernel_T133,
	uint64_t inscalar_SmithKernel_T134,
	uint64_t inscalar_SmithKernel_T135,
	uint64_t inscalar_SmithKernel_T136,
	uint64_t inscalar_SmithKernel_T137,
	uint64_t inscalar_SmithKernel_T138,
	uint64_t inscalar_SmithKernel_T139,
	uint64_t inscalar_SmithKernel_T14,
	uint64_t inscalar_SmithKernel_T140,
	uint64_t inscalar_SmithKernel_T141,
	uint64_t inscalar_SmithKernel_T142,
	uint64_t inscalar_SmithKernel_T143,
	uint64_t inscalar_SmithKernel_T144,
	uint64_t inscalar_SmithKernel_T145,
	uint64_t inscalar_SmithKernel_T146,
	uint64_t inscalar_SmithKernel_T147,
	uint64_t inscalar_SmithKernel_T148,
	uint64_t inscalar_SmithKernel_T149,
	uint64_t inscalar_SmithKernel_T15,
	uint64_t inscalar_SmithKernel_T150,
	uint64_t inscalar_SmithKernel_T151,
	uint64_t inscalar_SmithKernel_T152,
	uint64_t inscalar_SmithKernel_T153,
	uint64_t inscalar_SmithKernel_T154,
	uint64_t inscalar_SmithKernel_T155,
	uint64_t inscalar_SmithKernel_T156,
	uint64_t inscalar_SmithKernel_T157,
	uint64_t inscalar_SmithKernel_T158,
	uint64_t inscalar_SmithKernel_T159,
	uint64_t inscalar_SmithKernel_T16,
	uint64_t inscalar_SmithKernel_T160,
	uint64_t inscalar_SmithKernel_T161,
	uint64_t inscalar_SmithKernel_T162,
	uint64_t inscalar_SmithKernel_T163,
	uint64_t inscalar_SmithKernel_T164,
	uint64_t inscalar_SmithKernel_T165,
	uint64_t inscalar_SmithKernel_T166,
	uint64_t inscalar_SmithKernel_T167,
	uint64_t inscalar_SmithKernel_T168,
	uint64_t inscalar_SmithKernel_T169,
	uint64_t inscalar_SmithKernel_T17,
	uint64_t inscalar_SmithKernel_T170,
	uint64_t inscalar_SmithKernel_T171,
	uint64_t inscalar_SmithKernel_T172,
	uint64_t inscalar_SmithKernel_T173,
	uint64_t inscalar_SmithKernel_T174,
	uint64_t inscalar_SmithKernel_T175,
	uint64_t inscalar_SmithKernel_T176,
	uint64_t inscalar_SmithKernel_T177,
	uint64_t inscalar_SmithKernel_T178,
	uint64_t inscalar_SmithKernel_T179,
	uint64_t inscalar_SmithKernel_T18,
	uint64_t inscalar_SmithKernel_T180,
	uint64_t inscalar_SmithKernel_T181,
	uint64_t inscalar_SmithKernel_T182,
	uint64_t inscalar_SmithKernel_T183,
	uint64_t inscalar_SmithKernel_T184,
	uint64_t inscalar_SmithKernel_T185,
	uint64_t inscalar_SmithKernel_T186,
	uint64_t inscalar_SmithKernel_T187,
	uint64_t inscalar_SmithKernel_T188,
	uint64_t inscalar_SmithKernel_T189,
	uint64_t inscalar_SmithKernel_T19,
	uint64_t inscalar_SmithKernel_T190,
	uint64_t inscalar_SmithKernel_T191,
	uint64_t inscalar_SmithKernel_T192,
	uint64_t inscalar_SmithKernel_T193,
	uint64_t inscalar_SmithKernel_T194,
	uint64_t inscalar_SmithKernel_T195,
	uint64_t inscalar_SmithKernel_T196,
	uint64_t inscalar_SmithKernel_T197,
	uint64_t inscalar_SmithKernel_T198,
	uint64_t inscalar_SmithKernel_T199,
	uint64_t inscalar_SmithKernel_T2,
	uint64_t inscalar_SmithKernel_T20,
	uint64_t inscalar_SmithKernel_T200,
	uint64_t inscalar_SmithKernel_T201,
	uint64_t inscalar_SmithKernel_T202,
	uint64_t inscalar_SmithKernel_T203,
	uint64_t inscalar_SmithKernel_T204,
	uint64_t inscalar_SmithKernel_T205,
	uint64_t inscalar_SmithKernel_T206,
	uint64_t inscalar_SmithKernel_T207,
	uint64_t inscalar_SmithKernel_T208,
	uint64_t inscalar_SmithKernel_T209,
	uint64_t inscalar_SmithKernel_T21,
	uint64_t inscalar_SmithKernel_T210,
	uint64_t inscalar_SmithKernel_T211,
	uint64_t inscalar_SmithKernel_T212,
	uint64_t inscalar_SmithKernel_T213,
	uint64_t inscalar_SmithKernel_T214,
	uint64_t inscalar_SmithKernel_T215,
	uint64_t inscalar_SmithKernel_T216,
	uint64_t inscalar_SmithKernel_T217,
	uint64_t inscalar_SmithKernel_T218,
	uint64_t inscalar_SmithKernel_T219,
	uint64_t inscalar_SmithKernel_T22,
	uint64_t inscalar_SmithKernel_T220,
	uint64_t inscalar_SmithKernel_T221,
	uint64_t inscalar_SmithKernel_T222,
	uint64_t inscalar_SmithKernel_T223,
	uint64_t inscalar_SmithKernel_T224,
	uint64_t inscalar_SmithKernel_T225,
	uint64_t inscalar_SmithKernel_T226,
	uint64_t inscalar_SmithKernel_T227,
	uint64_t inscalar_SmithKernel_T228,
	uint64_t inscalar_SmithKernel_T229,
	uint64_t inscalar_SmithKernel_T23,
	uint64_t inscalar_SmithKernel_T230,
	uint64_t inscalar_SmithKernel_T231,
	uint64_t inscalar_SmithKernel_T232,
	uint64_t inscalar_SmithKernel_T233,
	uint64_t inscalar_SmithKernel_T234,
	uint64_t inscalar_SmithKernel_T235,
	uint64_t inscalar_SmithKernel_T236,
	uint64_t inscalar_SmithKernel_T237,
	uint64_t inscalar_SmithKernel_T238,
	uint64_t inscalar_SmithKernel_T239,
	uint64_t inscalar_SmithKernel_T24,
	uint64_t inscalar_SmithKernel_T240,
	uint64_t inscalar_SmithKernel_T241,
	uint64_t inscalar_SmithKernel_T242,
	uint64_t inscalar_SmithKernel_T243,
	uint64_t inscalar_SmithKernel_T244,
	uint64_t inscalar_SmithKernel_T245,
	uint64_t inscalar_SmithKernel_T246,
	uint64_t inscalar_SmithKernel_T247,
	uint64_t inscalar_SmithKernel_T248,
	uint64_t inscalar_SmithKernel_T249,
	uint64_t inscalar_SmithKernel_T25,
	uint64_t inscalar_SmithKernel_T250,
	uint64_t inscalar_SmithKernel_T251,
	uint64_t inscalar_SmithKernel_T252,
	uint64_t inscalar_SmithKernel_T253,
	uint64_t inscalar_SmithKernel_T254,
	uint64_t inscalar_SmithKernel_T255,
	uint64_t inscalar_SmithKernel_T256,
	uint64_t inscalar_SmithKernel_T257,
	uint64_t inscalar_SmithKernel_T258,
	uint64_t inscalar_SmithKernel_T259,
	uint64_t inscalar_SmithKernel_T26,
	uint64_t inscalar_SmithKernel_T260,
	uint64_t inscalar_SmithKernel_T261,
	uint64_t inscalar_SmithKernel_T262,
	uint64_t inscalar_SmithKernel_T263,
	uint64_t inscalar_SmithKernel_T264,
	uint64_t inscalar_SmithKernel_T265,
	uint64_t inscalar_SmithKernel_T266,
	uint64_t inscalar_SmithKernel_T267,
	uint64_t inscalar_SmithKernel_T268,
	uint64_t inscalar_SmithKernel_T269,
	uint64_t inscalar_SmithKernel_T27,
	uint64_t inscalar_SmithKernel_T270,
	uint64_t inscalar_SmithKernel_T271,
	uint64_t inscalar_SmithKernel_T272,
	uint64_t inscalar_SmithKernel_T273,
	uint64_t inscalar_SmithKernel_T274,
	uint64_t inscalar_SmithKernel_T275,
	uint64_t inscalar_SmithKernel_T276,
	uint64_t inscalar_SmithKernel_T277,
	uint64_t inscalar_SmithKernel_T278,
	uint64_t inscalar_SmithKernel_T279,
	uint64_t inscalar_SmithKernel_T28,
	uint64_t inscalar_SmithKernel_T280,
	uint64_t inscalar_SmithKernel_T281,
	uint64_t inscalar_SmithKernel_T282,
	uint64_t inscalar_SmithKernel_T283,
	uint64_t inscalar_SmithKernel_T284,
	uint64_t inscalar_SmithKernel_T285,
	uint64_t inscalar_SmithKernel_T286,
	uint64_t inscalar_SmithKernel_T287,
	uint64_t inscalar_SmithKernel_T288,
	uint64_t inscalar_SmithKernel_T289,
	uint64_t inscalar_SmithKernel_T29,
	uint64_t inscalar_SmithKernel_T290,
	uint64_t inscalar_SmithKernel_T291,
	uint64_t inscalar_SmithKernel_T292,
	uint64_t inscalar_SmithKernel_T293,
	uint64_t inscalar_SmithKernel_T294,
	uint64_t inscalar_SmithKernel_T295,
	uint64_t inscalar_SmithKernel_T296,
	uint64_t inscalar_SmithKernel_T297,
	uint64_t inscalar_SmithKernel_T298,
	uint64_t inscalar_SmithKernel_T299,
	uint64_t inscalar_SmithKernel_T3,
	uint64_t inscalar_SmithKernel_T30,
	uint64_t inscalar_SmithKernel_T300,
	uint64_t inscalar_SmithKernel_T301,
	uint64_t inscalar_SmithKernel_T302,
	uint64_t inscalar_SmithKernel_T303,
	uint64_t inscalar_SmithKernel_T304,
	uint64_t inscalar_SmithKernel_T305,
	uint64_t inscalar_SmithKernel_T306,
	uint64_t inscalar_SmithKernel_T307,
	uint64_t inscalar_SmithKernel_T308,
	uint64_t inscalar_SmithKernel_T309,
	uint64_t inscalar_SmithKernel_T31,
	uint64_t inscalar_SmithKernel_T310,
	uint64_t inscalar_SmithKernel_T311,
	uint64_t inscalar_SmithKernel_T312,
	uint64_t inscalar_SmithKernel_T313,
	uint64_t inscalar_SmithKernel_T314,
	uint64_t inscalar_SmithKernel_T315,
	uint64_t inscalar_SmithKernel_T316,
	uint64_t inscalar_SmithKernel_T317,
	uint64_t inscalar_SmithKernel_T318,
	uint64_t inscalar_SmithKernel_T319,
	uint64_t inscalar_SmithKernel_T32,
	uint64_t inscalar_SmithKernel_T320,
	uint64_t inscalar_SmithKernel_T321,
	uint64_t inscalar_SmithKernel_T322,
	uint64_t inscalar_SmithKernel_T323,
	uint64_t inscalar_SmithKernel_T324,
	uint64_t inscalar_SmithKernel_T325,
	uint64_t inscalar_SmithKernel_T326,
	uint64_t inscalar_SmithKernel_T327,
	uint64_t inscalar_SmithKernel_T328,
	uint64_t inscalar_SmithKernel_T329,
	uint64_t inscalar_SmithKernel_T33,
	uint64_t inscalar_SmithKernel_T330,
	uint64_t inscalar_SmithKernel_T331,
	uint64_t inscalar_SmithKernel_T332,
	uint64_t inscalar_SmithKernel_T333,
	uint64_t inscalar_SmithKernel_T334,
	uint64_t inscalar_SmithKernel_T335,
	uint64_t inscalar_SmithKernel_T336,
	uint64_t inscalar_SmithKernel_T337,
	uint64_t inscalar_SmithKernel_T338,
	uint64_t inscalar_SmithKernel_T339,
	uint64_t inscalar_SmithKernel_T34,
	uint64_t inscalar_SmithKernel_T340,
	uint64_t inscalar_SmithKernel_T341,
	uint64_t inscalar_SmithKernel_T342,
	uint64_t inscalar_SmithKernel_T343,
	uint64_t inscalar_SmithKernel_T344,
	uint64_t inscalar_SmithKernel_T345,
	uint64_t inscalar_SmithKernel_T346,
	uint64_t inscalar_SmithKernel_T347,
	uint64_t inscalar_SmithKernel_T348,
	uint64_t inscalar_SmithKernel_T349,
	uint64_t inscalar_SmithKernel_T35,
	uint64_t inscalar_SmithKernel_T350,
	uint64_t inscalar_SmithKernel_T351,
	uint64_t inscalar_SmithKernel_T352,
	uint64_t inscalar_SmithKernel_T353,
	uint64_t inscalar_SmithKernel_T354,
	uint64_t inscalar_SmithKernel_T355,
	uint64_t inscalar_SmithKernel_T356,
	uint64_t inscalar_SmithKernel_T357,
	uint64_t inscalar_SmithKernel_T358,
	uint64_t inscalar_SmithKernel_T359,
	uint64_t inscalar_SmithKernel_T36,
	uint64_t inscalar_SmithKernel_T360,
	uint64_t inscalar_SmithKernel_T361,
	uint64_t inscalar_SmithKernel_T362,
	uint64_t inscalar_SmithKernel_T363,
	uint64_t inscalar_SmithKernel_T364,
	uint64_t inscalar_SmithKernel_T365,
	uint64_t inscalar_SmithKernel_T366,
	uint64_t inscalar_SmithKernel_T367,
	uint64_t inscalar_SmithKernel_T368,
	uint64_t inscalar_SmithKernel_T369,
	uint64_t inscalar_SmithKernel_T37,
	uint64_t inscalar_SmithKernel_T370,
	uint64_t inscalar_SmithKernel_T371,
	uint64_t inscalar_SmithKernel_T372,
	uint64_t inscalar_SmithKernel_T373,
	uint64_t inscalar_SmithKernel_T374,
	uint64_t inscalar_SmithKernel_T375,
	uint64_t inscalar_SmithKernel_T376,
	uint64_t inscalar_SmithKernel_T377,
	uint64_t inscalar_SmithKernel_T378,
	uint64_t inscalar_SmithKernel_T379,
	uint64_t inscalar_SmithKernel_T38,
	uint64_t inscalar_SmithKernel_T380,
	uint64_t inscalar_SmithKernel_T381,
	uint64_t inscalar_SmithKernel_T382,
	uint64_t inscalar_SmithKernel_T383,
	uint64_t inscalar_SmithKernel_T384,
	uint64_t inscalar_SmithKernel_T385,
	uint64_t inscalar_SmithKernel_T386,
	uint64_t inscalar_SmithKernel_T387,
	uint64_t inscalar_SmithKernel_T388,
	uint64_t inscalar_SmithKernel_T389,
	uint64_t inscalar_SmithKernel_T39,
	uint64_t inscalar_SmithKernel_T390,
	uint64_t inscalar_SmithKernel_T391,
	uint64_t inscalar_SmithKernel_T392,
	uint64_t inscalar_SmithKernel_T393,
	uint64_t inscalar_SmithKernel_T394,
	uint64_t inscalar_SmithKernel_T395,
	uint64_t inscalar_SmithKernel_T396,
	uint64_t inscalar_SmithKernel_T397,
	uint64_t inscalar_SmithKernel_T398,
	uint64_t inscalar_SmithKernel_T399,
	uint64_t inscalar_SmithKernel_T4,
	uint64_t inscalar_SmithKernel_T40,
	uint64_t inscalar_SmithKernel_T400,
	uint64_t inscalar_SmithKernel_T401,
	uint64_t inscalar_SmithKernel_T402,
	uint64_t inscalar_SmithKernel_T403,
	uint64_t inscalar_SmithKernel_T404,
	uint64_t inscalar_SmithKernel_T405,
	uint64_t inscalar_SmithKernel_T406,
	uint64_t inscalar_SmithKernel_T407,
	uint64_t inscalar_SmithKernel_T408,
	uint64_t inscalar_SmithKernel_T409,
	uint64_t inscalar_SmithKernel_T41,
	uint64_t inscalar_SmithKernel_T410,
	uint64_t inscalar_SmithKernel_T411,
	uint64_t inscalar_SmithKernel_T412,
	uint64_t inscalar_SmithKernel_T413,
	uint64_t inscalar_SmithKernel_T414,
	uint64_t inscalar_SmithKernel_T415,
	uint64_t inscalar_SmithKernel_T416,
	uint64_t inscalar_SmithKernel_T417,
	uint64_t inscalar_SmithKernel_T418,
	uint64_t inscalar_SmithKernel_T419,
	uint64_t inscalar_SmithKernel_T42,
	uint64_t inscalar_SmithKernel_T420,
	uint64_t inscalar_SmithKernel_T421,
	uint64_t inscalar_SmithKernel_T422,
	uint64_t inscalar_SmithKernel_T423,
	uint64_t inscalar_SmithKernel_T424,
	uint64_t inscalar_SmithKernel_T425,
	uint64_t inscalar_SmithKernel_T426,
	uint64_t inscalar_SmithKernel_T427,
	uint64_t inscalar_SmithKernel_T428,
	uint64_t inscalar_SmithKernel_T429,
	uint64_t inscalar_SmithKernel_T43,
	uint64_t inscalar_SmithKernel_T430,
	uint64_t inscalar_SmithKernel_T431,
	uint64_t inscalar_SmithKernel_T432,
	uint64_t inscalar_SmithKernel_T433,
	uint64_t inscalar_SmithKernel_T434,
	uint64_t inscalar_SmithKernel_T435,
	uint64_t inscalar_SmithKernel_T436,
	uint64_t inscalar_SmithKernel_T437,
	uint64_t inscalar_SmithKernel_T438,
	uint64_t inscalar_SmithKernel_T439,
	uint64_t inscalar_SmithKernel_T44,
	uint64_t inscalar_SmithKernel_T440,
	uint64_t inscalar_SmithKernel_T441,
	uint64_t inscalar_SmithKernel_T442,
	uint64_t inscalar_SmithKernel_T443,
	uint64_t inscalar_SmithKernel_T444,
	uint64_t inscalar_SmithKernel_T445,
	uint64_t inscalar_SmithKernel_T446,
	uint64_t inscalar_SmithKernel_T447,
	uint64_t inscalar_SmithKernel_T448,
	uint64_t inscalar_SmithKernel_T449,
	uint64_t inscalar_SmithKernel_T45,
	uint64_t inscalar_SmithKernel_T450,
	uint64_t inscalar_SmithKernel_T451,
	uint64_t inscalar_SmithKernel_T452,
	uint64_t inscalar_SmithKernel_T453,
	uint64_t inscalar_SmithKernel_T454,
	uint64_t inscalar_SmithKernel_T455,
	uint64_t inscalar_SmithKernel_T456,
	uint64_t inscalar_SmithKernel_T457,
	uint64_t inscalar_SmithKernel_T458,
	uint64_t inscalar_SmithKernel_T459,
	uint64_t inscalar_SmithKernel_T46,
	uint64_t inscalar_SmithKernel_T460,
	uint64_t inscalar_SmithKernel_T461,
	uint64_t inscalar_SmithKernel_T462,
	uint64_t inscalar_SmithKernel_T463,
	uint64_t inscalar_SmithKernel_T464,
	uint64_t inscalar_SmithKernel_T465,
	uint64_t inscalar_SmithKernel_T466,
	uint64_t inscalar_SmithKernel_T467,
	uint64_t inscalar_SmithKernel_T468,
	uint64_t inscalar_SmithKernel_T469,
	uint64_t inscalar_SmithKernel_T47,
	uint64_t inscalar_SmithKernel_T470,
	uint64_t inscalar_SmithKernel_T471,
	uint64_t inscalar_SmithKernel_T472,
	uint64_t inscalar_SmithKernel_T473,
	uint64_t inscalar_SmithKernel_T474,
	uint64_t inscalar_SmithKernel_T475,
	uint64_t inscalar_SmithKernel_T476,
	uint64_t inscalar_SmithKernel_T477,
	uint64_t inscalar_SmithKernel_T478,
	uint64_t inscalar_SmithKernel_T479,
	uint64_t inscalar_SmithKernel_T48,
	uint64_t inscalar_SmithKernel_T480,
	uint64_t inscalar_SmithKernel_T481,
	uint64_t inscalar_SmithKernel_T482,
	uint64_t inscalar_SmithKernel_T483,
	uint64_t inscalar_SmithKernel_T484,
	uint64_t inscalar_SmithKernel_T485,
	uint64_t inscalar_SmithKernel_T486,
	uint64_t inscalar_SmithKernel_T487,
	uint64_t inscalar_SmithKernel_T488,
	uint64_t inscalar_SmithKernel_T489,
	uint64_t inscalar_SmithKernel_T49,
	uint64_t inscalar_SmithKernel_T490,
	uint64_t inscalar_SmithKernel_T491,
	uint64_t inscalar_SmithKernel_T492,
	uint64_t inscalar_SmithKernel_T493,
	uint64_t inscalar_SmithKernel_T494,
	uint64_t inscalar_SmithKernel_T495,
	uint64_t inscalar_SmithKernel_T496,
	uint64_t inscalar_SmithKernel_T497,
	uint64_t inscalar_SmithKernel_T498,
	uint64_t inscalar_SmithKernel_T499,
	uint64_t inscalar_SmithKernel_T5,
	uint64_t inscalar_SmithKernel_T50,
	uint64_t inscalar_SmithKernel_T500,
	uint64_t inscalar_SmithKernel_T501,
	uint64_t inscalar_SmithKernel_T502,
	uint64_t inscalar_SmithKernel_T503,
	uint64_t inscalar_SmithKernel_T504,
	uint64_t inscalar_SmithKernel_T505,
	uint64_t inscalar_SmithKernel_T506,
	uint64_t inscalar_SmithKernel_T507,
	uint64_t inscalar_SmithKernel_T508,
	uint64_t inscalar_SmithKernel_T509,
	uint64_t inscalar_SmithKernel_T51,
	uint64_t inscalar_SmithKernel_T510,
	uint64_t inscalar_SmithKernel_T511,
	uint64_t inscalar_SmithKernel_T52,
	uint64_t inscalar_SmithKernel_T53,
	uint64_t inscalar_SmithKernel_T54,
	uint64_t inscalar_SmithKernel_T55,
	uint64_t inscalar_SmithKernel_T56,
	uint64_t inscalar_SmithKernel_T57,
	uint64_t inscalar_SmithKernel_T58,
	uint64_t inscalar_SmithKernel_T59,
	uint64_t inscalar_SmithKernel_T6,
	uint64_t inscalar_SmithKernel_T60,
	uint64_t inscalar_SmithKernel_T61,
	uint64_t inscalar_SmithKernel_T62,
	uint64_t inscalar_SmithKernel_T63,
	uint64_t inscalar_SmithKernel_T64,
	uint64_t inscalar_SmithKernel_T65,
	uint64_t inscalar_SmithKernel_T66,
	uint64_t inscalar_SmithKernel_T67,
	uint64_t inscalar_SmithKernel_T68,
	uint64_t inscalar_SmithKernel_T69,
	uint64_t inscalar_SmithKernel_T7,
	uint64_t inscalar_SmithKernel_T70,
	uint64_t inscalar_SmithKernel_T71,
	uint64_t inscalar_SmithKernel_T72,
	uint64_t inscalar_SmithKernel_T73,
	uint64_t inscalar_SmithKernel_T74,
	uint64_t inscalar_SmithKernel_T75,
	uint64_t inscalar_SmithKernel_T76,
	uint64_t inscalar_SmithKernel_T77,
	uint64_t inscalar_SmithKernel_T78,
	uint64_t inscalar_SmithKernel_T79,
	uint64_t inscalar_SmithKernel_T8,
	uint64_t inscalar_SmithKernel_T80,
	uint64_t inscalar_SmithKernel_T81,
	uint64_t inscalar_SmithKernel_T82,
	uint64_t inscalar_SmithKernel_T83,
	uint64_t inscalar_SmithKernel_T84,
	uint64_t inscalar_SmithKernel_T85,
	uint64_t inscalar_SmithKernel_T86,
	uint64_t inscalar_SmithKernel_T87,
	uint64_t inscalar_SmithKernel_T88,
	uint64_t inscalar_SmithKernel_T89,
	uint64_t inscalar_SmithKernel_T9,
	uint64_t inscalar_SmithKernel_T90,
	uint64_t inscalar_SmithKernel_T91,
	uint64_t inscalar_SmithKernel_T92,
	uint64_t inscalar_SmithKernel_T93,
	uint64_t inscalar_SmithKernel_T94,
	uint64_t inscalar_SmithKernel_T95,
	uint64_t inscalar_SmithKernel_T96,
	uint64_t inscalar_SmithKernel_T97,
	uint64_t inscalar_SmithKernel_T98,
	uint64_t inscalar_SmithKernel_T99,
	uint64_t inscalar_SmithKernel_n,
	uint64_t inscalar_SmithKernel_open,
	const void *instream_cpu_to_lmem,
	size_t instream_size_cpu_to_lmem,
	void *outstream_SW,
	size_t outstream_size_SW,
	void *outstream_lmem_to_cpu,
	size_t outstream_size_lmem_to_cpu,
	void *outstream_which,
	size_t outstream_size_which,
	size_t lmem_address_write_lmem,
	size_t lmem_arr_size_write_lmem,
	size_t lmem_address_inS,
	size_t lmem_arr_size_inS,
	size_t lmem_address_inhflag,
	size_t lmem_arr_size_inhflag,
	size_t lmem_address_read_lmem,
	size_t lmem_arr_size_read_lmem);

/**
 * \brief Advanced static interface, structure for the engine interface 'default'
 * 
 */
typedef struct { 
	uint64_t ticks_SmithKernel; /**<  [in] The number of ticks for which kernel "SmithKernel" will run. */
	uint64_t inscalar_SmithKernel_T0; /**<  [in] Input scalar parameter "SmithKernel.T0". */
	uint64_t inscalar_SmithKernel_T1; /**<  [in] Input scalar parameter "SmithKernel.T1". */
	uint64_t inscalar_SmithKernel_T10; /**<  [in] Input scalar parameter "SmithKernel.T10". */
	uint64_t inscalar_SmithKernel_T100; /**<  [in] Input scalar parameter "SmithKernel.T100". */
	uint64_t inscalar_SmithKernel_T101; /**<  [in] Input scalar parameter "SmithKernel.T101". */
	uint64_t inscalar_SmithKernel_T102; /**<  [in] Input scalar parameter "SmithKernel.T102". */
	uint64_t inscalar_SmithKernel_T103; /**<  [in] Input scalar parameter "SmithKernel.T103". */
	uint64_t inscalar_SmithKernel_T104; /**<  [in] Input scalar parameter "SmithKernel.T104". */
	uint64_t inscalar_SmithKernel_T105; /**<  [in] Input scalar parameter "SmithKernel.T105". */
	uint64_t inscalar_SmithKernel_T106; /**<  [in] Input scalar parameter "SmithKernel.T106". */
	uint64_t inscalar_SmithKernel_T107; /**<  [in] Input scalar parameter "SmithKernel.T107". */
	uint64_t inscalar_SmithKernel_T108; /**<  [in] Input scalar parameter "SmithKernel.T108". */
	uint64_t inscalar_SmithKernel_T109; /**<  [in] Input scalar parameter "SmithKernel.T109". */
	uint64_t inscalar_SmithKernel_T11; /**<  [in] Input scalar parameter "SmithKernel.T11". */
	uint64_t inscalar_SmithKernel_T110; /**<  [in] Input scalar parameter "SmithKernel.T110". */
	uint64_t inscalar_SmithKernel_T111; /**<  [in] Input scalar parameter "SmithKernel.T111". */
	uint64_t inscalar_SmithKernel_T112; /**<  [in] Input scalar parameter "SmithKernel.T112". */
	uint64_t inscalar_SmithKernel_T113; /**<  [in] Input scalar parameter "SmithKernel.T113". */
	uint64_t inscalar_SmithKernel_T114; /**<  [in] Input scalar parameter "SmithKernel.T114". */
	uint64_t inscalar_SmithKernel_T115; /**<  [in] Input scalar parameter "SmithKernel.T115". */
	uint64_t inscalar_SmithKernel_T116; /**<  [in] Input scalar parameter "SmithKernel.T116". */
	uint64_t inscalar_SmithKernel_T117; /**<  [in] Input scalar parameter "SmithKernel.T117". */
	uint64_t inscalar_SmithKernel_T118; /**<  [in] Input scalar parameter "SmithKernel.T118". */
	uint64_t inscalar_SmithKernel_T119; /**<  [in] Input scalar parameter "SmithKernel.T119". */
	uint64_t inscalar_SmithKernel_T12; /**<  [in] Input scalar parameter "SmithKernel.T12". */
	uint64_t inscalar_SmithKernel_T120; /**<  [in] Input scalar parameter "SmithKernel.T120". */
	uint64_t inscalar_SmithKernel_T121; /**<  [in] Input scalar parameter "SmithKernel.T121". */
	uint64_t inscalar_SmithKernel_T122; /**<  [in] Input scalar parameter "SmithKernel.T122". */
	uint64_t inscalar_SmithKernel_T123; /**<  [in] Input scalar parameter "SmithKernel.T123". */
	uint64_t inscalar_SmithKernel_T124; /**<  [in] Input scalar parameter "SmithKernel.T124". */
	uint64_t inscalar_SmithKernel_T125; /**<  [in] Input scalar parameter "SmithKernel.T125". */
	uint64_t inscalar_SmithKernel_T126; /**<  [in] Input scalar parameter "SmithKernel.T126". */
	uint64_t inscalar_SmithKernel_T127; /**<  [in] Input scalar parameter "SmithKernel.T127". */
	uint64_t inscalar_SmithKernel_T128; /**<  [in] Input scalar parameter "SmithKernel.T128". */
	uint64_t inscalar_SmithKernel_T129; /**<  [in] Input scalar parameter "SmithKernel.T129". */
	uint64_t inscalar_SmithKernel_T13; /**<  [in] Input scalar parameter "SmithKernel.T13". */
	uint64_t inscalar_SmithKernel_T130; /**<  [in] Input scalar parameter "SmithKernel.T130". */
	uint64_t inscalar_SmithKernel_T131; /**<  [in] Input scalar parameter "SmithKernel.T131". */
	uint64_t inscalar_SmithKernel_T132; /**<  [in] Input scalar parameter "SmithKernel.T132". */
	uint64_t inscalar_SmithKernel_T133; /**<  [in] Input scalar parameter "SmithKernel.T133". */
	uint64_t inscalar_SmithKernel_T134; /**<  [in] Input scalar parameter "SmithKernel.T134". */
	uint64_t inscalar_SmithKernel_T135; /**<  [in] Input scalar parameter "SmithKernel.T135". */
	uint64_t inscalar_SmithKernel_T136; /**<  [in] Input scalar parameter "SmithKernel.T136". */
	uint64_t inscalar_SmithKernel_T137; /**<  [in] Input scalar parameter "SmithKernel.T137". */
	uint64_t inscalar_SmithKernel_T138; /**<  [in] Input scalar parameter "SmithKernel.T138". */
	uint64_t inscalar_SmithKernel_T139; /**<  [in] Input scalar parameter "SmithKernel.T139". */
	uint64_t inscalar_SmithKernel_T14; /**<  [in] Input scalar parameter "SmithKernel.T14". */
	uint64_t inscalar_SmithKernel_T140; /**<  [in] Input scalar parameter "SmithKernel.T140". */
	uint64_t inscalar_SmithKernel_T141; /**<  [in] Input scalar parameter "SmithKernel.T141". */
	uint64_t inscalar_SmithKernel_T142; /**<  [in] Input scalar parameter "SmithKernel.T142". */
	uint64_t inscalar_SmithKernel_T143; /**<  [in] Input scalar parameter "SmithKernel.T143". */
	uint64_t inscalar_SmithKernel_T144; /**<  [in] Input scalar parameter "SmithKernel.T144". */
	uint64_t inscalar_SmithKernel_T145; /**<  [in] Input scalar parameter "SmithKernel.T145". */
	uint64_t inscalar_SmithKernel_T146; /**<  [in] Input scalar parameter "SmithKernel.T146". */
	uint64_t inscalar_SmithKernel_T147; /**<  [in] Input scalar parameter "SmithKernel.T147". */
	uint64_t inscalar_SmithKernel_T148; /**<  [in] Input scalar parameter "SmithKernel.T148". */
	uint64_t inscalar_SmithKernel_T149; /**<  [in] Input scalar parameter "SmithKernel.T149". */
	uint64_t inscalar_SmithKernel_T15; /**<  [in] Input scalar parameter "SmithKernel.T15". */
	uint64_t inscalar_SmithKernel_T150; /**<  [in] Input scalar parameter "SmithKernel.T150". */
	uint64_t inscalar_SmithKernel_T151; /**<  [in] Input scalar parameter "SmithKernel.T151". */
	uint64_t inscalar_SmithKernel_T152; /**<  [in] Input scalar parameter "SmithKernel.T152". */
	uint64_t inscalar_SmithKernel_T153; /**<  [in] Input scalar parameter "SmithKernel.T153". */
	uint64_t inscalar_SmithKernel_T154; /**<  [in] Input scalar parameter "SmithKernel.T154". */
	uint64_t inscalar_SmithKernel_T155; /**<  [in] Input scalar parameter "SmithKernel.T155". */
	uint64_t inscalar_SmithKernel_T156; /**<  [in] Input scalar parameter "SmithKernel.T156". */
	uint64_t inscalar_SmithKernel_T157; /**<  [in] Input scalar parameter "SmithKernel.T157". */
	uint64_t inscalar_SmithKernel_T158; /**<  [in] Input scalar parameter "SmithKernel.T158". */
	uint64_t inscalar_SmithKernel_T159; /**<  [in] Input scalar parameter "SmithKernel.T159". */
	uint64_t inscalar_SmithKernel_T16; /**<  [in] Input scalar parameter "SmithKernel.T16". */
	uint64_t inscalar_SmithKernel_T160; /**<  [in] Input scalar parameter "SmithKernel.T160". */
	uint64_t inscalar_SmithKernel_T161; /**<  [in] Input scalar parameter "SmithKernel.T161". */
	uint64_t inscalar_SmithKernel_T162; /**<  [in] Input scalar parameter "SmithKernel.T162". */
	uint64_t inscalar_SmithKernel_T163; /**<  [in] Input scalar parameter "SmithKernel.T163". */
	uint64_t inscalar_SmithKernel_T164; /**<  [in] Input scalar parameter "SmithKernel.T164". */
	uint64_t inscalar_SmithKernel_T165; /**<  [in] Input scalar parameter "SmithKernel.T165". */
	uint64_t inscalar_SmithKernel_T166; /**<  [in] Input scalar parameter "SmithKernel.T166". */
	uint64_t inscalar_SmithKernel_T167; /**<  [in] Input scalar parameter "SmithKernel.T167". */
	uint64_t inscalar_SmithKernel_T168; /**<  [in] Input scalar parameter "SmithKernel.T168". */
	uint64_t inscalar_SmithKernel_T169; /**<  [in] Input scalar parameter "SmithKernel.T169". */
	uint64_t inscalar_SmithKernel_T17; /**<  [in] Input scalar parameter "SmithKernel.T17". */
	uint64_t inscalar_SmithKernel_T170; /**<  [in] Input scalar parameter "SmithKernel.T170". */
	uint64_t inscalar_SmithKernel_T171; /**<  [in] Input scalar parameter "SmithKernel.T171". */
	uint64_t inscalar_SmithKernel_T172; /**<  [in] Input scalar parameter "SmithKernel.T172". */
	uint64_t inscalar_SmithKernel_T173; /**<  [in] Input scalar parameter "SmithKernel.T173". */
	uint64_t inscalar_SmithKernel_T174; /**<  [in] Input scalar parameter "SmithKernel.T174". */
	uint64_t inscalar_SmithKernel_T175; /**<  [in] Input scalar parameter "SmithKernel.T175". */
	uint64_t inscalar_SmithKernel_T176; /**<  [in] Input scalar parameter "SmithKernel.T176". */
	uint64_t inscalar_SmithKernel_T177; /**<  [in] Input scalar parameter "SmithKernel.T177". */
	uint64_t inscalar_SmithKernel_T178; /**<  [in] Input scalar parameter "SmithKernel.T178". */
	uint64_t inscalar_SmithKernel_T179; /**<  [in] Input scalar parameter "SmithKernel.T179". */
	uint64_t inscalar_SmithKernel_T18; /**<  [in] Input scalar parameter "SmithKernel.T18". */
	uint64_t inscalar_SmithKernel_T180; /**<  [in] Input scalar parameter "SmithKernel.T180". */
	uint64_t inscalar_SmithKernel_T181; /**<  [in] Input scalar parameter "SmithKernel.T181". */
	uint64_t inscalar_SmithKernel_T182; /**<  [in] Input scalar parameter "SmithKernel.T182". */
	uint64_t inscalar_SmithKernel_T183; /**<  [in] Input scalar parameter "SmithKernel.T183". */
	uint64_t inscalar_SmithKernel_T184; /**<  [in] Input scalar parameter "SmithKernel.T184". */
	uint64_t inscalar_SmithKernel_T185; /**<  [in] Input scalar parameter "SmithKernel.T185". */
	uint64_t inscalar_SmithKernel_T186; /**<  [in] Input scalar parameter "SmithKernel.T186". */
	uint64_t inscalar_SmithKernel_T187; /**<  [in] Input scalar parameter "SmithKernel.T187". */
	uint64_t inscalar_SmithKernel_T188; /**<  [in] Input scalar parameter "SmithKernel.T188". */
	uint64_t inscalar_SmithKernel_T189; /**<  [in] Input scalar parameter "SmithKernel.T189". */
	uint64_t inscalar_SmithKernel_T19; /**<  [in] Input scalar parameter "SmithKernel.T19". */
	uint64_t inscalar_SmithKernel_T190; /**<  [in] Input scalar parameter "SmithKernel.T190". */
	uint64_t inscalar_SmithKernel_T191; /**<  [in] Input scalar parameter "SmithKernel.T191". */
	uint64_t inscalar_SmithKernel_T192; /**<  [in] Input scalar parameter "SmithKernel.T192". */
	uint64_t inscalar_SmithKernel_T193; /**<  [in] Input scalar parameter "SmithKernel.T193". */
	uint64_t inscalar_SmithKernel_T194; /**<  [in] Input scalar parameter "SmithKernel.T194". */
	uint64_t inscalar_SmithKernel_T195; /**<  [in] Input scalar parameter "SmithKernel.T195". */
	uint64_t inscalar_SmithKernel_T196; /**<  [in] Input scalar parameter "SmithKernel.T196". */
	uint64_t inscalar_SmithKernel_T197; /**<  [in] Input scalar parameter "SmithKernel.T197". */
	uint64_t inscalar_SmithKernel_T198; /**<  [in] Input scalar parameter "SmithKernel.T198". */
	uint64_t inscalar_SmithKernel_T199; /**<  [in] Input scalar parameter "SmithKernel.T199". */
	uint64_t inscalar_SmithKernel_T2; /**<  [in] Input scalar parameter "SmithKernel.T2". */
	uint64_t inscalar_SmithKernel_T20; /**<  [in] Input scalar parameter "SmithKernel.T20". */
	uint64_t inscalar_SmithKernel_T200; /**<  [in] Input scalar parameter "SmithKernel.T200". */
	uint64_t inscalar_SmithKernel_T201; /**<  [in] Input scalar parameter "SmithKernel.T201". */
	uint64_t inscalar_SmithKernel_T202; /**<  [in] Input scalar parameter "SmithKernel.T202". */
	uint64_t inscalar_SmithKernel_T203; /**<  [in] Input scalar parameter "SmithKernel.T203". */
	uint64_t inscalar_SmithKernel_T204; /**<  [in] Input scalar parameter "SmithKernel.T204". */
	uint64_t inscalar_SmithKernel_T205; /**<  [in] Input scalar parameter "SmithKernel.T205". */
	uint64_t inscalar_SmithKernel_T206; /**<  [in] Input scalar parameter "SmithKernel.T206". */
	uint64_t inscalar_SmithKernel_T207; /**<  [in] Input scalar parameter "SmithKernel.T207". */
	uint64_t inscalar_SmithKernel_T208; /**<  [in] Input scalar parameter "SmithKernel.T208". */
	uint64_t inscalar_SmithKernel_T209; /**<  [in] Input scalar parameter "SmithKernel.T209". */
	uint64_t inscalar_SmithKernel_T21; /**<  [in] Input scalar parameter "SmithKernel.T21". */
	uint64_t inscalar_SmithKernel_T210; /**<  [in] Input scalar parameter "SmithKernel.T210". */
	uint64_t inscalar_SmithKernel_T211; /**<  [in] Input scalar parameter "SmithKernel.T211". */
	uint64_t inscalar_SmithKernel_T212; /**<  [in] Input scalar parameter "SmithKernel.T212". */
	uint64_t inscalar_SmithKernel_T213; /**<  [in] Input scalar parameter "SmithKernel.T213". */
	uint64_t inscalar_SmithKernel_T214; /**<  [in] Input scalar parameter "SmithKernel.T214". */
	uint64_t inscalar_SmithKernel_T215; /**<  [in] Input scalar parameter "SmithKernel.T215". */
	uint64_t inscalar_SmithKernel_T216; /**<  [in] Input scalar parameter "SmithKernel.T216". */
	uint64_t inscalar_SmithKernel_T217; /**<  [in] Input scalar parameter "SmithKernel.T217". */
	uint64_t inscalar_SmithKernel_T218; /**<  [in] Input scalar parameter "SmithKernel.T218". */
	uint64_t inscalar_SmithKernel_T219; /**<  [in] Input scalar parameter "SmithKernel.T219". */
	uint64_t inscalar_SmithKernel_T22; /**<  [in] Input scalar parameter "SmithKernel.T22". */
	uint64_t inscalar_SmithKernel_T220; /**<  [in] Input scalar parameter "SmithKernel.T220". */
	uint64_t inscalar_SmithKernel_T221; /**<  [in] Input scalar parameter "SmithKernel.T221". */
	uint64_t inscalar_SmithKernel_T222; /**<  [in] Input scalar parameter "SmithKernel.T222". */
	uint64_t inscalar_SmithKernel_T223; /**<  [in] Input scalar parameter "SmithKernel.T223". */
	uint64_t inscalar_SmithKernel_T224; /**<  [in] Input scalar parameter "SmithKernel.T224". */
	uint64_t inscalar_SmithKernel_T225; /**<  [in] Input scalar parameter "SmithKernel.T225". */
	uint64_t inscalar_SmithKernel_T226; /**<  [in] Input scalar parameter "SmithKernel.T226". */
	uint64_t inscalar_SmithKernel_T227; /**<  [in] Input scalar parameter "SmithKernel.T227". */
	uint64_t inscalar_SmithKernel_T228; /**<  [in] Input scalar parameter "SmithKernel.T228". */
	uint64_t inscalar_SmithKernel_T229; /**<  [in] Input scalar parameter "SmithKernel.T229". */
	uint64_t inscalar_SmithKernel_T23; /**<  [in] Input scalar parameter "SmithKernel.T23". */
	uint64_t inscalar_SmithKernel_T230; /**<  [in] Input scalar parameter "SmithKernel.T230". */
	uint64_t inscalar_SmithKernel_T231; /**<  [in] Input scalar parameter "SmithKernel.T231". */
	uint64_t inscalar_SmithKernel_T232; /**<  [in] Input scalar parameter "SmithKernel.T232". */
	uint64_t inscalar_SmithKernel_T233; /**<  [in] Input scalar parameter "SmithKernel.T233". */
	uint64_t inscalar_SmithKernel_T234; /**<  [in] Input scalar parameter "SmithKernel.T234". */
	uint64_t inscalar_SmithKernel_T235; /**<  [in] Input scalar parameter "SmithKernel.T235". */
	uint64_t inscalar_SmithKernel_T236; /**<  [in] Input scalar parameter "SmithKernel.T236". */
	uint64_t inscalar_SmithKernel_T237; /**<  [in] Input scalar parameter "SmithKernel.T237". */
	uint64_t inscalar_SmithKernel_T238; /**<  [in] Input scalar parameter "SmithKernel.T238". */
	uint64_t inscalar_SmithKernel_T239; /**<  [in] Input scalar parameter "SmithKernel.T239". */
	uint64_t inscalar_SmithKernel_T24; /**<  [in] Input scalar parameter "SmithKernel.T24". */
	uint64_t inscalar_SmithKernel_T240; /**<  [in] Input scalar parameter "SmithKernel.T240". */
	uint64_t inscalar_SmithKernel_T241; /**<  [in] Input scalar parameter "SmithKernel.T241". */
	uint64_t inscalar_SmithKernel_T242; /**<  [in] Input scalar parameter "SmithKernel.T242". */
	uint64_t inscalar_SmithKernel_T243; /**<  [in] Input scalar parameter "SmithKernel.T243". */
	uint64_t inscalar_SmithKernel_T244; /**<  [in] Input scalar parameter "SmithKernel.T244". */
	uint64_t inscalar_SmithKernel_T245; /**<  [in] Input scalar parameter "SmithKernel.T245". */
	uint64_t inscalar_SmithKernel_T246; /**<  [in] Input scalar parameter "SmithKernel.T246". */
	uint64_t inscalar_SmithKernel_T247; /**<  [in] Input scalar parameter "SmithKernel.T247". */
	uint64_t inscalar_SmithKernel_T248; /**<  [in] Input scalar parameter "SmithKernel.T248". */
	uint64_t inscalar_SmithKernel_T249; /**<  [in] Input scalar parameter "SmithKernel.T249". */
	uint64_t inscalar_SmithKernel_T25; /**<  [in] Input scalar parameter "SmithKernel.T25". */
	uint64_t inscalar_SmithKernel_T250; /**<  [in] Input scalar parameter "SmithKernel.T250". */
	uint64_t inscalar_SmithKernel_T251; /**<  [in] Input scalar parameter "SmithKernel.T251". */
	uint64_t inscalar_SmithKernel_T252; /**<  [in] Input scalar parameter "SmithKernel.T252". */
	uint64_t inscalar_SmithKernel_T253; /**<  [in] Input scalar parameter "SmithKernel.T253". */
	uint64_t inscalar_SmithKernel_T254; /**<  [in] Input scalar parameter "SmithKernel.T254". */
	uint64_t inscalar_SmithKernel_T255; /**<  [in] Input scalar parameter "SmithKernel.T255". */
	uint64_t inscalar_SmithKernel_T256; /**<  [in] Input scalar parameter "SmithKernel.T256". */
	uint64_t inscalar_SmithKernel_T257; /**<  [in] Input scalar parameter "SmithKernel.T257". */
	uint64_t inscalar_SmithKernel_T258; /**<  [in] Input scalar parameter "SmithKernel.T258". */
	uint64_t inscalar_SmithKernel_T259; /**<  [in] Input scalar parameter "SmithKernel.T259". */
	uint64_t inscalar_SmithKernel_T26; /**<  [in] Input scalar parameter "SmithKernel.T26". */
	uint64_t inscalar_SmithKernel_T260; /**<  [in] Input scalar parameter "SmithKernel.T260". */
	uint64_t inscalar_SmithKernel_T261; /**<  [in] Input scalar parameter "SmithKernel.T261". */
	uint64_t inscalar_SmithKernel_T262; /**<  [in] Input scalar parameter "SmithKernel.T262". */
	uint64_t inscalar_SmithKernel_T263; /**<  [in] Input scalar parameter "SmithKernel.T263". */
	uint64_t inscalar_SmithKernel_T264; /**<  [in] Input scalar parameter "SmithKernel.T264". */
	uint64_t inscalar_SmithKernel_T265; /**<  [in] Input scalar parameter "SmithKernel.T265". */
	uint64_t inscalar_SmithKernel_T266; /**<  [in] Input scalar parameter "SmithKernel.T266". */
	uint64_t inscalar_SmithKernel_T267; /**<  [in] Input scalar parameter "SmithKernel.T267". */
	uint64_t inscalar_SmithKernel_T268; /**<  [in] Input scalar parameter "SmithKernel.T268". */
	uint64_t inscalar_SmithKernel_T269; /**<  [in] Input scalar parameter "SmithKernel.T269". */
	uint64_t inscalar_SmithKernel_T27; /**<  [in] Input scalar parameter "SmithKernel.T27". */
	uint64_t inscalar_SmithKernel_T270; /**<  [in] Input scalar parameter "SmithKernel.T270". */
	uint64_t inscalar_SmithKernel_T271; /**<  [in] Input scalar parameter "SmithKernel.T271". */
	uint64_t inscalar_SmithKernel_T272; /**<  [in] Input scalar parameter "SmithKernel.T272". */
	uint64_t inscalar_SmithKernel_T273; /**<  [in] Input scalar parameter "SmithKernel.T273". */
	uint64_t inscalar_SmithKernel_T274; /**<  [in] Input scalar parameter "SmithKernel.T274". */
	uint64_t inscalar_SmithKernel_T275; /**<  [in] Input scalar parameter "SmithKernel.T275". */
	uint64_t inscalar_SmithKernel_T276; /**<  [in] Input scalar parameter "SmithKernel.T276". */
	uint64_t inscalar_SmithKernel_T277; /**<  [in] Input scalar parameter "SmithKernel.T277". */
	uint64_t inscalar_SmithKernel_T278; /**<  [in] Input scalar parameter "SmithKernel.T278". */
	uint64_t inscalar_SmithKernel_T279; /**<  [in] Input scalar parameter "SmithKernel.T279". */
	uint64_t inscalar_SmithKernel_T28; /**<  [in] Input scalar parameter "SmithKernel.T28". */
	uint64_t inscalar_SmithKernel_T280; /**<  [in] Input scalar parameter "SmithKernel.T280". */
	uint64_t inscalar_SmithKernel_T281; /**<  [in] Input scalar parameter "SmithKernel.T281". */
	uint64_t inscalar_SmithKernel_T282; /**<  [in] Input scalar parameter "SmithKernel.T282". */
	uint64_t inscalar_SmithKernel_T283; /**<  [in] Input scalar parameter "SmithKernel.T283". */
	uint64_t inscalar_SmithKernel_T284; /**<  [in] Input scalar parameter "SmithKernel.T284". */
	uint64_t inscalar_SmithKernel_T285; /**<  [in] Input scalar parameter "SmithKernel.T285". */
	uint64_t inscalar_SmithKernel_T286; /**<  [in] Input scalar parameter "SmithKernel.T286". */
	uint64_t inscalar_SmithKernel_T287; /**<  [in] Input scalar parameter "SmithKernel.T287". */
	uint64_t inscalar_SmithKernel_T288; /**<  [in] Input scalar parameter "SmithKernel.T288". */
	uint64_t inscalar_SmithKernel_T289; /**<  [in] Input scalar parameter "SmithKernel.T289". */
	uint64_t inscalar_SmithKernel_T29; /**<  [in] Input scalar parameter "SmithKernel.T29". */
	uint64_t inscalar_SmithKernel_T290; /**<  [in] Input scalar parameter "SmithKernel.T290". */
	uint64_t inscalar_SmithKernel_T291; /**<  [in] Input scalar parameter "SmithKernel.T291". */
	uint64_t inscalar_SmithKernel_T292; /**<  [in] Input scalar parameter "SmithKernel.T292". */
	uint64_t inscalar_SmithKernel_T293; /**<  [in] Input scalar parameter "SmithKernel.T293". */
	uint64_t inscalar_SmithKernel_T294; /**<  [in] Input scalar parameter "SmithKernel.T294". */
	uint64_t inscalar_SmithKernel_T295; /**<  [in] Input scalar parameter "SmithKernel.T295". */
	uint64_t inscalar_SmithKernel_T296; /**<  [in] Input scalar parameter "SmithKernel.T296". */
	uint64_t inscalar_SmithKernel_T297; /**<  [in] Input scalar parameter "SmithKernel.T297". */
	uint64_t inscalar_SmithKernel_T298; /**<  [in] Input scalar parameter "SmithKernel.T298". */
	uint64_t inscalar_SmithKernel_T299; /**<  [in] Input scalar parameter "SmithKernel.T299". */
	uint64_t inscalar_SmithKernel_T3; /**<  [in] Input scalar parameter "SmithKernel.T3". */
	uint64_t inscalar_SmithKernel_T30; /**<  [in] Input scalar parameter "SmithKernel.T30". */
	uint64_t inscalar_SmithKernel_T300; /**<  [in] Input scalar parameter "SmithKernel.T300". */
	uint64_t inscalar_SmithKernel_T301; /**<  [in] Input scalar parameter "SmithKernel.T301". */
	uint64_t inscalar_SmithKernel_T302; /**<  [in] Input scalar parameter "SmithKernel.T302". */
	uint64_t inscalar_SmithKernel_T303; /**<  [in] Input scalar parameter "SmithKernel.T303". */
	uint64_t inscalar_SmithKernel_T304; /**<  [in] Input scalar parameter "SmithKernel.T304". */
	uint64_t inscalar_SmithKernel_T305; /**<  [in] Input scalar parameter "SmithKernel.T305". */
	uint64_t inscalar_SmithKernel_T306; /**<  [in] Input scalar parameter "SmithKernel.T306". */
	uint64_t inscalar_SmithKernel_T307; /**<  [in] Input scalar parameter "SmithKernel.T307". */
	uint64_t inscalar_SmithKernel_T308; /**<  [in] Input scalar parameter "SmithKernel.T308". */
	uint64_t inscalar_SmithKernel_T309; /**<  [in] Input scalar parameter "SmithKernel.T309". */
	uint64_t inscalar_SmithKernel_T31; /**<  [in] Input scalar parameter "SmithKernel.T31". */
	uint64_t inscalar_SmithKernel_T310; /**<  [in] Input scalar parameter "SmithKernel.T310". */
	uint64_t inscalar_SmithKernel_T311; /**<  [in] Input scalar parameter "SmithKernel.T311". */
	uint64_t inscalar_SmithKernel_T312; /**<  [in] Input scalar parameter "SmithKernel.T312". */
	uint64_t inscalar_SmithKernel_T313; /**<  [in] Input scalar parameter "SmithKernel.T313". */
	uint64_t inscalar_SmithKernel_T314; /**<  [in] Input scalar parameter "SmithKernel.T314". */
	uint64_t inscalar_SmithKernel_T315; /**<  [in] Input scalar parameter "SmithKernel.T315". */
	uint64_t inscalar_SmithKernel_T316; /**<  [in] Input scalar parameter "SmithKernel.T316". */
	uint64_t inscalar_SmithKernel_T317; /**<  [in] Input scalar parameter "SmithKernel.T317". */
	uint64_t inscalar_SmithKernel_T318; /**<  [in] Input scalar parameter "SmithKernel.T318". */
	uint64_t inscalar_SmithKernel_T319; /**<  [in] Input scalar parameter "SmithKernel.T319". */
	uint64_t inscalar_SmithKernel_T32; /**<  [in] Input scalar parameter "SmithKernel.T32". */
	uint64_t inscalar_SmithKernel_T320; /**<  [in] Input scalar parameter "SmithKernel.T320". */
	uint64_t inscalar_SmithKernel_T321; /**<  [in] Input scalar parameter "SmithKernel.T321". */
	uint64_t inscalar_SmithKernel_T322; /**<  [in] Input scalar parameter "SmithKernel.T322". */
	uint64_t inscalar_SmithKernel_T323; /**<  [in] Input scalar parameter "SmithKernel.T323". */
	uint64_t inscalar_SmithKernel_T324; /**<  [in] Input scalar parameter "SmithKernel.T324". */
	uint64_t inscalar_SmithKernel_T325; /**<  [in] Input scalar parameter "SmithKernel.T325". */
	uint64_t inscalar_SmithKernel_T326; /**<  [in] Input scalar parameter "SmithKernel.T326". */
	uint64_t inscalar_SmithKernel_T327; /**<  [in] Input scalar parameter "SmithKernel.T327". */
	uint64_t inscalar_SmithKernel_T328; /**<  [in] Input scalar parameter "SmithKernel.T328". */
	uint64_t inscalar_SmithKernel_T329; /**<  [in] Input scalar parameter "SmithKernel.T329". */
	uint64_t inscalar_SmithKernel_T33; /**<  [in] Input scalar parameter "SmithKernel.T33". */
	uint64_t inscalar_SmithKernel_T330; /**<  [in] Input scalar parameter "SmithKernel.T330". */
	uint64_t inscalar_SmithKernel_T331; /**<  [in] Input scalar parameter "SmithKernel.T331". */
	uint64_t inscalar_SmithKernel_T332; /**<  [in] Input scalar parameter "SmithKernel.T332". */
	uint64_t inscalar_SmithKernel_T333; /**<  [in] Input scalar parameter "SmithKernel.T333". */
	uint64_t inscalar_SmithKernel_T334; /**<  [in] Input scalar parameter "SmithKernel.T334". */
	uint64_t inscalar_SmithKernel_T335; /**<  [in] Input scalar parameter "SmithKernel.T335". */
	uint64_t inscalar_SmithKernel_T336; /**<  [in] Input scalar parameter "SmithKernel.T336". */
	uint64_t inscalar_SmithKernel_T337; /**<  [in] Input scalar parameter "SmithKernel.T337". */
	uint64_t inscalar_SmithKernel_T338; /**<  [in] Input scalar parameter "SmithKernel.T338". */
	uint64_t inscalar_SmithKernel_T339; /**<  [in] Input scalar parameter "SmithKernel.T339". */
	uint64_t inscalar_SmithKernel_T34; /**<  [in] Input scalar parameter "SmithKernel.T34". */
	uint64_t inscalar_SmithKernel_T340; /**<  [in] Input scalar parameter "SmithKernel.T340". */
	uint64_t inscalar_SmithKernel_T341; /**<  [in] Input scalar parameter "SmithKernel.T341". */
	uint64_t inscalar_SmithKernel_T342; /**<  [in] Input scalar parameter "SmithKernel.T342". */
	uint64_t inscalar_SmithKernel_T343; /**<  [in] Input scalar parameter "SmithKernel.T343". */
	uint64_t inscalar_SmithKernel_T344; /**<  [in] Input scalar parameter "SmithKernel.T344". */
	uint64_t inscalar_SmithKernel_T345; /**<  [in] Input scalar parameter "SmithKernel.T345". */
	uint64_t inscalar_SmithKernel_T346; /**<  [in] Input scalar parameter "SmithKernel.T346". */
	uint64_t inscalar_SmithKernel_T347; /**<  [in] Input scalar parameter "SmithKernel.T347". */
	uint64_t inscalar_SmithKernel_T348; /**<  [in] Input scalar parameter "SmithKernel.T348". */
	uint64_t inscalar_SmithKernel_T349; /**<  [in] Input scalar parameter "SmithKernel.T349". */
	uint64_t inscalar_SmithKernel_T35; /**<  [in] Input scalar parameter "SmithKernel.T35". */
	uint64_t inscalar_SmithKernel_T350; /**<  [in] Input scalar parameter "SmithKernel.T350". */
	uint64_t inscalar_SmithKernel_T351; /**<  [in] Input scalar parameter "SmithKernel.T351". */
	uint64_t inscalar_SmithKernel_T352; /**<  [in] Input scalar parameter "SmithKernel.T352". */
	uint64_t inscalar_SmithKernel_T353; /**<  [in] Input scalar parameter "SmithKernel.T353". */
	uint64_t inscalar_SmithKernel_T354; /**<  [in] Input scalar parameter "SmithKernel.T354". */
	uint64_t inscalar_SmithKernel_T355; /**<  [in] Input scalar parameter "SmithKernel.T355". */
	uint64_t inscalar_SmithKernel_T356; /**<  [in] Input scalar parameter "SmithKernel.T356". */
	uint64_t inscalar_SmithKernel_T357; /**<  [in] Input scalar parameter "SmithKernel.T357". */
	uint64_t inscalar_SmithKernel_T358; /**<  [in] Input scalar parameter "SmithKernel.T358". */
	uint64_t inscalar_SmithKernel_T359; /**<  [in] Input scalar parameter "SmithKernel.T359". */
	uint64_t inscalar_SmithKernel_T36; /**<  [in] Input scalar parameter "SmithKernel.T36". */
	uint64_t inscalar_SmithKernel_T360; /**<  [in] Input scalar parameter "SmithKernel.T360". */
	uint64_t inscalar_SmithKernel_T361; /**<  [in] Input scalar parameter "SmithKernel.T361". */
	uint64_t inscalar_SmithKernel_T362; /**<  [in] Input scalar parameter "SmithKernel.T362". */
	uint64_t inscalar_SmithKernel_T363; /**<  [in] Input scalar parameter "SmithKernel.T363". */
	uint64_t inscalar_SmithKernel_T364; /**<  [in] Input scalar parameter "SmithKernel.T364". */
	uint64_t inscalar_SmithKernel_T365; /**<  [in] Input scalar parameter "SmithKernel.T365". */
	uint64_t inscalar_SmithKernel_T366; /**<  [in] Input scalar parameter "SmithKernel.T366". */
	uint64_t inscalar_SmithKernel_T367; /**<  [in] Input scalar parameter "SmithKernel.T367". */
	uint64_t inscalar_SmithKernel_T368; /**<  [in] Input scalar parameter "SmithKernel.T368". */
	uint64_t inscalar_SmithKernel_T369; /**<  [in] Input scalar parameter "SmithKernel.T369". */
	uint64_t inscalar_SmithKernel_T37; /**<  [in] Input scalar parameter "SmithKernel.T37". */
	uint64_t inscalar_SmithKernel_T370; /**<  [in] Input scalar parameter "SmithKernel.T370". */
	uint64_t inscalar_SmithKernel_T371; /**<  [in] Input scalar parameter "SmithKernel.T371". */
	uint64_t inscalar_SmithKernel_T372; /**<  [in] Input scalar parameter "SmithKernel.T372". */
	uint64_t inscalar_SmithKernel_T373; /**<  [in] Input scalar parameter "SmithKernel.T373". */
	uint64_t inscalar_SmithKernel_T374; /**<  [in] Input scalar parameter "SmithKernel.T374". */
	uint64_t inscalar_SmithKernel_T375; /**<  [in] Input scalar parameter "SmithKernel.T375". */
	uint64_t inscalar_SmithKernel_T376; /**<  [in] Input scalar parameter "SmithKernel.T376". */
	uint64_t inscalar_SmithKernel_T377; /**<  [in] Input scalar parameter "SmithKernel.T377". */
	uint64_t inscalar_SmithKernel_T378; /**<  [in] Input scalar parameter "SmithKernel.T378". */
	uint64_t inscalar_SmithKernel_T379; /**<  [in] Input scalar parameter "SmithKernel.T379". */
	uint64_t inscalar_SmithKernel_T38; /**<  [in] Input scalar parameter "SmithKernel.T38". */
	uint64_t inscalar_SmithKernel_T380; /**<  [in] Input scalar parameter "SmithKernel.T380". */
	uint64_t inscalar_SmithKernel_T381; /**<  [in] Input scalar parameter "SmithKernel.T381". */
	uint64_t inscalar_SmithKernel_T382; /**<  [in] Input scalar parameter "SmithKernel.T382". */
	uint64_t inscalar_SmithKernel_T383; /**<  [in] Input scalar parameter "SmithKernel.T383". */
	uint64_t inscalar_SmithKernel_T384; /**<  [in] Input scalar parameter "SmithKernel.T384". */
	uint64_t inscalar_SmithKernel_T385; /**<  [in] Input scalar parameter "SmithKernel.T385". */
	uint64_t inscalar_SmithKernel_T386; /**<  [in] Input scalar parameter "SmithKernel.T386". */
	uint64_t inscalar_SmithKernel_T387; /**<  [in] Input scalar parameter "SmithKernel.T387". */
	uint64_t inscalar_SmithKernel_T388; /**<  [in] Input scalar parameter "SmithKernel.T388". */
	uint64_t inscalar_SmithKernel_T389; /**<  [in] Input scalar parameter "SmithKernel.T389". */
	uint64_t inscalar_SmithKernel_T39; /**<  [in] Input scalar parameter "SmithKernel.T39". */
	uint64_t inscalar_SmithKernel_T390; /**<  [in] Input scalar parameter "SmithKernel.T390". */
	uint64_t inscalar_SmithKernel_T391; /**<  [in] Input scalar parameter "SmithKernel.T391". */
	uint64_t inscalar_SmithKernel_T392; /**<  [in] Input scalar parameter "SmithKernel.T392". */
	uint64_t inscalar_SmithKernel_T393; /**<  [in] Input scalar parameter "SmithKernel.T393". */
	uint64_t inscalar_SmithKernel_T394; /**<  [in] Input scalar parameter "SmithKernel.T394". */
	uint64_t inscalar_SmithKernel_T395; /**<  [in] Input scalar parameter "SmithKernel.T395". */
	uint64_t inscalar_SmithKernel_T396; /**<  [in] Input scalar parameter "SmithKernel.T396". */
	uint64_t inscalar_SmithKernel_T397; /**<  [in] Input scalar parameter "SmithKernel.T397". */
	uint64_t inscalar_SmithKernel_T398; /**<  [in] Input scalar parameter "SmithKernel.T398". */
	uint64_t inscalar_SmithKernel_T399; /**<  [in] Input scalar parameter "SmithKernel.T399". */
	uint64_t inscalar_SmithKernel_T4; /**<  [in] Input scalar parameter "SmithKernel.T4". */
	uint64_t inscalar_SmithKernel_T40; /**<  [in] Input scalar parameter "SmithKernel.T40". */
	uint64_t inscalar_SmithKernel_T400; /**<  [in] Input scalar parameter "SmithKernel.T400". */
	uint64_t inscalar_SmithKernel_T401; /**<  [in] Input scalar parameter "SmithKernel.T401". */
	uint64_t inscalar_SmithKernel_T402; /**<  [in] Input scalar parameter "SmithKernel.T402". */
	uint64_t inscalar_SmithKernel_T403; /**<  [in] Input scalar parameter "SmithKernel.T403". */
	uint64_t inscalar_SmithKernel_T404; /**<  [in] Input scalar parameter "SmithKernel.T404". */
	uint64_t inscalar_SmithKernel_T405; /**<  [in] Input scalar parameter "SmithKernel.T405". */
	uint64_t inscalar_SmithKernel_T406; /**<  [in] Input scalar parameter "SmithKernel.T406". */
	uint64_t inscalar_SmithKernel_T407; /**<  [in] Input scalar parameter "SmithKernel.T407". */
	uint64_t inscalar_SmithKernel_T408; /**<  [in] Input scalar parameter "SmithKernel.T408". */
	uint64_t inscalar_SmithKernel_T409; /**<  [in] Input scalar parameter "SmithKernel.T409". */
	uint64_t inscalar_SmithKernel_T41; /**<  [in] Input scalar parameter "SmithKernel.T41". */
	uint64_t inscalar_SmithKernel_T410; /**<  [in] Input scalar parameter "SmithKernel.T410". */
	uint64_t inscalar_SmithKernel_T411; /**<  [in] Input scalar parameter "SmithKernel.T411". */
	uint64_t inscalar_SmithKernel_T412; /**<  [in] Input scalar parameter "SmithKernel.T412". */
	uint64_t inscalar_SmithKernel_T413; /**<  [in] Input scalar parameter "SmithKernel.T413". */
	uint64_t inscalar_SmithKernel_T414; /**<  [in] Input scalar parameter "SmithKernel.T414". */
	uint64_t inscalar_SmithKernel_T415; /**<  [in] Input scalar parameter "SmithKernel.T415". */
	uint64_t inscalar_SmithKernel_T416; /**<  [in] Input scalar parameter "SmithKernel.T416". */
	uint64_t inscalar_SmithKernel_T417; /**<  [in] Input scalar parameter "SmithKernel.T417". */
	uint64_t inscalar_SmithKernel_T418; /**<  [in] Input scalar parameter "SmithKernel.T418". */
	uint64_t inscalar_SmithKernel_T419; /**<  [in] Input scalar parameter "SmithKernel.T419". */
	uint64_t inscalar_SmithKernel_T42; /**<  [in] Input scalar parameter "SmithKernel.T42". */
	uint64_t inscalar_SmithKernel_T420; /**<  [in] Input scalar parameter "SmithKernel.T420". */
	uint64_t inscalar_SmithKernel_T421; /**<  [in] Input scalar parameter "SmithKernel.T421". */
	uint64_t inscalar_SmithKernel_T422; /**<  [in] Input scalar parameter "SmithKernel.T422". */
	uint64_t inscalar_SmithKernel_T423; /**<  [in] Input scalar parameter "SmithKernel.T423". */
	uint64_t inscalar_SmithKernel_T424; /**<  [in] Input scalar parameter "SmithKernel.T424". */
	uint64_t inscalar_SmithKernel_T425; /**<  [in] Input scalar parameter "SmithKernel.T425". */
	uint64_t inscalar_SmithKernel_T426; /**<  [in] Input scalar parameter "SmithKernel.T426". */
	uint64_t inscalar_SmithKernel_T427; /**<  [in] Input scalar parameter "SmithKernel.T427". */
	uint64_t inscalar_SmithKernel_T428; /**<  [in] Input scalar parameter "SmithKernel.T428". */
	uint64_t inscalar_SmithKernel_T429; /**<  [in] Input scalar parameter "SmithKernel.T429". */
	uint64_t inscalar_SmithKernel_T43; /**<  [in] Input scalar parameter "SmithKernel.T43". */
	uint64_t inscalar_SmithKernel_T430; /**<  [in] Input scalar parameter "SmithKernel.T430". */
	uint64_t inscalar_SmithKernel_T431; /**<  [in] Input scalar parameter "SmithKernel.T431". */
	uint64_t inscalar_SmithKernel_T432; /**<  [in] Input scalar parameter "SmithKernel.T432". */
	uint64_t inscalar_SmithKernel_T433; /**<  [in] Input scalar parameter "SmithKernel.T433". */
	uint64_t inscalar_SmithKernel_T434; /**<  [in] Input scalar parameter "SmithKernel.T434". */
	uint64_t inscalar_SmithKernel_T435; /**<  [in] Input scalar parameter "SmithKernel.T435". */
	uint64_t inscalar_SmithKernel_T436; /**<  [in] Input scalar parameter "SmithKernel.T436". */
	uint64_t inscalar_SmithKernel_T437; /**<  [in] Input scalar parameter "SmithKernel.T437". */
	uint64_t inscalar_SmithKernel_T438; /**<  [in] Input scalar parameter "SmithKernel.T438". */
	uint64_t inscalar_SmithKernel_T439; /**<  [in] Input scalar parameter "SmithKernel.T439". */
	uint64_t inscalar_SmithKernel_T44; /**<  [in] Input scalar parameter "SmithKernel.T44". */
	uint64_t inscalar_SmithKernel_T440; /**<  [in] Input scalar parameter "SmithKernel.T440". */
	uint64_t inscalar_SmithKernel_T441; /**<  [in] Input scalar parameter "SmithKernel.T441". */
	uint64_t inscalar_SmithKernel_T442; /**<  [in] Input scalar parameter "SmithKernel.T442". */
	uint64_t inscalar_SmithKernel_T443; /**<  [in] Input scalar parameter "SmithKernel.T443". */
	uint64_t inscalar_SmithKernel_T444; /**<  [in] Input scalar parameter "SmithKernel.T444". */
	uint64_t inscalar_SmithKernel_T445; /**<  [in] Input scalar parameter "SmithKernel.T445". */
	uint64_t inscalar_SmithKernel_T446; /**<  [in] Input scalar parameter "SmithKernel.T446". */
	uint64_t inscalar_SmithKernel_T447; /**<  [in] Input scalar parameter "SmithKernel.T447". */
	uint64_t inscalar_SmithKernel_T448; /**<  [in] Input scalar parameter "SmithKernel.T448". */
	uint64_t inscalar_SmithKernel_T449; /**<  [in] Input scalar parameter "SmithKernel.T449". */
	uint64_t inscalar_SmithKernel_T45; /**<  [in] Input scalar parameter "SmithKernel.T45". */
	uint64_t inscalar_SmithKernel_T450; /**<  [in] Input scalar parameter "SmithKernel.T450". */
	uint64_t inscalar_SmithKernel_T451; /**<  [in] Input scalar parameter "SmithKernel.T451". */
	uint64_t inscalar_SmithKernel_T452; /**<  [in] Input scalar parameter "SmithKernel.T452". */
	uint64_t inscalar_SmithKernel_T453; /**<  [in] Input scalar parameter "SmithKernel.T453". */
	uint64_t inscalar_SmithKernel_T454; /**<  [in] Input scalar parameter "SmithKernel.T454". */
	uint64_t inscalar_SmithKernel_T455; /**<  [in] Input scalar parameter "SmithKernel.T455". */
	uint64_t inscalar_SmithKernel_T456; /**<  [in] Input scalar parameter "SmithKernel.T456". */
	uint64_t inscalar_SmithKernel_T457; /**<  [in] Input scalar parameter "SmithKernel.T457". */
	uint64_t inscalar_SmithKernel_T458; /**<  [in] Input scalar parameter "SmithKernel.T458". */
	uint64_t inscalar_SmithKernel_T459; /**<  [in] Input scalar parameter "SmithKernel.T459". */
	uint64_t inscalar_SmithKernel_T46; /**<  [in] Input scalar parameter "SmithKernel.T46". */
	uint64_t inscalar_SmithKernel_T460; /**<  [in] Input scalar parameter "SmithKernel.T460". */
	uint64_t inscalar_SmithKernel_T461; /**<  [in] Input scalar parameter "SmithKernel.T461". */
	uint64_t inscalar_SmithKernel_T462; /**<  [in] Input scalar parameter "SmithKernel.T462". */
	uint64_t inscalar_SmithKernel_T463; /**<  [in] Input scalar parameter "SmithKernel.T463". */
	uint64_t inscalar_SmithKernel_T464; /**<  [in] Input scalar parameter "SmithKernel.T464". */
	uint64_t inscalar_SmithKernel_T465; /**<  [in] Input scalar parameter "SmithKernel.T465". */
	uint64_t inscalar_SmithKernel_T466; /**<  [in] Input scalar parameter "SmithKernel.T466". */
	uint64_t inscalar_SmithKernel_T467; /**<  [in] Input scalar parameter "SmithKernel.T467". */
	uint64_t inscalar_SmithKernel_T468; /**<  [in] Input scalar parameter "SmithKernel.T468". */
	uint64_t inscalar_SmithKernel_T469; /**<  [in] Input scalar parameter "SmithKernel.T469". */
	uint64_t inscalar_SmithKernel_T47; /**<  [in] Input scalar parameter "SmithKernel.T47". */
	uint64_t inscalar_SmithKernel_T470; /**<  [in] Input scalar parameter "SmithKernel.T470". */
	uint64_t inscalar_SmithKernel_T471; /**<  [in] Input scalar parameter "SmithKernel.T471". */
	uint64_t inscalar_SmithKernel_T472; /**<  [in] Input scalar parameter "SmithKernel.T472". */
	uint64_t inscalar_SmithKernel_T473; /**<  [in] Input scalar parameter "SmithKernel.T473". */
	uint64_t inscalar_SmithKernel_T474; /**<  [in] Input scalar parameter "SmithKernel.T474". */
	uint64_t inscalar_SmithKernel_T475; /**<  [in] Input scalar parameter "SmithKernel.T475". */
	uint64_t inscalar_SmithKernel_T476; /**<  [in] Input scalar parameter "SmithKernel.T476". */
	uint64_t inscalar_SmithKernel_T477; /**<  [in] Input scalar parameter "SmithKernel.T477". */
	uint64_t inscalar_SmithKernel_T478; /**<  [in] Input scalar parameter "SmithKernel.T478". */
	uint64_t inscalar_SmithKernel_T479; /**<  [in] Input scalar parameter "SmithKernel.T479". */
	uint64_t inscalar_SmithKernel_T48; /**<  [in] Input scalar parameter "SmithKernel.T48". */
	uint64_t inscalar_SmithKernel_T480; /**<  [in] Input scalar parameter "SmithKernel.T480". */
	uint64_t inscalar_SmithKernel_T481; /**<  [in] Input scalar parameter "SmithKernel.T481". */
	uint64_t inscalar_SmithKernel_T482; /**<  [in] Input scalar parameter "SmithKernel.T482". */
	uint64_t inscalar_SmithKernel_T483; /**<  [in] Input scalar parameter "SmithKernel.T483". */
	uint64_t inscalar_SmithKernel_T484; /**<  [in] Input scalar parameter "SmithKernel.T484". */
	uint64_t inscalar_SmithKernel_T485; /**<  [in] Input scalar parameter "SmithKernel.T485". */
	uint64_t inscalar_SmithKernel_T486; /**<  [in] Input scalar parameter "SmithKernel.T486". */
	uint64_t inscalar_SmithKernel_T487; /**<  [in] Input scalar parameter "SmithKernel.T487". */
	uint64_t inscalar_SmithKernel_T488; /**<  [in] Input scalar parameter "SmithKernel.T488". */
	uint64_t inscalar_SmithKernel_T489; /**<  [in] Input scalar parameter "SmithKernel.T489". */
	uint64_t inscalar_SmithKernel_T49; /**<  [in] Input scalar parameter "SmithKernel.T49". */
	uint64_t inscalar_SmithKernel_T490; /**<  [in] Input scalar parameter "SmithKernel.T490". */
	uint64_t inscalar_SmithKernel_T491; /**<  [in] Input scalar parameter "SmithKernel.T491". */
	uint64_t inscalar_SmithKernel_T492; /**<  [in] Input scalar parameter "SmithKernel.T492". */
	uint64_t inscalar_SmithKernel_T493; /**<  [in] Input scalar parameter "SmithKernel.T493". */
	uint64_t inscalar_SmithKernel_T494; /**<  [in] Input scalar parameter "SmithKernel.T494". */
	uint64_t inscalar_SmithKernel_T495; /**<  [in] Input scalar parameter "SmithKernel.T495". */
	uint64_t inscalar_SmithKernel_T496; /**<  [in] Input scalar parameter "SmithKernel.T496". */
	uint64_t inscalar_SmithKernel_T497; /**<  [in] Input scalar parameter "SmithKernel.T497". */
	uint64_t inscalar_SmithKernel_T498; /**<  [in] Input scalar parameter "SmithKernel.T498". */
	uint64_t inscalar_SmithKernel_T499; /**<  [in] Input scalar parameter "SmithKernel.T499". */
	uint64_t inscalar_SmithKernel_T5; /**<  [in] Input scalar parameter "SmithKernel.T5". */
	uint64_t inscalar_SmithKernel_T50; /**<  [in] Input scalar parameter "SmithKernel.T50". */
	uint64_t inscalar_SmithKernel_T500; /**<  [in] Input scalar parameter "SmithKernel.T500". */
	uint64_t inscalar_SmithKernel_T501; /**<  [in] Input scalar parameter "SmithKernel.T501". */
	uint64_t inscalar_SmithKernel_T502; /**<  [in] Input scalar parameter "SmithKernel.T502". */
	uint64_t inscalar_SmithKernel_T503; /**<  [in] Input scalar parameter "SmithKernel.T503". */
	uint64_t inscalar_SmithKernel_T504; /**<  [in] Input scalar parameter "SmithKernel.T504". */
	uint64_t inscalar_SmithKernel_T505; /**<  [in] Input scalar parameter "SmithKernel.T505". */
	uint64_t inscalar_SmithKernel_T506; /**<  [in] Input scalar parameter "SmithKernel.T506". */
	uint64_t inscalar_SmithKernel_T507; /**<  [in] Input scalar parameter "SmithKernel.T507". */
	uint64_t inscalar_SmithKernel_T508; /**<  [in] Input scalar parameter "SmithKernel.T508". */
	uint64_t inscalar_SmithKernel_T509; /**<  [in] Input scalar parameter "SmithKernel.T509". */
	uint64_t inscalar_SmithKernel_T51; /**<  [in] Input scalar parameter "SmithKernel.T51". */
	uint64_t inscalar_SmithKernel_T510; /**<  [in] Input scalar parameter "SmithKernel.T510". */
	uint64_t inscalar_SmithKernel_T511; /**<  [in] Input scalar parameter "SmithKernel.T511". */
	uint64_t inscalar_SmithKernel_T52; /**<  [in] Input scalar parameter "SmithKernel.T52". */
	uint64_t inscalar_SmithKernel_T53; /**<  [in] Input scalar parameter "SmithKernel.T53". */
	uint64_t inscalar_SmithKernel_T54; /**<  [in] Input scalar parameter "SmithKernel.T54". */
	uint64_t inscalar_SmithKernel_T55; /**<  [in] Input scalar parameter "SmithKernel.T55". */
	uint64_t inscalar_SmithKernel_T56; /**<  [in] Input scalar parameter "SmithKernel.T56". */
	uint64_t inscalar_SmithKernel_T57; /**<  [in] Input scalar parameter "SmithKernel.T57". */
	uint64_t inscalar_SmithKernel_T58; /**<  [in] Input scalar parameter "SmithKernel.T58". */
	uint64_t inscalar_SmithKernel_T59; /**<  [in] Input scalar parameter "SmithKernel.T59". */
	uint64_t inscalar_SmithKernel_T6; /**<  [in] Input scalar parameter "SmithKernel.T6". */
	uint64_t inscalar_SmithKernel_T60; /**<  [in] Input scalar parameter "SmithKernel.T60". */
	uint64_t inscalar_SmithKernel_T61; /**<  [in] Input scalar parameter "SmithKernel.T61". */
	uint64_t inscalar_SmithKernel_T62; /**<  [in] Input scalar parameter "SmithKernel.T62". */
	uint64_t inscalar_SmithKernel_T63; /**<  [in] Input scalar parameter "SmithKernel.T63". */
	uint64_t inscalar_SmithKernel_T64; /**<  [in] Input scalar parameter "SmithKernel.T64". */
	uint64_t inscalar_SmithKernel_T65; /**<  [in] Input scalar parameter "SmithKernel.T65". */
	uint64_t inscalar_SmithKernel_T66; /**<  [in] Input scalar parameter "SmithKernel.T66". */
	uint64_t inscalar_SmithKernel_T67; /**<  [in] Input scalar parameter "SmithKernel.T67". */
	uint64_t inscalar_SmithKernel_T68; /**<  [in] Input scalar parameter "SmithKernel.T68". */
	uint64_t inscalar_SmithKernel_T69; /**<  [in] Input scalar parameter "SmithKernel.T69". */
	uint64_t inscalar_SmithKernel_T7; /**<  [in] Input scalar parameter "SmithKernel.T7". */
	uint64_t inscalar_SmithKernel_T70; /**<  [in] Input scalar parameter "SmithKernel.T70". */
	uint64_t inscalar_SmithKernel_T71; /**<  [in] Input scalar parameter "SmithKernel.T71". */
	uint64_t inscalar_SmithKernel_T72; /**<  [in] Input scalar parameter "SmithKernel.T72". */
	uint64_t inscalar_SmithKernel_T73; /**<  [in] Input scalar parameter "SmithKernel.T73". */
	uint64_t inscalar_SmithKernel_T74; /**<  [in] Input scalar parameter "SmithKernel.T74". */
	uint64_t inscalar_SmithKernel_T75; /**<  [in] Input scalar parameter "SmithKernel.T75". */
	uint64_t inscalar_SmithKernel_T76; /**<  [in] Input scalar parameter "SmithKernel.T76". */
	uint64_t inscalar_SmithKernel_T77; /**<  [in] Input scalar parameter "SmithKernel.T77". */
	uint64_t inscalar_SmithKernel_T78; /**<  [in] Input scalar parameter "SmithKernel.T78". */
	uint64_t inscalar_SmithKernel_T79; /**<  [in] Input scalar parameter "SmithKernel.T79". */
	uint64_t inscalar_SmithKernel_T8; /**<  [in] Input scalar parameter "SmithKernel.T8". */
	uint64_t inscalar_SmithKernel_T80; /**<  [in] Input scalar parameter "SmithKernel.T80". */
	uint64_t inscalar_SmithKernel_T81; /**<  [in] Input scalar parameter "SmithKernel.T81". */
	uint64_t inscalar_SmithKernel_T82; /**<  [in] Input scalar parameter "SmithKernel.T82". */
	uint64_t inscalar_SmithKernel_T83; /**<  [in] Input scalar parameter "SmithKernel.T83". */
	uint64_t inscalar_SmithKernel_T84; /**<  [in] Input scalar parameter "SmithKernel.T84". */
	uint64_t inscalar_SmithKernel_T85; /**<  [in] Input scalar parameter "SmithKernel.T85". */
	uint64_t inscalar_SmithKernel_T86; /**<  [in] Input scalar parameter "SmithKernel.T86". */
	uint64_t inscalar_SmithKernel_T87; /**<  [in] Input scalar parameter "SmithKernel.T87". */
	uint64_t inscalar_SmithKernel_T88; /**<  [in] Input scalar parameter "SmithKernel.T88". */
	uint64_t inscalar_SmithKernel_T89; /**<  [in] Input scalar parameter "SmithKernel.T89". */
	uint64_t inscalar_SmithKernel_T9; /**<  [in] Input scalar parameter "SmithKernel.T9". */
	uint64_t inscalar_SmithKernel_T90; /**<  [in] Input scalar parameter "SmithKernel.T90". */
	uint64_t inscalar_SmithKernel_T91; /**<  [in] Input scalar parameter "SmithKernel.T91". */
	uint64_t inscalar_SmithKernel_T92; /**<  [in] Input scalar parameter "SmithKernel.T92". */
	uint64_t inscalar_SmithKernel_T93; /**<  [in] Input scalar parameter "SmithKernel.T93". */
	uint64_t inscalar_SmithKernel_T94; /**<  [in] Input scalar parameter "SmithKernel.T94". */
	uint64_t inscalar_SmithKernel_T95; /**<  [in] Input scalar parameter "SmithKernel.T95". */
	uint64_t inscalar_SmithKernel_T96; /**<  [in] Input scalar parameter "SmithKernel.T96". */
	uint64_t inscalar_SmithKernel_T97; /**<  [in] Input scalar parameter "SmithKernel.T97". */
	uint64_t inscalar_SmithKernel_T98; /**<  [in] Input scalar parameter "SmithKernel.T98". */
	uint64_t inscalar_SmithKernel_T99; /**<  [in] Input scalar parameter "SmithKernel.T99". */
	uint64_t inscalar_SmithKernel_n; /**<  [in] Input scalar parameter "SmithKernel.n". */
	uint64_t inscalar_SmithKernel_open; /**<  [in] Input scalar parameter "SmithKernel.open". */
	const void *instream_cpu_to_lmem; /**<  [in] Stream "cpu_to_lmem". */
	size_t instream_size_cpu_to_lmem; /**<  [in] The size of the stream instream_cpu_to_lmem in bytes. */
	void *outstream_SW; /**<  [out] Stream "SW". */
	size_t outstream_size_SW; /**<  [in] The size of the stream outstream_SW in bytes. */
	void *outstream_lmem_to_cpu; /**<  [out] Stream "lmem_to_cpu". */
	size_t outstream_size_lmem_to_cpu; /**<  [in] The size of the stream outstream_lmem_to_cpu in bytes. */
	void *outstream_which; /**<  [out] Stream "which". */
	size_t outstream_size_which; /**<  [in] The size of the stream outstream_which in bytes. */
	size_t lmem_address_write_lmem; /**<  [in] Linear LMem control for "write_lmem" stream: base address, in bytes. */
	size_t lmem_arr_size_write_lmem; /**<  [in] Linear LMem control for "write_lmem" stream: array size, in bytes. */
	size_t lmem_address_inS; /**<  [out] Linear LMem control for "inS" stream: base address, in bytes. */
	size_t lmem_arr_size_inS; /**<  [out] Linear LMem control for "inS" stream: array size, in bytes. */
	size_t lmem_address_inhflag; /**<  [out] Linear LMem control for "inhflag" stream: base address, in bytes. */
	size_t lmem_arr_size_inhflag; /**<  [out] Linear LMem control for "inhflag" stream: array size, in bytes. */
	size_t lmem_address_read_lmem; /**<  [out] Linear LMem control for "read_lmem" stream: base address, in bytes. */
	size_t lmem_arr_size_read_lmem; /**<  [out] Linear LMem control for "read_lmem" stream: array size, in bytes. */
} SmithWaterman_actions_t;

/**
 * \brief Advanced static function for the interface 'default'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void SmithWaterman_run(
	max_engine_t *engine,
	SmithWaterman_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'default'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *SmithWaterman_run_nonblock(
	max_engine_t *engine,
	SmithWaterman_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'default'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void SmithWaterman_run_group(max_group_t *group, SmithWaterman_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *SmithWaterman_run_group_nonblock(max_group_t *group, SmithWaterman_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'default'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void SmithWaterman_run_array(max_engarray_t *engarray, SmithWaterman_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *SmithWaterman_run_array_nonblock(max_engarray_t *engarray, SmithWaterman_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* SmithWaterman_convert(max_file_t *maxfile, SmithWaterman_actions_t *interface_actions);

/**
 * \brief Initialise a maxfile.
 */
max_file_t* SmithWaterman_init(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SLIC_DECLARATIONS_SmithWaterman_H */

