/*
    class: CSCI 381/780
    First Name : Trisha
    Last Name: Espejo
    Project 4
    language: C++
    project name: Connect Component
    
 */
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;
struct Property {
    int label = 0;
    int numPixel = 0;
    int minR = 9999;
    int minC = 9999;
    int maxR = 0;
    int maxC = 0;
};
class CCLabel {
    public:
    int numRows = -1;
    int numCols= -1;
    int minVal = -1;
    int maxVal = -1;
    int newMin = -1;
    int newMax = -1;
    int newLabel = 0;
    int trueNumCC = 0;
    int **zeroFramedAry;
    int NonZeroNeighborAry[5];
    int *EQAry;
    struct Property *CCProperty;
    
public:
   
    void constructor(ifstream & input){
        input >> this->numRows >> this->numCols >> this->minVal >> this->maxVal;
        newMin = minVal;
        newMax = maxVal;
        newLabel = 0;
        this -> zeroFramedAry = new int*[this -> numRows + 2];
        for (int i = 0; i < this -> numRows + 2; ++i){
            zeroFramedAry[i] = new int[ this -> numCols + 2];
        }
        
        for (int i = 0; i < 5; ++i){
            NonZeroNeighborAry[i] = -1;
            
        }
        this -> EQAry = new  int[(this->numRows * this -> numCols)/ 4];
        for (int i = 0; i < (this->numRows * this-> numCols)/ 4 ; ++i){
            EQAry[i] = i;
            
        }
    }
    void zero2D (){
        for (int i = 0; i < this -> numRows + 2; ++i){
            for (int j = 0; j < this -> numCols + 2; ++j)
                zeroFramedAry[i][j] = 0;
        }
    }
    void loadImage (ifstream & input){
        
        for (int i = 1; i < this -> numRows + 1 ; ++i){
            for (int j = 1; j < this -> numCols + 1 ; ++j)
            {
                input >> zeroFramedAry[i][j];
                
            }
        }
  
    }
    void connect4Pass1(){
        newMin = 9999;
        newMax = 0;
        for (int r = 1; r < numRows +  1; r++){
            for (int c = 1; c < numCols + 1; c++){
                if ( zeroFramedAry[r][c] > 0)
                    pass1Connect4(zeroFramedAry, r, c);
                if (newMin > zeroFramedAry[r][c])
                    newMin = zeroFramedAry[r][c];
                if (newMax < zeroFramedAry[r][c])
                    newMax = zeroFramedAry[r][c];
                
            }
        }
        
    }
    
    void pass1Connect4(int **zeroFramedAry, int r, int c){
        int a = zeroFramedAry[r - 1][c];
        int b = zeroFramedAry [r][c - 1];
        int min = 0;
        int max = 0;
        //case 1 : a = b = 0
        if ( a == 0 && b == 0) {
            newLabel++;
            zeroFramedAry[r][c] = newLabel;
        }
        //case 2: a == b or a or b already has label
        else if( a == b && a != 0 && b != 0)
            zeroFramedAry[r][c] = a;
        else if ( a != 0 && b == 0)
            zeroFramedAry[r][c] = a;
        else if (a == 0 && b != 0)
            zeroFramedAry[r][c] = b;
        //case 3 a != b and a and b has label
        else
        {
            if (a < b){
                min =  a;
                max = b;
            }
            else
            {
                min = b;
                max = a;
            }
            zeroFramedAry[r][c] = min;
            updateEQ(max, min);
        }
    }
    void connect4Pass2(){
        newMin = 9999;
        newMax = 0;
        for (int r = numRows; r > 0; r--){
            for (int c = numCols; c > 0; c--){
                if ( zeroFramedAry[r][c] > 0)
                    pass2Connect4(zeroFramedAry, r, c);
                if (newMin > zeroFramedAry[r][c])
                    newMin = zeroFramedAry[r][c];
                if (newMax < zeroFramedAry[r][c])
                    newMax = zeroFramedAry[r][c];
            }
        }
     }
    void pass2Connect4 (int **zeroFramedAry, int i, int j){
        int c = zeroFramedAry[i][j + 1];
        int d = zeroFramedAry[i + 1][j];
        int x = zeroFramedAry[i][j];
        int minLabel = 0;
        //case 1 : a = b = 0
        if ( c == 0 && d == 0) {
            zeroFramedAry[i][j] = zeroFramedAry[i][j];
           
        }
        //case 2: a == b or a or b already has label
        else if( c == d == x && c != 0 && d != 0)
        {
            zeroFramedAry[i][j] = zeroFramedAry[i][j];
        }
        else if ( c != 0 && d == 0 && c == x){
            zeroFramedAry[i][j] = zeroFramedAry[i][j];
            
        }
        else if (c == 0 && d != 0 && d == x){
            zeroFramedAry[i][j] = zeroFramedAry[i][j];
            
        }
        //case 3 a != b and a and b has label
        else
        {
            if (c == 0) minLabel = min( d, x);
            else if (d == 0) minLabel =  min( c, x);
            else {
                minLabel = min(c, d);
                minLabel = min (minLabel, x);
            }
            if ( x > minLabel)
                updateEQ(x, minLabel);
            
            
            zeroFramedAry[i][j] = minLabel;
        }
    }
    void connect8Pass1() {
        newMin = 9999;
        newMax = 0;
        for (int r = 1; r < numRows + 1; r++){
            for (int c = 1; c < numCols + 1; c++){
                if ( zeroFramedAry[r][c] > 0)
                    pass1Connect8(zeroFramedAry, r, c);
                if (newMin > zeroFramedAry[r][c])
                    newMin = zeroFramedAry[r][c];
                if (newMax < zeroFramedAry[r][c])
                    newMax = zeroFramedAry[r][c];
            }
        }
    }
    void pass1Connect8(int **zeroFramedAry, int r, int c){
        int row = r - 1;
        int col = c - 1;
        int temp = 0;
        int min =  0;
        int max = 0;
        int index = 0;
        bool stop = false;
        bool isAllZero = true;
        bool isEqual = false;
        for (int i = 0; i < 2 && !stop; i++){
            for (int j = 0; j < 3 && !stop; j++){
                //cout << j << " " << j;
                if ( i == 1 && j == 1) stop = true;
                else{
                    NonZeroNeighborAry[index] = zeroFramedAry[i + row][j + col];
                    index++;
                }
            }
        }
        for (int i = 0; i < 4; i++){
            if (NonZeroNeighborAry[i] != 0) {
                isAllZero = false;
            }
        }
        //cout << count;
        for (int i = 0; i < 3; i++){
            for (int j = 1; j < 4; j++){
                int a = NonZeroNeighborAry[i];
                int b = NonZeroNeighborAry[j];
                if(a != 0 && b != 0 && a != b){
                    isEqual = false;
                }
                else
                {
                    isEqual = true;
                    if ( a == 0 && b != 0)
                        temp = b;
                    else if ( b == 0 && a != 0)
                        temp = a;
                    else if (a == b && a != 0 && b != 0 )
                        temp = a;
                }
            }
        }
        // case 1
        if (isAllZero)
        {
            newLabel++;
            zeroFramedAry[r][c] = newLabel;
        }
        //case 2
        else if (isEqual){
            zeroFramedAry[r][c] = temp;
        }
        // case 3
        else {
            for (int i = 0; i < 3; i++){
                for (int j = 1; j < 4; j++){
                    int a = NonZeroNeighborAry[i];
                    int b = NonZeroNeighborAry[j];
                    if (a < b && a != 0 && b != 0)
                    {
                        min = a;
                        max = b;
                    }
                    else
                    {
                        min = b;
                        max = a;
                    }
                }
            }
            zeroFramedAry[r][c] = min;
            updateEQ(max, min);
        }
    }
    void connect8Pass2() {
        newMin = 9999;
        newMax = 0;
        for (int r = numRows; r > 0; r--){
           for (int c = numCols; c > 0; c--){
                if ( zeroFramedAry[r][c] > 0)
                    pass2Connect8(zeroFramedAry, r, c);
               if (newMin > zeroFramedAry[r][c])
                   newMin = zeroFramedAry[r][c];
               if (newMax < zeroFramedAry[r][c])
                   newMax = zeroFramedAry[r][c];
            }
        }
    }
    void pass2Connect8(int **Ary, int r, int c){
        int row = r - 1;
        int col = c - 1;
        int index = 0;
        bool isAllZero = true;
        bool isEqual = true;
        int minLabel = 0;
        int i = 1;
        int j = 1;
        while (i < 3)
        {
            while (j < 3 ){
                NonZeroNeighborAry[index] = Ary[i + row][j + col];
                index++;
                j++;
            }
            j = 0;
            i++;
        }
        for (int i = 1; i < 5; i++){
            if (NonZeroNeighborAry[i] != 0) {
                isAllZero = false;
            }
        }
        for (int i = 0; i < 4; i++){
            for (int j = 1; j < 5; j++){
                int a = NonZeroNeighborAry[i];
                int b = NonZeroNeighborAry[j];
                if(a != 0 && b != 0 && a != b){
                    isEqual = false;
                }
                
            }
        }
        if(isAllZero)
            Ary[r][c] = Ary[r][c];
        else if (isEqual)
            Ary[r][c] = Ary[r][c];
        else
        {
            minLabel = NonZeroNeighborAry[0];
            for (int i = 1; i < 5; i++){
                if (NonZeroNeighborAry[i] != 0)
                    minLabel = min (minLabel, NonZeroNeighborAry[i]);
            }
            if ( Ary[r][c] > minLabel)
                updateEQ(Ary[r][c], minLabel);
            Ary[r][c] = minLabel;
            
        }
  
    }
    
    void connectPass3(){
        newMin = 9999;
        newMax = 0;
        for (int r = 1; r < numRows +  1; r++){
            for (int c = 1; c < numCols + 1; c++){
                if( zeroFramedAry[r][c] > 0)
                    zeroFramedAry[r][c] = EQAry[zeroFramedAry[r][c]];
                if (newMin > zeroFramedAry[r][c])
                    newMin = zeroFramedAry[r][c];
                if (newMax < zeroFramedAry[r][c])
                    newMax = zeroFramedAry[r][c];
            }
        }
    }
    void genProperty()
    {
        this -> CCProperty = new struct Property[this->trueNumCC + 1];
        int x = 0;
       
        for (int a = 1; a < trueNumCC + 1; a++){
            CCProperty[a].label =  a;
            for (int i = 1; i < numRows + 1; i++){
                for (int j = 1; j < numCols + 1; j++){
                    x = zeroFramedAry[i][j];
                    
                    if ( x == CCProperty[a].label)
                    {
                        CCProperty[a].numPixel++;
                        if (CCProperty[a].minR > i)
                            CCProperty[a].minR = i;
                        if (CCProperty[a].minC > j)
                            CCProperty[a].minC = j;
                        if (CCProperty[a].maxR < i)
                            CCProperty[a].maxR = i;
                        if (CCProperty[a].maxC < j)
                            CCProperty[a].maxC = j;
                    }
                }
            }
        }
    }
    void updateEQ( int index, int min){
        EQAry[index] = min;
        
    }
    int manageEQAry(int *EQAry, int newLabel){
        int readLabel = 0;
        for (int i = 1; i < newLabel + 1; i++)
        {
            if (i != EQAry[i])
                EQAry[i] = EQAry[EQAry[i]];
            else {
                readLabel++;
                EQAry[i] = readLabel;
                }
            
        }
        return readLabel;
    }
    void drawBoxes (){
        int index = 1;
        
        while (index < trueNumCC + 1)
        {
            
            int minRow = CCProperty[index].minR;
            int minCol = CCProperty[index].minC;
            int maxRow = CCProperty[index].maxR;
            int maxCol = CCProperty[index].maxC;
            int label =  CCProperty[index].label;
            
            
            for (int i = minCol; i < maxCol + 1; i++)
            {
                zeroFramedAry[minRow][i] = label;
                
            }
            for (int i = minCol; i < maxCol + 1; i++)
                zeroFramedAry[maxRow][i] = label;
            for (int i = minRow; i < maxRow + 1; i++)
                zeroFramedAry[i][minCol] = label;
            for (int i = minRow; i < maxRow + 1; i++)
                zeroFramedAry[i][maxCol] = label;
            
            index++;
        }
    }
    
    void imgReformat(int **inAry, ofstream & OutImg){
        OutImg <<" " << this->numRows <<" " << this->numCols << " " << this->newMin << " " << this->newMax << endl;
        OutImg << endl;
        
        
        for (int r = 1; r < numRows +  1; r++){
            for (int c = 1; c < numCols + 1; c++){
                if  (0 < inAry[r][c] )
                    OutImg << inAry[r][c] ;
                else
                    OutImg << ".";
                if (inAry[r][c + 1] < 10)
                    OutImg << "  ";
                else if (inAry[r][c + 1] > 9 )OutImg << " ";
            }
    
            OutImg << endl;
        }
        OutImg << endl;
    }
    void printEQAry (int label, ofstream & OutImg){
        for (int i = 1; i < label + 1; i++)
        {
            OutImg << i << ": " << EQAry[i] << endl;
        }
        OutImg << endl << endl;
    }
    
    void printImg(ofstream & OutImg){
        OutImg <<" " << this->numRows <<" " << this->numCols << " " << this->newMin << " " << this->newMax << endl;
        OutImg << endl;
        
        for (int r = 1; r < numRows +  1; r++){
            for (int c = 1; c < numCols + 1; c++){
                OutImg << setw(2) << zeroFramedAry[r][c] << " ";
            }
            OutImg << endl;
        }
        OutImg << endl;
    }
    
    void printCCproperty(ofstream & Output){
                Output << endl;
        Output << " " << this->numRows <<" " << this->numCols << " " << this->newMin << " " << this->newMax << endl;
        Output << " " << this ->trueNumCC << endl;
        
        Output << "********************************************************" <<endl;
        for (int i = 1; i < trueNumCC + 1; i++){
            Output << endl;
            Output << CCProperty[i].label << endl;
            Output << CCProperty[i].numPixel << endl;
            Output << CCProperty[i].minR << "  " << CCProperty[i].minC <<endl;
            Output << CCProperty[i].maxR << "  " << CCProperty[i].maxC <<endl;
            Output << "********************************************************" <<endl;
        }
        
    }
    
        
    void free_Heap (){
        for (int i = 0; i < this->numRows + 2; ++i)
            delete[] this->zeroFramedAry[i];
        delete[] this->zeroFramedAry;
        
        delete[] this->CCProperty;
        
        delete[] this-> EQAry;
    }
};

int main(int argc, const char * argv[]) {
    int connectness = atoi(argv[2]);
    
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);
    
    string output1 = argv[3];
    ofstream RFprettyPrintFile;
    RFprettyPrintFile.open(output1);
    
    string output2 = argv[4];
    ofstream labelFile;
    labelFile.open(output2);
    
    string output3 = argv[5];
    ofstream propertyFile;
    propertyFile.open(output3);
    
    CCLabel* read_img = new CCLabel();
    read_img -> constructor(input);
    read_img -> zero2D ();
    read_img -> loadImage(input);
    
    if (connectness == 4){
        read_img -> connect4Pass1();
        RFprettyPrintFile << "Connect 4 Pass 1: " << endl;
        read_img -> imgReformat(read_img -> zeroFramedAry, RFprettyPrintFile);
        RFprettyPrintFile << "Equivalence Table after Pass 1: " << endl;
        read_img -> printEQAry (read_img -> newLabel, RFprettyPrintFile);
        
        read_img -> connect4Pass2();
        RFprettyPrintFile << "Connect 4 Pass 2: " << endl;
        read_img -> imgReformat(read_img -> zeroFramedAry, RFprettyPrintFile);
        RFprettyPrintFile << "Equivalence Table after Pass 2: " << endl;
        read_img -> printEQAry (read_img -> newLabel, RFprettyPrintFile);
    }
    if (connectness == 8){
        read_img -> connect8Pass1();
        RFprettyPrintFile << "Connect 8 Pass 1: " << endl;
        read_img -> imgReformat(read_img -> zeroFramedAry, RFprettyPrintFile);
        RFprettyPrintFile << "Equivalence Table after Pass 1: " << endl;
        read_img -> printEQAry (read_img -> newLabel, RFprettyPrintFile);
        
        read_img -> connect8Pass2();
        RFprettyPrintFile << "Connect 8 Pass 2: " << endl;
        read_img -> imgReformat(read_img -> zeroFramedAry, RFprettyPrintFile);
        RFprettyPrintFile << "Equivalence Table after Pass 2: " << endl;
        read_img -> printEQAry (read_img -> newLabel, RFprettyPrintFile);
    }
    
    
    read_img -> trueNumCC = read_img -> manageEQAry(read_img-> EQAry, read_img-> newLabel);
    RFprettyPrintFile << " New Equivalence Table after ManageEQ : " << endl;
    read_img -> printEQAry (read_img -> newLabel, RFprettyPrintFile);
    read_img -> connectPass3();
    if (connectness == 4)
        RFprettyPrintFile << "Connect 4 Pass 3: " << endl;
    if (connectness == 8)
        RFprettyPrintFile << "Connect 8 Pass 3: " << endl;
    read_img -> imgReformat(read_img -> zeroFramedAry, RFprettyPrintFile);
    RFprettyPrintFile << "Equivalence Table after Pass 3: " << endl;
    read_img -> printEQAry (read_img -> newLabel, RFprettyPrintFile);
   
    read_img -> printImg(labelFile);
    read_img -> genProperty();
    read_img -> printCCproperty(propertyFile);
    read_img -> drawBoxes();
    RFprettyPrintFile << "Connect 8 After drawBoxes: " << endl;
    read_img -> imgReformat(read_img -> zeroFramedAry, RFprettyPrintFile);
    
    RFprettyPrintFile << "Total Number of Connected Components: " << endl;
    RFprettyPrintFile << "Number of CC: " << read_img -> trueNumCC << endl;

    
    read_img -> free_Heap();
    input.close();
    RFprettyPrintFile.close();
    labelFile.close();
    propertyFile.close();
    return 0;
    

}
    
