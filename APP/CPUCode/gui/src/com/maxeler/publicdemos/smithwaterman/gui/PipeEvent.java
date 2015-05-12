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

//Class to handle pipe data
public class PipeEvent {

	private ControlMessage outMessage;
	private float time;
	private String label;
	private String sequence;
	private String bestMatch;
	private int queryLength = 0;
	private int bestMatchLength;
	private int minLength = 0;
	private int maxLength = 0;
	private int maxVar = 0;
	private int numberSequences = 0;
	private int numberResidues = 0;
	private int score = 0;
	private float CUPS = 0;
	private String[] labelBest;
	private int[] scoreBest;
	private int[] seqLenBest;
	private int numBest;
	
	private int numDevice;
	private int type;
	
	public PipeEvent(ControlMessage outMessage) {
		this.outMessage = outMessage;
	}
	public ControlMessage getMessage() {
		return this.outMessage;
	}
	
	public void setTime(float time) {
		this.time = time;
	}
	public float getTime() {
		return time;
	}
	
	public void setBestMatch(String bestMatch){
		this.bestMatch=bestMatch;
	}
	public String getBestMatch(){
		return bestMatch;
	}
	
	public void setBestMatchLength(int bestMatchLength){
		this.bestMatchLength=bestMatchLength;
	}
	public int getBestMatchLength(){
		return bestMatchLength;
	}
	
	public void setLabel(String s){
		this.label=s;
	}
	public String getLabel(){
		return label;
	}
	
	public void setSequence(String s){
		this.sequence=s;
	}
	public String getSequence(){
		return sequence;
	}

	public void setQueryLength(int queryLength){
		this.queryLength=queryLength;
	}
	public int getQueryLength(){
		return queryLength;
	}
	
	public void setMaxLength(int maxLength){
		this.maxLength=maxLength;
	}
	public int getMaxLength(){
		return maxLength;
	}
	public void setMinLength(int minLength){
		this.minLength=minLength;
	}
	public int getMinLength(){
		return minLength;
	}
	
	public int getMaxVar(){
		return maxVar;
	}
	public void setMaxVar(int maxVar){
		this.maxVar=maxVar;
	}
	
	public int getNumDevice(){
		return numDevice;
	}
	public void setNumDevice(int numDevice){
		this.numDevice=numDevice;
	}
	public int getCardType(){
		return type;
	}
	public void setCardType(int type){
		this.type=type;
	}
	
	public void setNumberSequences(int numSeq){
		this.numberSequences=numSeq;
	}
	public int getNumberSequences(){
		return numberSequences;
	}
	
	public void setNumberResidues(int numRes){
		this.numberResidues=numRes;
	}
	public int getNumberResidues(){
		return numberResidues;
	}
	
	public void setScore(int sw){
		this.score=sw;
	}
	public int getScore(){
		return score;
	}
	
	
	public void setCUPS(float cups){
		this.CUPS=cups;
	}
	public float getCUPS(){
		return CUPS;
	}
	
	public void newResults(int nbDisplay){
		this.labelBest = new String[nbDisplay];
		this.scoreBest= new int[nbDisplay];
		this.seqLenBest= new int[nbDisplay];
		this.numBest=nbDisplay;
	}
	public int getNumDisplay(){
		return numBest;
	}
	
	public void setBestLabel(String labelBest, int i){
		this.labelBest[i]=labelBest;
	}
	public String getBestLabel(int index){
		return labelBest[index];
	}
	
	public void setBestScore(int score, int i){
		this.scoreBest[i]=score;
	}
	public int getBestScore(int index){
		return scoreBest[index];
	}
	
	public void setBestSeqLen(int length, int i){
		this.seqLenBest[i]=length;
	}
	public int getBestSeqLen(int index){
		return seqLenBest[index];
	}
}
