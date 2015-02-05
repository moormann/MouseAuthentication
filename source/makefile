CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=./featureExtraction/Main.cxx ./featureExtraction/FeatureExtractor.cxx ./featureExtraction/FeatureExtractor.h
OBJECTS=Main.o FeatureExtractor.o
EXECUTABLE=FeatureExtractor.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cxx.o:
	$(CC) $(CFLAGS) $< -o $@
