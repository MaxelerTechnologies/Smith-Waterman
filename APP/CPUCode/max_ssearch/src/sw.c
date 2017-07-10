/*********************************************************************
 * Maxeler Technologies: Smith Waterman Demo                         *
 *                                                                   *
 * Version: 1.3                                                      *
 * Date:    30 July 2013                                             *
 *                                                                   *
 * Backend application code source file                              *
 *                                                                   *
 *********************************************************************/

#include "sw.h"


void out_new_lib(data *lib, int n){
	int i;
	int ii;
	for(i=0;i<n;i++){
		printf(">%s",lib[i].label);
		for(ii=0;ii<lib[i].n;ii++){
			printf("%c",lib[i].s[ii]);
			if(ii%71==70)printf("\n");
		}
		printf("\n");
	}
}


data *smithwaterman(char* argv1, char* argv2,int open,int extend, double *time,int dna){
	//argv1=target_query
	//argv2=target_database

	//load the query
	data *query=NULL;
	query = allocate_query(argv1);

	//load the library
	data *lib=NULL;
	int size=0;
	lib = allocate_database(lib,argv2, &size, 1, dna);

	//calculation of Smith-Waterman Algorithm
	double start=gettime();
	sw(query,lib,size,open,extend,dna);
	*time=gettime()-start;

	for(int i=0;i<size;i++){
		free(lib[i].label);
		free(lib[i].s);
	}
	free(lib);
	free(query->label);
	free(query->s);
	free(query);
	return lib;
}

//loop in the library
void sw(data *query, data *lib,int n,int open,int extend, int dna){

	//some declarations
	fprintf(stderr,"start caluculation for %d elements\n",n);
	int ii;

	//loop in the library
	for(ii=0;ii<n;ii++){
		if(ii%10000==0)fprintf(stderr,"-------------------\ncaluculating %dth element\n",ii);
		lib[ii].sw=0;
		execute_sw_affine(query,&(lib[ii]),open,extend, dna);
	}

	//out put the high scores
	fprintf(stderr,"finish calculation! \n");
	get_order(lib, n, 15);
}



//return the similarity of two input sequence
void execute_sw_affine(data *s, data *t,int open,int extend, int dna){

	//some declarations
	int i,j;

	score **v;
	v = (score**)malloc(sizeof(score*)*(1+t->n));
	int iii;
	for(iii=0;iii<1+t->n;iii++){
		v[iii]=(score*)malloc(sizeof(score)*(1+s->n));
	}

	//initialize the allocated array
	for(j=0;j<=t->n;j++){
		for(i=0;i<=s->n;i++){
			v[j][i].e=0;
			v[j][i].f=0;
			v[j][i].v=0;
		}
	}

	//main calculation of Smith-Waterman Alg.
	int a,b,c,d;
	int tmp;
	int maximum = -1;

	//the main loop
	for(j=1;j<=t->n;j++){
	for(i=1;i<=s->n;i++){
		a = 0;

		b = //v[j][i-1].v + sub(s->s[i-1],'*');
			max(	v[j-1][i].v + open,
				v[j-1][i].e + extend);
		c = //v[j-1][i].v + sub('*',t->s[j-1]);
			max(	v[j][i-1].v + open,
				v[j][i-1].f + extend);
		d = v[j-1][i-1].v + sub(s->s[i-1],t->s[j-1], dna);


		tmp=-100;
		if(a>tmp)tmp = a;
		if(b>tmp)tmp = b;
		if(c>tmp)tmp = c;
		if(d>tmp)tmp = d;

		v[j][i].e = b;
		v[j][i].f = c;
		v[j][i].v = tmp;

		if(v[j][i].v>maximum) maximum = v[j][i].v;
	}
	}


	//store the result in the lib[].sw array
	t->sw = maximum;
	t->p = (t->sw)*10000 - t->n;

	//simple(t);

	//free the score matrix
	for(iii=0;iii<1+t->n;iii++){
		free(v[iii]);
	}
	free(v);
}




/*****************************************************************/
/**************** functions to support calculation ***************/
/*****************************************************************/


//return the smaller value
int min(int a,int b){
	if(a<=b){
		return a;
	}else if(b<a){
		return b;
	}else{
		fprintf(stderr,"error in function min [%d,%d]",a,b);
		exit(0);
	}
}

//return the larger value
int max(int a,int b){
	if(a>=b){
		return a;
	}else if(b>a){
		return b;
	}else{
		fprintf(stderr,"error in function max [%d,%d]",a,b);
		exit(0);
	}
}



//for debug
//test of substitution matrix
void test_matrix(){
	int iii,jjj;
	char sss[]={'A','R','N','D','C','Q','E','G','H','I','L','K','M','F','P','S','T','W','Y','V','B','Z','X','*'};
	for(iii=0;iii<=23;iii++){
	for(jjj=0;jjj<=23;jjj++){
			fprintf(stdout,"%3d",sub(sss[iii],sss[jjj],0));
	}fprintf(stdout,"\n");
	}
}


void ph(data *high,int n){
	int ii;
	fprintf(stdout,"The best scores are:\n");
	for(ii=0;ii<n;ii++){
		//high[ii].label[50] = '\0';
		fprintf(stdout," (%4d)%5d  ",high[ii].n,high[ii].sw);
		fprintf(stdout,"%s",high[ii].label);
	}
}


void copy_data(data *dest, data *src){
	int ii;
	dest->sw = src->sw;
	dest->n = src->n;
	dest->p = src->p;
	for(ii=0;ii<1024;ii++){
		dest->label[ii]=src->label[ii];
	}
}


void get_order(data *lib, int n, int order){
	//allocate the array
	data high[order+1];
	int ii;
	for(ii=0;ii<order+1;ii++){
		high[ii].label = (char*)malloc(sizeof(char)*1024);
		high[ii].label[0] = '*';
		high[ii].label[1] = '\n';
		high[ii].label[2] = '\0';
		high[ii].sw = -ii;
		high[ii].n = 0;
	}

	int iii;
	for(ii=0;ii<n;ii++){
		if(high[order+1-1].p < lib[ii].p){
			for(iii=order+1-2;iii>=0;iii--){
				if(high[iii].p < lib[ii].p){
					copy_data(&(high[iii+1]),&(high[iii]));
					copy_data(&(high[iii]),&(lib[ii]));
				}
			}
		}
	}
	ph(high,order);
}








