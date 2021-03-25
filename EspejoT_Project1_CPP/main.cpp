/*
    class: CSCI 381/780
    First Name : Trisha
    Last Name: Espejo
    Project 1
    language: C++
    project name: Histogram & Threshold
    
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;
class Image{
public :
    int numRows = -1, numCols= -1, minVal = -1, maxVal = -1;
    int *hisArray;
    
    int thresholdValue = -1;
public:
    Image(ifstream & input){
        read_header(input);
        
        this -> hisArray = new  int[this->maxVal + 1];
        for (int i = 0; i < this -> maxVal + 1; ++i){
            hisArray[i] = 0;
            
        }
        
    }
    void read_header(ifstream & input)
    {
        input >> this->numRows >> this->numCols >> this->minVal >> this->maxVal;
    }
    void computeHist (ifstream & input){
        
        int **pixel;
        int pixelValue = 0;
        
        
       
        pixel = new int*[this -> numRows];
        for (int i = 0; i < this -> numRows; ++i){
            pixel[i] = new int[ this -> numCols ];
            for (int j = 0; j < this -> numCols; ++j)
                pixel[i][j] = 0;
        }
        
        
        for (int i = 0; i < this -> numRows; ++i){
            for (int j = 0; j < this -> numCols; ++j)
            {
               
                input >> pixel[i][j];
                pixelValue = pixel[i][j];
                hisArray[pixelValue]++;
            }
        }
        
      
        for (int i = 0; i < this->numRows; ++i)
            delete[] pixel[i];
        delete[] pixel;
    }
    
    
    
    void printHist(ofstream & output)
    {
        
        output <<" " << this->numRows <<" " << this->numCols << " " << this->minVal << " " << this->maxVal << endl;
        for (int i = 0; i < this -> maxVal + 1; ++i)
        {
            output << i << " ";
            output << hisArray[i] << endl;
        }
    }
    
    
    void displayHist (ofstream & output2){
        
        int count = 0;
        int temp = 0;
        
        output2 <<" " << this->numRows <<" " << this->numCols << " " << this->minVal << " " << this->maxVal << endl;
        
        for (int i = 0; i < this -> maxVal + 1; ++i){
            temp = hisArray[i];
            if (count < 10)
                output2 << count << "  " << "("<< temp << ")" << ": ";
            else
                output2 << count << " " << "("<< temp << ")" << ": ";
            if ( temp > 0 )
            {
                if (temp > 70)
                    temp = 70;
                for (int j = 0; j < temp; j++)
                    output2 << "+" ;
            }
            output2 << endl;
            count++;
        }
            
    }
    void free_Heap (){
        delete[] this->hisArray;
        
    }
    
    void threshold (ifstream & input, ofstream & output3, ofstream & output4, int thrVal)
    {
        thresholdValue = thrVal;
        int **pixel;
        int pixelValue = 0;
        minVal = 0;
        maxVal = 1;
        
        output3 <<" " << this->numRows <<" " << this->numCols << " " << this->minVal << " " << this->maxVal << endl;
        output4 <<" " << this->numRows <<" " << this->numCols << " " << this->minVal << " " << this->maxVal << endl;
        
        pixel = new int*[this -> numRows];
        for (int i = 0; i < this -> numRows; ++i){
            pixel[i] = new int[ this -> numCols ];
            for (int j = 0; j < this -> numCols; ++j)
                 pixel[i][j] = 0;
        }
        
        for (int i = 0; i < this -> numRows; ++i){
            for (int j = 0; j < this -> numCols; ++j)
            {
                input >> pixel[i][j];
                pixelValue = pixel[i][j];
                if (thresholdValue <= pixelValue){
                    output3 << "1" << " ";
                    output4 << "1" << " ";
                }
                else{
                    output3 << "0" << " ";
                    output4 << "." << " ";
                }
            }
            output3 << endl;
            output4 << endl;
        }
        
        for (int i = 0; i < this->numRows; ++i)
            delete[] pixel[i];
        delete[] pixel;
    }

};
int main(int argc, const char * argv[]) {
    
    // input 1
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);
    
    // output 1
    string outputName1 = argv[3];
    ofstream outputFile1;
    outputFile1.open(outputName1);
    
    //output 2
    string outputName2 = argv[4];
    ofstream outputFile2;
    outputFile2.open(outputName2);
    
    // ouput 3
    string outputName3 = argv[5];
    ofstream outputFile3;
    outputFile3.open(outputName3);
    
    //output 4
    string outputName4 = argv[6];
    ofstream outputFile4;
    outputFile4.open(outputName4);
    
    
    if (input.is_open()){
        if (outputFile1.is_open()){
            if (outputFile2.is_open()){
                
                Image* read_img = new Image(input);
                read_img -> computeHist(input);
                read_img -> printHist(outputFile1);
                read_img -> displayHist(outputFile2);
                input.close();
                outputFile1.close();
                outputFile2.close();
                read_img -> free_Heap();
                delete read_img;
            } else cout << "Error Output 2"<< endl;
        } else cout << "Error Output 1"<< endl;
    }
    else cout << "Error Input"<< endl;
    

    input.open(inputName);
    int thrVal = atoi(argv[2]);
    
    if (input.is_open()){
        if (outputFile3.is_open()){
            if (outputFile4.is_open()){
                Image* read_img = new Image(input);
                outputFile3 << "The threshold value is " << thrVal << endl;
                outputFile4 << "The threshold value is " << thrVal << endl;
                read_img -> threshold(input, outputFile3, outputFile4, thrVal);
                input.close();
                outputFile3.close();
                outputFile4.close();
                
            } else cout << "Error Output 4"<< endl;
        } else cout << "Error Output 3"<< endl;
    }
    else cout << "Error Input"<< endl;
    return 0;
    
}
    


