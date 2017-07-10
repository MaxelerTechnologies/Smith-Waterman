/*********************************************************************
 * Maxeler Technologies: Smith Waterman Demo                         *
 *                                                                   *
 * Version: 1.3                                                      *
 * Date:    30 July 2013                                             *
 *                                                                   *
 * Backend application code source file                              *
 *                                                                   *
 *********************************************************************/

#ifndef SW_H
#define SW_H
#include "io.h"
#include "timing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

data *smithwaterman(char* argv1, char* argv2,int open ,int extend, double *time, int dna);

int min(int a,int b);
int max(int a,int b);
void test_matrix();

void ph(data *high,int n);
void copy_data(data *saki, data *moto);
void get_order(data *lib, int n, int order);

void execute_sw_affine(data *s, data *t,int open,int extend,int dna);
void execute_sw(data *ss, data *tt);
void sw(data *query, data *lib,int n,int open,int extend, int dna);

typedef struct{
	int e;
	int f;
	int v;
}score;

#endif 



