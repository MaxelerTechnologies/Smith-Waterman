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


//Class to store sequences
public class Sequence {
	private String label;
	private String seq;
	private int n;
	
	public Sequence(){
		label 	= new String();
		seq 	= new String();
	}
	
	public Sequence(String label, String sequence, int n){
		this.label	= new String(label);
		this.seq	= new String(sequence);
		this.n		= n;
	}
	
	public void setSequence(String sequence){
		this.seq=sequence;
	}
	public String getSequence(){
		return seq;
	}
	
	public char getChar(int i){
		return seq.charAt(i);
	}
	public char charAt(int i){
		return seq.charAt(i);
	}
	
	public void setLabel(String label){
		this.label=label;
	}
	public String getLabel(){
		return label;
	}
	
	public int getSize(){
		return n;
	}
	
	public enum BgColor{
		GREEN,
		YELLOW,
		NONE
	}
	
	public String formatAlignment(String type, int offset, int width){
		String formatted = new String();
		n=seq.length();

		int stop = type.length();

		//Leading part in grey
		int leading = 0;
		while(type.charAt(leading)==' '){
			leading++;
		}
		//Counting the number of character in the trailing part
		int trailing = stop-1;
		while(type.charAt(trailing)==' '){
			trailing--;
		}
		
		BgColor bgColor=BgColor.NONE;
		formatted += "<span style=\"background-color:'FFFFFF';\">";
		
		for(int i=offset; i<offset+width && i<type.length(); i++){
			if(type.charAt(i) == ':'){
				//green
				//if previous color is different, close the span style and open a new one
				if(bgColor != BgColor.GREEN){
					formatted += "</span><span style=\"background-color:'33FF33';\">";
					bgColor=BgColor.GREEN;
				}
				formatted += seq.charAt(i);
			}
			else if(type.charAt(i) == '.'){
				//yellow
				//if previous color is different, close the span style and open a new one
				if(bgColor != BgColor.YELLOW){
					formatted += "</span><span style=\"background-color:'CCFF33';\">";
					bgColor=BgColor.YELLOW;
				}
				formatted += seq.charAt(i);
			}
			else{
				//normal
				//if previous color is different, close the span style and open a new one
				if(bgColor != BgColor.NONE){
					formatted += "</span><span style=\"background-color:'FFFFFF';\">";
					bgColor=BgColor.NONE;
				}
				formatted += ((seq.charAt(i)==' ')? "&nbsp;" : Character.toString(seq.charAt(i)));
			}
		}
		formatted += "</span>";
		
		return formatted;
	}
	
	
	
}
