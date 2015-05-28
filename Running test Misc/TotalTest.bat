ECHO ON
SETLOCAL ENABLEDELAYEDEXPANSION

SET sngRVals=15 20 25 30 35 40
SET dblRVals=175 180 185 190 195 200
SET windSizes=40 50 60 70
SET mVals=.7 .8 .9 1.5 1.6 1.7 1.8 1.9
SET lengthFlags=all same

ECHO Starting Testing...
ECHO ...

RD /S Tests
MD Tests 


::Update Name File
IF EXIST "Names.txt" (

 DEL "Names.txt"

)

FOR %%z IN (./raw/*) DO (

  ECHO %%z>>./Names.txt

)

FOR %%s IN (%sngRVals%) DO (

  FOR %%d IN (%dblRVals%) DO (

    FOR %%r IN (./raw/*) DO (

      START /B /WAIT FeatureExtraction.exe %%r %%s %%d
      
    )

    FOR %%w IN (%windSizes%) DO (

      FOR %%m IN (%mVals%) Do (

        FOR %%f IN (%lengthFlags%) DO (

          START /B /WAIT validator.exe %%m %%w !!f      

          REN "Imposter.txt" %%m_%%w_!!f_%%s_%%d_!!r_Impos.txt
          REN "Legitimate.txt" %%m_%%w_!!f_%%s_%%d_!!r_Legit.txt

          MOVE /Y %%m_%%w_!!f_%%s_%%d_!!r_Impos.txt ./Tests
          MOVE /Y %%m_%%w_!!f_%%s_%%d_!!r_Legit.txt ./Tests

          PAUSE
        )
      )
    )
  )
)
