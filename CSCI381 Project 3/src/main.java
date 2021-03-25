import java.io.*;
import java.util.Scanner;

public class main {

	public static void main(String[] args) throws IOException {
		int numImgRows = 0, numImgCols = 0;
		int minImg = 0, maxImg = 0;
		
		int numStructRows = 0, numStructCols = 0;
		int minStruct = 0, maxStruct = 0;
		int minOrigin = 0, maxOrigin = 0;
		int row = 0;
		int col = 0;
				
		try(
				Scanner imgFile = new Scanner(new BufferedReader( new FileReader( args[0])));
				Scanner structFile = new Scanner(new BufferedReader( new FileReader( args[1])));
				BufferedWriter dilateOutFile = new BufferedWriter( new FileWriter( args[2]));
				BufferedWriter erodeOutFile = new BufferedWriter( new FileWriter( args[3]));
				BufferedWriter closingOutFile = new BufferedWriter( new FileWriter( args[4]));
				BufferedWriter openingOutFile = new BufferedWriter( new FileWriter( args[5]));	
				BufferedWriter prettyPrintFile = new BufferedWriter( new FileWriter( args[6]));
			){
			
			//img file
			if (imgFile.hasNextInt()) numImgRows = imgFile.nextInt();
			if (imgFile.hasNextInt()) numImgCols = imgFile.nextInt();
			if (imgFile.hasNextInt()) minImg = imgFile.nextInt();
			if (imgFile.hasNextInt()) maxImg = imgFile.nextInt();
			
			//struct file
			if (structFile.hasNextInt()) numStructRows = structFile.nextInt();
			if (structFile.hasNextInt()) numStructCols = structFile.nextInt();
			if (structFile.hasNextInt()) minStruct = structFile.nextInt();
			if (structFile.hasNextInt()) maxStruct = structFile.nextInt();
			if (structFile.hasNextInt()) minOrigin = structFile.nextInt();
			if (structFile.hasNextInt()) maxOrigin = structFile.nextInt();
			
			
		
			Image readObj = new Image();
			readObj.readImageheader(numImgRows, numImgCols, minImg, maxImg);
			readObj.readStructheader(numStructRows, numStructCols, minStruct, maxStruct, minOrigin, maxOrigin);
			readObj.initAry();
			
			
			row = readObj.numImgRows + readObj.extraRow;
			col = readObj.numImgCols + readObj.extraCols;
			readObj.zero2DAry(readObj.zeroFrameAry, row, col);
			readObj.loadImg(imgFile, readObj.zeroFrameAry, 1);
			
			prettyPrintFile.write("Original Image: " + "\n\n");
			readObj.prettyPrint(readObj.zeroFrameAry, prettyPrintFile, 1);
			
			readObj.zero2DAry(readObj.structAry, numStructRows, numStructCols);
			readObj.loadImg(structFile, readObj.structAry, 0);
			prettyPrintFile.write("Struct Image: " + "\n\n");
			readObj.prettyPrint(readObj.structAry, prettyPrintFile, 0);
			
			readObj.zero2DAry(readObj.morphAry, row, col);
			readObj.ComputeDilation(readObj.zeroFrameAry, readObj.morphAry);
			readObj.ArytoFile(readObj.morphAry, dilateOutFile);
			prettyPrintFile.write("Dilation: " + "\n\n");
			readObj.prettyPrint(readObj.morphAry, prettyPrintFile, 1);
			
			
			readObj.zero2DAry(readObj.morphAry, row, col);
			readObj.ComputeErosion(readObj.zeroFrameAry, readObj.morphAry);
			readObj.ArytoFile(readObj.morphAry, erodeOutFile);
			prettyPrintFile.write("Erosion: " + "\n\n");
			readObj.prettyPrint(readObj.morphAry, prettyPrintFile, 1);
			
			
			readObj.zero2DAry(readObj.morphAry, row, col);
			readObj.ComputeClosing(readObj.zeroFrameAry, readObj.morphAry, readObj.tempAry);
			readObj.ArytoFile(readObj.morphAry, closingOutFile);
			prettyPrintFile.write("Closing: " + "\n\n");
			readObj.prettyPrint(readObj.morphAry, prettyPrintFile, 1);
			
		
			readObj.zero2DAry(readObj.morphAry, row, col);
			readObj.zero2DAry(readObj.tempAry, row, col);
			readObj.ComputeOpening(readObj.zeroFrameAry, readObj.morphAry, readObj.tempAry);
			openingOutFile.write("Opening without fill in: " + "\n\n");
			readObj.ArytoFile(readObj.morphAry, openingOutFile);
			prettyPrintFile.write("Opening without fill in : " + "\n\n");
			readObj.prettyPrint(readObj.morphAry, prettyPrintFile, 1);
			
			
			readObj.zero2DAry(readObj.morphAry, row, col);
			readObj.zero2DAry(readObj.tempAry, row, col);
			int[][] tempAry2 = new int [readObj.numImgRows + readObj.extraRow][readObj.numImgCols + readObj.extraCols];
			readObj.ComputeOpening(readObj.zeroFrameAry, tempAry2, readObj.tempAry);
			readObj.zero2DAry(readObj.tempAry, row, col);
			readObj.ComputeClosing(tempAry2, readObj.morphAry, readObj.tempAry);
			openingOutFile.write("Opening with fill in for image 4 only: " + "\n\n");
			readObj.ArytoFile(readObj.morphAry, openingOutFile);
			prettyPrintFile.write("Opening with fill in : " + "\n\n");
			readObj.prettyPrint(readObj.morphAry, prettyPrintFile, 1);
			
			
			System.out.println("Compilation Complete" );
	
		}
		

	}

}
