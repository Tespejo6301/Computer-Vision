/*
    class: CSCI 381/780
    First Name: Trisha
    Last Name: Espejo
    Project 7
    language: JAVA
    project name: Chain Code
    
 */
import java.io.*;
import java.util.*;

public class main {

	public static void main(String[] args) throws IOException {
		
		try(
				Scanner imgFile = new Scanner(new BufferedReader( new FileReader( args[0])));
				Scanner CCFile = new Scanner(new BufferedReader( new FileReader( args[1])));
				BufferedWriter chainCodeFile = new BufferedWriter( new FileWriter("chainCode.txt"));
				BufferedWriter boundaryFile = new BufferedWriter( new FileWriter("Boundary.txt"));
		 ){
			
			image img = new image();
			CCproperty prop = new CCproperty();
			chainCode chain = new chainCode();
			img.loadImg(imgFile);
			prop.readImageheader(CCFile);
			int numCC = 0;
			if (CCFile.hasNextInt()) numCC = CCFile.nextInt();
			chain.numCC = numCC;
			chain.constructor();
			chain.CC = prop;	
			chain.printImgHeader(chainCodeFile);
			while(prop.label <= chain.numCC){
				prop.loadprop(CCFile);
				prop.clearCC(img.CCAry);
				prop.loadCCAry(img.imgAry, img.CCAry);
				chain.CC = prop;
				chain.getChainCode(img.CCAry, chainCodeFile);
				if (prop.label == chain.numCC)
					break;
		
			}
			System.out.println("finish getting chain code");
			imgFile.close();
			CCFile.close();
			chainCodeFile.close();
			Scanner chainCodeFile2 = new Scanner(new BufferedReader( new FileReader( "chainCode.txt")));
			chain.constructBoundary (img.boundaryAry, chainCodeFile2);
			System.out.println("finish creating boundary");
			chain.reformatPrettyPrint(img.boundaryAry, boundaryFile);
			System.out.println("finish printing boundary");
			boundaryFile.close();
			System.out.println("Compilation Complete");
			
		
		
	 }

	}

}
