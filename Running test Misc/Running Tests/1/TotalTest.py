import shutil
import os
import time
import subprocess

sngRVals = [15]
dblRVals = [175, 180, 185, 190, 195, 200]
windSizes = [.40, .50, .60, .70]
mVals = [.7, .8, .9, 1.5, 1.6, 1.7, 1.8, 1.9]
lengthFlags = ["all", "same"]

print("Cleaning Files...")

shutil.rmtree('./Tests')

os.makedirs('./Tests')

try:
   nameFile = open('./Names.txt', 'w+')
except IOError:
   print("File Failed to open")
   
for name in os.listdir('./raw/'):
   if os.path.isfile('./raw/' + name):
      nameFile.write(name + '\n')

nameFile.close();

count = 0

for sRVal in sngRVals:
   for dRVal in dblRVals:
      for rawF in os.listdir('./raw/'):
         if os.path.isfile('./raw/' + rawF):
            subprocess.call(['./FeatureExtraction.exe', str(rawF), str(sRVal), str(dRVal)], shell=True)
            print("\nFeatures Extracted\n Validating");
            for windS in windSizes:
               for mVal in mVals:
                  for flag in lengthFlags:
                     
                     subprocess.call(['./validator.exe', str(mVal), str(windS), flag])

                     os.rename('./Imposter.txt','./Tests/' + flag + "_" + str(windS) + "_" + str(mVal) + "_" + str(sRVal) + "_" + str(dRVal) + "_" + rawF + "Impos.txt")
                     os.rename('./Legitimate.txt','./Tests/' + flag + "_" + str(windS) + "_" + str(mVal) + "_" + str(sRVal) + "_" + str(dRVal) + "_" + rawF + "Legit.txt")

                     print('.',end="",flush=True)

