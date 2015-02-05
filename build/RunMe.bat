@ECHO OFF

ECHO Cleaning Files

COPY /b /y "./MouseRecords.arff" "./features"
DEL "./Names.txt"

FOR %%N IN (./raw/*) DO (

ECHO|set /P bleh= "%%N" >>"./features/MouseRecords.arff"
ECHO|set /P bleh= "," >>"./features/MouseRecords.arff"

)

ECHO }>> "./features/MouseRecords.arff"

ECHO @data >> "./features/MouseRecords.arff"

ECHO Starting file processing.

FOR %%i IN (./raw/*) DO (
  START /B /WAIT FeatureExtraction.exe %%i
  ECHO File %%i finished
  ECHO %%i>>./Names.txt
)

ECHO Starting Validation...
START /B /WAIT validator.exe


ECHO Finished
PAUSE
EXIT
