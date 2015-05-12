/*********************************************************************
 * Maxeler Technologies: Smith Waterman Demo                         *
 *                                                                   *
 * Version: 1.3                                                      *
 * Date:    30 July 2013                                             *
 *                                                                   *
 * DFE code source file                                              *
 *                                                                   *
 *********************************************************************/

package com.maxeler.publicdemos.smithwaterman;

import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEVar;

public class DataStream{
	DFEVar S;
	DFEVar E;
	DFEVar Vdiag;
	DFEVar SW;
	DFEVar open;
	DFEVar extend;

	DFEVar match;
	DFEVar mismatch;

	DFEVar MinusOpen;
	DFEVar Sflag;

	public DataStream(DFEVar inS, DFEVar inE, DFEVar inVdiag, DFEVar inSflag, DFEVar inSW, DFEVar inMinusOpen, DFEVar inopen, DFEVar inextend){
		S = inS;				// Database
		E = inE;				// Gap extension (affine SW)
		Vdiag = inVdiag;		// V from 'upper left diagonal' : previous PE, -2*loopLength of offset
		SW = inSW;				// Smith Waterman value
		open = inopen;			// open penalty
		extend = inextend;		// extend penalty (affine SW)

		MinusOpen = inMinusOpen;// V-open instead of V to factorize subtraction
		Sflag = inSflag;		// Flag at the end/beginning of a database sequence
	}

}
