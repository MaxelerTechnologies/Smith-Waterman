/*********************************************************************
 * Maxeler Technologies: Smith Waterman Demo                         *
 *                                                                   *
 * Version: 1.3                                                      *
 * Date:    30 July 2013                                             *
 *                                                                   *
 * Common library code source file                                   *
 *                                                                   *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "controlpipe.h"


int open_pipe(const char * pipe_name, int flag){
	printf("Opening pipe [%s]...", pipe_name);
	int pipe = open(pipe_name, flag);
	if (pipe == -1) {
		perror("Cannot open input pipe");
		return -1;
	}
	printf("OK\n");
	return pipe;
}

void write_int(int fd, int val) {
	uint8_t bytes[4];
	bytes[0] = (uint8_t) ((val >> 24) & 0xff);
	bytes[1] = (uint8_t) ((val >> 16) & 0xff);
	bytes[2] = (uint8_t) ((val >> 8) & 0xff);
	bytes[3] = (uint8_t) ((val >> 0) & 0xff);
	write(fd, bytes, 4);
}

void write_char(int fd, char val) {
	uint8_t byte = val & 0xff;
	write(fd, &byte, 1);
}

void write_nchar(int fd, char* s, int n){
	write(fd, s,n);
}

void write_four_char(int fd, char *val) {
	uint8_t bytes[4];
	bytes[0] = (uint8_t) (val[3] & 0xff);
	bytes[1] = (uint8_t) (val[2] & 0xff);
	bytes[2] = (uint8_t) (val[1] & 0xff);
	bytes[3] = (uint8_t) (val[0] & 0xff);
	write(fd, bytes, 4);
}

void write_message(int fd, msg_t msg){
	write_int(fd, (int) msg);
}

void write_float(int fd, float f)
{
	union {
		float f;
		int i;
	} u;
	u.f = f;
	write_int(fd, u.i);
}

int has_message(int fd)
{
	int ret;
	struct timeval tv;
	fd_set rfds;

	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);

	tv.tv_sec = 0;
	tv.tv_usec = 100;

	int retval = select(fd+1, &rfds, NULL, NULL, &tv);
	if (retval == -1) {
		perror("select()");
		ret = 0;
	} else if (retval) {
		ret = 1;
	} else {
		ret = 0;
	}
	return ret;
}

/* synchronous - see has_message */
int read_int(int fd)
{
	uint8_t bytes[4];
	int c = 0;
	int r;
	do {
		r = read(fd, &bytes, 4 - c);
		c += r;
	} while (c < 4);

	return (bytes[0] << 24 |
			bytes[1] << 16 |
			bytes[2] << 8 |
			bytes[3]);
}


char* read_nchar(int fd, char* s, int n){
	int c = 0;
	int r;
	do {
		r = read(fd, s, n - c);
		c += r;
	} while (c < n);

	return s;
}


msg_t read_message(int fd)
{
	msg_t msg = (msg_t) read_int(fd);
	return msg;
}
