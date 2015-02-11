ECHO OFF

SET sngRVals=15 20 25 30 35 40
SET dblRVals=175 180 185 190 195 200
SET windSizes=40 50 60 70
SET mVals=.7 .8 .9 1.5 1.6 1.7 1.8 1.9
SET lengthFlags=all same

ECHO Starting Testing...
ECHO 

RD /S Tests
MD Tests


::Update Name File
DEL "./Names.txt"

FOR %%file IN (./raw/*) DO (

  ECHO %%file>>./Names.txt

)

FOR %%sngRVal IN (sngRVals) DO (

  FOR %%dblRVal IN (dblRVals) Do (

    FOR %%file IN (./raw/*) DO (

      START /B /WAIT FeatureExtraction.exe %%file %%sngVal %%dblVal
      
    )


    FOR %%windSize IN (windSizes) DO (

      FOR %%mVal IN (mVals) Do (

        FOR %%flag IN (lengthFlags) DO (

          START /B /WAIT validator.exe %%mVal %%windSize %%flag
          ::create file tree        

        )
      )

    )

  )

)