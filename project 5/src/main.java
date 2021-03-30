import java.io.*;
import java.util.Scanner;

public class main {

	public static void main(String[] args) throws IOException {
		int numImgRows = 0, numImgCols = 0;
		int minImg = 0, maxImg = 0;
		
		try(
				Scanner inFile = new Scanner(new BufferedReader( new FileReader( args[0])));
				BufferedWriter outFile_1 = new BufferedWriter( new FileWriter( args[1]));
				BufferedWriter outFile_2 = new BufferedWriter( new FileWriter( args[2]));
				BufferedWriter skeletonFile = new BufferedWriter( new FileWriter("skeleton.txt"));
				BufferedWriter decompressFile = new BufferedWriter( new FileWriter( "decompress.txt"));

			){
			
			if (inFile.hasNextInt()) numImgRows = inFile.nextInt();
			if (inFile.hasNextInt()) numImgCols = inFile.nextInt();
			if (inFile.hasNextInt()) minImg = inFile.nextInt();
			if (inFile.hasNextInt()) maxImg = inFile.nextInt();
			
			ImageProcessing readObj = new ImageProcessing();
			readObj.readImageheader(numImgRows, numImgCols, minImg, maxImg);
			readObj.initAry();
			readObj.setZero(readObj.zeroFramedAry);
			readObj.loadImg(inFile);
			readObj.Compute8Distance(outFile_1);
			readObj.skeletonExtraction(skeletonFile, outFile_1);
			// reopen the skeleton file
			Scanner skeletonFile1 = new Scanner(new BufferedReader( new FileReader("skeleton.txt")));
			readObj.skeletonExpansion(skeletonFile1, outFile_2);
			readObj.ary2File(decompressFile);
			
			System.out.println("Compilation Complete");
	
			
		}
	}

}
