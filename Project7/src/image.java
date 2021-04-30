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
public class image {
	public int numRows = -1;
	public int numCols = -1;
	public int minValue = -1;
	public int maxValue = -1;
	
	public int[][] imgAry;
	public int[][] boundaryAry;
	public int[][] CCAry;
	
	
	
	public void initAry() {
		this.imgAry = new int [numRows + 2][numCols + 2];
		this.boundaryAry = new int [numRows + 2][numCols + 2];
		this.CCAry = new int [numRows + 2][numCols + 2];
	}
	public void setZero(int[][] Ary) {
		for (int i = 0; i < numRows + 2; i++) {
			for(int j = 0; j < numCols + 2; j++) {
				Ary[i][j] = 0;
			}	
		}
	}
	
	public void loadImg(Scanner file) throws IOException {
		
		if (file.hasNextInt()) this.numRows = file.nextInt();
		if (file.hasNextInt()) this.numCols = file.nextInt();
		if (file.hasNextInt()) this.minValue = file.nextInt();
		if (file.hasNextInt()) this.maxValue = file.nextInt();
		initAry();
		setZero(imgAry);
		
		
		for (int i = 1; i < this.numRows + 1; i++) {
			for(int j = 1; j < this.numCols + 1; j++) {		
				if (file.hasNextInt())imgAry[i][j] = file.nextInt();
			}	
		}
	
	}
	
}
