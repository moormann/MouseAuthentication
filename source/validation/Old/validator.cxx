//IMPLEMENTATION FILE

#include "validator.h"

void getData(ifstream& inFile, data& oldData)
 {
  inFile >> oldData.leftMean >> oldData.leftStd >> oldData.rightMean >> oldData.rightStd
	 >> oldData.dblMean >> oldData.dblStd >> oldData.int1Mean >> oldData.int1Std
	 >> oldData.int2Mean >> oldData.int2Std >> oldData.int3Mean >> oldData.int3Std
	 >> oldData.spdMean >> oldData.spdStd >> oldData.accelMean >>oldData.accelStd
	 >> oldData.jerkMean >> oldData.jerkStd;
 };

void getNewData(ifstream& inFile, newData& currentData)
 {
  inFile >> currentData.start >> currentData.type >> currentData.length >> currentData.speed >> currentData.accel
	 >> currentData.jerk  >> currentData.int1 >> currentData.int2 >> currentData.int3;
 };

void type0(data& oldData, newData& currentData, int& yesCount)
 {
  if(    (currentData.speed <= currentData.speed + (1 * oldData.spdStd))
     && (currentData.speed >= currentData.speed - (1 * oldData.spdStd))
     && (currentData.jerk <= currentData.jerk + (1 * oldData.jerkStd))
     && (currentData.jerk >= currentData.jerk - (1 * oldData.jerkStd))
     && (currentData.accel <= currentData.accel + (1 * oldData.accelStd))
     && (currentData.accel >= currentData.accel - (1 * oldData.accelStd))
     && (currentData.length <= currentData.length + (1 * oldData.spdStd))
     && (currentData.length >= currentData.length - (1 * oldData.spdStd))
    )
   yesCount = yesCount + 1;
 };

void type1(data& oldData, newData& currentData, int& yesCount)
 {
  if(   (currentData.speed <= currentData.speed + (1 * oldData.spdStd))
     && (currentData.speed >= currentData.speed - (1 * oldData.spdStd))
     && (currentData.jerk <= currentData.jerk + (1 * oldData.jerkStd))
     && (currentData.jerk >= currentData.jerk - (1 * oldData.jerkStd))
     && (currentData.accel <= currentData.accel + (1 * oldData.accelStd))
     && (currentData.accel >= currentData.accel - (1 * oldData.accelStd))
     && (currentData.length <= currentData.length + (1 * oldData.spdStd))
     && (currentData.length >= currentData.length - (1 * oldData.spdStd))
    )
   yesCount = yesCount + 1;
 };

void type2(data& oldData, newData& currentData, int& yesCount)
 {
  if(   (currentData.speed <= currentData.speed + (1 * oldData.spdStd))
     && (currentData.speed >= currentData.speed - (1 * oldData.spdStd))
     && (currentData.jerk <= currentData.jerk + (1 * oldData.jerkStd))
     && (currentData.jerk >= currentData.jerk - (1 * oldData.jerkStd))
     && (currentData.accel <= currentData.accel + (1 * oldData.accelStd))
     && (currentData.accel >= currentData.accel - (1 * oldData.accelStd))
     && (currentData.int1 <= currentData.int1 + (1 * oldData.int1Std))
     && (currentData.int1 >= currentData.int1 - (1 * oldData.int1Std))
     && (currentData.int2 <= currentData.int2 + (1 * oldData.int2Std))
     && (currentData.int2 >= currentData.int2 - (1 * oldData.int2Std))
     && (currentData.int3 <= currentData.int3 + (1 * oldData.int3Std))
     && (currentData.int3 >= currentData.int3 - (1 * oldData.int3Std))
    )
   yesCount = yesCount + 1;
 };

void type3(data& oldData, newData& currentData, int& yesCount)
 {
  if(    (currentData.speed <= currentData.speed + (1 * oldData.spdStd))
     && (currentData.speed >= currentData.speed - (1 * oldData.spdStd))
     && (currentData.jerk <= currentData.jerk + (1 * oldData.jerkStd))
     && (currentData.jerk >= currentData.jerk - (1 * oldData.jerkStd))
     && (currentData.accel <= currentData.accel + (1 * oldData.accelStd))
     && (currentData.accel >= currentData.accel - (1 * oldData.accelStd))
    )
   yesCount = yesCount + 1;
 };

void type4(data& oldData, newData& currentData, int& yesCount)
 {
  
 }

void print(ofstream& outFile, double matrix[56][56])
 {
  int a;
  int b;

  for (a = 0; a < 56; a++)
   {
    for (b = 0; b < 56; b++)
     {
      outFile << setw(6) << matrix[a][b] << " ";
     }
     outFile << endl;
   }
 }
