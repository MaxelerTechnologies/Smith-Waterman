/*********************************************************************
 * Maxeler Technologies: Smith Waterman Demo                         *
 *                                                                   *
 * Version: 1.3                                                      *
 * Date:    30 July 2013                                             *
 *                                                                   *
 * Common library code source file                                   *
 *                                                                   *
 *********************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#include "io.h"
#include "timing.h"

#define TABLE_WIDTH 24

#define LINE_LENGTH 80
//#define BEST

int N = 1024;

//Capital letters have to be converted into an index in [0;23] before hand by a simple subtraction by 'A' ('*' is 23)
//Then, to_aa_index[index] gives the index of the letter in the classic order of BLOSUM62 (ARNDCQ...)

//				   A,	 B, C,  D,  E,   F, G,  H,  I,   J,  K,  L,  M, N,   O,  P, Q,  R,   S,  T,  U,  V,  W,  X,  Y,  Z, unknown/padding/*
int to_aa_index[]={0,	20,	4,	3,	6,	13,	7,	8,	9,	23,	11,	10,	12,	2,	23,	14,	5,	1,	15,	16,	23,	19,	17,	22,	18,	21,	23};


int BL62[]={
		 4,-1,-2,-2, 0,-1,-1, 0,-2,-1,-1,-1,-1,-2,-1, 1, 0,-3,-2, 0,-2,-1, 0,-4,
		-1, 5, 0,-2,-3, 1, 0,-2, 0,-3,-2, 2,-1,-3,-2,-1,-1,-3,-2,-3,-1, 0,-1,-4,
		-2, 0, 6, 1,-3, 0, 0, 0, 1,-3,-3, 0,-2,-3,-2, 1, 0,-4,-2,-3, 3, 0,-1,-4,
		-2,-2, 1, 6,-3, 0, 2,-1,-1,-3,-4,-1,-3,-3,-1, 0,-1,-4,-3,-3, 4, 1,-1,-4,
		 0,-3,-3,-3, 9,-3,-4,-3,-3,-1,-1,-3,-1,-2,-3,-1,-1,-2,-2,-1,-3,-3,-2,-4,
		-1, 1, 0, 0,-3, 5, 2,-2, 0,-3,-2, 1, 0,-3,-1, 0,-1,-2,-1,-2, 0, 3,-1,-4,
		-1, 0, 0, 2,-4, 2, 5,-2, 0,-3,-3, 1,-2,-3,-1, 0,-1,-3,-2,-2, 1, 4,-1,-4,
		 0,-2, 0,-1,-3,-2,-2, 6,-2,-4,-4,-2,-3,-3,-2, 0,-2,-2,-3,-3,-1,-2,-1,-4,
		-2, 0, 1,-1,-3, 0, 0,-2, 8,-3,-3,-1,-2,-1,-2,-1,-2,-2, 2,-3, 0, 0,-1,-4,
		-1,-3,-3,-3,-1,-3,-3,-4,-3, 4, 2,-3, 1, 0,-3,-2,-1,-3,-1, 3,-3,-3,-1,-4,
		-1,-2,-3,-4,-1,-2,-3,-4,-3, 2, 4,-2, 2, 0,-3,-2,-1,-2,-1, 1,-4,-3,-1,-4,
		-1, 2, 0,-1,-3, 1, 1,-2,-1,-3,-2, 5,-1,-3,-1, 0,-1,-3,-2,-2, 0, 1,-1,-4,
		-1,-1,-2,-3,-1, 0,-2,-3,-2, 1, 2,-1, 5, 0,-2,-1,-1,-1,-1, 1,-3,-1,-1,-4,
		-2,-3,-3,-3,-2,-3,-3,-3,-1, 0, 0,-3, 0, 6,-4,-2,-2, 1, 3,-1,-3,-3,-1,-4,
		-1,-2,-2,-1,-3,-1,-1,-2,-2,-3,-3,-1,-2,-4, 7,-1,-1,-4,-3,-2,-2,-1,-2,-4,
		 1,-1, 1, 0,-1, 0, 0, 0,-1,-2,-2, 0,-1,-2,-1, 4, 1,-3,-2,-2, 0, 0, 0,-4,
		 0,-1, 0,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-2,-1, 1, 5,-2,-2, 0,-1,-1, 0,-4,
		-3,-3,-4,-4,-2,-2,-3,-2,-2,-3,-2,-3,-1, 1,-4,-3,-2,11, 2,-3,-4,-3,-2,-4,
		-2,-2,-2,-3,-2,-1,-2,-3, 2,-1,-1,-2,-1, 3,-3,-2,-2, 2, 7,-1,-3,-2,-1,-4,
		 0,-3,-3,-3,-1,-2,-2,-3,-3, 3, 1,-2, 1,-1,-2,-2, 0,-3,-1, 4,-3,-2,-1,-4,
		-2,-1, 3, 4,-3, 0, 1,-1, 0,-3,-4, 0,-3,-3,-2, 0,-1,-4,-3,-3, 4, 1,-1,-4,
		-1, 0, 0, 1,-3, 3, 4,-2, 0,-3,-3, 1,-1,-3,-1, 0,-1,-3,-2,-2, 1, 4,-1,-4,
		 0,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2, 0, 0,-2,-1,-1,-1,-1,-1,-4,
		-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4, 1
};


//allocate the query sequence
data *allocate_query(char *filename){
	FILE *fp;
	if((fp = fopen(filename,"r"))==NULL){
		fprintf(stderr,"query file open error!!\n");
		exit(0);
	}

	//allocate structure
	data *d;
	d = (data*)malloc(sizeof(data));
	d->label = (char*)malloc(sizeof(char)*N);

	//count the length of sequence
	fgetc(fp);
	fgets(d->label,N,fp);
	int i=0;
        char c;
        while((c=fgetc(fp))!=EOF){
		if(c!='\n')i++;
    	}

	//store the input sequence into memory
	fp=fopen(filename,"r");
	fgetc(fp);
	fgets(d->label,N,fp);
	int ii=0;
	d->n = i;
	d->s = (unsigned char*)malloc(sizeof(unsigned char)*i);
	while((c=fgetc(fp))!=EOF){
		if(c!='\n'){
			d->s[ii]=c;
			ii++;
		}
	}
	return d;
}

//allocate multiple queries in memory
query_stream *allocate_queries(query_stream * lib, char *filename, int *size, int num_pe, int dna){
	int invalid = 0;
	FILE *fp;
	if((fp = fopen(filename,"r"))==NULL){
		fprintf(stderr,"database file open error 1!!\n");
		exit(0);
	}

	FILE *tmp;
	if((tmp = fopen(filename,"r"))==NULL){
		fprintf(stderr,"database file open error 2!!\n");
		exit(0);
	}

	FILE *count;
	if((count = fopen(filename,"r"))==NULL){
		fprintf(stderr,"database file open error 2!!\n");
		exit(0);
	}

	//count the number of sequences in the database
	int num = 0;
	char c;
	char cc[N];
	while((fgets(cc,N,count))!=NULL){
		if(cc[0]=='>')num++;
	}
	int SS = num;

	//allocate the array
	if(lib!=NULL){
		for(int i=0;i<*size;i++){
			free(lib[i].label);
			free(lib[i].s);
			free(lib[i].inT);
		}
		free(lib);
	}
	lib = (query_stream*)malloc(sizeof(query_stream)*num);
	for(int i=0;i<num;i++){
		lib[i].s=NULL;
		lib[i].inT=NULL;
		lib[i].label=NULL;
	}

	//store the library in the array
	int ii;
	int iii;
	char s[N];
	int counter = 0;
	int padded_size=0;
	fgetc(tmp);
//	printf("Loading %d elements from %s \n",num,filename);

	int flag;
	c=fgetc(fp); // to remove the first '>'
	for(ii=0;ii<num;ii++){
		flag = 0;

		//collect information of the data
		counter=0;
		fgets(s,N,tmp);
		while((c=fgetc(tmp))!='>'){
			if(c==EOF)break;
			if(c!='\n')counter++;
		}
		padded_size=num_pe;

		//For library sequences, ssearch seems to replace O by K and U by C
		//In addition, we replace J by X (unknown) (don't know how ssearch handles this)
#ifdef BEST
		if(counter==num_pe){
#else
		if(counter <= num_pe){
#endif

			//store the data in array
			lib[ii].n = counter; // number of residues in the sequence
			lib[ii].n_padded = padded_size;
			lib[ii].label = (char*)malloc(sizeof(char)*N);
			fgets(lib[ii].label,N,fp);
			int label_len = strlen(lib[ii].label);
			for(int k=0;k<label_len;k++){
				if(lib[ii].label[k]=='\n')lib[ii].label[k]=' ';
			}
			lib[ii].s = (unsigned char*)malloc(sizeof(unsigned char)*counter);
			lib[ii].inT = (unsigned char*)malloc(sizeof(unsigned char)*padded_size);

			for(int k=0;k<padded_size;k++){
				lib[ii].inT[k]=(unsigned char)( dna ? 15 : 22);
			}
			iii=0;
			while((c = fgetc(fp))!='>'){

				if(dna==0){
					if(c==EOF){
						break;
					}
					else if(c=='U'){
						c='C';
					}
					else if(c=='O'){
						c='K';
					}
					else if(c=='J'){
						c='X';
					}
				}
				else{
					if(c==EOF){
						break;
					}
				}

				if(c!='\n'){
					lib[ii].s[iii] = c;
					lib[ii].inT[iii]= translate_for_dfe(c, dna);
					iii++;
				}
			}
		}
#ifdef BEST
		else if(counter >0 && (counter>num_pe || counter <num_pe)){

#else
		else if(counter>num_pe){
#endif
			invalid++;
			ii--;
			fgets(s,N,fp);
			while((c = fgetc(fp))!='>'){
				if(c==EOF)break;
			}
		}
		else{
		}
	}
	if(invalid >0) printf("Number of queries ignored : [%d]\n",invalid);
	SS-=invalid;
	*size=SS;
	fclose(fp);
	fclose(tmp);
	fclose(count);

#ifdef BEST
	char * best = ".opt";
	char * best_perf_queries = (char*)malloc(strlen(filename)+strlen(best)+1);
	sprintf(best_perf_queries, "%s%s", filename, best);
	write_database(best_perf_queries, lib, SS);
#endif
	return lib;
}


//Write a query_stream into a file
void write_database(char * filename, query_stream * lib, int size){
	FILE *fp;
	if((fp = fopen(filename,"w"))==NULL){
		fprintf(stderr,"Error while opening file\n");
		exit(0);
	}

	for(int i=0;i<size;i++){
		int j=0;
		fputc('>',fp);
		fputs(lib[i].label,fp );
		fputc('\n',fp);
		for(j=0;j<lib[i].n;j++){
			fputc(lib[i].s[j],fp);
			if(((j+1)%80)==0)fputc('\n',fp);
		}
		if(j%80)fputc('\n',fp);
	}
	fclose(fp);
}


//Allocate the database in memory in one AoS containing the sequences and their labels
//Parameter "align" is used to make sure the 16bits outputs are aligned on pci-e width
data *allocate_database(data *lib, char *filename, int *size, int align, int dna){
	int invalid = 0;
	FILE *fp;
	if((fp = fopen(filename,"r"))==NULL){
		fprintf(stderr,"database file open error 1!!\n");
		exit(0);
	}

	FILE *tmp;
	if((tmp = fopen(filename,"r"))==NULL){
		fprintf(stderr,"database file open error 2!!\n");
		exit(0);
	}

	FILE *count;
	if((count = fopen(filename,"r"))==NULL){
		fprintf(stderr,"database file open error 2!!\n");
		exit(0);
	}

	//count the number of sequences in the database
	int num = 0;
	char c;
	char cc[N];
	while((fgets(cc,N,count))!=NULL){
		if(cc[0]=='>')num++;
	}
	int padding = ((num%align)==0) ? 0 : align-(num%align);
	int SS = num + padding;

	//allocate the array
	if(lib!=NULL){
		for(int i=0;i<*size;i++){
			free(lib[i].label);
			free(lib[i].s);
		}
		free(lib);
	}
	lib = (data*)malloc(sizeof(data)*SS);
	for(int i=0;i<SS;i++){
		lib[i].label=NULL;
		lib[i].s=NULL;
	}

	//store the library in the array
	int iii;
	char s[N];
	int counter = 0;
	c=fgetc(tmp);

	c=fgetc(fp); // to remove the first '>'

	for(int ii=0;ii<num;ii++){
		//collect information of the data
		counter=0;
		fgets(s,N,tmp);
		while((c=fgetc(tmp))!='>'){
			if(c==EOF)break;
			if(c!='\n')counter++;
		}

		// For library sequences, ssearch seems to replace O by K and U by C
		// We also replace J by X (unknown)

		lib[ii].n = counter; // number of residues in the sequence
		lib[ii].label = (char*)malloc(sizeof(char)*N);
		fgets(lib[ii].label,N,fp);
		int label_len = strlen(lib[ii].label);
		for(int k=0;k<label_len;k++){
			if(lib[ii].label[k]=='\n')lib[ii].label[k]=' ';
		}
		lib[ii].s = (unsigned char*)malloc(sizeof(unsigned char)*counter);
		iii=0;

		while((c = fgetc(fp))!='>'){
			if(dna==0){
				if(c==EOF){
					break;
				}
				else if(c=='U'){
					c='C';
				}
				else if(c=='O'){
					c='K';
				}
				else if(c=='J'){
					c='X';
				}
			}
			else{
				if(c==EOF){
					break;
				}
			}

			if(c!='\n'){
				lib[ii].s[iii] = c;
				iii++;
			}
		}
	}
	for(int ii=num;ii<num+padding;ii++){
		lib[ii].n=lib[num-1].n;
		lib[ii].label=(char*)malloc(sizeof(char)*N);
		lib[ii].label=strncpy(lib[ii].label, lib[num-1].label, N);
		lib[ii].s = (unsigned char*)malloc(sizeof(unsigned char)*lib[ii].n);
		lib[ii].s = (unsigned char*)memcpy(lib[ii].s, lib[num-1].s, lib[ii].n);
	}
	if(invalid > 0)	printf("Number of sequences ignored = [%d]\n",invalid);
	SS-=invalid;
	*size=SS;

	fclose(fp);
	fclose(tmp);
	fclose(count);

	return lib;
}


//Interlace partitions
lib_stream* max_integrate_library_stream(lib_stream *s , lib_stream *lls,int loopLength,int cards, int wordLength){
	//use wordLength to add padding to database sequence if needed
	wordLength=wordLength;

	// Allocate stream
	s = (lib_stream*)malloc(sizeof(lib_stream)*cards);
	for(int k=0;k<cards;k++){
		s[k].label=NULL;
		s[k].inS=NULL;
		s[k].vflag=NULL;
		s[k].Sflag=NULL;
		s[k].twobitflag=NULL;
		s[k].output=NULL;
		s[k].which=NULL;
		s[k].cycles = lls[0].cycles;
		s[k].n = lls[0].n;
		s[k].tn = lls[0].tn;
		s[k].num = lls[0].num * loopLength;
		s[k].tnum = lls[0].tnum * loopLength;
		s[k].inS = (unsigned char*)realloc(s[k].inS,sizeof(unsigned char) * s[k].tn * loopLength);

		//Interlace sequences
		int counter = 0;
		for(int i=0;i<lls[0].tn;i++){
			for(int j=k*loopLength;j<(k+1)*loopLength;j++){
				s[k].inS[counter] = lls[j].inS[i];
				counter++;
			}
		}

		int c[loopLength];
		int count[loopLength];
		for(int i=0;i<loopLength;i++){
			c[i] = count[i] = 0;
		}
		int hoge = 0;
		s[k].vflag = (int*)malloc(sizeof(int)*(s[k].tnum));

		for(int i=0;i<lls[k].tn;i++){
			for(int j=k*loopLength;j<(k+1)*loopLength;j++){
				int jloc= j%loopLength;
				if( c[jloc] == i && count[jloc]<lls[j].tnum){
					s[k].vflag[hoge++] = lls[j].vflag[count[jloc]];
					c[jloc] += lls[j].vflag[count[jloc]];
					count[jloc]++;
				}
			}

		}
		for(int i=hoge;i<s[k].tnum;i++){
			s[k].vflag[i] = 1000000000;
		}

		//Interlace flags
		s[k].Sflag = (unsigned char*)malloc(sizeof(unsigned char)*s[k].tn*loopLength);
		for(int i=0;i<loopLength;i++){
			c[i] = count[i] = 0;
		}
		for(int i=0;i<lls[k].tn;i++){
			for(int j=k*loopLength;j<(k+1)*loopLength;j++){
				int jloc = j%loopLength;
				if(c[jloc]==0 && count[jloc]< lls[j].tnum ){
					c[jloc] = lls[j].vflag[count[jloc]] - 1 ;
					count[jloc]++;
					s[k].Sflag[i*loopLength+jloc] = 1;

				}else if(c[jloc]==1){
					s[k].Sflag[i*loopLength+jloc] = 2;
					c[jloc]--;

				}else{
					s[k].Sflag[i*loopLength+jloc] = 0;
					c[jloc]--;
				}
			}
		}
		int sktn4 = s[k].tn / 4;
		s[k].ttn = sktn4;
		while(s[k].ttn%8!=0){
			s[k].ttn++;
		}

		//Converts to 2 bits flag
		s[k].twobitflag = (unsigned char*)realloc(s[k].twobitflag,sizeof(unsigned char) * s[k].ttn * loopLength);
		for(int i=0;i<sktn4*loopLength;i++){
			s[k].twobitflag[i] = ((s[k].Sflag[i*4] & 0x3) |
						(s[k].Sflag[i*4+1] & 0x3)<<2 |
						(s[k].Sflag[i*4+2] & 0x3)<<4 |
						(s[k].Sflag[i*4+3] & 0x3)<<6 );
		}

		// Allocate output
		s[k].output = (int*)realloc(s[k].output,sizeof(int)*s[k].tnum);
		s[k].which = (int*)realloc(s[k].which,sizeof(int)*s[k].tnum);
		// Count the number of output
		s[k].number_of_output = 0;
		for(int i=k*loopLength;i<(k+1)*loopLength;i++){
			s[k].number_of_output += lls[i].num;
		}
	}

	return s;
}


//Divide a library into partitions
int max_create_library_stream(lib_stream ** p_s, int number, data *lib, int size, int dna){

	int ii,jj;
	//allocate stream
	lib_stream *s;
	s = (lib_stream*)malloc(sizeof(lib_stream)*number);
	for(int i=0;i<number;i++){
		s[i].label=NULL;
		s[i].inS=NULL;
		s[i].vflag=NULL;
		s[i].Sflag=NULL;
		s[i].twobitflag=NULL;
		s[i].output=NULL;
		s[i].which=NULL;
	}

	int n = 0; //number of characters

	//create data for S and flag
	for(ii=0;ii<size;ii++){
		n += lib[ii].n;
	}

	int ne[number];
	int nc[number];

	for(ii=0;ii<number;ii++){
		ne[ii] = 0;
		nc[ii] = 0;
	}
		
	int tne;
	int tnc;

	int emax = 0;
	int cmax = 0;

	int tmp = 0;

	ii=0;

	while(ii<size){
		tne = 0;
		tnc = 0;
		while(1){
			tne++;
			tnc = tnc + lib[ii].n;
			ii++;
			if(((tnc >= (int)(n/number)) &  (tne%4 == 0)) || ii==size )
				break;
		}
		ne[tmp] = tne;
		nc[tmp] = tnc;
		tmp++;
	}

	//emax = largest partition in number of element
	//cmax = largest partition in number of residues
	for(ii=0;ii<number;ii++){
		if(emax<ne[ii]) emax = ne[ii];
		if(cmax<nc[ii]) cmax = nc[ii];
	}

	unsigned char *temp;

	//tcmax = largest partition in number of residues + padding(8)
	//temp is large enough to hold any partition
	int tcmax = cmax;
	while(tcmax%8!=0){
		tcmax++;
	}

	temp  = (unsigned char*)malloc(sizeof(unsigned char)*tcmax);

	//temax = largest partition in number of element + padding(8)
	int temax = emax;
	while(temax%8!=0){
		temax++;
	}


	int counter = 0;
	int init = 0;
	int end = 0;
	int i;
	int c = 0;
	for(i=0;i<number;i++){
		init = end;
		end = end + ne[i];
		c = 0;
		counter = 0;

		s[i].vflag = (int*)realloc(s[i].vflag,sizeof(int)*temax);
		//initializing
		for(ii=0;ii<temax;ii++){
			s[i].vflag[ii] = 1000000000;
		}

		//copy the data
		for(ii=init;ii<end;ii++){

			s[i].vflag[counter] = lib[ii].n;
			counter++;
			for(jj=0;jj<lib[ii].n;jj++){
				temp[c] = lib[ii].s[jj];
				c++;
			}
		}
		s[i].inS = (unsigned char*)malloc(tcmax*sizeof(unsigned char));
		s[i].inS = convert(s[i].inS, temp,nc[i],tcmax,dna);
		s[i].n = nc[i];
		s[i].tn = tcmax;
		s[i].cycles = cmax;
		//end creating data for S
		s[i].size = size;
		s[i].num = ne[i];
		s[i].tnum = temax;
		s[i].output = (int*)malloc(sizeof(int)*temax);
	}
	*p_s=s;

	return n;
}


//Get the n higher sores of lib
void get_higher_scores(int p, int **p_index, int **p_sw, data *lib, int n) {
	int *index = (int *) realloc((*p_index), (p + 1) * sizeof(int));
	int *bestsw = (int *) realloc((*p_sw), (p + 1) * sizeof(int));

	for (int i = 0; i < p; i++) {
		bestsw[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		if (bestsw[p - 1] < lib[i].sw) {
			for (int j = p - 1; j >= 0; j--) {
				if (bestsw[j] <= lib[i].sw) {
					bestsw[j + 1] = bestsw[j];
					bestsw[j] = lib[i].sw;
					index[j + 1] = index[j];
					index[j] = i;
				}
			}
		}
	}

	(*p_sw) = bestsw;
	(*p_index) = index;
}

//dna_conversion gives the index of dna_tab for a given nucleotide between A=0 and Z=25
//						A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, unknown/padding
//int to_dna_index[]={	0,12, 1,13,16,16, 2,14,16,16, 6,16, 9, 4,16,16,16,11, 7, 3, 5,15,10,16, 8,16, 16};
int to_dna_index[]={	0,14, 1,11,15,15, 2,12,15,15,10,15, 7,15,15,15,15, 5, 9, 3, 4,13, 8,15, 6,15, 15};

//dna_bit gives the encoding of a nucleotide for the dfe
//The encoding follows this rule :
//msb on the left : A|C|G|T|padding
//When the bit is set to 1, the nucleotide is a possible match
//That way, the code is compatible with letters such as D = G or A or T without the use of a scoring matrix.

//						  A, C, G, T, N, U, K, S, Y, M, W, R, B, D, H, V, unknown/padding
unsigned char dna_bit[]={ 16, 8, 4, 2,30, 2, 6,12,10,24,18,20,14,22,26,28, 1};

//a scoring matrix for dna would have been a 2bits values matrix match/mismatch/padding
//size = (16+1)x(16+1)
//bonus bit to encode padding
//1 for possible match
//-1 for mismatch
//0 for padding

//the function dna_bit_match emulates this matrix for encoded nucleotides as above
int dna_bit_match(unsigned char t, unsigned char s, int match, int mismatch){
	return ((t&1)|(s&1)) ? 0 : ((t&s)>0? match : mismatch);
}

//Converts a nucleotide character into an unsigned char in [0;17] usable by the dfe
unsigned char translate_for_dfe(char t, int dna){
	int upperCaseShift = 'a'-'A';
	int range = 'Z'-'A';
	int scalingShift = 'A';
	if(t>'Z') t-=upperCaseShift;
	t-=scalingShift;
	if(t<0 || t>range){
		t=range+1; //unknown/padding
	}
	return (dna==1) ? to_dna_index[(int)t] : to_aa_index[(int)t];
}

// Converts a (valid) character to its index in [0;tableWidth-1] for the usual scoring matrix order (ARND..)
void translate(unsigned char *res, const char *s, int dna){
	int t = (int) *s;
	int upperCaseShift = 'Z'-'A';
	int scalingShift = 'A';
	if(t>'Z') t-=upperCaseShift;
	t-=scalingShift;
	if(t<0 || t>upperCaseShift) t=upperCaseShift+1; //unknown/padding

	*res=dna ? dna_bit[to_dna_index[t]] : to_aa_index[t];
}

//for regular characters as arguments :
int dna_match(char t, char s, int match, int mismatch){
	//s and t are uppercased and shifted to values between 0 and 25
	int upperCaseShift = 'a'-'A';
	int scalingShift = 'A';
	if(t>'Z') t-=upperCaseShift;
	if(s>'Z') s-=upperCaseShift;
	t-=scalingShift;
	s-=scalingShift;

	//if they are out of bound, they are set to shiftedZ = 'Z'-'A' = upperCaseShift
	if(t<0 || t>upperCaseShift) t=upperCaseShift;
	if(s<0 || s>upperCaseShift) s=upperCaseShift;

	//conversion to bit encoded nucleotides
	unsigned char ut = dna_bit[to_dna_index[(int)t]];
	unsigned char us = dna_bit[to_dna_index[(int)s]];

	//bitwise match/mismatch/padding
	return(dna_bit_match(ut,us,match,mismatch));
}



// Converts a (valid) string to its array of indexes in [0;tableWidth-1] for the usual scoring matrix order (ARND..)
unsigned char * convert(unsigned char *d, unsigned char *s,int n,int tn, int dna){
	int i;
	for(i=0;i<tn;i++){
		d[i] = 0;
	}
	for(i=0;i<n;i++){
		d[i]= translate_for_dfe(s[i], dna);
	}
	for(i=n;i<tn;i++){
		d[i]=dna ? 15 : 22;//15 for dfe_dna is padding : 22 for dfe_proteins is 'X' and scores negatively with everything and therefore can be used as padding
	}
	return d;
}


//return the value of the substitution matrix
int sub(char ss,char tt, int dna){
	char s=tt;
	char t=ss;
	if(dna==0){
		if(s=='U'||s=='O'||s=='J'){
			s='*';
			fprintf(stderr,"fixed ...\n");
			//sleep(1);
		}
		if(t=='U'||t=='O'||t=='J'){
			t='*';
			fprintf(stderr,"fixed ...\n");
		}
	}

	unsigned char si;
	unsigned char ti;

	translate(&si,&s,dna);
	translate(&ti,&t,dna);

	int index = (int)(TABLE_WIDTH*si+ti);
	return BL62[index];

}
