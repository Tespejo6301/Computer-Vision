/*
    class: CSCI 381/780
    First Name : Trisha
    Last Name: Espejo
    Project 3
    language: JAVA
    project name: Implementation of 4 Morphological Operations
    
 */

import java.io.*;
import java.util.Scanner;

public class Image {
	public int numImgRows = 0, numImgCols = 0, imgMin = 0, imgMax = 0;
	public int numStructRows = 0, numStructCols = 0, structMin = 0, structMax = 0;
	public int rowOrigin = 0, colOrigin = 0;
	public int rowFrameSize = 0, colFrameSize = 0;
	public int extraRow = 0, extraCols = 0;
	public int[][] zeroFrameAry;
	public int[][] morphAry;
	public int[][] tempAry;
	public int[][] structAry;
	
	public Image() {
		
	}
	
	public void readImageheader(int row, int col, int min, int max){
		this.numImgRows = row;
		this.numImgCols = col;
		this.imgMin = min;
		this.imgMax = max;
	}
	public void readStructheader(int row, int col, int min, int max, int rowOri, int colOri){
		this.numStructRows = row;
		this.numStructCols = col;
		this.structMin = min;
		this.structMax = max;
		this.rowOrigin = rowOri;
		this.colOrigin = colOri;
		this.rowFrameSize  = this.numStructRows / 2;
		this.colFrameSize  = this.numStructCols / 2;
		this.extraRow = this.rowFrameSize * 2;
		this.extraCols = this.colFrameSize * 2;
		
		
		
		
	}
	public void initAry() {
		this.zeroFrameAry = new int [this.numImgRows + this.extraRow][this.numImgCols + this.extraCols];
		this.morphAry = new int [this.numImgRows + this.extraRow][this.numImgCols + this.extraCols];
		this.tempAry = new int [this.numImgRows + this.extraRow][this.numImgCols + this.extraCols];
		this.structAry = new int [this.numStructRows][this.numStructCols];
		
	}
	public void zero2DAry(int[][] Ary,int rows,int cols) {
		for (int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				Ary[i][j] = 0;
				
			}
			
		}
	 
	}
	
	public void loadImg(Scanner file, int[][] Ary, int frame) {
		if (frame == 1) {
		for (int i = 0; i < this.numImgRows; i++) {
			for(int j = 0; j < this.numImgCols; j++) {
				if (file.hasNextInt())Ary[rowOrigin + i][colOrigin + j] = file.nextInt();
				}	
			}
		}
		else 
		{
			for (int i = 0; i < this.numStructRows ; i++) {
				for(int j = 0; j < this.numStructCols ; j++) {
					
					if (file.hasNextInt())Ary[i][j] = file.nextInt();
				}	
				
			}
		}
		
		
	}

	public void prettyPrint(int[][] Ary, BufferedWriter file, int frame) throws IOException {
		if (frame == 1) {
			
			file.write( (this.numImgRows) + " " + Integer.toString(this.numImgCols) + " "  );
			file.write( Integer.toString(this.imgMin) + " " +  Integer.toString(this.imgMax) );
			file.write("\n");
			for (int i = this.rowFrameSize; i < this.numImgRows + this.rowFrameSize; i++) {
				for(int j = this.colFrameSize; j < this.numImgCols + this.colFrameSize; j++) {
					if (Ary[i][j] == 1) file.write( Integer.toString(Ary[i][j]) + " ");
					else file.write(". ");
							
				}
				file.write("\n");
			}
			
		}
		else {
			file.write( Integer.toString(this.numStructRows) + " " + Integer.toString(this.numStructCols) + " "  );
			file.write( Integer.toString(this.structMin) + " " +  Integer.toString(this.structMax) );
			file.write("\n");
			for (int i = 0; i < this.numStructRows ; i++) {
				for(int j = 0; j < this.numStructCols ; j++) {
					if (Ary[i][j] == 1) file.write("1 ");
					else file.write(". ");
							
				}
				file.write("\n");
			}
		}
		file.write("\n\n");
		
		
	}


	public void ArytoFile(int[][] Ary, BufferedWriter file) throws IOException {
		file.write( Integer.toString(this.numImgRows) + " " + Integer.toString(this.numImgCols) + " "  );
		file.write( Integer.toString(this.imgMin) + " " +  Integer.toString(this.imgMax) );
		file.write("\n");
		for (int i = this.rowFrameSize; i < this.numImgRows + this.rowFrameSize; i++) {
			for(int j = this.colFrameSize; j < this.numImgCols + this.colFrameSize; j++) {
				file.write( Integer.toString(Ary[i][j]) + " ");
			}
			file.write("\n");
		}
		file.write("\n\n");		
		
	}
	
	public void ComputeDilation(int[][]inAry, int[][] outAry) {
			
			for (int i = this.rowFrameSize;i < this.numImgRows + this.rowFrameSize; i++) {
				for (int j = this.colFrameSize; j < this.numImgCols + this.colFrameSize; j++) {
					if (inAry[i][j] > 0) dilation(i, j, outAry);
				}
			}
			
		}

	private void dilation(int i, int j, int[][] outAry) {
			int row = i - this.rowOrigin;
			int col = j - this.colOrigin;
			for (int r = 0; r < this.numStructRows; r++) {
				for (int c = 0; c < this.numStructCols; c++) {
					if(structAry[r][c] == 1) {
						outAry[row + r][col + c] = structAry[r][c];
						
					}
				}
			}
		
	}

	public void ComputeErosion(int[][]inAry, int[][] outAry) {

		for (int i = this.rowFrameSize;i < this.numImgRows + this.rowFrameSize; i++) {
			for (int j = this.colFrameSize; j < this.numImgCols + this.colFrameSize; j++) {
				if (inAry[i][j] > 0) erosion(i, j, inAry, outAry);
			}
		}
		
	}

	private void erosion(int i, int j, int[][] inAry, int[][] outAry) {
		int row = i - this.rowOrigin;
		int col = j - this.colOrigin;
		int input = 1;
		for (int r = 0; r < this.numStructRows; r++) {
			for (int c = 0; c < this.numStructCols; c++) {
				if (structAry[r][c] == 1 ) {
					if(row  != this.numImgRows  && col  != this.numImgCols) {
						if(structAry[r][c] != inAry[row + r][col + c]) input = 0;
					}
				}
			}
		}
		outAry[i][j] = input;	
	}

	public void ComputeClosing(int[][] inAry, int[][] outAry, int[][] tempAry) {
		ComputeDilation(inAry, tempAry);
		ComputeErosion(tempAry,outAry);
		
	}
	public void ComputeOpening(int[][] inAry, int[][] outAry, int[][] tempAry) {
		ComputeErosion(inAry, tempAry);
		ComputeDilation(tempAry,outAry);
		
	
		
	}
	
}
