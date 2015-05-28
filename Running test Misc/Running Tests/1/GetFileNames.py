import shutil
import os
import time
import subprocess

sngRVals = [15, 20, 25, 30, 35, 40]
dblRVals = [175, 180, 185, 190, 195, 200]
windSizes = [.40, .50, .60, .70]
mVals = [.7, .8, .9, 1.5, 1.6, 1.7, 1.8, 1.9]
lengthFlags = ["all", "same"]

print("Cleaning Files...")

leNF = open('legitNameFile.txt', 'w+')
imNF = open('imposNameFile.txt', 'w+')


for sRVal in sngRVals:
   for dRVal in dblRVals:
      for rawF in os.listdir('./raw/'):
         if os.path.isfile('./raw/' + rawF):
            for windS in windSizes:
               for mVal in mVals:
                  for flag in lengthFlags:
                     impos ='Tests/' + flag + "_" + str(windS) + "_" + str(mVal) + "_" + str(sRVal) + "_" + str(dRVal) + "_" + rawF + "Impos.txt\n"
                     legit ='Tests/' + flag + "_" + str(windS) + "_" + str(mVal) + "_" + str(sRVal) + "_" + str(dRVal) + "_" + rawF + "Legit.txt\n"
                     imNF.write(impos);
                     leNF.write(legit);


