#include <iostream>
#include <cmath>
#include <fstream>
#include <string>


using namespace std;

double const a1 = 53; //113.58 - 57.70;
double const T = 72; //60.00;//
double const F = 59; // 57.70;//
double const C = 30;
double const PI = 3.14159265;

double* splitLineToDoubleArray(string line) {
    // format splitting khusus untuk output inverse kinematic
    int j = 0;
    int i = 0;
    int k = 0;
    double* result = new double[3];
    while (i < line.size()) {
        if (line.substr(i, 1) == ",") {
            result[k] = stod(line.substr(j, i-j));
            k++;
        } else if (line.substr(i, 1) == " "){
            j = i+1;
        }
        i++;
    }
    result[k] = stod(line.substr(j, line.size()));
    return result;  
}

double* forwardKinematics(double sudut[]) {
    double x, y, z;
    double ang[3];
    ang[0] = sudut[0]*PI/180;
    ang[1] = -1*sudut[1]*PI/180;
    ang[2] = sudut[2]*PI/180;
    
    

    double* posisi = new double[3];
    posisi[0] = (x+y)*sqrt(2)/2;
    posisi[1] = (-x+y)*sqrt(2)/2;
    posisi[2] = -1*z;
    return posisi;
}

int main(){
    string line;
    ifstream infile ("inverseKin/test.txt");
    ofstream outfile ("forwardKin/forwardtest.txt");
    double x, y, z;
    int i;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            cout << line << endl;
            double * sudut = splitLineToDoubleArray(line);   
            double * posisi = forwardKinematics(sudut);
            
            cout << "{" << posisi[0] << ", " << posisi[1] << ", " << posisi[2] << "},"<< endl;
            outfile << posisi[0] << ", " << posisi[1] << ", " << posisi[2] << endl;

            delete[] posisi;
            delete[] sudut;
        }
    }
    outfile.close();
    infile.close();
    return 0;
}