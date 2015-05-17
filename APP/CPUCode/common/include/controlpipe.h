/*********************************************************************
 * Maxeler Technologies: Smith Waterman Demo                         *
 *                                                                   *
 * Version: 1.3                                                      *
 * Date:    30 July 2013                                             *
 *                                                                   *
 * Common library code source file                                   *
 *                                                                   *
 *********************************************************************/

#ifndef CONTROLPIPE_H
#define CONTROLPIPE_H

typedef enum {
	QUERY 			= 0,
	LIBRARY 		= 1,
	COMPUTE			= 2,
	STOP			= 3,
	CONFIGURATION	= 4,
	QUIT			= 5,
	NEW_CONFIG		= 6,
	NONE 			= 7
} msg_t;

int open_pipe(const char * pipe, int flag);

void write_int(int fd, int val);
void write_message(int fd, msg_t msg);
void write_float(int fd, float f);

void write_char(int fd, char val);
void write_nchar(int fd, char* s, int n);
void write_four_char(int fd, char * val);

int has_message(int fd);

msg_t read_message(int fd);
int read_int(int fd);

char* read_nchar(int fd, char* s, int n);

#endif //_CONTROL_PIPE_H
