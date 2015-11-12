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

import com.maxeler.maxcompiler.v2.build.EngineParameters;


public class SmithParameters extends EngineParameters {
		public SmithParameters(String[] args) { super(args); }

		public int getNumPE() { return getParam("numPE"); }

		public int getMaxVariation() {return getParam("maxVariation");}

		public int getMatch() { return getParam("match");}

		public int getMisMatch() { return getParam("mismatch");}

		public boolean isLinear() {return getParam("linear");}

		public boolean isDna() {return getParam("dna");}

		public boolean useDnaMatrix(){return getParam("useDnaMatrix");}

		public String getTag() {return getParam("tag");}

		public int getLoopLength() { return getParam("loopLength"); }

		public int getFrequency() { return getParam("frequency"); }

		public double getPipeliningFactor() { return getParam("pipeliningFactor"); }

		public int getTableWidth() {return getParam("tableWidth");}

		public boolean getLmem() {return getParam("lmem");}

		public boolean isSimulation() {return getParam("target") == Target.DFE_SIM;}

		@Override
		protected void declarations() {
			declareParam("tag"				, DataType.STRING			, "");
			declareParam("target"			, Target.class				, Target.DFE);
			declareParam("maxFileName"		, DataType.STRING			, "SmithWaterman");

			declareParam("tableWidth"		, DataType.INT				, 24);
			declareParam("loopLength"		, DataType.INT				, 0); //0 = auto
			declareParam("numPE"			, DataType.INT				, 512);

			declareParam("simulation"		, DataType.BOOL				, false);
			declareParam("lmem"				, DataType.BOOL				, true);
			declareParam("dna"				, DataType.BOOL				, true);
			declareParam("linear"			, DataType.BOOL				, true);
			declareParam("useDnaMatrix" 	, DataType.BOOL				, true);

			declareParam("match"			, DataType.INT				, 5);	//*	Values for the		*//
			declareParam("mismatch"			, DataType.INT				, -4);	//* dna scoring matrix	*//

			declareParam("maxVariation" 	, DataType.INT				, 5);	// Absolute value | Determine the bit growth

			declareParam("frequency"		, DataType.INT				, 150);
			declareParam("pipeliningFactor"	, DataType.DOUBLE			, 1.0);

			declareParam("MPPRStartCT"		, DataType.INT				, 1);
			declareParam("MPPREndCT"		, DataType.INT				, 20);
			declareParam("MPPRThreads"		, DataType.INT				, 1);
		}

		@Override
		protected void deriveParameters() { }

		@Override
		public String getBuildName() {
			StringBuilder buildName = new StringBuilder(getMaxFileName() + "_" + getTarget().toString());

			if(isDna()){
				buildName.append("_n");
			}
			else{
				buildName.append("_p");
			}

			if(isLinear()){
				buildName.append("_lin");
			}
			else{
				buildName.append("_aff");
			}

			buildName.append("_" + getNumPE() + "PE");
			buildName.append("_" + getFrequency() + "MHz");

			buildName.append("_" + getDFEModel().toString() + "_" + getTarget().toString());

			if(getPipeliningFactor()>0.0){
				buildName.append("_" + String.format("%d", (int)(100.0*getPipeliningFactor())) + "PF");
			}



			return buildName.toString();
		}

		@Override
		protected void validate() { }

	}
