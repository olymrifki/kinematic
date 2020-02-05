#include <iostream>
#include <cmath>
#include <fstream>
#include <string>


using namespace std;

//bagian kaki
double const T = 72; //60.00;//
double const F = 59; // 57.70;//
double const C = 30;

//bagian badan
double const H = -56;
double const X = 30;
double const Y = 50;

double const PI = 3.14159265;

enum Loc1{
    kiri = -1, kanan = 1
};
enum Loc2{
    belakang = -1, tengah, depan
};



class Servo {
    private:
        double sudut;
        int id;
    public:
        Servo(int id)
            :id(id)
        {
            sudut = 0;
        }

        int getId() {
            return id;
        }
        double getSudut() {
            return sudut;
        }
        double setSudut(double sudut) {
            this->sudut = sudut;
            return sudut;
        }
};

class Kaki {
    private:
        Servo servoCoxa;
        Servo servoFemur;
        Servo servoTibia;
        int sudutAwal;
        double posisiX, posisiY, posisiZ;
        Loc1 letak1;
        Loc2 letak2;

        void setPosisiServo() {
            double x, y, z;
            double ang[3];
            ang[0] = servoCoxa.getSudut();
            ang[1] = servoFemur.getSudut();
            ang[2] = servoTibia.getSudut();
            
            x = C*cos(ang[0]) + F*cos(ang[0])*cos(ang[1]) + T*sin(ang[1])*cos(ang[0])*cos(ang[2]) + T*sin(ang[2])*cos(ang[0])*cos(ang[1]);
            y = C*sin(ang[0]) + F*sin(ang[0])*cos(ang[1]) + T*sin(ang[0])*sin(ang[1])*cos(ang[2]) + T*sin(ang[0])*sin(ang[2])*cos(ang[1]);
            z = -1*(F*sin(ang[1]) + T*sin(ang[1])*sin(ang[2]) - T*cos(ang[1])*cos(ang[2]));

            posisiX = x; 
            posisiY = y;
            posisiZ = z;
        } //menset posisi dengan forwardKinematic. digunakan setelah sudut diubah
        void setSudutServo(){
            double x, y, z, r, num, den, t1, t2, t3;
            x = posisiX; 
            y = posisiY;
            z = posisiZ;
            r = sqrt(x*x+y*y);
            // t1
            t1 = atan2(y, x);
            //  t2
            num = F*F + (r-C)*(r-C) + z*z - T*T;
            den = 2*F*sqrt(z*z + (r-C)*(r-C));
            if (z >= 0) {
                t2 = acos (num/den) + atan((r-C)/z) - 90*PI/180;
            } else {
                t2 = acos (num/den) + atan((r-C)/z) - 90*PI/180+PI;
            }
            if (t2 < -PI) {
                t2+=2*PI;
            } else if (t2 > PI){
                t2-=2*PI;
            }
            //  t3
            t3 = acos((F*F + T*T - z*z -(r-C)*(r-C))/(2*F*T)) - 90*PI/180;
            if (t3 < -PI/2) {
                t3+=2*PI;
            } else if (t3 > 3*PI/2) {
                t3-=2*PI;
            }
            
            servoCoxa.setSudut(t1);
            servoFemur.setSudut(t2);
            servoTibia.setSudut(t3);
        } //menset sudut dengan inverseKinematic. digunakan setelah posisi diubah

        void forwardKinematic() {
            double x, y, z;
            double ang[3];
            ang[0] = servoCoxa.getSudut();
            ang[1] = servoFemur.getSudut();
            ang[2] = servoTibia.getSudut();
            
            x = C*cos(ang[0]) + F*cos(ang[0])*cos(ang[1]) + T*sin(ang[1])*cos(ang[0])*cos(ang[2]) + T*sin(ang[2])*cos(ang[0])*cos(ang[1]);
            y = C*sin(ang[0]) + F*sin(ang[0])*cos(ang[1]) + T*sin(ang[0])*sin(ang[1])*cos(ang[2]) + T*sin(ang[0])*sin(ang[2])*cos(ang[1]);
            z = -1*(F*sin(ang[1]) + T*sin(ang[1])*sin(ang[2]) - T*cos(ang[1])*cos(ang[2]));

            cout << int(x) << ", " << int(y) << ", " << int(z) << endl; 
        } //hanya mencetak posisi dari sudut-sudut dengan persamaan forwardKinematic
        void inverseKinematic() {
            double x, y, z, r, num, den, t1, t2, t3;
            x = posisiX;
            y = posisiY;
            z = posisiZ;
            r = sqrt(x*x+y*y);
            // t1
            t1 = atan2(y, x);
            //  t2
            num = F*F + (r-C)*(r-C) + z*z - T*T;
            den = 2*F*sqrt(z*z + (r-C)*(r-C));
            if (z >= 0) {
                t2 = acos (num/den) + atan((r-C)/z) - 90*PI/180;
            } else {
                t2 = acos (num/den) + atan((r-C)/z) - 90*PI/180+PI;
            }
            if (t2 < -PI) {
                t2+=2*PI;
            } else if (t2 > PI){
                t2-=2*PI;
            }
            //  t3
            t3 = acos((F*F + T*T - z*z -(r-C)*(r-C))/(2*F*T)) - 90*PI/180;
            if (t3 < -PI/2) {
                t3+=2*PI;
            } else if (t3 > 3*PI/2) {
                t3-=2*PI;
            }
            cout << int(t1*180/PI) - sudutAwal << ", "<< int(t2*180/PI) << ", " << int(t3*180/PI) << endl;
        } //hanya mencetak sudut-sudut dari posisi dengan persamaan inverseKinematic
    public:

        Kaki(int s1, int s2, int s3, int sudut)
            :servoCoxa(s1), servoFemur(s2), servoTibia(s3), sudutAwal(sudut)
        {
            posisiX = (C + F)*cos(sudut*PI/180);
            posisiY = (C + F)*sin(sudut*PI/180);
            posisiZ = T;
            setSudutServo();
            switch (sudutAwal)
            {
            case 0:
                letak1 = kanan;
                letak2 = tengah;
                break;
            case 45:
                letak1 = kanan; 
                letak2 = depan;
                break;
            case -45:
                letak1 = kanan; 
                letak2 = belakang;
                break;
            case 180:
                letak1 = kiri;
                letak2 = tengah;
                break;
            case 135:
                letak1 = kiri; 
                letak2 = depan;
                break;
            case -135:
                letak1 = kiri; 
                letak2 = belakang;
                break;
            default:
                cout << "LOKASI KAKI BELUM ADA" << endl;
                break;
            }
        }

        void pindahPosisiSejauh(double x, double y, double z) {
            posisiX += x;
            posisiY += y;
            posisiZ += z;
            setSudutServo();
        }
        void pindahKeTitik(double x, double y, double z) {
            posisiX = x;
            posisiY = y;
            posisiZ = z;
            setSudutServo();
        }
        void printPosisi(){
            cout << "POSISI "  << letak1 << ", " << letak2 << ":" << endl; 
            cout << "   Sebenarnya: ";
            cout << int(posisiX) << ", " << int(posisiY) << ", " << int(posisiZ) << endl; 
            cout << "   Dari forward sudut: ";
            forwardKinematic();
        }

        void pindahSudutServoSebesar(int id, double sudut) {
            if (id == servoCoxa.getId()) {
                servoCoxa.setSudut((servoCoxa.getSudut()+sudut));
                setPosisiServo();
            }else if (id == servoFemur.getId()) {
                servoFemur.setSudut((servoFemur.getSudut()+sudut));
                setPosisiServo();
            }else if (id == servoTibia.getId()) {
                servoTibia.setSudut((servoTibia.getSudut()+sudut));
                setPosisiServo();
            }else{
                cout << "id " << id << " tidak ada di kaki ini" << endl;
            }
        }
        void pindahSudutServoKeSudut(int id, double sudut){
            if (id == servoCoxa.getId()) {
                servoCoxa.setSudut((sudut));
                setPosisiServo();
            }else if (id == servoFemur.getId()) {
                servoFemur.setSudut((sudut));
                setPosisiServo();
            }else if (id == servoTibia.getId()) {
                servoTibia.setSudut((sudut));
                setPosisiServo();
            }else{
                cout << "id " << id << " tidak ada di kaki ini" << endl;
            }
        }
        void printSudut() {
            cout << "Sudut servo id " << servoCoxa.getId() << ", "<< servoFemur.getId() << ", " << servoTibia.getId() << ": " << endl;
            cout << "   Sebenarnya: ";
            cout << int(servoCoxa.getSudut()*180/PI) - sudutAwal << ", "<< int(servoFemur.getSudut()*180/PI) << ", " << int(servoTibia.getSudut()*180/PI) << endl; 
            cout << "   Dari forward sudut: ";
            inverseKinematic();
        }

        void printLoc() {
            cout << "Lokasi kaki: " << letak1 << ", " << letak2 << endl;
        }      

        int getSudutAwal() {
            return sudutAwal;
        }
};

class Robot {
    private:
        Kaki legs[6] = {Kaki(1, 2, 3, 45),
            Kaki(7,8,9 ,0),
            Kaki(13,14,15, -45),
            Kaki(4,5,6, 135),
            Kaki(10,11,12, 180),
            Kaki(16,17,18, -135)};
    public:
        Robot()
            
        {

        }
        void print() {
            for (int i = 0; i < 6; i++){
                legs[i].printLoc();
            }
        }

        void pindah3KakiSebesar(Loc1 letak, double x, double y, double z) {
            int i = 0;
            if (letak < 0) {
                i = 1;
            }
            for (i; i < 6; i+=2){
                legs[i].pindahPosisiSejauh(x, y, z);
            }
        }
        void reset3Kaki(Loc1 letak){
            int i = 0;
            if (letak < 0) {
                i = 1;
            }
            for (i; i < 6; i+=2){
                int sudut = legs[i].getSudutAwal();
                legs[i].pindahKeTitik((C + F)*cos(sudut*PI/180),(C + F)*sin(sudut*PI/180),T);
            }
        }

        void printPosisi(){
            for (int i = 0; i < 6; i++){
                legs[i].printPosisi();
            }
        }
};

int main(){
    int i;
    Robot KRPAI;

    KRPAI.printPosisi();

    KRPAI.pindah3KakiSebesar(kanan, 0, 10, -10);

    KRPAI.printPosisi();
    
    cin >> i;
    return 0;
}