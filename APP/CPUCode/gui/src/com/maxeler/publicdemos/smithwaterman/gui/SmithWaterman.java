/*********************************************************************
 * Maxeler Technologies: Smith Waterman Demo                         *
 *                                                                   *
 * Version: 1.3                                                      *
 * Date:    30 July 2013                                             *
 *                                                                   *
 * GUI code source file                                              *
 *                                                                   *
 *********************************************************************/

package com.maxeler.publicdemos.smithwaterman.gui;

import com.maxeler.publicdemos.smithwaterman.gui.ScoringMatrix;
import com.maxeler.publicdemos.smithwaterman.gui.Sequence;

public class SmithWaterman {

	private Sequence S;
	private Sequence T;
	private ScoringMatrix scoringMatrix;
	private int gapOpen;
	private int gapExtend;
	private String paddedAlignedT;
	private String paddedAlignedS;
	private String paddedAlignedType;
	

	public SmithWaterman(String T, String S, int open, int extend, boolean dna, int match, int mismatch){
		this.S 	= new Sequence("",S,S.length());
		this.T 	= new Sequence("",T,T.length());
		this.gapOpen = open;
		this.gapExtend = extend;
		scoringMatrix = new ScoringMatrix(dna ? ScoringMatrix.Type.DNA : ScoringMatrix.Type.BLOSUM62, match, mismatch);
	}
	
	//Display the scoring matrix
	public void printMatrix(){
		int n = scoringMatrix.getTableWidth();
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				int a = scoringMatrix.getMatrix()[i*n+j];
				if(a<0) System.out.print(" "+a);
				else System.out.print("  "+a);
			}
			System.out.println("");
		}
	}
	
	public void setS(Sequence sequence){
		this.S = sequence;
	}
	public void setT(Sequence sequence){
		this.T = sequence;
	}
	public void setMatrixType(ScoringMatrix.Type type){
		scoringMatrix.setType(type);
	}
	public String getAlignedT(){
		return paddedAlignedT;
	}
	public String getAlignedS(){
		return paddedAlignedS;
	}
	public String getAlignedType(){
		return paddedAlignedType;
	}
	
	//Shift for the traceback
	private enum Shift{
		UP,
		LEFT,
		DIAG,
		END
	}
	
	//Get the direction for the traceback
	private Shift getShift(int i, int j, int[][] V){
		if(i<1||j<1){
			return Shift.END;
		}
		int diag = V[i-1][j-1];
		int left = V[i][j-1];
		int up   = V[i-1][j];
		
		if(up>left && up>diag){
			return Shift.UP;
		}
		else if(left>diag && left>up){
			return Shift.LEFT;
		}
		else{
			return Shift.DIAG;
		}
	}
	
	//Reverse a string (the traceback gives reversed strings)
	private String reverseString(String s){
		String res=new String();
		int L=s.length();
		int i=L-1;
		for(i=L-1;i>=0;i--){
			res+=s.charAt(i);
		}
		return res;
	}
	
	//Add padding to strings to align them for display
	private String addPadding(String s, int offset, int width){
		String res=new String();
		res += s.substring(0,offset>0 ? offset : 0);
		int i=offset;
		for(i=offset;i<offset+width;i++){
			res+=" ";
		}
		if(offset<s.length()){
			res += s.substring(offset,s.length());
		}
		return res;
	}
	
	//Compute the traceback
	public void computeTraceBack(){
		int m = T.getSize(); //one character per row
		int n = S.getSize(); //one character per column
		
		String revTrace = new String();
		String trace = new String();

		int iSW = 0;
		int jSW = 0;
		int maxSW = 0;
		
		// build the n*m matrix and keep highest score + location
		int[][] V = new int[n+1][m+1];
		int[][] E = new int[n+1][m+1];
		int[][] F = new int[n+1][m+1];
		Shift[][] direction = new Shift[n+1][m+1];
	
		//first row to 0
		for(int j=0; j<m+1; j++){
			V[0][j]=0;
			E[0][j]=0;
			F[0][j]=0;
		}
		//first column to 0
		for(int i=0; i<n+1; i++){
			V[i][0]=0;
			E[i][0]=0;
			F[i][0]=0;
		}
		/**
		 * from current position
		 * left : column shift  = shift    & 1
		 * up   : line shift    = shift>>1 & 1
		 * diag : both shift 
		 * 
		 **/
		int maxEF=0;
		int score=0;
		//Build the matrix and store the coordinates of the maxSW + shifts
		for(int i=1; i<n+1; i++){
			for(int j=1; j<m+1; j++){
				
				F[i][j] = V[i-1][j]+gapOpen > F[i-1][j]+gapExtend ? V[i-1][j]+gapOpen : F[i-1][j]+gapExtend;
				E[i][j] = V[i][j-1]+gapOpen > E[i][j-1]+gapExtend ? V[i][j-1]+gapOpen : E[i][j-1]+gapExtend;
								
				if(E[i][j]>F[i][j]){
					maxEF = E[i][j];
					direction[i][j]=Shift.LEFT;
				}
				else{
					maxEF = F[i][j];
					direction[i][j]=Shift.UP;
				}
				
				score = scoringMatrix.getScore(T.getChar(j-1),S.getChar(i-1));
				V[i][j] = V[i-1][j-1]+score;
				V[i][j] = V[i][j] > 0 ? V[i][j] : 0 ;
				if(V[i][j] > maxEF){
					direction[i][j]=Shift.DIAG;
				}
				else{
					V[i][j]=maxEF;
				}
				
				if(V[i][j] >= maxSW){
					iSW = i-1;
					jSW = j-1;
					maxSW = V[i][j];
				}
			}
		}
		
		String alignedS = new String();
		String alignedT = new String();
		String type = new String();
		
		// printout the alignment matrix.
//		System.out.println("[java] The matrix :");
//		for(int j=1; j<m+1; j++){
//			for(int i=1; i<n+1; i++){
//				System.out.print("\t"+V[i][j]+",");
//			}
//			System.out.println("");
//		}
		
		
		int i = iSW;
		int j = jSW;
		
		int firsti=0;
		int firstj=0;
		Shift shift=Shift.END;
		while(i>=0 && j>=0){
			int Vdiag = V[i][j];
			int Vleft = V[i+1][j];
			int Vup   = V[i][j+1];
			
			/**
			 * from current position
			 * left : column shift  = shift    & 1
			 * up   : line shift    = shift>>1 & 1
			 * diag : both shift 
			 * 
			 **/

			firsti=i;
			firstj=j;
			
			switch(direction[i+1][j+1]){
			case DIAG :
				alignedT += Character.toUpperCase(T.getChar(j));
				alignedS += Character.toUpperCase(S.getChar(i));
				type += Character.toUpperCase(T.getChar(j))==Character.toUpperCase(S.getChar(i)) ? ":" : scoringMatrix.getScore(T.getChar(j),S.getChar(i)) >0 ? "." : " " ;
				i--;
				j--;
				break;
				
			case LEFT :
				type += " ";
				alignedS += '-';
				alignedT += Character.toUpperCase(T.getChar(j));
				j--;
				break;
			
			case UP :
				type +=" ";
				alignedS += Character.toUpperCase(S.getChar(i));
				alignedT += '-';
				i--;
				break;
			}
		}
		
		//Reverse back traceback results
		paddedAlignedT = reverseString(alignedT);
		paddedAlignedS = reverseString(alignedS);
		paddedAlignedType = reverseString(type);
		
		
//		System.out.println("[java]best score :"+maxSW);
//		String revType = reverseString(type);
//		String revT = reverseString(alignedT);
//		String revS = reverseString(alignedS);
		
//		// Non matching beginning
//		int startj = firstj - 7;
//		int starti = firsti - 7;
//		starti = starti > 0 ? starti : 0;
//		startj = startj > 0 ? startj : 0;
//		
//		int wj = firstj - startj;
//		int wi = firsti - starti;
//		
//		String finalT = (startj > 0 ? "..." : "") + T.getSequence().substring(startj,firstj);
//		String finalS = (starti > 0 ? "..." : "") + S.getSequence().substring(starti,firsti);
//		
//		// Matching part + gaps
//		finalT += revT;
//		finalS += revS;
//		
//		
////		// Non matching tail
////		int tailj = jSW+8;
////		int taili = iSW+8;
////		int endj = T.getSequence().length();
////		int endi = S.getSequence().length();
////		tailj = tailj>endj ? endj : tailj;
////		taili = taili>endi ? endi : taili;
////		finalT += T.getSequence().substring(jSW+1,tailj) + (tailj<endj?"...":"");
////		finalS += S.getSequence().substring(iSW+1,taili) + (taili<endi?"...":"");
//			
//		//+leading padding to align the display and trailing padding so that everything has the same length
//
//		paddedAlignedT = new String(addPadding(finalT,0,wi));
//		paddedAlignedS = new String(addPadding(finalS,0,wj));
//		paddedAlignedType = new String(addPadding(revType,0,wi>wj ? wi: wj));
//		
////		String paT = new String(addPadding(finalT,0,firsti));
////		String paS = new String(addPadding(finalS,0,firstj));
////		String paType = new String(addPadding(revType,0,firsti>firstj ? firsti:firstj));
//		
////		int longest = paT.length()> paS.length() ? paT.length(): paS.length();
////		paddedAlignedT		= addPadding(paT	,paT.length()	,longest-paT.length()); 
////		paddedAlignedS		= addPadding(paS	,paS.length()	,longest-paS.length());
////		paddedAlignedType	= addPadding(paType	,paType.length(),longest-paType.length());
	}
	
	
}
