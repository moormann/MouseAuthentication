//SPECIFICATION FILE

#include<fstream>
#include<iomanip>
#include<iostream>
#include<sstream>
   
using namespace std;

struct data
 {
  double leftMean;
  double leftStd;
  double rightMean;
  double rightStd;
  double dblMean;
  double dblStd;
  double int1Mean;
  double int1Std;
  double int2Mean;
  double int2Std;
  double int3Mean;
  double int3Std;
  double spdMean;
  double spdStd;
  double accelMean;
  double accelStd;
  double jerkMean;
  double jerkStd;
 };

struct newData
 {
  int start;
  int type;
  int length;
  double speed;
  double accel;
  double jerk;
  int int1;
  int int2;
  int int3;
 };

void getData(ifstream& inFile, data& oldData);
//This function gathers the origional data.

void getNewData(ifstream& inFile, newData& currentData);
//This function is for gathering the data of the file that is being compared.

void type0(data& oldData, newData& currentData, int& yesCount);
void type1(data& oldData,newData& currentData, int& yesCount);
void type2(data& oldData,newData& currentData, int& yesCount);
void type3(data& oldData,newData& currentData, int& yesCount);
void type4(data& oldData,newData& currentData, int& yesCount);

void print(ofstream& outFile, double matrix[56][56]);
