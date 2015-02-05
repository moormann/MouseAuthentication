#include"FeatureExtractor.h"
#include<iostream>
#include<sstream>


int main(int argc, char *argv[]){

 std::string name;
 std::stringstream fileNum;


 if(argc == 1){
   std::cout << " Enter the File name" << std::endl << " ";
   std::cin  >> name;
   FeatureExtractor e;
   e.ExtractFrom(name);
 }else{

   fileNum << argv[1];

   FeatureExtractor v;
   v.ExtractFrom(fileNum.str());

 }

 return 0;
}
