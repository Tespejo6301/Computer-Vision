//
//  main.cpp
//  project 6
//
//  Created by Trisha Espejo on 4/5/21.
//

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Thinning {
    
    public:
    int numRows = -1;
    int numCols= -1;
    int minVal = -1;
    int maxVal = -1;
    int changeflag = 1;
    int cycleCount = -1;
   
    int **aryOne;
    int **aryTwo;
    
    
    // dynamically allocate aryOne and ary2 and obtain all values of the header
    void constructor(ifstream & input){
            input >> this->numRows >> this->numCols >> this->minVal >> this->maxVal;

            this -> aryOne = new int*[this -> numRows + 2];
            for (int i = 0; i < this -> numRows + 2; ++i){
                aryOne[i] = new int[ this -> numCols + 2];
            }
            this -> aryTwo = new int*[this -> numRows + 2];
            for (int i = 0; i < this -> numRows + 2; ++i){
                aryTwo[i] = new int[ this -> numCols + 2];
            }
        
        }
    
    // zero frame the ary
    void zeroFrame (int **Ary){
            for (int i = 0; i < this -> numRows + 2; ++i){
                for (int j = 0; j < this -> numCols + 2; ++j)
                    Ary[i][j] = 0;
            }
        
    }
    
    //adds the inFile values to aryOne
    void loadImage (ifstream & input){
        
        for (int i = 1; i < this -> numRows + 1 ; ++i){
            for (int j = 1; j < this -> numCols + 1 ; ++j)
                input >> aryOne[i][j];
        }
        
    }
    
    // copy all the values of aryTwo to aryOne
    void copyAry(int **ary1, int **ary2){
        for (int i = 0; i < this -> numRows + 2; ++i){
            for (int j = 0; j < this -> numCols + 2; ++j)
            ary1[i][j] = ary2[i][j];
        }
        
    }
    
    void NorthThinning(){
        //copyAry(aryTwo, aryOne);

        for (int i = 1; i < numRows +  1; i++){
            for (int j = 1; j < numCols + 1; j++){
                if ( aryOne[i][j] > 0)
                    North(i, j);
            }
        }
        
      
    }
    void North(int i, int j){
        
        bool Objneighbor = false;
        bool connector = false;
        // check if there is at least 4 object neighbor
        Objneighbor = neighbor(4, i, j);
        // check if it is a connector
        connector = connectedness(i, j);

        if (aryOne[i - 1][j] == 0 && Objneighbor == true && connector == false){
            aryTwo[i][j] = 0;
            changeflag++;
        }
        
 
    }
    
    void SouthThinning(){
        for (int i = 1; i < numRows +  1; i++){
            for (int j = 1; j < numCols + 1; j++){
                if ( aryOne[i][j] > 0)
                    South(i, j);
                
            }
        }
    }
    void South(int i, int j){
        bool Objneighbor = false;
        bool connect = false;
        // if there are at least 4 object neighbor set pixel to zero
        Objneighbor = neighbor(4, i, j);
        //if it is not a connector then flip
        connect = connectedness(i, j);
        //North neighbor == 0 then set pixel to 0
        if (aryOne[i + 1][j] == 0 && Objneighbor == true && connect == false){
            aryTwo[i][j] = 0;
            changeflag++;
        }
        
    }
    void WestThinning(){
        
        for (int i = 1; i < numRows +  1; i++){
            for (int j = 1; j < numCols + 1; j++){
                if ( aryOne[i][j] > 0)
                    West(i, j);
            }
        }
    }
    
    void West( int i, int j){
        bool Objneighbor = false;
        bool connect = false;
        // if there are at least 4 object neighbor set pixel to zero
        Objneighbor = neighbor(3, i, j);
        //if it is not a connector then flip
        connect = connectedness(i, j);
        //West neighbor == 0 then set pixel to 0
        if (aryOne[i][j - 1] == 0 && Objneighbor == true && connect == false){
            aryTwo[i][j] = 0;
            changeflag++;
        }
    }
    
    void EastThinning(){
        for (int i = 1; i < numRows +  1; i++){
            for (int j = 1; j < numCols + 1; j++){
                if ( aryOne[i][j] > 0)
                    East(i, j);
            }
        }
    }
    
    void East( int i, int j){
        bool Objneighbor = false;
        bool connect = false;
        // if there are at least 4 object neighbor set pixel to zero
        Objneighbor = neighbor(3, i, j);
        //if it is not a connector then flip
        connect = connectedness(i, j);
        //West neighbor == 0 then set pixel to 0
        if (aryOne[i][j + 1] == 0 && Objneighbor == true && connect == false){
            aryTwo[i][j] = 0;
            changeflag++;
        }
        
    }
    
    // North: objNeighbor = 4
    bool neighbor(int objNeighbor, int i, int j){
        bool result = false;
        int count = 0;
            for ( int row = i - 1; row <= i + 1; row++) {
                for ( int col = j - 1; col <= j + 1; col++) {
                    if ( row == i && col == j)
                        continue;
                    if (aryOne[row][col] > 0)
                        count++;
                }
            }
        
        
        if (count > objNeighbor)
            result = true;
        //cout << result;
        return result;
    }
    
    
    
    bool connectedness(int i, int j){
        
        bool TS = false;
        bool BS = false;
        bool LHS = false;
        bool RHS = false;
        for(int c = j - 1; c < j + 1; c++){
            if(aryOne[i - 1][c] == 1)
                TS = true;
            if(aryOne[i + 1][c] == 1)
                BS = true;
        }
        for(int r = i - 1; r < i + 1; r++){
            if(aryOne[r][j - 1] == 1)
                LHS = true;
            if(aryOne[r][j + 1] == 1)
                RHS = true;
        }
        
        
        // if left and right = 0 and TS is 1
        if (aryOne[i][j - 1] == 0 && aryOne[i][j + 1] == 0){
            if (TS && BS)
                return true;
        }
        //top and bottom == 0 and LHS and RHS == 1
        if (aryOne[i - 1][j] == 0 && aryOne[i + 1][j] == 0){
            if (LHS && RHS)
                return true;
        }
        // top and left = 0 and top-left = 1
        if (aryOne[i - 1][j] == 0 && aryOne[i][j - 1] == 0){
            if (aryOne[i - 1][j - 1] == 1)
                return true;
        }
        
        // bottom and left = 0 and bottom-left = 1
        if (aryOne[i + 1][j] == 0 && aryOne[i][j - 1] == 0){
            if (aryOne[i + 1][j - 1] == 1)
                return true;
        }
        
        // top and right = 0 and top-right = 1
        if (aryOne[i - 1][j] == 0 && aryOne[i][j + 1] == 0){
            if (aryOne[i - 1][j + 1] == 1)
                return true;
        }
        // bottom and right = 0 and bottom-right = 1
        if (aryOne[i + 1][j] == 0 && aryOne[i][j + 1] == 0){
            if (aryOne[i + 1][j + 1] == 1)
                return true;
        }
        return false;
       
    }

    
    
    void imgReformat(int **inAry, ofstream & OutImg){
        OutImg << " " << this->numRows << " "
               << this->numCols << " "
               << this->minVal << " "
               << this->maxVal << endl;
        OutImg << endl;
        
        
        for (int r = 1; r < numRows +  1; r++){
            for (int c = 1; c < numCols + 1; c++){
                if  (0 != inAry[r][c])
                    OutImg << inAry[r][c] << " ";
                else
                    OutImg << ". ";
            }
    
            OutImg << endl;
        }
        OutImg << endl;
    }
        
    void free_Heap (){
        for (int i = 0; i < this->numRows + 2; ++i)
            delete[] this->aryOne[i];
        delete[] this->aryOne;
        
        
        for (int i = 0; i < this->numRows + 2; ++i)
            delete[] this->aryTwo[i];
        delete[] this->aryTwo;
    }

    
        
    
    
};
int main(int argc, const char * argv[]) {
    
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);

    
    string output1 = argv[2];
    ofstream outFile1;
    outFile1.open(output1);

    
    string output2 = argv[3];
    ofstream outFile2;
    outFile2.open(output2);

    
    Thinning* read_img = new Thinning();
    read_img -> constructor(input);

    read_img -> zeroFrame(read_img -> aryOne);
    read_img -> zeroFrame(read_img -> aryTwo);
    read_img -> loadImage(input);

    read_img -> cycleCount = 0;
    outFile2 << "Original Image: " << "Cycle " << read_img -> cycleCount  << endl;
    read_img -> imgReformat(read_img -> aryOne, outFile2);

    read_img -> copyAry(read_img -> aryTwo, read_img -> aryOne);
    read_img -> changeflag = 0;
    read_img -> copyAry(read_img -> aryTwo, read_img -> aryOne);
    
    read_img -> NorthThinning();
    read_img -> copyAry(read_img -> aryOne, read_img -> aryTwo);

    
    read_img -> SouthThinning();
    read_img -> copyAry(read_img -> aryOne, read_img -> aryTwo);

   
    read_img -> WestThinning();
    read_img -> copyAry(read_img -> aryOne, read_img -> aryTwo);

    
    read_img -> EastThinning();
    read_img -> copyAry(read_img -> aryOne, read_img -> aryTwo);
    read_img -> cycleCount++;
    
    outFile2 << "Thinning Image : " << "Cycle " << read_img -> cycleCount << endl;
    read_img -> imgReformat(read_img -> aryOne, outFile2);
    
    while (read_img -> changeflag > 0){
        read_img -> changeflag = 0;
        read_img -> NorthThinning();
        read_img -> copyAry(read_img -> aryOne, read_img -> aryTwo);

        
        read_img -> SouthThinning();
        read_img -> copyAry(read_img -> aryOne, read_img -> aryTwo);

        
        read_img -> WestThinning();
        read_img -> copyAry(read_img -> aryOne, read_img -> aryTwo);
        
        read_img -> EastThinning();
        read_img -> copyAry(read_img -> aryOne, read_img -> aryTwo);
        read_img -> cycleCount++;
        outFile1 << "Thinning Image : " << "Cycle " << read_img -> cycleCount << endl;
        read_img -> imgReformat(read_img -> aryOne, outFile1);

    }
    
    read_img -> free_Heap();
    outFile1.close();
    outFile2.close();
    
    return 0;
    
}
