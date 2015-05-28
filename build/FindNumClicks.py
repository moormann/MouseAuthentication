import os

maxSngClicks = 0
minSngClicks = 100000
maxDblClicks = 0
minDblClicks = 100000
maxRgtClicks = 0
minRgtClicks = 100000
totalFiles = 0
leftAvg = 0
rightAvg = 0
dblAvg = 0
lowTotalAvg = 100000
lowTotalAvgName = ""
thisL = 0;
thisR = 0;
thisD = 0;


for fileN in os.listdir("./features"):
    if fileN.endswith(".mrf"):
        totalFiles += 1
        file = open("./features/"+fileN);
        for line in file:
            if "Num Left" in line:
                thisL = int(line[line.find(':')+ 1:len(line)])
            if "Num Right" in line:
                thisR = int(line[line.find(':')+ 1:len(line)])
            if "Num Double" in line:
                thisD = int(line[line.find(':')+ 1:len(line)])
                
            thisAvg = (thisL + thisR + thisD) / 3

    if(thisAvg < lowTotalAvg):
        lowTotalAvg = thisAvg
        lowTotalAvgName = fileN
        
    if maxSngClicks < thisL:
        maxSngClicks = thisL
    if maxRgtClicks < thisR:
        maxRgtClicks = thisR
    if maxDblClicks < thisD:
        maxDblClicks = thisD
        
    if minSngClicks > thisL:
        minSngClicks = thisL
    if minRgtClicks > thisR:
        minRgtClicks = thisR
    if minDblClicks > thisD:
        minDblClicks = thisD
                    
    leftAvg += thisL
    rightAvg += thisR
    dblAvg += thisD
        
    

#Calc Averages
leftAvg /= totalFiles
rightAvg /= totalFiles
dblAvg /= totalFiles


outFile = open('ClickStats.txt', 'w')

outFile.write("Num Files:         " + str(totalFiles)   + "\n\n" +
              "Max Left Clicks:   " + str(maxSngClicks) + "\n" +
              "Min Left Clicks:   " + str(minSngClicks) + "\n" +
              "Average:           " + str(leftAvg) + "\n\n" +
              "Max Right Clicks:  " + str(maxRgtClicks) + "\n" +
              "Min Right Clicks:  " + str(minRgtClicks) + "\n" +
              "Average:           " + str(rightAvg) + "\n\n" +
              "Max Double Clicks: " + str(maxDblClicks) + "\n" +
              "Min Double Clicks: " + str(minDblClicks) + "\n" +
              "Average:           " + str(dblAvg) + "\n\n" +
              "Lowest Total Avg:  " + str(lowTotalAvg) + " file: " + lowTotalAvgName)

outFile.close()

