#include <iostream>
#include <cmath>
#include <fstream>  
#include <string>


//  //  //  //   //  //  //  
//untuk kaki tengah, sudut t1 dikurangi 45 derajat sebelum diinput ke servo
//tapi untuk masuk forward kinematik, ditambah 45 derajat lagi
//  //  //  //  //  //  //  

using namespace std;

double const T = 72; //60.00;//
double const F = 59; // 57.70;//
double const C = 30;
double const PI = 3.14159265;


double* inverseKinematics(double posisi[]) {
    double r, x_, y_, num, den, t1, t2, t3;
    double pos[3];
    pos[0] = posisi[0];
    pos[1] = posisi[1];
    pos[2] = posisi[2];
    r = sqrt(pos[0]*pos[0]+pos[1]*pos[1]);
    //transformasi koordinat
    x_ = pos[0];
    y_ = pos[1];
    pos[0] = (x_-y_)*sqrt(2)/2;
    pos[1] = (x_+y_)*sqrt(2)/2;
    // inverse kinematics
    //  t1
    t1 = atan2(pos[1], pos[0]);
    //  t2
    num = F*F + (r-C)*(r-C) + pos[2]*pos[2] - T*T;
    den = 2*F*sqrt(pos[2]*pos[2] + (r-C)*(r-C));
    if (pos[2] >= 0) {
        t2 = acos (num/den) + atan((r-C)/pos[2]) - 90*PI/180;
    } else {
        t2 = acos (num/den) + atan((r-C)/pos[2]) - 90*PI/180+PI;
    }
    if (t2 < -PI) {
        t2+=2*PI;
    } else if (t2 > PI){
        t2-=2*PI;
    }
    //  t3
    t3 = acos((F*F + T*T - pos[2]*pos[2] -(r-C)*(r-C))/(2*F*T)) - 90*PI/180;
    if (t3 < -PI/2) {
        t3+=2*PI;
    } else if (t3 > 3*PI/2) {
        t3-=2*PI;
    }
    double* legAngle = new double[3];
    legAngle[0] = t1;
    legAngle[1] = t2;
    legAngle[2] = t3;
    return legAngle;
}

int main(){
    ofstream outfile ("inverseKin/test.txt");
    double x, y, z, t1, t2, t3, x_, y_, z_, r, m;
    double num, den;
    int i = 1;
    while (i > 0) {      
        cout << "masukkan x : "; cin >> x;
        cout << "masukkan y : "; cin >> y;
        cout << "masukkan z : "; cin >> z;
    
        double posisi[3];
        posisi[0] = x; 
        posisi[1] = y;
        posisi[2] = z;
        double * legAngle = inverseKinematics(posisi);

        cout << "{" << int(legAngle[0]*180/PI) << ", " << int(-1*legAngle[1]*180/PI) << ", " << int(legAngle[2]*180/PI) << "}"<< endl;
        outfile << int(legAngle[0]*180/PI) << ", " << int(-1*legAngle[1]*180/PI) << ", " << int(legAngle[2]*180/PI) << endl;

        delete[] legAngle;
        cout << "lanjut? (1/0)"; cin >> i;
    }
    outfile.close();
    return 0;
}