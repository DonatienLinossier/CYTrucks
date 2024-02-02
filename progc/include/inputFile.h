#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//Return the city, nbOfTraject and nbBeingStart
void getDataForTFromPreTreatment(const char* input, char** city, int* nbOfTraject, int* nbBeingStart);

//Return the routeID and dist from an input line, using string manipulation
void getDataForSbis(const char* input, int* routeID, float* dist);

//Return the routeID and dist from an input line, using strtok | deprecated - use getDataForSbis
void getDataForS(const char* input, int* routeID, float* dist);

//Return the stepID, the cityA and the cityB from an input line | not used
void getDataForT(const char* input, char** cityA, char** cityB, int* isFirst);

#endif