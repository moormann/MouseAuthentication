#include<fstream>
#include<cmath>
#include<iostream>
#include<vector>
#include<iomanip>
#include<sstream>

using namespace std;

struct mouseAction{
 
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

struct featFile{

 //Averaged data

 double lMean, lStd;
 double rMean, rStd;
 double dblMean, dblStd;
 double int1Mean, int1Std;
 double int2Mean, int2Std;
 double int3Mean, int3Std;
 double spdMean, spdStd;
 double aclMean, aclStd;
 double jrkMean, jrkStd;
  

 //The individual mouse actions

 vector<mouseAction> actions;

};



//FUNCTION DEFINITIONS//
void   ReadIn(featFile &f, string name);
double compare(featFile out, featFile in, double m);
void   partition(featFile &out, featFile &in, double perc);


int main(){


 vector<std::string> fileList;
 ifstream nameFile("Names.txt");
 string temp;
 double mult, trainPerc;
 



 //Ask user for parameters
 cout << " What m would you like?" << endl;
 cin >> mult;
 cout << endl << " What percentage of the file should be used to train?"  << endl;
 cin >> trainPerc;



 featFile outerFile, innerFile;

 //Populate the name list
 nameFile >> temp;
 fileList.push_back(temp); 

 
 nameFile >> temp;

 while(nameFile.good()){

   fileList.push_back(temp);
   nameFile >> temp;

 }

 //create matrix to store results
 double matrix[fileList.size()][fileList.size()];


 featFile tempFeats;

 for(int i = 0; i < fileList.size(); i++){

   ReadIn(outerFile, fileList[i]);  

   for(int x = 0; x < fileList.size(); x++){

     ReadIn(innerFile, fileList[x]);
 
     if( true ){
      
       matrix[i][x] = compare(outerFile, innerFile, mult);
     
     }else{

       featFile tempOut = outerFile;
       featFile tempIn  = innerFile;

       partition(tempOut, tempIn, trainPerc);

       matrix[i][x] = compare(tempOut, tempIn, mult);

     }
   }
 }


 //Output
 ofstream legitFile( "legitimate.txt" );
 ofstream imposterFile( "Imposter.txt"  );
 ofstream out("Chart.txt");

 for(int i = 0; i < fileList.size(); i++){
   
   out << endl << fileList[i] << " ";

   for(int x = 0; x < fileList.size(); x++){
   
     out << setw(10) << matrix[i][x];
     if( x == i ){ out << "<- " ;}else{ out << " " ;};

     if( i == x ){

       legitFile << matrix[i][x] << endl;

     }else{

       imposterFile << matrix[i][x] << endl;

     }


   }

 }


 return 0;
}



void partition(featFile &out, featFile &in, double perc){


  int trainSize = out.actions.size() * perc;

  featFile tOut = {}, tIn = {};
  int      numActions = 0, numRActions = 0, numLActions = 0, numDActions = 0;
 
  //Clean up
  tIn = in;
  tIn.actions.clear();
  tOut = out;


  //Find Means
  for(int i = 0; i < trainSize; i++){

    switch( out.actions[i].type ){

      case 0: tOut.lMean += out.actions[i].length;
              numLActions++;
      break;

      case 1: tOut.rMean += out.actions[i].length;
              numRActions++;
      break;

      case 2: tOut.dblMean  += out.actions[i].length;
	      tOut.int1Mean += out.actions[i].int1;
	      tOut.int2Mean += out.actions[i].int2;
	      tOut.int3Mean += out.actions[i].int3;
              numDActions++;
      break;

      default: //do nothing
      break;
    }

    if( out.actions[i].type == 0 ||
        out.actions[i].type == 1 ||
        out.actions[i].type == 2   ){

      tOut.spdMean += out.actions[i].speed;
      tOut.aclMean += out.actions[i].accel;
      tOut.jrkMean += out.actions[i].jerk;

      numActions++;
    }

  }

  //Divide to find average
  tOut.lMean    /= numLActions;
  tOut.rMean    /= numRActions;
  tOut.dblMean  /= numDActions;
  tOut.int1Mean /= numDActions;
  tOut.int2Mean /= numDActions;
  tOut.int3Mean /= numDActions;
  tOut.spdMean  /= numActions;
  tOut.aclMean  /= numActions;
  tOut.jrkMean  /= numActions;

  //Find Stds
  for(int i = 0; i < trainSize; i++){

    switch( out.actions[i].type ){

      case 0: tOut.lStd += sqrt( pow((out.actions[i].length - tOut.lMean), 2));
      break;

      case 1: tOut.rStd += sqrt( pow((out.actions[i].length - tOut.rMean), 2));
      break;

      case 2: tOut.dblStd += sqrt( pow((out.actions[i].length - tOut.dblMean), 2));
	      tOut.int1Std += sqrt( pow(out.actions[i].int1 - tOut.int1Mean,2));
	      tOut.int2Std += sqrt( pow(out.actions[i].int2 - tOut.int2Mean,2));
	      tOut.int3Std += sqrt( pow(out.actions[i].int3 - tOut.int3Mean,2));
      break;

      default: //do nothing
      break;
    }

    if( out.actions[i].type == 0 ||
        out.actions[i].type == 1 ||
        out.actions[i].type == 2   ){

      tOut.spdStd += sqrt( pow((out.actions[i].speed - tOut.spdMean), 2));
      tOut.aclStd += sqrt( pow((out.actions[i].accel - tOut.aclMean), 2));
      tOut.jrkStd += sqrt( pow((out.actions[i].jerk - tOut.jrkMean), 2));

    }

  }

  //Divide to find average
  tOut.lStd    /= numLActions;
  tOut.rStd    /= numRActions;
  tOut.dblStd  /= numDActions;
  tOut.int1Std /= numDActions;
  tOut.int2Std /= numDActions;
  tOut.int3Std /= numDActions;
  tOut.spdStd  /= numActions;
  tOut.aclStd  /= numActions;
  tOut.jrkStd  /= numActions;


  //Redo the inner file action vector.
  for(int i = trainSize; i < out.actions.size(); i++){

    tIn.actions.push_back(out.actions[i]);

  }

  //"output"
  out = tOut;
 // in  = tIn;
}


void ReadIn(featFile &f, string name){

 ifstream in(("./features/" + name + "TIMELINE.txt").c_str());

 in >> f.lMean >> f.lStd >> f.rMean >> f.rStd >> f.dblMean 
    >> f.dblStd >> f.int1Mean >> f.int1Std >> f.int2Mean >> f.int2Std 
    >> f.int3Mean >> f.int3Std >> f.spdMean >> f.spdStd >> f.aclMean >> f.aclStd
    >> f.jrkMean >> f.jrkStd;

 mouseAction tA; 

 f.actions.clear();

 in >> tA.start >> tA.type >> tA.length >> tA.speed >> tA.accel >> tA.jerk >> tA.int1 >> tA.int2 >> tA.int3;

 while(in.good()){
   
  f.actions.push_back(tA);

  in >> tA.start >> tA.type >> tA.length >> tA.speed >> tA.accel >> tA.jerk >> tA.int1 >> tA.int2 >> tA.int3;

 }

 in.clear();
 in.close();

}



double compare(featFile out, featFile in, double m){


  double numValid = 0, numTotal = 0;

  for(int i = 0; i < in.actions.size(); i++){

    switch(in.actions[i].type){

      case 0: if(abs(out.lMean -  in.actions[i].length) < (out.lStd   * m) &&
                 abs(out.spdMean - in.actions[i].speed) < (out.spdStd * m) &&
                 abs(out.aclMean - in.actions[i].accel) < (out.aclStd * m) &&
                 abs(out.jrkMean - in.actions[i].jerk)  < (out.jrkStd * m)   ){

                numValid++;
              }

      break;
      case 1: if(abs(out.rMean -  in.actions[i].length) < (out.rStd   * m) &&
                 abs(out.spdMean - in.actions[i].speed) < (out.spdStd * m) &&
                 abs(out.aclMean - in.actions[i].accel) < (out.aclStd * m) &&
                 abs(out.jrkMean - in.actions[i].jerk)  < (out.jrkStd * m)   ){

                numValid++;
              }
      break;
      case 2: if(abs(out.dblMean -  in.actions[i].length) < (out.dblStd * m) &&
                 abs(out.int1Mean - in.actions[i].int1) < (out.int1Std * m) &&
                 abs(out.int2Mean - in.actions[i].int2) < (out.int2Std * m) &&
                 abs(out.int3Mean - in.actions[i].int3) < (out.int3Std * m) &&
                 abs(out.spdMean - in.actions[i].speed) < (out.spdStd * m) &&
                 abs(out.aclMean - in.actions[i].accel) < (out.aclStd * m) &&
                 abs(out.jrkMean - in.actions[i].jerk)  < (out.jrkStd * m)   ){

                numValid++;
              }
      break;
      default: //Do nothing
      break;
    } 

  }  

  //calculate # of left, right and double clicks
  for(int z = 0; z < in.actions.size(); z++){
  
      if(in.actions[z].type == 0 ||
         in.actions[z].type == 1 ||
	 in.actions[z].type == 2   ){
 
        numTotal++;
      }   

  } 

  if(numTotal == 0){
    return 0;
  }else{

    return numValid / numTotal;

  }
}
