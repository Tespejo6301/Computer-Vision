/*
    class: CSCI 381/780
    First Name: Trisha
    Last Name: Espejo
    Project 7
    language: JAVA
    project name: Chain Code
    
 */
import java.io.*;
import java.util.Scanner;

public class chainCode {
	public int lastQ = -1;
	public int nextDir = -1;
	public int PchainDir;
	public int numCC = -1;
	public int[] zeroTable;
	
	public point[] neighborCoord;
	public point startP;
	public point currP;
	public point nextP;
	
	public CCproperty CC;

	public void constructor() {
		zeroTable = new int[8];
		neighborCoord = new point[8];
		startP = new point();
		currP = new point();
		nextP = new point();
		initzeroTable();
	}

	private void initzeroTable() {
		zeroTable[0] = 6;
		zeroTable[1] = 0;
		zeroTable[2] = 0;
		zeroTable[3] = 2;
		zeroTable[4] = 2;
		zeroTable[5] = 4;
		zeroTable[6] = 4;
		zeroTable[7] = 6;	
	}
	public void printImgHeader(BufferedWriter output) throws IOException  {
		output.write( (CC.numRows) + " " + Integer.toString(CC.numCols) + " "  );
		output.write( Integer.toString(CC.minValue) + " " +  Integer.toString(CC.maxValue));
		output.write("\n");
		
	}
	public void getChainCode(int[][] CCAry, BufferedWriter output) throws IOException {
		int label = CC.label;
		int nextQ = 0;
		boolean isfound = false;

		for (int i = 1; i < CC.numRows + 1 && !isfound; i++) {
			for (int j = 1; j < CC.numCols + 1 && !isfound; j++) {
				if (CCAry[i][j] == label) {
					output.write(label + " " + i + " " + j + " ");
					isfound = true;					// stop the double nested for loop when label is found
					
					startP.row = i;
					startP.col = j;
					currP.row = i;
					currP.col = j;
					lastQ = 4;
				}
			}
		}
		nextQ = (lastQ + 1) % 8;
		PchainDir = findNextP(CCAry, currP, nextQ);
		nextP = neighborCoord[PchainDir];
		output.write(PchainDir + " ");
		if( PchainDir == 0)
			lastQ =zeroTable[7];
		else 
			lastQ = zeroTable[PchainDir - 1];	
		currP = nextP;
		
		while (true) {

			nextQ = (lastQ + 1) % 8;
			
			PchainDir = findNextP(CCAry, currP, nextQ);
			nextP = neighborCoord[PchainDir];
			output.write(PchainDir + " ");
			if( PchainDir == 0)
				lastQ =zeroTable[7];
			else 
				lastQ = zeroTable[PchainDir - 1];
			currP = nextP;
			
			if (currP.row == startP.row && currP.col == startP.col) {
				break;
			}	
		}
		output.write("\n");
		
		
		
	}

	private int findNextP(int[][] CCAry, point currP, int nextQ) {
		
		int row = 0; 
		int col = 0;

		point temp = new point();
		loadNeighborCoord(currP);
		temp = neighborCoord[nextQ];
		row = temp.row;
		col = temp.col;

		while(CCAry[row][col] <= 0) {
			temp = new point();		
			nextQ = (++nextQ) % 8;
			
			temp = neighborCoord[nextQ];
			row = temp.row;
			col = temp.col;

		}

		return nextQ;
	}

	
	private void loadNeighborCoord( point currP) {
		int row = currP.row;
		int col = currP.col;
		point temp = new point();
		temp.row = row;
		temp.col = col + 1;
		neighborCoord[0] = temp;
		temp = new point();
		temp.row = row - 1;
		temp.col = col + 1;
		neighborCoord[1] = temp;
		temp = new point();
		temp.row = row - 1;
		temp.col = col;
		neighborCoord[2] = temp;
		temp = new point();
		temp.row = row - 1;
		temp.col = col - 1;
		neighborCoord[3] = temp;
		temp = new point();
		temp.row = row;
		temp.col = col - 1;
		neighborCoord[4] = temp;
		temp = new point();
		temp.row = row + 1;
		temp.col = col - 1;
		neighborCoord[5] = temp;
		temp = new point();
		temp.row = row + 1;
		temp.col = col;
		neighborCoord[6] = temp;
		temp = new point();
		temp.row = row + 1;
		temp.col = col + 1;
		neighborCoord[7] = temp;
	}

	public void constructBoundary(int[][] boundaryAry, Scanner file) {
		if (file.hasNextInt()) CC.numRows = file.nextInt();
		if (file.hasNextInt()) CC.numCols = file.nextInt();
		if (file.hasNextInt()) CC.minValue = file.nextInt();
		if (file.hasNextInt()) CC.maxValue = file.nextInt();
		
		int direct = 0;
		int r = 0;
		int c = 0;
		if (file.hasNextInt()) CC.label = file.nextInt();
		while(CC.label <= numCC){
			if (file.hasNextInt()) r = file.nextInt();
			if (file.hasNextInt()) c = file.nextInt();
			if (file.hasNextInt()) direct = file.nextInt();
			
			startP.row = r;
			startP.col = c;
			currP = startP;
			boundaryAry[currP.row][currP.col] = CC.label;
			loadNeighborCoord(currP);
			point temp = new point();
			temp = neighborCoord[direct];
			currP = temp;
			while (true) {
				if (file.hasNextInt()) direct = file.nextInt();
				boundaryAry[currP.row][currP.col] = CC.label;
				loadNeighborCoord(currP);
				temp = new point();
				temp = neighborCoord[direct];
				currP = temp;
				if(currP.row == startP.row && currP.col == startP.col)
					break;
			}
			if (CC.label == numCC)
				break;
			
			if (file.hasNextInt()) CC.label = file.nextInt();
			
		
		}
		
	}
	
	public void reformatPrettyPrint(int[][] Ary, BufferedWriter output) throws IOException  {
		output.write( (CC.numRows) + " " + Integer.toString(CC.numCols) + " "  );
		output.write( Integer.toString(CC.minValue) + " " +  Integer.toString(CC.maxValue));
		output.write("\n");
		
		for (int i = 1; i < CC.numRows + 1; i++) {
			for(int j = 1; j < CC.numCols + 1; j++) {
				
				if (Ary[i][j] > 0) output.write( Integer.toString(Ary[i][j]) + " ");
				else output.write(". ");
			}	
			output.write("\n");
		}
		output.write("\n\n");
	
	}
}