//
//  main.cpp
//  project8
//
//  Created by Trisha Espejo on 5/10/21.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class image {
    public:
    int numRows = -1;
    int numCols= -1;
    int minVal = -1;
    int maxVal = -1;
    int label = -1;
    int **imgAry;

    void constructor(ifstream & input, int k){
        input >> this->numRows >> this->numCols >> this->minVal >> this->maxVal;
        input >> this -> label;
        this -> imgAry = new int*[this -> numRows];
        for (int i = 0; i < this -> numRows; ++i){
            imgAry[i] = new int[ this -> numCols];
        }
        
        for (int i = 0; i < this -> numRows; ++i){
            for (int j = 0; j < this -> numCols; ++j){
                imgAry[i][j] = 0;
            }
        }
    }
    
    void imgReformat(ofstream & output){
        output << " " << this->numRows << " "
                       << this->numCols << " "
                       << this->minVal << " "
                       << this->maxVal << endl;
        output << endl;
        
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
                if  (0 != imgAry[i][j])
                    output << imgAry[i][j] << " ";
                else
                    output << ". ";
            }
            output << endl;
        }
    }
    void free_Heap (){
            for (int i = 0; i < this->numRows; ++i)
                delete[] this->imgAry[i];
            delete[] this->imgAry;
    }
   
};


class boundaryPt {
public:
    int x = -1;
    int y = -1;
    double curvature = 0.0;
    int localMax = -1;
    int corner = -1;
    
};

class kCurvature {
public:
    int K = -1;
    int numPts = -1;
    int Q = 0;
    int P = -1;
    int R = -1;
    int numRow = -1;
    int numCol = -1;
    int min = -1;
    int max = -1;
    int label = -1;
    boundaryPt** PtAry;
    

    void constructor(int k){
        this-> K = k;
        this-> P = K;
        this-> R = 2 * K;
        
    }
    void initialization(ifstream & input, string args){
        this-> numPts = countPts(input);
        input.close();
        input.open(args);
        int index = 0;
       
        input >> this-> numRow >> this-> numCol >> this-> min >> this-> max;
        input >> this-> label;
        
        this -> PtAry = new boundaryPt*[this -> numPts];
        int x = -1;
        int y = -1;
        while(input >> x){
            input >> y;
            storePT(x, y, index);
            index++;
        }
    }
    int countPts (ifstream & input){
        int count = 0;
        string x;
        string y;
        
        while( input >> x ){
            input >> y;
            count++;
        }
        return count;
    }
    
    void storePT( int a, int b, int index){
        boundaryPt* temp = new boundaryPt();
        temp -> x = a;
        temp -> y = b;
        PtAry[index] = temp;
    }
    void printPtAry(ofstream & output){
        output << this-> numRow << " " << this-> numCol << " ";
        output << this-> min << " "<< this-> max;
        output << endl;
        
        output << this -> label << endl;
        for(int i = 0; i < numPts; i++){
            boundaryPt* temp = new boundaryPt();
            temp = PtAry[i];
            output <<"x: " << temp -> x << " y: " << temp -> y << " curvature: ";
            output << temp -> curvature << " " ;
            if (temp -> localMax  >= 0)
                output << " localMax:"<< temp -> localMax;
            output << endl;
        }
        output << endl << endl;
    }
    void cornerDetection(ofstream & output){
        
        output << "Calculating Curvature debugging" << endl;
        output << endl;
        string letter = "";
        int index = 0;
        while (true){
            
            index = P;
            boundaryPt* temp = new boundaryPt();
            temp = PtAry[index];
            temp -> curvature = computeCurvature(Q, P, R, output);
            PtAry[index] = temp;
            output << endl;
            if (P == K - 1) break;
            Q = (Q + 1) % numPts;
            P = (P + 1) % numPts;
            R = (R + 1) % numPts;
        }
        output << endl;
        
    }
    double computeCurvature(int Q, int P, int R, ofstream & output){
        double result = 0.0;
        
        boundaryPt* temp = new boundaryPt();
        temp = PtAry[Q];
        int r1 = temp -> x;
        int c1 = temp -> y;
        printDebug("Q", Q , output);
        temp = new boundaryPt();
        temp = PtAry[P];
        int r2 = temp -> x;
        int c2 = temp -> y;
        temp = new boundaryPt();
        printDebug("P", P, output);
        temp = PtAry[R];
        int r3 = temp -> x;
        int c3 = temp -> y;
        printDebug("R", R , output);
        double y1 = c1 - c2;
        double y2 = c2 - c3;
        double x1 = abs(r1 - r2);
        double x2 = abs(r2 - r3);
        double s1 = 0.0;
        double s2 = 0.0;
        
        if (x1 == 0 )
            x1 = 0.5;
        if(x2 == 0)
           x2 = 0.5;
        s1 = (double)(y1 / x1);
        s2 = (double)(y2 / x2);
        result = abs(s1 - s2);
        
        output << c1 << " - " << c2 << " = "<< c1 - c2 <<endl;
        output << c2 << " - " << c3 << " = " << c2 - c3 << endl;
        output << r1 << " - " << r2 << " = " << abs(r1 - r2)<< endl;
        output << r2 << " - " << r3 << " = " << abs(r2 - r3) << endl;
        output << y1 << " / " << x1 << " = " << (double)(y1 / x1) << endl;
        output << y2 << " / " << x2 << " = " << (double)(y1 / x1) << endl;
        output << s1 << " - " << s2 << " = " << abs(s1 - s2) << endl;
        

        
        
        return result;
        
    }
    void printDebug(string l, int i, ofstream & output){
        boundaryPt* temp = new boundaryPt();
        temp = PtAry[i];
        int r = temp -> x;
        int c = temp -> y;
        output << l << " index: " << i << " x: " << r << " y: " << c << endl;
        
    }
    void computeLocalMaxima(){
        for (int i = 0; i < numPts; i++){
            int index = ((i + numPts) - 2 ) % numPts;
            double n1 = PtAry[index] -> curvature;
            index = ((i + numPts) - 1 ) % numPts;
            double n2 = PtAry[index] -> curvature;
            index = (i + 1) % numPts;
            double n3 = PtAry[index] -> curvature;
            index = (i + 2) % numPts;
            double n4 = PtAry[index] -> curvature;
            double p = PtAry[i] -> curvature;
            
            if (p >= n1 && p >= n2 && p >= n3 && p >= n4 &&  p > 0)
                PtAry[i] -> localMax = 1;
            else
                PtAry[i] -> localMax = 0;

        }
    }
    
    
    void markCorner(){
    
        for (int i = 0; i < numPts; i++){
            int index1 = ((i + numPts) - 1 ) % numPts;
            int p1 = PtAry[index1] -> localMax;
            int p2 = PtAry[i] -> localMax;
            int index2 = (i + 1) % numPts;
            int p3 = PtAry[index2] -> localMax;
            bool otherNeig = false;
            bool nextNeig = false;
        
            if (p2 == 1 ){
                if (p1 == 1 && p3 == 1)
                    nextNeig = true;
                for (int j = ((i + numPts) - 2 ) % numPts; j < (i + 2) % numPts; j++){
                    int x = PtAry[j] -> localMax;
                    
                    if( j == index1 || j == index2 || j == i)
                        continue;
                    if (x == 1){
                        otherNeig = true;
                        break;
                    }
                }
                if( !nextNeig && !otherNeig )
                    PtAry[i] -> corner = 9;
                
                else if(nextNeig && !otherNeig){
                    PtAry[i] -> corner = 9;
                }
                else
                    PtAry[i] -> corner = 1;
            }
            else
                PtAry[i] -> corner = 1;
           
        }
    }
    
    void printBoundary(ofstream & output){
        output << numRow << " " << numCol << " " << min << " " << max << endl;
        output<< label;
        for (int i = 0; i < numPts; i++){
            boundaryPt* temp = new boundaryPt();
            temp = PtAry[i];
            int r = temp -> x;
            int c = temp -> y;
            int corner = temp -> corner;
            output << r << " " << c << " " << corner << endl;
        }
    }
    void display(int **imgAry){
        for (int i = 0; i < numPts; i++){
            boundaryPt* temp = new boundaryPt();
            temp = PtAry[i];
            int r = temp -> x;
            int c = temp -> y;
            int corner = temp -> corner;
            imgAry[r][c] = corner;
        }
    }
    void free_Heap (){
            delete[] this->PtAry;
    }
        
    };
    


int main(int argc, const char * argv[]) {
    int k = -1;
    
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);
    
    string output1 = argv[2];
    ofstream outFile1;
    outFile1.open(output1);

        
    string output2 = argv[3];
    ofstream outFile2;
    outFile2.open(output2);
    
    string output3 = argv[4];
    ofstream outFile3;
    outFile3.open(output3);
    cout << "Please provide a K value: ";
    cin >> k;
    
    image* img = new image();
    img -> constructor(input, k);
    kCurvature* kCurv = new kCurvature();
    kCurv -> constructor(k);
    outFile3 << "K value: " << k << endl;
    kCurv -> initialization(input, inputName);
    outFile3 << "PtAry after initialization " << endl;
    kCurv -> printPtAry (outFile3);
    kCurv -> cornerDetection (outFile3);
    outFile3 << "PtAry after Corner Detection " << endl;
    kCurv -> printPtAry (outFile3);
    kCurv -> computeLocalMaxima();
    kCurv -> markCorner();
    kCurv -> printBoundary(outFile1);
    kCurv-> display(img -> imgAry);
    img -> imgReformat(outFile2);
    img -> free_Heap();
    kCurv -> free_Heap();
    input.close();
    outFile1.close();
    outFile2.close();
    outFile3.close();
    
    cout << "Compilation Complete"<< endl;
    
    return 0;
}
