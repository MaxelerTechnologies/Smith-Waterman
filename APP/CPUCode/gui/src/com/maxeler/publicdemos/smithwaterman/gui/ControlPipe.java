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

import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Iterator;
import java.util.Properties;
import java.util.Vector;

//Class to handle pipes creation and I/O
public class ControlPipe {
	private static final int LABEL_DISPLAY_LENGTH = 60;
	private File pipeIn;
	private File pipeOut;
	private Vector<PipeListener> listeners;
	private ReaderThread readerThread;
	private DataInputStream dis;
	private FileOutputStream fos;
	
	public ControlPipe() {
		listeners = new Vector<PipeListener>();
		dis = null;
		fos = null;
	}
	
	public int getDisplayLength(){
		return LABEL_DISPLAY_LENGTH;
	}

	//Set pipes location
	public void loadState(Properties props) {
		String locationIn = props.getProperty("controlInput");
		this.pipeIn = new File(locationIn);
		String locationOut = props.getProperty("controlOutput");
		this.pipeOut = new File(locationOut);
	}

	public void setControlInputPath(String path){
		this.pipeIn = new File(path);
	}
	
	public void setControlOutputPath(String path){
		this.pipeOut = new File(path);
	}
	
	//Open the GUI side of the output pipe from hostcode
	public void openOutPipe() {
		try {
			dis = new DataInputStream(new FileInputStream(pipeOut));
		} catch (FileNotFoundException e) {
			System.out.println(e);
		}
	}
	
	//Open the GUI side of the input pipe the hostcode
	public void openInPipe() {
		try {
			fos =  new FileOutputStream(pipeIn);
		} catch (FileNotFoundException e) {
			System.out.println(e);
		}	
	}

	//Write a 32bits integer
	public void writeInt(int value) {
		try {
			byte[] bytes = new byte[4];
			bytes[0] = (byte)((value >> 24) & 0xff);
			bytes[1] = (byte)((value >> 16) & 0xff);
			bytes[2] = (byte)((value >> 8) & 0xff);
			bytes[3] = (byte)((value >> 0) & 0xff);
			fos.write(bytes);
			fos.flush();
		} catch (IOException e) {
			System.out.println(e);
		}
	}
	
	//Write a string
	public void writeString(String s) {
		try {
			fos.write(s.getBytes());
			fos.flush();
		} catch (IOException e) {
			System.out.println(e);
		}
	}

	//Write a command
	public void writeCommand(ControlMessage msg) {
		writeInt(msg.ordinal());
	}
	
	public void addPipeListener(PipeListener pl) {
		listeners.add(pl);
	}
	
	public void removePipeListener(PipeListener pl) {
		listeners.remove(pl);
	}

	public void runReadingThread() {
		readerThread = new ReaderThread();
		readerThread.run();
	}
	
	private void notifyListeners(PipeEvent e) {
		Iterator<PipeListener> iter = listeners.iterator();
		while (iter.hasNext()) {
			PipeListener pl = iter.next();
			pl.messageReceived(e);
		}
	}

	//Reads on the pipe what comes from the host code
	//fill pipeEvent with what needs to be displayed and notify the guiHandler
	private class ReaderThread implements Runnable {

		@Override
		public void run() {
			ControlMessage 	msg = null;
			PipeEvent 		pipeEvent = null;

			try {			
				while (true) {
					while (dis.available() >= 4) {
						int msgval = dis.readInt();
						msg = ControlMessage.values()[msgval];
						pipeEvent = new PipeEvent(msg);
						switch(msg){
						case QUERY :
							int numQueries = dis.readInt();
							pipeEvent.setNumberSequences(numQueries);
							if(numQueries>0){
								int minLength = dis.readInt();
								int maxLength = dis.readInt();
								pipeEvent.setMinLength(minLength);
								pipeEvent.setMaxLength(maxLength);
							}
							notifyListeners(pipeEvent);
							break;
						
						case LIBRARY :
							int numRes = dis.readInt();
							pipeEvent.setNumberResidues(numRes);
							if(numRes>0){
								int numSeq = dis.readInt();
								pipeEvent.setNumberSequences(numSeq);
							}
							notifyListeners(pipeEvent);
							break;
							
						case COMPUTE :
							//number of results
							int nbDisplay = dis.readInt();
							pipeEvent.newResults(nbDisplay);
							
							//CUPS
							float cups = dis.readFloat();
							pipeEvent.setCUPS(cups);

							//query length + sequence
							int queryLength = dis.readInt();
							pipeEvent.setQueryLength(queryLength);
							byte[] stringByte = new byte[queryLength];
							dis.read(stringByte, 0, queryLength);
							String string = new String(stringByte);
							pipeEvent.setSequence(string);
							
							//query label
							stringByte = new byte[LABEL_DISPLAY_LENGTH];
							dis.read(stringByte, 0, LABEL_DISPLAY_LENGTH);
							string = new String(stringByte);
							pipeEvent.setLabel(string);
							
							//nb_display * (write 80 char + seqlen + score)
							for(int i=0;i<nbDisplay;i++){
								dis.read(stringByte, 0, LABEL_DISPLAY_LENGTH);
								string = new String(stringByte);
								pipeEvent.setBestLabel(string, i);
								
								int length = dis.readInt();
								pipeEvent.setBestSeqLen(length, i);
								
								int score = dis.readInt();
								pipeEvent.setBestScore(score, i);
							}
							
							//best match length + sequence
							int bestMatchLength = dis.readInt();
							pipeEvent.setBestMatchLength(bestMatchLength);
							stringByte = new byte[bestMatchLength];
							dis.read(stringByte, 0, bestMatchLength);
							string = new String(stringByte);
							pipeEvent.setBestMatch(string);
							
							notifyListeners(pipeEvent);
							break;
							
						case STOP :
							notifyListeners(pipeEvent);
							break;
							
						case NEW_CONFIG :
							notifyListeners(pipeEvent);
							break;
						case CONFIGURATION :
							pipeEvent.setMaxLength(dis.readInt());
							pipeEvent.setMaxVar(dis.readInt());
							pipeEvent.setNumDevice(dis.readInt());
							pipeEvent.setCardType(dis.readInt());
							notifyListeners(pipeEvent);
							break;
						case QUIT :
							
							break;
						
						}
					}
					
					Thread.sleep(20);
				}
			} catch (InterruptedException e) {
				System.out.println(e);
			} catch (IOException e) {
				System.out.println(e);
			} finally {
				if (dis != null) {
					try {
						dis.close();
					} catch (IOException e) {
						System.out.println(e);
					}
				}
			}		
		}
		
	}

}
