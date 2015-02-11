#include"FeatureExtractor.h"
#include<iostream>
#include<sstream>


int main(int argc, char *argv[]){

 std::string name;
 std::stringstream fileNum, sngStream, dblStream;
 int sngR, dblR;

 if(argc == 1){

   std::cout << " Enter the File name" << std::endl << " ";
   std::cin  >> name;
   FeatureExtractor e;
   e.ExtractFrom(name);

 }else if(argc == 2){

   fileNum << argv[1];

   FeatureExtractor v;
   v.ExtractFrom(fileNum.str());

 }else if(argc == 4){

   fileNum << argv[1];
   sngStream << argv[2];
   dblStream << argv[3];
   dblStream >> dblR;
   sngStream >> sngR;

   FeatureExtractor v;
   v.ExtractFrom(fileNum.str(), sngR, dblR);

 }else{

   std::cout << "Error with passed arguments\n\n";

 }

 return 0;
}
