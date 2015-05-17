/*********************************************************************
 * Maxeler Technologies: Smith Waterman Demo                         *
 *                                                                   *
 * Version: 1.3                                                      *
 * Date:    30 July 2013                                             *
 *                                                                   *
 * Common library code source file                                   *
 *                                                                   *
 *********************************************************************/

#ifndef IO_H
#define IO_H

#define MAX_DISPLAY_LENGTH 80

typedef struct {
	char *label;		//label information of the data
	unsigned char *s;	//sequence
	int n;				//number of residues
	int n_padded;		//number of residues + padding
	int sw;				//store the result of sw
	int p;
}data;

typedef struct{
	char *label;		//label of the protein or dna sequence
	unsigned char *s;	//sequence in plain characters
	unsigned char *inT;	//sequence translated for dfe
	int n;				//sequence length
	int n_padded;		//sequence length + padding
}query_stream;

typedef struct{
	char *label;
	unsigned char *inS;
	int *vflag;
	unsigned char *Sflag;
	unsigned char *twobitflag;
	int *output;
	int *which;
	int n;		//number of residues+padding in the partition
	int tn;		//greatest number of residues in all partitions
	int ttn;	//tn/4 : number of Bytes to encode twobitsflags
	int num;	//number of elements in the partition
	int tnum;	//greatest number of elements in all partitions
	int cycles;	//greatest number of residues in all partitions
	int number_of_output;
	int size;
}lib_stream;


// Allocate one query sequence
data *allocate_query(char *filename);

// Allocate an AoS of queries
query_stream *allocate_queries(query_stream * query, char *filename, int *size, int num_pe, int dna);

// Write a query_stream into a file
void write_database(char * filename, query_stream * lib, int size);

// Allocate the database on memory
data *allocate_database(data * lib, char *filename, int *size, int align, int dna);

// Divide the database in partitions
int max_create_library_stream(lib_stream ** p_s, int number, data *lib, int size, int dna);

// Interlace partitions
lib_stream* max_integrate_library_stream(lib_stream *p_s , lib_stream *lls,int loopLength,int cards, int wordLength);

// Translate s into a encoded sequence for the DFE
unsigned char *convert(unsigned char *d,unsigned char *s,int n,int tn, int dna);

// Bitwise match for dna
int dna_bit_match(unsigned char t, unsigned char s, int match, int mismatch);

// Translate a single character
unsigned char translate_for_dfe(char t, int dna);

// Get the score for a dna alignment
int dna_match(char t, char s, int match, int mismatch);

// Get the n higher scores of lib
void get_higher_scores(int p, int **p_index, int **p_sw, data *lib, int n);

// Score given by the substitution matrix
int sub(char s,char t, int dna);

// Translate s
void translate(unsigned char *res, const char *s,int dna);

#endif 
