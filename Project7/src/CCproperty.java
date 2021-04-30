/*
    class: CSCI 381/780
    First Name: Trisha
    Last Name: Espejo
    Project 7
    language: JAVA
    project name: Chain Code
    
 */
import java.io.BufferedWriter;
import java.util.Scanner;

public class CCproperty {
	public int numRows = -1;
	public int numCols = -1;
	public int minValue = -1;
	public int maxValue = -1;
	public int label = 0;
	public int numpixels = 0;
	public int minRow = -1;
	public int minCol = -1;
	public int maxRow = -1;
	public int maxCol = -1;
	
	public void readImageheader(Scanner file){
		if (file.hasNextInt()) this.numRows = file.nextInt();
		if (file.hasNextInt()) this.numCols = file.nextInt();
		if (file.hasNextInt()) this.minValue = file.nextInt();
		if (file.hasNextInt()) this.maxValue = file.nextInt();
	}
	public void clearCC(int[][] Ary) {
		for (int i = 0; i < numRows + 2; i++) {
			for(int j = 0; j < numCols + 2; j++) {
				Ary[i][j] = 0;
			}	
		}
	}
	public void loadprop(Scanner file) {
		if (file.hasNextInt()) this.label = file.nextInt();
		if (file.hasNextInt()) this.numpixels = file.nextInt();
		if (file.hasNextInt()) this.minRow = file.nextInt();
		if (file.hasNextInt()) this.minCol = file.nextInt();
		if (file.hasNextInt()) this.maxRow = file.nextInt();
		if (file.hasNextInt()) this.maxCol = file.nextInt();
		
		
	}
	public void loadCCAry(int[][] imgAry, int[][] CCAry) {
		for(int i = minRow + 1; i < maxRow + 2; i++) {
			for(int j = minCol + 1; j < maxCol + 2; j++) {
				CCAry[i][j] = imgAry[i][j];
			}
		}
	}
}
