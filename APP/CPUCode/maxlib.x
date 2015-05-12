/* X-macros defining dynamically-loaded functions */
X(start, maxlib_context *, (const int idx_first_device, const int num_devices, int simulation, card_type type, int feedback_pipe, const char *engine_pattern));
X(restart, maxlib_context *, (maxlib_context * this_, int feedback_pipe));
X(end, void, (maxlib_context *context));
X(load_queries, query_stream * ,(maxlib_context *context, query_stream *query, int *num_queries, char *query_filename,int control_pipe,int feedback_pipe));
X(load_database, data*, (maxlib_context *context, data *lib, int *lib_size, char *lib_filename, int control_pipe, int feedback_pipe));
X(prepare_database, lib_stream*, (maxlib_context *context, lib_stream *ls, data *lib, int lib_size,int feedback_pipe));
X(set_sw, void, (maxlib_context *context, lib_stream *ls, int control_pipe, int lib_size, int *nb_dislpay, int *display_len));
X(set_query, void, (maxlib_context * context, query_stream * query, int compute_count));
X(set_pcie_stream, void, (maxlib_context *context, int num_cycles));
X(run_alignment, lib_stream*, (maxlib_context *context,lib_stream *ls));
X(send_results, void, (maxlib_context *context, query_stream * query, lib_stream * ls, data * lib, double dfeTime, int compute_count, int nb_display, int LABEL_DISPLAY_LENGTH, int feedback_pipe, int check_results));
