/*
    class: CSCI 381/780
    First Name : Trisha
    Last Name: Espejo
    Project 2
    language: C++
    project name: Noise Filters
    
 */
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <cmath>

using namespace std;
class imageProcessing {
public :
    int numRows = -1, numCols= -1, minVal = -1, maxVal = -1;
    int newMin = -1, newMax = -1;
    int thresholdValue = 0;
    int neighborAry[9];
    int neighbor5x5[5][5];
    int CPmasks[8][5][5];
    
    int **mirror3by3Ary;
    int **mirror5by5Ary;
    int **avgAry;
    int **medianAry;
    int **CPAry;
    int **thrAry;

    int loadCPmasks[8][5][5] = {
        { {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 1, 1, 1, 0}, {1, 1, 1, 1, 1} },
        { {1, 0, 0, 0, 0}, {1, 1, 0, 0, 0}, {1, 1, 1, 0, 0}, {1, 1, 0, 0, 0}, {1, 0, 0, 0, 0} },
        { {1, 1, 1, 1, 1}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 1}, {0, 0, 0, 1, 1}, {0, 0, 1, 1, 1}, {0, 0, 0, 1, 1}, {0, 0, 0, 0, 1} },
        { {1, 1, 1, 0, 0}, {1, 1, 1, 0, 0}, {1, 1, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0} },
        { {0, 0, 1, 1, 1}, {0, 0, 1, 1, 1}, {0, 0, 1, 1, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 1, 1}, {0, 0, 1, 1, 1}, {0, 0, 1, 1, 1} },
        { {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {1, 1, 1, 0, 0}, {1, 1, 1, 0, 0}, {1, 1, 1, 0, 0} }
    
    };
    
    
public:
    imageProcessing(ifstream & input){
        read_header(input);
        
        for (int i = 0; i < 9; ++i)
            neighborAry[i] = 0;
        for (int i = 0; i < 5; ++i){
            for (int j = 0; j < 5; ++j)
            {
                neighbor5x5[i][j] = 0;
            }
        }
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 5; ++j){
                for (int k = 0; k < 5; ++k)
                    CPmasks[i][j][k] = 0;
            }
        }
        
        this -> mirror3by3Ary = new int*[this -> numRows + 2];
        for (int i = 0; i < this -> numRows + 2; ++i){
            mirror3by3Ary[i] = new int[ this -> numCols + 2];
            for (int j = 0; j < this -> numCols + 2; ++j)
            {
                mirror3by3Ary[i][j] = 0;
            }
        }
        
        this -> mirror5by5Ary = new int*[this -> numRows + 4];
        for (int i = 0; i < this -> numRows + 4; ++i){
            mirror5by5Ary[i] = new int[ this -> numCols + 4];
            for (int j = 0; j < this -> numCols + 4; ++j)
                mirror5by5Ary[i][j] = 0;
        }
        
        this -> avgAry = new int*[this -> numRows + 2];
        for (int i = 0; i < this -> numRows + 2; ++i){
            avgAry[i] = new int[ this -> numCols + 2];
            for (int j = 0; j < this -> numCols + 2; ++j)
                avgAry[i][j] = 0;
            
        }
        
        this -> medianAry = new int*[this -> numRows + 2];
        for (int i = 0; i < this -> numRows + 2; ++i){
            medianAry[i] = new int[ this -> numCols + 2];
            for (int j = 0; j < this -> numCols + 2; ++j)
                medianAry[i][j] = 0;
            
        }
        this -> CPAry= new int*[this -> numRows + 4];
        for (int i = 0; i < this -> numRows + 4; ++i){
            CPAry[i] = new int[ this -> numCols + 4];
            for (int j = 0; j < this -> numCols + 4; ++j)
                CPAry[i][j] = 0;
        }
        this -> thrAry = new int*[this -> numRows + 2];
        for (int i = 0; i < this -> numRows + 2; ++i){
            thrAry[i] = new int[ this -> numCols + 2];
            for (int j = 0; j < this -> numCols + 2; ++j)
                thrAry[i][j] = 0;
        }
       
        
    }
    
        
    void read_header(ifstream & input){
        input >> this->numRows >> this->numCols >> this->minVal >> this->maxVal;
        newMin = minVal;
        newMax = maxVal;
        
        
    }
    void loadImage (ifstream & input){
        
        for (int i = 1; i < this -> numRows + 1 ; ++i){
            for (int j = 1; j < this -> numCols + 1 ; ++j)
            {
                input >> mirror3by3Ary[i][j];
                mirror5by5Ary[i + 1][j + 1] = mirror3by3Ary[i][j] ;
            }
        }
  
    }
    
    void topLeftCorner (int **Ary, int framesize){
        if (framesize == 1)Ary[0][0] = Ary[1][0];
        if (framesize == 2){
            Ary[0][0] = Ary[3][3];
            Ary[1][1] = Ary[2][2];
            Ary[0][1]= Ary[3][2];
            Ary[1][0]= Ary[2][3];
        }
    }
    void topRightCorner (int **Ary, int framesize){
        if (framesize == 1) Ary[0][numCols + 1] = Ary[1][numCols + 1];
        if (framesize == 2){
            Ary[1][numCols + 2] =  Ary[2][numCols + 1];
            Ary[0][numCols + 3] = Ary[3][numCols];
            Ary[1][numCols + 3] = Ary[3][numCols + 1];
            Ary[0][numCols + 2] = Ary[2][numCols];
        }
        
    }
    void bottomLeftCorner (int **Ary, int framesize){
        if (framesize == 1) Ary[numRows + 1][0] = Ary[numRows][0];
        if (framesize == 2){
            Ary[numRows + 2][1] = Ary[numRows + 1][2];
            Ary[numRows + 3][0] = Ary[numRows][3];
            Ary[numRows + 2][0] =Ary[numRows][2];
            Ary[numRows + 3][1] = Ary[numRows + 1][3];
        }
    }
    void bottomRightCorner (int **Ary, int framesize){
        if (framesize == 1) Ary[numRows + 1][numCols + 1] = Ary[numRows][numCols + 1];
        if (framesize == 2){
            Ary[numRows + 2][numCols + 2] = Ary[numRows + 1][numCols + 1];
            Ary[numRows + 3][numCols + 3] = Ary[numRows ][numCols ];
            Ary[numRows + 2][numCols + 3] = Ary[numRows ][numCols + 1 ];
            Ary[numRows + 3][numCols + 2] = Ary[numRows + 1][numCols];
        }
    }
    void mirrorFraming (int **Ary,int frameSize){
        
            int x = frameSize;
            int y = frameSize + 1;
            if (frameSize == 1)
            {
                for (int i = 1; i < this -> numCols + 1; i++)
                {
                    
                    mirror3by3Ary[0][i] = mirror3by3Ary[1][i];
                    mirror3by3Ary[i][0] = mirror3by3Ary[i][1];
                    mirror3by3Ary[numRows + 1][i] = mirror3by3Ary[numRows ][i];
                    mirror3by3Ary[i][numCols + 1] = mirror3by3Ary[i][numCols];
                }
            }
            if (frameSize == 2){
                for (int i  = 2; i > 0; i--)
                    {
                        for (int j = 2; j < this -> numCols + 2; j++)
                        {
                            Ary[i - 1][j] = Ary[x][j];
                             Ary[j][i - 1] = Ary[j][x];
                             Ary[numRows + x][j] = Ary[numRows  - (frameSize - y) ][j];
                             Ary[j][numCols + x] = Ary[j][numCols  - (frameSize - y)];
                        }
                        x++;
                        y--;
                    }
            }
            topLeftCorner(Ary, frameSize);
            topRightCorner(Ary, frameSize);
            bottomLeftCorner(Ary, frameSize);
            bottomRightCorner(Ary, frameSize);
        
     }
    
    void imgReformat(int **inAry, ofstream & OutImg,  int frameSize){
        OutImg <<" " << this->numRows <<" " << this->numCols << " " << this->newMin << " " << this->newMax << endl;
        OutImg << endl;
        string str = to_string(newMax);;
        double Width = str.length();
        double WW = 0;
        int  r = 0, c = 0;
        r = frameSize;
        c = frameSize;
        str = to_string(inAry[r][c]);
        WW  = str.length();
        while (WW < Width){
            while (r < numRows + frameSize){
                while (c < numCols + frameSize){
                    str = to_string(inAry[r][c]);
                    WW  = str.length();
                    OutImg << setw(3) << inAry[r][c] ;
                    c++;
                }
                OutImg << endl;
                r++;
                c = frameSize;
            }
            WW++;
       }

    }
    
    void computeAvg(){
        newMin = 9999;
        newMax = 0;
        //int avg = 0;
        int r = 1, c = 1;
        
        
       while (r < numRows + 1 ){
            c = 1;
            while (c < numCols + 1 ){
               
               avgAry[r][c] = avg3x3(r, c);
               
               if (newMin > avgAry[r][c]) newMin = avgAry[r][c];
               if (newMax < avgAry[r][c]) newMax = avgAry[r][c];
               c++;
            }
            r++;
        }

    }
    
    int avg3x3(int r, int c){
        int avg = 0;
        int sum = 0;
        int index = 0;

        for(int i = r - 1; i < r + 2; i++){
            for (int j = c - 1; j < c + 2; j++){
                neighborAry[index] = mirror3by3Ary[i][j];
                index++;
            }
        }
        
        for (int a = 0; a < 9; a++)
            sum = neighborAry[a] + sum;
            
        avg = sum / 9;
        return avg;
    }
    
    void computeMedian(){
        newMin = 9999;
        newMax = 0;
        int r = 1, c = 1;
        
        
        while (r < numRows + 1 ){
           c = 1;
            while (c < numCols + 1 ){
               
                medianAry[r][c] = median(r, c);
                if (newMin > medianAry[r][c]) newMin = medianAry[r][c];
                if (newMax < medianAry[r][c]) newMax = medianAry[r][c];
                c++;
           }
           r++;
        }
        

    }
    
    int median(int r, int c){
        int mid = 0;
        int index = 0;
         for(int i = r - 1; i < r + 2; i++){
             for (int j = c - 1; j < c + 2; j++){
                 neighborAry[index] = mirror3by3Ary[i][j];
                 index++;
             }
         }
        sort( neighborAry );
        mid = neighborAry[4];
        return mid;
        
    }
    
    void sort(int *Ary){
        int temp = 0;
       
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8 - i ; j++){
                if (Ary[j] > Ary[j+ 1]){
                    temp = Ary[j];
                    Ary[j] = Ary[j + 1];
                    Ary[j + 1] = temp;
                }
            }
        }
    }
    
    void computeCPfilter(){
        newMin = 9999;
        newMax = 0;
        int r = 2, c = 2;
        
        while (r < numRows + 2 ){
            c = 2;
            while (c < numCols + 2 ){
                CPAry[r][c] = CP5x5(r, c);
                if (newMin > CPAry[r][c]) newMin = CPAry[r][c];
                if (newMax < CPAry[r][c]) newMax = CPAry[r][c];
                c++;
                }
            r++;
        }
    }
   
    int CP5x5(int r, int c){
        
        int result = 0;
        int row = r - 2;
        int cols = c - 2;
        double sum = 0;
        double avg = 0.0;
        int diff = 0;
        int min_Dif = 999999;
        
        for(int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++)
                neighbor5x5[i][j] = mirror5by5Ary[row + i][cols + j];
        }
        
        for (int i = 0; i < 8; i++){
            sum = convolution(i);
            avg = sum / 8;
            diff = abs(avg - mirror5by5Ary[r][c] );
            if (min_Dif  > diff){
                min_Dif = diff;
                result = avg;
                
            }
       }
        return result;
    
    }
    
    int convolution(int i){
        int sum = 0;
       
        for(int j = 0; j < 5; j++){
            for (int k = 0; k < 5; k++){
                CPmasks[i][j][k] = loadCPmasks[i][j][k] * neighbor5x5[j][k];
                if (CPmasks[i][j][k] != 0)
                    sum = (CPmasks[i][j][k]) + sum;
            }
        }
        // remove 'X' or the center pixel
        sum = sum - CPmasks[i][2][2];
                return sum;
    }

        
    void threshold( int **Ary1, int **Ary2,int framesize){
        newMin = 0;
        newMax = 1;
        int r = framesize;
        int c = framesize;
        while(r < numRows + framesize){
            c = framesize;
                while (c < numCols + framesize){
                    if(Ary1[r][c] >= thresholdValue)
                        Ary2[r][c] = 1;
                    else
                        Ary2[r][c] = 0;
                    c++;
                    
                }
            r++;
            
        }
        
    }
    
    void AryToFile (int **thrArry, ofstream & output ,int framesize){
        int r = framesize;
        int c = framesize;
        output << "The threshold value is: " << thresholdValue << endl;
        output << " " << this->numRows << " " << this->numCols << " " << this->newMin << " " << this->newMax << endl;
        for(r = framesize; r < numRows + framesize; r++){
            for(c = framesize; c < numCols + framesize; c++){
                output << thrArry[r][c] << " ";
            }
            output << endl;
        }
    }
    
    void prettyPrint (int **thrArry, ofstream & output, int framesize){
        int r = framesize;
        int c = framesize;
        output << "The threshold value is: " << thresholdValue << endl;
        output << " " << this->numRows << " " << this->numCols << " " << this->newMin << " " << this->newMax << endl;
        for(r = framesize; r < numRows + framesize; r++){
            for(c = framesize; c < numCols + framesize; c++){
                if (thrArry[r][c] == 1)
                    output << "1" << " " ;
                else
                    output << "." << " " ;
                
            }
            output << endl;
        }
    }
  

    void free_Heap (){
        for (int i = 0; i < this->numRows + 2; ++i)
            delete[] this->mirror3by3Ary[i];
        delete[] this->mirror3by3Ary;
        
        
        for (int i = 0; i < this->numRows + 2; ++i)
            delete[] this->avgAry[i];
        delete[] this->avgAry;
        
        for (int i = 0; i < this->numRows + 2; ++i)
            delete[] this->medianAry[i];
        delete[] this->medianAry;
        
        for (int i = 0; i < this->numRows + 2; ++i)
            delete[] this->thrAry[i];
        delete[] this->thrAry;
        
        for (int i = 0; i < this->numRows + 4; ++i)
            delete[] this->mirror5by5Ary[i];
        delete[] this->mirror5by5Ary;

        for (int i = 0; i < this->numRows + 4; ++i)
            delete[] this->CPAry[i];
        delete[] this->CPAry;
    
    }


};

int main(int argc, const char * argv[]) {
    int thrVal = atoi(argv[2]);
    
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);
     
    string output1 = argv[3];
    ofstream rfImg;
    rfImg.open(output1);
    
    
    string output2 = argv[4];
    ofstream AvgOutImg;
    AvgOutImg.open(output2);
    
    string output3 = argv[5];
    ofstream AvgThrImg;
    AvgThrImg.open(output3);
    
    string output4 = argv[6];
    ofstream AvgPrettyPrint;
    AvgPrettyPrint.open(output4);
    
    
    string output5 = argv[7];
    ofstream MedianOutImg;
    MedianOutImg.open(output5);
    
    string output6 = argv[8];
    ofstream MedianThrImg;
    MedianThrImg.open(output6);
   
    
    string output7 = argv[9];
    ofstream MedianPrettyPrint;
    MedianPrettyPrint.open(output7);
    
    string output8 = argv[10];
    ofstream CPOutImg;
    CPOutImg.open(output8);
    
    string output9 = argv[11];
    ofstream CPThrImg;
    CPThrImg.open(output9);
    
    string output10 = argv[12];
    ofstream CPPrettyPrint;
    CPPrettyPrint.open(output10);
    
    imageProcessing* read_img = new imageProcessing(input);
    read_img -> loadImage(input);
    read_img -> thresholdValue = thrVal;
    read_img -> mirrorFraming(read_img -> mirror3by3Ary, 1);
    read_img -> imgReformat(read_img -> mirror3by3Ary, rfImg, 1);
    
    read_img -> computeAvg();
    read_img -> imgReformat(read_img -> avgAry, AvgOutImg, 1);
    read_img -> threshold(read_img -> avgAry, read_img -> thrAry, 1);
    read_img -> AryToFile (read_img -> thrAry,  AvgThrImg, 1);
    read_img -> prettyPrint(read_img -> thrAry,  AvgPrettyPrint, 1);
    
    read_img -> computeMedian();
    read_img -> imgReformat(read_img -> medianAry, MedianOutImg, 1);
    read_img -> threshold(read_img -> medianAry, read_img -> thrAry, 1);
    read_img -> AryToFile (read_img -> thrAry,  MedianThrImg, 1);
    read_img -> prettyPrint(read_img -> thrAry,  MedianPrettyPrint, 1);
    
    read_img -> mirrorFraming(read_img -> mirror5by5Ary, 2);
    read_img -> computeCPfilter();
    read_img -> imgReformat(read_img -> CPAry, CPOutImg, 2);
    read_img -> threshold(read_img -> CPAry, read_img -> thrAry, 2);
    read_img -> AryToFile (read_img -> thrAry,  CPThrImg, 2);
    read_img -> prettyPrint(read_img -> thrAry,  CPPrettyPrint, 2);
    
    read_img-> free_Heap();
 
    input.close();
    rfImg.close();

    AvgOutImg.close();
    AvgThrImg.close();
    AvgPrettyPrint.close();
     
    MedianOutImg.close();
    MedianThrImg.close();
    MedianPrettyPrint.close();
    
    CPOutImg.close();
    CPThrImg.close();
    CPPrettyPrint.close();
    
}
    
    
