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

import com.maxeler.maxcompiler.v2.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v2.kernelcompiler.KernelParameters;
import com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.core.Count.Counter;
import com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.core.Count.Params;
import com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.core.Count.WrapMode;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEType;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEVar;
import com.maxeler.maxcompiler.v2.utils.MathUtils;


public class SmithKernel extends Kernel {

	public SmithKernel(KernelParameters parameters, SmithParameters params) {
		super(parameters);

		// Kernel initialisation
		kernelInit(params);

		// Scalar inputs
		DFEVar n 		= io.scalarInput("n", 				counterType);
		DFEVar open 		= io.scalarInput("open", 			firstPEType);
		DFEVar extend 	= affine ? io.scalarInput("extend",	firstPEType) : null;

		// Control
		Control ctrl 	= new Control(n);

		// Initial values
		DFEVar initE 	= affine ? constant.var(firstPEType, 0) : null;
		DFEVar initSW 	= constant.var(firstPEType, 0);
		DFEVar initVv 	= constant.var(firstPEType, 0);
		DFEVar initMinusOpen = open;

		// Inputs
		DFEVar inputS 	= io.input("inS", inputcharType,	ctrl.input).cast(dfeUInt(charBits));
		DFEVar Sflag 	= io.input("inhflag", flagType,		ctrl.input).cast(flagType);

		// Chained Processing Elements
		DataStream dataPE = new DataStream(inputS, initE, initVv, Sflag, initSW, initMinusOpen, open, extend);
		for (int i = 0; i < numPE; i++) {
			dataPE = makePE(i, dataPE);
		}

		// Processing Element Outputs
		DFEVar SW 		= stream.offset(dataPE.SW, 		loopLength);
		DFEVar outSflag 	= stream.offset(dataPE.Sflag, 	loopLength);

		// Hold the max SW value
		DFEVar lastoldsw = lastPEType.newInstance(this);
		DFEVar oldsw 	= outSflag.eq(1) ? 0 : lastoldsw;
		DFEVar max 		= SW > oldsw ? SW : oldsw;
		DFEVar oldswOffset = stream.offset(max, -loopLength);
		lastoldsw <== oldswOffset;

		// Bitstream outputs
		DFEVar output = outSflag.eq(2) & ctrl.output;
		io.output("SW", 	max.cast(integerType)				, integerType, output );
		io.output("which", 	ctrl.cslowCount.cast(integerType)	, integerType, output );
	}




	// Processing Element Code (PE)

	// A processing element computes the V value of one cell using the data from the previous PE.
	// Processing elements follow the classic diagonal organization.

	// The query sequence T is set by scalar input, each PE is attributed one query character.
	// The database sequence S is stream through the PE.
	// Scoring matrix used are standard (BLOSUM62 for amino acid, FASTA's default DNA matrix for nucleotides)

	// The Smith-Waterman score is obtained by keeping the maximum V value.
	// V and the SW value are then passed to the next PE with S.
	private DataStream makePE(int pe, DataStream prev) {
		optimization.pushPipeliningFactor(pipeliningFactor);

		// Optimal type to minimize bit width
		int swBits= (int)Math.ceil(Math.log(maxVar*(pe+1))/Math.log(2)) +1;
		DFEType PEType = dfeInt(swBits>minBits ? swBits : minBits);

		// not to make a too large fan out
		DFEVar open 		= optimization.pipeline(prev.open.cast(PEType));
		DFEVar extend 	= affine ? optimization.pipeline(prev.extend.cast(PEType)) : null;

		// Init flag
		DFEVar initFlag = prev.Sflag.eq(1);

		// Input from stream
		DFEVar inf = affine ? PEType.newInstance(this) : null;
		DFEVar inVh = PEType.newInstance(this);

		// Initialization of stream
		DFEVar f = affine ? (initFlag ? 0 : inf) : null;
		DFEVar Vh = initFlag ? 0 : inVh;
		DFEVar Vdiag = initFlag ? 0 : prev.Vdiag;

		// Vdiag + score
		DFEVar T = io.scalarInput("T"+pe, dfeUInt(charBits));
		DFEVar score = mem.rom(T#prev.S,dfeInt(MathUtils.bitsToRepresent(maxVar)+1), dna ? dnaScoring : BLOSUM62);
		DFEVar V = Vdiag.cast(PEType) + score.cast(PEType);

		// E = affine ? max(Eup-extend,Vup-open) : Vup-open
		DFEVar tE2 	= affine ? (prev.E.cast(PEType) + extend) : null;
		DFEVar E   	= affine ? (prev.MinusOpen.cast(PEType) > tE2 ? prev.MinusOpen.cast(PEType) : tE2) : prev.MinusOpen.cast(PEType);

		// F = affine ? max(Fleft-extend,Vleft-open) : Vleft-open
		DFEVar tF2 	= affine ? (f + extend) : null;
		DFEVar F 	= affine ? (Vh > tF2 ? Vh : tF2) : Vh;

		// Vfinal
		DFEVar ef = E > F ? E : F;
		DFEVar V0 = V > 0 ? V : 0;
		DFEVar Vfinal = ef > V0 ? ef : V0;

		// MinusOpen
		DFEVar MinusOpen = Vfinal + open;

		// SW
		DFEVar SW = prev.SW.cast(PEType) > Vfinal ? prev.SW.cast(PEType) : Vfinal;

		optimization.popPipeliningFactor();

		// Stream offsets
		DFEVar initOffset 		= stream.offset(prev.Sflag, -loopLength);
		DFEVar SOffset 			= stream.offset(prev.S, -loopLength);
		DFEVar EOffset 			= stream.offset(E, -loopLength);
		DFEVar VfinalOffset 		= stream.offset(Vfinal, -2 * loopLength);
		DFEVar MinusOpenOffset 	= stream.offset(MinusOpen, -loopLength);
		DFEVar SWOffset 			= stream.offset(SW, -loopLength);

		// Local loop backs
		if(affine) inf <== stream.offset(F, -loopLength);
		inVh <== MinusOpenOffset;

		DataStream d = new DataStream(SOffset, EOffset, VfinalOffset, initOffset, SWOffset, MinusOpenOffset, open, extend);
		return d;
	}


	// Counters and input/output control
	private class Control{
		final DFEVar cslowCount;
		final DFEVar col;

		DFEVar input;
		DFEVar output;

		Control(DFEVar n) {
			// Cslow counter
			Params paramsCslow = control.count.makeParams(32).withMax(loopLength).withWrapMode(WrapMode.COUNT_LT_MAX_THEN_WRAP);
			Counter CslowCounter = control.count.makeCounter(paramsCslow);
			cslowCount = CslowCounter.getCount();

			// Column counter
			Params paramsCol = control.count.makeParams(32).withEnable(CslowCounter.getWrap()).withMax(numPE+n-1).withWrapMode(WrapMode.COUNT_LT_MAX_THEN_WRAP);
			Counter colCounter = control.count.makeCounter(paramsCol);
			col = colCounter.getCount();

			input = col < n;
			output = col >= numPE;
		}
	}


	// Amino Acids scoring matrix
	// BLOSUM62 with padding to allow bit concatenation instead of T*tableWidth+S
	double BLOSUM62[] = {
			 4,-1,-2,-2, 0,-1,-1, 0,-2,-1,-1,-1,-1,-2,-1, 1, 0,-3,-2, 0,-2,-1, 0,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-1, 5, 0,-2,-3, 1, 0,-2, 0,-3,-2, 2,-1,-3,-2,-1,-1,-3,-2,-3,-1, 0,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-2, 0, 6, 1,-3, 0, 0, 0, 1,-3,-3, 0,-2,-3,-2, 1, 0,-4,-2,-3, 3, 0,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-2,-2, 1, 6,-3, 0, 2,-1,-1,-3,-4,-1,-3,-3,-1, 0,-1,-4,-3,-3, 4, 1,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			 0,-3,-3,-3, 9,-3,-4,-3,-3,-1,-1,-3,-1,-2,-3,-1,-1,-2,-2,-1,-3,-3,-2,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-1, 1, 0, 0,-3, 5, 2,-2, 0,-3,-2, 1, 0,-3,-1, 0,-1,-2,-1,-2, 0, 3,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-1, 0, 0, 2,-4, 2, 5,-2, 0,-3,-3, 1,-2,-3,-1, 0,-1,-3,-2,-2, 1, 4,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			 0,-2, 0,-1,-3,-2,-2, 6,-2,-4,-4,-2,-3,-3,-2, 0,-2,-2,-3,-3,-1,-2,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-2, 0, 1,-1,-3, 0, 0,-2, 8,-3,-3,-1,-2,-1,-2,-1,-2,-2, 2,-3, 0, 0,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-1,-3,-3,-3,-1,-3,-3,-4,-3, 4, 2,-3, 1, 0,-3,-2,-1,-3,-1, 3,-3,-3,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-1,-2,-3,-4,-1,-2,-3,-4,-3, 2, 4,-2, 2, 0,-3,-2,-1,-2,-1, 1,-4,-3,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-1, 2, 0,-1,-3, 1, 1,-2,-1,-3,-2, 5,-1,-3,-1, 0,-1,-3,-2,-2, 0, 1,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-1,-1,-2,-3,-1, 0,-2,-3,-2, 1, 2,-1, 5, 0,-2,-1,-1,-1,-1, 1,-3,-1,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-2,-3,-3,-3,-2,-3,-3,-3,-1, 0, 0,-3, 0, 6,-4,-2,-2, 1, 3,-1,-3,-3,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-1,-2,-2,-1,-3,-1,-1,-2,-2,-3,-3,-1,-2,-4, 7,-1,-1,-4,-3,-2,-2,-1,-2,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			 1,-1, 1, 0,-1, 0, 0, 0,-1,-2,-2, 0,-1,-2,-1, 4, 1,-3,-2,-2, 0, 0, 0,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			 0,-1, 0,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-2,-1, 1, 5,-2,-2, 0,-1,-1, 0,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-3,-3,-4,-4,-2,-2,-3,-2,-2,-3,-2,-3,-1, 1,-4,-3,-2,11, 2,-3,-4,-3,-2,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-2,-2,-2,-3,-2,-1,-2,-3, 2,-1,-1,-2,-1, 3,-3,-2,-2, 2, 7,-1,-3,-2,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			 0,-3,-3,-3,-1,-2,-2,-3,-3, 3, 1,-2, 1,-1,-2,-2, 0,-3,-1, 4,-3,-2,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-2,-1, 3, 4,-3, 0, 1,-1, 0,-3,-4, 0,-3,-3,-2, 0,-1,-4,-3,-3, 4, 1,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-1, 0, 0, 1,-3, 3, 4,-2, 0,-3,-3, 1,-1,-3,-1, 0,-1,-3,-2,-2, 1, 4,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			 0,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2, 0, 0,-2,-1,-1,-1,-1,-1,-4, 0, 0, 0, 0, 0, 0, 0, 0,
			-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4, 1, 0, 0, 0, 0, 0, 0, 0, 0
	};


	  // A   C   G   T   U   R   Y   M   W   S   K   D   H   V   B   N   X
	double dnaScoring[] = {
	     5, -4, -4, -4, -4,  2, -1,  2,  2, -1, -1,  1,  1,  1, -2, -1, //X same as N : removed to keep a 16x16 matrix
	    -4,  5, -4, -4, -4, -1,  2,  2, -1,  2, -1, -2,  1,  1,  1, -1,
	    -4, -4,  5, -4, -4,  2, -1, -1, -1,  2,  2,  1, -2,  1,  1, -1,
	    -4, -4, -4,  5,  5, -1,  2, -1,  2, -1,  2,  1,  1, -2,  1, -1,
	    -4, -4, -4,  5,  5, -1,  2, -1,  2, -1,  2,  1,  1, -2,  1, -1,
	     2, -1,  2, -1, -1,  2, -2, -1,  1,  1,  1,  1, -1,  1, -1, -1,
	    -1,  2, -1,  2,  2, -2,  2, -1,  1,  1,  1, -1,  1, -1,  1, -1,
	     2,  2, -1, -1, -1, -1, -1,  2,  1,  1, -1, -1,  1,  1, -1, -1,
	     2, -1, -1,  2,  2,  1,  1,  1,  2, -1,  1,  1,  1, -1, -1, -1,
	    -1,  2,  2, -1, -1,  1,  1,  1, -1,  2,  1, -1, -1,  1,  1, -1,
	    -1, -1,  2,  2,  2,  1,  1, -1,  1,  1,  2,  1, -1, -1,  1, -1,
	     1, -2,  1,  1,  1,  1, -1, -1,  1, -1,  1,  1, -1, -1, -1, -1,
	     1,  1, -2,  1,  1, -1,  1,  1,  1, -1, -1, -1,  1, -1, -1, -1,
	     1,  1,  1, -2, -2,  1, -1,  1, -1,  1, -1, -1, -1,  1, -1, -1,
	    -2,  1,  1,  1,  1, -1,  1, -1, -1,  1,  1, -1, -1, -1,  1, -1,
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	};


	private void kernelInit(SmithParameters params){
		this.loopLength = params.getLoopLength()==0 ? (params.isLinear() ? 6 : 8) : params.getLoopLength();
		this.dnaMatrix	= params.useDnaMatrix();
		this.matchScore = params.getMatch();
		this.misMatchScore = params.getMisMatch();

		this.affine 	= !params.isLinear();
		this.dna 		= params.isDna();
		this.numPE 		= params.getNumPE();
		this.maxVar 	= params.getMaxVariation();
		int absMatch 	= Math.abs(params.getMatch());
		int absMisMatch = Math.abs(params.getMisMatch());
		this.highScore 	= (absMatch > absMisMatch ? absMatch : absMisMatch);
		this.charBits 	= params.isDna() ? 4 : 5;
		this.pipeliningFactor = params.getPipeliningFactor();


		int swBits 		= (int)Math.ceil(Math.log(maxVar)/Math.log(2)) +1;
		int lastSwBits	= (int)Math.ceil(Math.log(maxVar*numPE)/Math.log(2)) +1;
		firstPEType 	= dfeInt(swBits>minBits ? swBits : minBits);
		lastPEType 		= dfeInt(lastSwBits>minBits ? lastSwBits : minBits);

	}


	int loopLength;
	int numPE;
	int maxVar;
	int highScore;
	int minBits=5;
	int charBits;
	int matchScore;
	int misMatchScore;
	double pipeliningFactor;
	boolean affine;
	boolean dna;
	boolean dnaMatrix;

	DFEType firstPEType;
	DFEType lastPEType;

	// Types definition
	final DFEType minType 		= dfeInt(minBits);
	final DFEType counterType 	= dfeUInt(32);
	final DFEType flagType 		= dfeUInt(2);
	final DFEType integerType 	= dfeInt(32);
	final DFEType inputcharType 	= dfeUInt(8);


}
