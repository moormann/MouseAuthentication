#include "validator.h"

int main()
 {
  data oldData;			//This struct is for header data.
  data trash;
  newData currentData;		//This struct is for the data in the body.
  double matrix[56][56];

  ifstream inFile;
  ifstream testFile;
  ofstream outFile;

  outFile.open("Chart.data");
  outFile.setf(ios::fixed);
  outFile.precision(2);

  stringstream ss;
  int t;
  int r;

  int yesCount = 0;             //Determines the number of times data is within a specified standard deviation.
  int totalCount = 0;           //Total number of actions in a file.

//#comp This will be the name of every file.

  for (t = 1; t < 57; t++)
{
  ss << t;
  inFile.open((ss.str() + "TIMELINE.txt").c_str());
  

  getData(inFile, oldData);     //Retrieves header data.


  if(inFile.good()){
    cout << "File " << ss.str() << endl;
  }else{
    cout << ss.str() + "TIMELINE.txt" << endl;
  }

  ss.str("");
  


  cout << oldData.leftMean << endl;



  for (r = 1; r < 57; r++)
{
  ss << r;
  testFile.open((ss.str() + "TIMELINE.txt").c_str());
  ss.str("");

  getData(testFile, trash); 

  yesCount = 0;
  totalCount = 0;

  getNewData(testFile, currentData);			//Retrieves data from body.
  
  while (testFile.good() && inFile.good())
   {
    totalCount = totalCount + 1;

    if (currentData.type == 0)				//These are for determining actions based on type.
     {
      type0(oldData, currentData, yesCount);
     };

    if (currentData.type == 1)
     {
      type1(oldData, currentData, yesCount);
     };

    if (currentData.type == 2)
     {
      type2(oldData, currentData, yesCount);
     };

    if (currentData.type == 3)
     {
      type3(oldData, currentData, yesCount);
     };

    getNewData(testFile, currentData);			//Retrieves data from body.
   };

  if(totalCount != 0){
    matrix[t-1][r-1] = (double(yesCount)/double(totalCount));
  }else{
    matrix[t-1][r-1] = -1;
  }
  cout << oldData.leftMean << " " << trash.leftMean << endl;
  //cout << t << " " << r << " " << matrix[t-1][r-1] << " " << yesCount << " " << totalCount << endl;
  testFile.close();
}

inFile.close();
}

  print(outFile, matrix);

  outFile.close();

  cin >> t;

  return 0;
 }
