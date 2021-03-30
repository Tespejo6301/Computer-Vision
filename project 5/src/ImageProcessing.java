/*
    class: CSCI 381/780
    First Name : Trisha
    Last Name: Espejo
    Project 5
    language: JAVA
    project name: Image Compression via Distance Transform
    
 */

import java.io.*;
import java.util.Scanner;

public class ImageProcessing {
	public int numRows = -1;
	public int numCols = -1;
	public int minValue = -1;
	public int maxValue = -1;
	public int newMinVal = 0;
	public int newMaxVal = 0;
	
	public int[][] zeroFramedAry;
	public int[][] skeletonAry;
	
	public void setZero(int[][] Ary) {
		for (int i = 0; i < numRows + 2; i++) {
			for(int j = 0; j < numCols + 2; j++) {
				Ary[i][j] = 0;
				
			}
			
		}
	}
	public void readImageheader(int row, int col, int min, int max){
		this.numRows = row;
		this.numCols = col;
		this.minValue = min;
		this.maxValue = max;
	
	}
	
	public void initAry() {
		this.zeroFramedAry = new int [this.numRows + 2][this.numCols + 2];
		this.skeletonAry = new int [this.numRows + 2][this.numCols + 2];
	}
	
	public void loadImg(Scanner file) {
		for (int i = 1; i < this.numRows + 1; i++) {
			for(int j = 1; j < this.numCols + 1; j++) {
				
				if (file.hasNextInt())zeroFramedAry[i][j] = file.nextInt();
			}	
			
		}
		
	}
	
	public void Compute8Distance(BufferedWriter output) throws IOException {

		output.write("Original Image: \n\n"  );
		reformatPrettyPrint (this.zeroFramedAry, this.minValue, this.maxValue, output);
		fistPass_8Distance (this.zeroFramedAry);
		output.write("Compute 8 Connected Distance Pass 1: \n\n" );
		reformatPrettyPrint (this.zeroFramedAry,this.newMinVal, this.newMaxVal, output);
		secondPass_8Distance(this.zeroFramedAry);
		output.write("Compute 8 Connected Pass 2: \n\n" );
		reformatPrettyPrint (this.zeroFramedAry,this.newMinVal, this.newMaxVal, output);
	}
	
	
	
	private void fistPass_8Distance (int[][] Ary) {
		this.newMinVal = 99999;
		this.newMaxVal = 0;
		for (int i = 1; i < this.numRows + 1; i++) {
			for (int j = 1; j < this.numCols + 1; j++) {
				if (Ary[i][j] > 0) {
					int distance = -1;
					int a = Ary[i - 1][j - 1];
					int b = Ary[i - 1][j];
					int c = Ary[i -1 ][j + 1];
					int d = Ary[i][j - 1];
					
					distance = Math.min(a, b);
					distance = Math.min(distance, c);
					distance = Math.min(distance, d);
					distance = distance + 1;
					Ary[i][j] = distance;
					
				}
				if (this.newMinVal > Ary[i][j])
                    this.newMinVal = Ary[i][j];
                if (this.newMaxVal < Ary[i][j])
                    this.newMaxVal = Ary[i][j];
			}
		}
		
	}
	
	private void secondPass_8Distance(int[][] Ary) {
		this.newMinVal = 99999;
		this.newMaxVal = 0;
		for (int i = this.numRows; i > 0; i--) {
			for (int j = this.numCols; j > 0; j--) {
				if (Ary[i][j] > 0) {
					int distance = -1;
					int e = Ary[i][j + 1];
					int f = Ary[i + 1][j - 1];
					int g = Ary[i + 1][j];
					int h = Ary[i + 1][j + 1];
					
					distance = Math.min(e + 1, f + 1);
					distance = Math.min(distance, g + 1);
					distance = Math.min(distance, h + 1);
					distance = Math.min(distance, Ary[i][j]);
					Ary[i][j] = distance;
				}
				if (this.newMinVal > Ary[i][j])
                    this.newMinVal = Ary[i][j];
                if (this.newMaxVal < Ary[i][j])
                    this.newMaxVal = Ary[i][j];
			}
		}

	}
	
	public void skeletonExtraction( BufferedWriter skeletonFile, BufferedWriter output) throws IOException{
		computeLocalMaxima(this.zeroFramedAry, this.skeletonAry);
		output.write("Compute Local Maxima Result: \n\n");
		reformatPrettyPrint (this.skeletonAry,this.newMinVal, this.newMaxVal, output);
		extractLocalMaxima(skeletonAry, skeletonFile);
		skeletonFile.close();
		
	}
	

	
	private void computeLocalMaxima(int[][] Ary, int[][] skeletonAry) {
		
		for (int i = 1; i < this.numRows + 1; i++) {
			for(int j = 1; j < this.numCols + 1; j++) {
				isLocalMaxima(Ary, skeletonAry, i, j);
			}
		}
		
	}
	
	private void isLocalMaxima(int[][] Ary, int[][] skeletonAry, int i, int j) {
		int a = Ary[i - 1][j - 1];
		int b = Ary[i - 1][j];
		int c = Ary[i - 1][j + 1];
		int d = Ary[i][j - 1];
		int e = Ary[i][j + 1];
		int f = Ary[i + 1][j - 1];
		int g = Ary[i + 1][j];
		int h = Ary[i + 1][j + 1];
		if (Ary[i][j] >= a && Ary[i][j] >= b &&
			Ary[i][j] >= c && Ary[i][j] >= d &&
			Ary[i][j] >= e && Ary[i][j] >= f &&
			Ary[i][j] >= g && Ary[i][j] >= h) 
				skeletonAry[i][j] = Ary[i][j];
		else	
			skeletonAry[i][j] = 0;
		
	}
	private void extractLocalMaxima(int[][] Ary, BufferedWriter output) throws IOException {
		output.write( (this.numRows) + " " + Integer.toString(this.numCols) + " "  );
		output.write( Integer.toString(this.newMinVal) + " " +  Integer.toString(this.newMaxVal));
		output.write("\n");
		for (int i = 1; i < this.numRows + 1; i++) {
			for(int j = 1; j < this.numCols + 1; j++) {
				
				if (Ary[i][j] > 0) {
					output.write(Integer.toString(i) + " " + Integer.toString(j) + " " + Integer.toString(Ary[i][j]));
					output.write("\n");
				}
			}	
		}
		output.write("\n\n");
		
		
	}
	
	public void skeletonExpansion(Scanner skeletonFile, BufferedWriter output) throws IOException {
		setZero(this.zeroFramedAry);
		load(skeletonFile);
		firstPassExpension (this.zeroFramedAry);
		output.write("Skeleton Expansion Pass 1: \n\n"  );
		reformatPrettyPrint (this.zeroFramedAry, this.minValue, this.maxValue, output);
		secondPassExpension (this.zeroFramedAry);
		output.write("Skeleton Expansion Pass 2: \n\n"  );
		reformatPrettyPrint (this.zeroFramedAry, this.minValue, this.maxValue, output);
	}

	private void load(Scanner file) {
		int row = -1;
		int col = -1;
		int value = -1;
		
		if (file.hasNextInt())this.numRows = file.nextInt();
		if (file.hasNextInt())this.numCols = file.nextInt();
		if (file.hasNextInt())this.minValue = file.nextInt();
		if (file.hasNextInt())this.maxValue = file.nextInt();
		
		while(file.hasNextInt()){
			row = file.nextInt();
			col = file.nextInt();
			value = file.nextInt();
			this.zeroFramedAry[row][col] = value;
			
		}

	}
	
	private void firstPassExpension(int[][] Ary) {
		for (int i = 1; i < this.numRows + 1; i++) {
			for(int j = 1; j < this.numCols + 1; j++) {
				if( Ary[i][j] == 0) {
					int a = Ary[i - 1][j - 1];
					int b = Ary[i - 1][j];
					int c = Ary[i - 1][j + 1];
					int d = Ary[i][j - 1];
					int e = Ary[i][j + 1];
					int f = Ary[i + 1][j - 1];
					int g = Ary[i + 1][j];
					int h = Ary[i + 1][j + 1];
					int max = Math.max(a - 1, b - 1);
					max = Math.max(max, c - 1);
					max = Math.max(max, d - 1);
					max = Math.max(max, e - 1);
					max = Math.max(max, f - 1);
					max = Math.max(max, g - 1);
					max = Math.max(max, h - 1);
					if (Ary[i][j] < max)
						Ary[i][j] = max;
				}
			}
		}

	}
	
	private void secondPassExpension(int[][] Ary) {
		for (int i = this.numRows; i > 0; i--) {
			for (int j = this.numCols; j > 0; j--) {
				int a = Ary[i - 1][j - 1];
				int b = Ary[i - 1][j];
				int c = Ary[i - 1][j + 1];
				int d = Ary[i][j - 1];
				int e = Ary[i][j + 1];
				int f = Ary[i + 1][j - 1];
				int g = Ary[i + 1][j];
				int h = Ary[i + 1][j + 1];
				int max = Math.max(a - 1, b - 1);
				max = Math.max(max, c);
				max = Math.max(max, d);
				max = Math.max(max, e);
				max = Math.max(max, f);
				max = Math.max(max, g);
				max = Math.max(max, h);
				if (Ary[i][j] < max)
					Ary[i][j] = max - 1;
			}
		}
	}
	
	private void reformatPrettyPrint(int[][] Ary, int min, int max, BufferedWriter output) throws IOException  {
		output.write( (this.numRows) + " " + Integer.toString(this.numCols) + " "  );
		output.write( Integer.toString(min) + " " +  Integer.toString(max));
		output.write("\n");
		
		for (int i = 1; i < this.numRows + 1; i++) {
			for(int j = 1; j < this.numCols + 1; j++) {
				
				if (Ary[i][j] > 0) output.write( Integer.toString(Ary[i][j]) + " ");
				else output.write(". ");
			}	
			output.write("\n");
		}
		output.write("\n\n");
	
	}
	
	
	
	public void ary2File(BufferedWriter output) throws IOException {
		output.write(this.numRows + " " + this.numCols + " " + 0 + " " + 1 + "\n");
		for (int i = 1; i < this.numRows + 1; i++) {
			for(int j = 1; j < this.numCols + 1; j++) {
				
				if (this.zeroFramedAry[i][j] >= 1) output.write("1 ");
				else output.write("0 ");
			}	
			output.write("\n");
		}
		
	}
}
