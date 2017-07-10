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
import java.awt.Font;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JFileChooser;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import javax.swing.JLabel;
import javax.swing.JTextField;
import java.awt.Color;
import java.util.Arrays;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JTextPane;
import javax.swing.JTextArea;
import javax.swing.JSeparator;
import javax.swing.JRadioButton;
import javax.swing.ButtonGroup;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.image.BufferedImage;
import java.awt.Component;
import javax.swing.Box;
import java.awt.Dimension;
import java.io.File;
import java.io.FileFilter;
import java.io.IOException;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import javax.swing.JOptionPane;
import javax.swing.JEditorPane;
import java.util.ArrayList;
import java.util.List;

import javax.swing.SwingConstants;


public class SWGui {
	
	private final String[] gapType={"Affine gap model", "Linear gap model"};
	
	private JFrame 		frame;
	private JRadioButton rdbProteins;
	private JRadioButton rdbNucleotides;
	private JTextArea 	txtTargetArea;
	private JTextArea 	txtLibraryArea;
	private JTextField 	txtMatch;
	private JTextField 	txtMisMatch;
	private JTextField 	txtGapOpen;
	private JTextField 	txtGapExtend;
	private JButton 	btnCompute;
	private	JButton 	btnStop;
	private JEditorPane	txtScores;
	private JEditorPane	txtResults;
	private JLabel 		lblGcups;
	private JLabel		lblInfo;
	private JLabel 		lblMatch;
	private JLabel 		lblMisMatch;
	private JComboBox 	comboBoxGapModel;
	private JComboBox 	cbTarget;
	private JComboBox 	cbLibrary;
	
	private int			maxDisplayLength = 80;
	private int			maxVar = 2;
	private int			cardType = 0;
	private int			numDevice = 1;
	private boolean		simulation = false;
	
	private boolean		queryLoaded = false;
	private boolean		libraryLoaded = false;
	private boolean 	stateReady 	= true;
	private boolean		stopPressed = false;
	
	
	private String[] queryList;
	private String[] libList;
	String sequencePath;
	String queryPath;
	String libPath;
	
	private GuiHandler 	guiHandler;
	
	private JFileChooser chooser;
	
	ControlPipe controlPipe;
	
	
	
	// Launch the application
	public static void main(String[] args) {
		SWGui window = new SWGui(args[2]);
		
		window.run(args);
		window.frame.setVisible(true);
		window.configure();
	}

	// Open pipes
	public void run(String[] args) {
		frame.setVisible(true);
		frame.setTitle("Smith Waterman Demo - Maxeler Technologies");
		
		BufferedImage img = null;
		try {
		    img = ImageIO.read(new File("MaxelerIcon.png"));
		} catch (IOException e) {
			System.err.println(e.getMessage());
		}
		
		frame.setIconImage(img);
		
		controlPipe.setControlInputPath(args[0]);
		controlPipe.openInPipe();	

		controlPipe.setControlOutputPath(args[1]);
		controlPipe.openOutPipe();
		controlPipe.runReadingThread();
		this.sequencePath = args[2];
		
	}
	
	
	// Disable buttons
	private void freeze(){
		cbTarget.setEnabled(false);
    	cbLibrary.setEnabled(false);
		btnCompute.setEnabled(false);
	}
	
	// Enable buttons
	private void unfreeze(boolean compute){
		cbTarget.setEnabled(true);
    	cbLibrary.setEnabled(true);
    	if(compute) btnCompute.setEnabled(true);
	}
	
	// Request new configurationt to the hostcode 
	private void configure(){
		freeze();
		controlPipe.writeCommand(ControlMessage.CONFIGURATION);
		controlPipe.writeInt(rdbNucleotides.isSelected()?1:0);
		controlPipe.writeInt(comboBoxGapModel.getSelectedIndex()); //value of linear. comboBoxGapModel[0] = affine. comboBoxGapModel[1] = linear.
	}
	
	// Check if parameters are valid
	private boolean checkParameters(){
		if(Math.abs(Integer.parseInt(txtGapOpen.getText()))>maxVar){
			JOptionPane.showMessageDialog(null, "Open Gap Penalty expected in ["+(-maxVar)+";"+maxVar+"]","Smith Waterman Demo", JOptionPane.ERROR_MESSAGE);
			return false;
		}
		return true;
	}
	
	// Handle GUI and pipe events
	public class GuiHandler implements ActionListener, PipeListener{
		
		public GuiHandler() {
		}
		
		@Override
		public void actionPerformed(ActionEvent e) {
			//Load the protein bitstream
			if(e.getSource()==rdbProteins){
				txtMisMatch.setEnabled(false);
				lblMisMatch.setEnabled(false);
				lblMatch.setEnabled(false);
				txtMatch.setEnabled(false);
				configure();
			}
			//Load the nucleotide bitstream
			else if(e.getSource()==rdbNucleotides){
				txtMisMatch.setEnabled(true);
				lblMisMatch.setEnabled(true);
				lblMatch.setEnabled(true);
				txtMatch.setEnabled(true);
				configure();
			}
			else if(e.getSource()==comboBoxGapModel){
				//Load the linear gap model
				if(comboBoxGapModel.getSelectedIndex()==1){
					txtGapExtend.setEnabled(false);
				}
				//Load the affine gap model
				else{
					txtGapExtend.setEnabled(true);
				}
				configure();
			}
			else if(e.getSource()==cbTarget){
				//Send the query filename
				int returnVal = cbTarget.getSelectedIndex();
			    if (returnVal>0) {
			    	String filename = queryPath+"/"+(String)cbTarget.getSelectedItem();
			    	File file = new File(filename);
			    	String filepath=file.getAbsolutePath();
			    	
			    	//Freeze the gui
			    	freeze();
			    	
			    	//display info
			    	lblInfo.setText("Loading query file - please wait...");
					
					int filename_len=filepath.length();
					controlPipe.writeCommand(ControlMessage.QUERY);
					controlPipe.writeInt( comboBoxGapModel.getSelectedIndex());
					controlPipe.writeInt( rdbNucleotides.isSelected() ? 1: 0);
					controlPipe.writeInt(filename_len);
					controlPipe.writeString(filepath);	
					
				}
			    queryLoaded = false;

			}
			else if(e.getSource()==cbLibrary){
				//Send the library filename
				int returnVal = cbLibrary.getSelectedIndex();
			    if (returnVal>0) {
			    	String filename = libPath+"/"+(String)cbLibrary.getSelectedItem();
			    	File file = new File(filename);
			    	String filepath=file.getAbsolutePath();
			    	
			    	//Freeze the gui
			    	freeze();
			    	
			    	//display info
			    	lblInfo.setText("Loading library file - please wait...");
					int filename_len=filepath.length();
					controlPipe.writeCommand(ControlMessage.LIBRARY);
					controlPipe.writeInt( comboBoxGapModel.getSelectedIndex());
					controlPipe.writeInt( rdbNucleotides.isSelected() ? 1: 0);
					controlPipe.writeInt(filename_len);
					controlPipe.writeString(filepath);				
				} 
			    libraryLoaded = false;
			}
			else if(e.getSource()==btnCompute){
				if(checkParameters()){
					//Read gap open and gap extend and send
					int gapOpen = Integer.parseInt(txtGapOpen.getText()); 
					int gapExtend = Integer.parseInt(txtGapExtend.getText()); 
					int matchScore = Integer.parseInt(txtMatch.getText()); 
					int mismatchScore = Integer.parseInt(txtMisMatch.getText());
					
					//Freeze the gui
					freeze();
					
					//Enable stop button
					btnStop.setEnabled(true);
					
					//Display info
					lblInfo.setText("Computing...");
					
					//Send compute order to the pipe
					controlPipe.writeCommand(ControlMessage.COMPUTE);
					controlPipe.writeInt( comboBoxGapModel.getSelectedIndex());
					controlPipe.writeInt( rdbNucleotides.isSelected() ? 1: 0);
					controlPipe.writeInt(10);
					controlPipe.writeInt(controlPipe.getDisplayLength());
					controlPipe.writeInt(matchScore);
					controlPipe.writeInt(mismatchScore);
					controlPipe.writeInt(gapOpen);
					controlPipe.writeInt(gapExtend);	
				}
				
			}
			else if(e.getSource()==btnStop){
				//Stop computation
				controlPipe.writeCommand(ControlMessage.STOP);
				stopPressed = true;
				lblInfo.setText("Stopping computation - please wait...");
			}
		}
		
		
		@Override
		public void  messageReceived(PipeEvent e){
			switch(e.getMessage()){
			case QUERY :
				if(e.getNumberSequences() > 0){
					//success
					//display number of queries, min length and max length
					txtTargetArea.setText("Number of queries : " + e.getNumberSequences() + "\n" +
							"Min length : " + e.getMinLength() + "\n" +
							"Max length : " + e.getMaxLength() );
					//Set query flag to TRUE
					queryLoaded = true;
				}
				else{
					//fail
					//Set query flag to FALSE
					queryLoaded = false;
					txtTargetArea.setText("");

					//pop up a warning
					JOptionPane.showMessageDialog(null, "Couldn't load query file","Smith Waterman Demo", JOptionPane.ERROR_MESSAGE);
				}
				//unfreeze the gui
				unfreeze(queryLoaded && libraryLoaded);
				
		    	//display info
		    	lblInfo.setText("Ready");
				break;
				
			case LIBRARY : 
				if(e.getNumberResidues()>0){
					//success
					txtLibraryArea.setText("Number of sequences : " + e.getNumberSequences() +
							"\nNumber of residues : " + e.getNumberResidues());
					
					libraryLoaded = true;
				}
				else{
					//fail
					libraryLoaded = false;
					txtLibraryArea.setText("");
					
					//pop up an invalid stuff
					JOptionPane.showMessageDialog(null, "Couldn't load library file","Smith Waterman Demo", JOptionPane.ERROR_MESSAGE);
				}
				unfreeze(queryLoaded && libraryLoaded);
		    	
		    	//display info
		    	lblInfo.setText("Ready");
				
				break;
				
			case COMPUTE : 
				//Get the list of best results
				String scores = new String();
				scores += "<html>";
				scores += "<span style=\"font-family: monospace;font-size: 0.7em;\">";
				scores += "Query :<br>";
				for(int i=0;i<60;i++){
					scores += (e.getLabel().charAt(i)==' ' ? "&nbsp;" : e.getLabel().charAt(i));
				}
				scores += "&nbsp;&nbsp;("+e.getQueryLength() + ")<br><br>";
				scores += "Best scores :";
				for(int i=0;i<47;i++){
					scores += "&nbsp;";
				}
				String scorLenString="Length";
				scores += "&nbsp;&nbsp;(" + scorLenString + ")&nbsp;&nbsp;SW<br>";
				for(int index=0;index<e.getNumDisplay();index++){
					for(int i=0;i<60;i++){
						scores += (e.getBestLabel(index).charAt(i)==' ' ? "&nbsp;" : e.getBestLabel(index).charAt(i)); 
					}
					scores += "&nbsp;&nbsp;(" +e.getBestSeqLen(index)+")&nbsp;&nbsp;";
					int nbSpaces = scorLenString.length()- (""+e.getBestSeqLen(index)).length();
					for(int i=0;i<nbSpaces;i++){
						scores += "&nbsp;";
					}
					
					scores += e.getBestScore(index)+"<br>";
				}
				scores += "</span></html>";
				
				//Recompute Smith Waterman on the best match to get the matrix and trace back the alignment
				int gapOpen 	= Integer.parseInt(txtGapOpen.getText());
				int gapExtend 	= Integer.parseInt(txtGapExtend.getText());
				int match 		= Integer.parseInt(txtMatch.getText());
				int mismatch 	= Integer.parseInt(txtMisMatch.getText());
				SmithWaterman SW = new SmithWaterman(
						e.getSequence(),e.getBestMatch(),
						comboBoxGapModel.getSelectedIndex()==0 ? gapExtend+gapOpen 	: gapOpen,
						comboBoxGapModel.getSelectedIndex()==0 ? gapExtend 			: gapOpen,
						rdbNucleotides.isSelected(),
						match,
						mismatch);
				SW.computeTraceBack();
				
				//Get the aligned part
				Sequence alignedS 		= new Sequence(e.getBestLabel(0)	, SW.getAlignedS(), e.getBestSeqLen(0));
				Sequence alignedT 		= new Sequence(e.getLabel()			, SW.getAlignedT(), e.getQueryLength());
				String alignmentType 	= SW.getAlignedType();
				
				//Formatting for display
				String results = new String();
				results += "<html>";
				results += "<span style=\"font-family: monospace;font-size: 0.7em;\">";
				results += "Best alignment :<br>";
				int leadingPart=0;
				while(alignmentType.charAt(leadingPart)==' '){
					leadingPart++;
				}
				for(int i=(int)(Math.floor((double)leadingPart/(double)maxDisplayLength)*maxDisplayLength); i< alignmentType.length(); i+=maxDisplayLength){
					results += "<br>";
					results += alignedT.formatAlignment(alignmentType,i,maxDisplayLength);
					results += "<br>";
					results += alignedS.formatAlignment(alignmentType,i,maxDisplayLength);
					results += "<br>";
				}
				results += "</span></html>";

				//Control
				if(stopPressed == false){
					txtScores.setText(scores);
					txtResults.setText(results);
					lblGcups.setText(""+String.format("%.4f",e.getCUPS()*1e-9));
				}
				break;
				
			case STOP :
				//unfreeze the gui
				unfreeze(queryLoaded && libraryLoaded);
				stopPressed = false;
				//disable stop button
				btnStop.setEnabled(false);
				//display info
		    	lblInfo.setText("Ready");
		    	break;
				
			case CONFIGURATION :
				//Remove all libs and querys from combo boxes and file lists
				cbTarget.removeAllItems();
				cbLibrary.removeAllItems();
				
				//maxVar gives the maximum variation per step to get a correct result in the worse case
				//With the Linear gap model, open should be within [-maxVar;+maxVar]
				//Affine gap model : open+extend should be within [-maxVar;+maxVar]
				maxVar 		= e.getMaxVar();
				
				//Number of devices running
				numDevice 	= e.getNumDevice();
				
				//Type of the card
				cardType 	= e.getCardType();
				
				//unfreeze the gui
				unfreeze(queryLoaded && libraryLoaded);
				
				//Remove unwanted query files, add file list to combo boxes and display info
				//max2c : keep filenames containing "max2c"
				//max2b && max 3 : keep filenames containing "max3"
				String info = new String("Smith Waterman Demo - running on " + numDevice + " * ");
				String cardString;
				switch (cardType) {
				  default:
				  case 0: cardString = "UNKNOWN"; break;
				  case 1: cardString = "MAX3424A"; break;
				  case 2: cardString = "Coria"; break;
				  case 3: cardString = "Maia"; break;
				  case 4: simulation = true; cardString = "Simulation Maxcard"; break;
				}
				info += cardString;
				
				//Load file lists
				queryPath 	= new String(sequencePath + "/query/" 	+ (simulation ? "sim" : cardString));
				libPath 	= new String(sequencePath + "/lib/" 	+ (simulation ? "sim" : "hw"));

				File qDir = new File(queryPath);
				File lDir = new File(libPath);
				String[] vide = {""};
				String[] qArray = qDir.list();
				String[] lArray = lDir.list();
				Arrays.sort(qArray);
				Arrays.sort(lArray);
								
				queryList = new String[qArray.length + 1];
				libList = new String[lArray.length + 1];
				
				System.arraycopy(vide, 		0, queryList, 	0, 				vide.length);
				System.arraycopy(qArray,	0, queryList, 	vide.length, 	qArray.length);
				System.arraycopy(vide, 		0, libList, 	0, 				vide.length);
				System.arraycopy(lArray,	0, libList, 	vide.length, 	lArray.length);
				
				for(int i=0;i<queryList.length;i++){
					cbTarget.addItem(queryList[i]);
				}
				for(int i=0;i<libList.length;i++){
					cbLibrary.addItem(libList[i]);
				}
				lblInfo.setText(info);
				break;
				
			case QUIT : 
				break;
				
			}
		}
		
	}

	// Create the application
	public SWGui(String path) {
		initialize(path);
	}
	
	// Initialize the contents of the frame.
	private void initialize(String path) {
		this.sequencePath = path;

		guiHandler=new GuiHandler();
		controlPipe=new ControlPipe();
		controlPipe.addPipeListener(guiHandler);
		
		frame = new JFrame();
		frame.setBounds(100, 100, 800, 600);
		frame.setResizable(false);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				try {
					if(stateReady){
						controlPipe.writeCommand(ControlMessage.QUIT);
					}
				} catch (Exception ex) {
					System.out.println(ex.getMessage());
				}
			}
		});
		
		
		JPanel panel = new JPanel();
		frame.getContentPane().add(panel, BorderLayout.CENTER);
		panel.setLayout(null);

		
		// Left side bar
		//--------------------------------------------------------------------
		
		JLabel lblAlignType = new JLabel("Alignment Type");
		lblAlignType.setBounds(12, 11, 125, 20);
		panel.add(lblAlignType);
		
		rdbProteins = new JRadioButton("Proteins");
		rdbNucleotides = new JRadioButton("Nucleotides");
		rdbProteins.setBounds(30, 38, 90, 20);
		rdbNucleotides.setBounds(120, 38, 125, 20);
		rdbProteins.addActionListener(guiHandler);
		rdbNucleotides.addActionListener(guiHandler);
		panel.add(rdbProteins);
		panel.add(rdbNucleotides);
		rdbProteins.setSelected(true);
		
		ButtonGroup group = new ButtonGroup();
		group.add(rdbProteins);
		group.add(rdbNucleotides);
		
		JSeparator separator_0 = new JSeparator();
		separator_0.setBounds(12, 70, 242, 2);
		panel.add(separator_0);
		
		//--------------------------------------------------------------------
		
		JLabel lblTarget = new JLabel("Query");
		lblTarget.setBounds(12, 80, 125, 20);
		panel.add(lblTarget);
		
		cbTarget = new JComboBox();
		cbTarget.setBounds(12, 110, 242, 20);
		cbTarget.setEnabled(false);
		cbTarget.addActionListener(guiHandler);
		panel.add(cbTarget);
		
		txtTargetArea = new JTextArea();
		txtTargetArea.setBounds(12, 142, 242, 40);
		txtTargetArea.setEditable(false);
		txtTargetArea.setLineWrap(true);
		txtTargetArea.setFont(new Font("Dialog",Font.PLAIN, 10));
		panel.add(txtTargetArea);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(12, 198, 242, 2);
		panel.add(separator);
		
		//--------------------------------------------------------------------
		
		JLabel lblLibrary = new JLabel("Database");
		lblLibrary.setBackground(Color.WHITE);
		lblLibrary.setBounds(12, 206, 125, 20);
		panel.add(lblLibrary);
		
		cbLibrary = new JComboBox();
		cbLibrary.setBounds(12, 235, 242, 20);
		cbLibrary.setEnabled(false);
		cbLibrary.addActionListener(guiHandler);
		panel.add(cbLibrary);
		
		
		txtLibraryArea = new JTextArea();
		txtLibraryArea.setBounds(12, 268, 242, 40);
		txtLibraryArea.setEditable(false);
		txtLibraryArea.setLineWrap(true);
		txtLibraryArea.setFont(new Font("Dialog",Font.PLAIN, 10));
		panel.add(txtLibraryArea);
		
		JSeparator separator_1 = new JSeparator();
		separator_1.setBounds(12, 320, 242, 2);
		panel.add(separator_1);
		
		//--------------------------------------------------------------------
		
		lblMatch = new JLabel("Match");
		lblMatch.setBounds(12, 335, 125, 20);
		panel.add(lblMatch);
		
		txtMatch = new JTextField();
		txtMatch.setHorizontalAlignment(SwingConstants.RIGHT);
		txtMatch.setText("5");
		txtMatch.setBounds(163, 336, 59, 20);
		txtMatch.setEditable(false);
		panel.add(txtMatch);
		txtMatch.setColumns(10);
		
		
		lblMisMatch = new JLabel("Mismatch");
		lblMisMatch.setBounds(12, 369, 125, 20);
		panel.add(lblMisMatch);
		
		txtMisMatch = new JTextField();
		txtMisMatch.setHorizontalAlignment(SwingConstants.RIGHT);
		txtMisMatch.setText("-4");
		txtMisMatch.setColumns(10);
		txtMisMatch.setBounds(163, 368, 59, 20);
		txtMisMatch.setEditable(false);
		panel.add(txtMisMatch);

		txtMisMatch.setEnabled(false);
		lblMisMatch.setEnabled(false);
		lblMatch.setEnabled(false);
		txtMatch.setEnabled(false);
		
		JSeparator separator_1b = new JSeparator();
		separator_1b.setBounds(12, 400, 242, 2);
		panel.add(separator_1b);
		
		//--------------------------------------------------------------------
		
		comboBoxGapModel = new JComboBox(gapType);
		comboBoxGapModel.setSelectedIndex(1);
		comboBoxGapModel.setBounds(12, 416, 200, 20);
		comboBoxGapModel.addActionListener(guiHandler);
		comboBoxGapModel.setVisible(false);
		panel.add(comboBoxGapModel);
		
		JLabel lblOpenGapPenalty = new JLabel("Open Gap Penalty");
		lblOpenGapPenalty.setBounds(12, 448, 125, 20);
		panel.add(lblOpenGapPenalty);
		
		txtGapOpen = new JTextField();
		txtGapOpen.setHorizontalAlignment(SwingConstants.RIGHT);
		txtGapOpen.setText("-5");
		txtGapOpen.setBounds(163, 449, 59, 20);
		panel.add(txtGapOpen);
		txtGapOpen.setColumns(10);
		
		JLabel lblExtendGapPenalty = new JLabel("Extend Gap Penalty");
		lblExtendGapPenalty.setBounds(12, 480, 125, 20);
		panel.add(lblExtendGapPenalty);
		
		txtGapExtend = new JTextField();
		txtGapExtend.setHorizontalAlignment(SwingConstants.RIGHT);
		txtGapExtend.setText("-5");
		txtGapExtend.setColumns(10);
		txtGapExtend.setBounds(163, 481, 59, 20);
		panel.add(txtGapExtend);
		
		JSeparator separator_2 = new JSeparator();
		separator_2.setBounds(12, 510, 242, 2);
		panel.add(separator_2);
		
		//--------------------------------------------------------------------
		
		btnCompute = new JButton("Compute");
		btnCompute.addActionListener(guiHandler);
		btnCompute.setBounds(147, 525, 107, 25);
		btnCompute.setEnabled(false);
		panel.add(btnCompute);
		
		btnStop = new JButton("Stop");
		btnStop.addActionListener(guiHandler);
		btnStop.setBounds(12, 525, 107, 25);
		btnStop.setEnabled(false);
		panel.add(btnStop);
		
		//--------------------------------------------------------------------
		
		
		// Right frame
		//--------------------------------------------------------------------
		
		txtScores = new JEditorPane();
		txtScores.setBounds(287, 12, 491, 200);
//		txtScores.setFont(new Font("monospace",Font.PLAIN, 10));
		txtScores.setContentType("text/html");
		txtScores.setEditable(false);
		panel.add(txtScores);

		txtResults = new JEditorPane();
		txtResults.setBounds(287, 230, 491, 300);
		txtResults.setContentType("text/html");
		txtResults.setEditable(false);
		panel.add(txtResults);

		JLabel lblPerformances = new JLabel("Performance :\n");
		lblPerformances.setBounds(365, 535, 119, 20);
		panel.add(lblPerformances);
		
		lblGcups = new JLabel("");
		lblGcups.setHorizontalAlignment(SwingConstants.RIGHT);
		lblGcups.setOpaque(true);
		lblGcups.setBackground(Color.WHITE);
		lblGcups.setBounds(486, 535, 84, 20);
		panel.add(lblGcups);
		
		JLabel lblGcupsInfo = new JLabel("GCUPS");
		lblGcupsInfo.setBounds(582, 535, 61, 20);
		panel.add(lblGcupsInfo);
		
		lblInfo = new JLabel("Smith Waterman Demo - Initializing...");
		lblInfo.setHorizontalAlignment(SwingConstants.LEADING);
		lblInfo.setBounds(20,555,770,15);
		lblInfo.setFont(new Font("Tahoma", Font.PLAIN, 12));
		panel.add(lblInfo);
		
		
		
		//--- For the protein only version
		rdbNucleotides.setSelected(false);
		rdbProteins.setSelected(true);
		rdbProteins.setVisible(false);
		rdbNucleotides.setVisible(false);
		
		lblExtendGapPenalty.setVisible(false);
		txtGapExtend.setVisible(false);
		
		lblMisMatch.setEnabled(true);
		lblMatch.setEnabled(true);
		lblMatch.setText("Scoring matrix :");
		lblMisMatch.setText("BLOSUM62");
		txtMisMatch.setVisible(false);
		txtMatch.setVisible(false);
		//---
		
		
		//--- Comment this zone to allow protein/nucleotide selection (untested)
//		rdbNucleotides.setSelected(true);
//		
//		rdbProteins.setVisible(false);
//		rdbNucleotides.setVisible(false);
//		lblAlignType.setBounds(12,11,242,50);
//		lblAlignType.setHorizontalAlignment(SwingConstants.CENTER);
//		lblAlignType.setText("<html>DNA pairwise alignment <br>&nbsp;-&nbsp;Linear gap model&nbsp;- </html>");
//		
//		lblExtendGapPenalty.setVisible(false);
//		txtGapExtend.setVisible(false);
//		
//		
//		lblMisMatch.setEnabled(true);
//		lblMatch.setEnabled(true);
//		txtMisMatch.setEnabled(true);
//		txtMatch.setEnabled(true);
//		txtMisMatch.setEditable(false);
//		txtMatch.setEditable(false);
		//---
	}
}
