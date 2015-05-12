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


import static com.maxeler.maxcompiler.v2.managers.standard.IOLink.IODestination.LMEM_LINEAR_1D;
import static com.maxeler.maxcompiler.v2.managers.standard.Manager.link;

import com.maxeler.maxcompiler.v2.managers.standard.IOLink.IODestination;
import com.maxeler.maxcompiler.v2.managers.standard.Manager;
import com.maxeler.maxcompiler.v2.managers.standard.Manager.IOType;


public class SmithBuilder {

	public static void main(String[] args) {

		SmithParameters params = new SmithParameters(args);
		Manager m = new Manager(params);
		m.setKernel( new SmithKernel(m.makeKernelParameters("SmithKernel"), params) );

		m.setEnableStreamStatusBlocks(false);

		if(params.getLmem()){
			m.setIO(link("inS", LMEM_LINEAR_1D), link("inhflag", LMEM_LINEAR_1D), link("SW", IODestination.CPU), link("which",IODestination.CPU));
		}
		else{
			m.setIO(IOType.ALL_CPU);
		}
		m.setClockFrequency(params.getFrequency());
		m.getBuildConfig().setMPPRParallelism(params.getMPPRThreads());
		m.getBuildConfig().setMPPRCostTableSearchRange(params.getMPPRStartCT(), params.getMPPREndCT());
		m.getBuildConfig().setMPPRRetryNearMissesThreshold(params.getMPPRRetryThreshold());
		m.getBuildConfig().setEnableTimingAnalysis(true);
//		m.getBuildConfig().setBuildEffort(BuildConfig.Effort.HIGH)s;
		m.addMaxFileConstant("loopLength", params.getLoopLength()==0 ? (params.isLinear()?6:8) : params.getLoopLength());
		m.addMaxFileConstant("numPE", params.getNumPE());
		m.addMaxFileConstant("lmem", params.getLmem() ? 1 : 0);
		m.addMaxFileConstant("linear", params.isLinear() ? 1 : 0);
		m.addMaxFileConstant("dna", params.isDna() ? 1 : 0);

		m.addMaxFileConstant("mismatch", params.isDna() ? 1 : 0);
		m.addMaxFileConstant("match", params.isDna() ? 1 : 0);

		m.addMaxFileConstant("useDnaMatrix", params.useDnaMatrix() ? 1 : 0);
		m.addMaxFileConstant("tableWidth", params.getTableWidth());
		m.addMaxFileConstant("maxVar",params.getMaxVariation());

		params.logParameters(m);

		m.build();
	}

}
