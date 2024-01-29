#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



//Return the stepID, the cityA and the cityB from an input line
void getDataForT(const char* input, char** cityA, char** cityB, int* isFirst);

//Return the routeID and dist from an input line, using strtok | deprecated 
void getDataForS(const char* input, int* routeID, float* dist);

//Return the routeID and dist from an input line, using string manipulation | faster
void getDataForSbis(const char* input, int* routeID, float* dist);

//Return the city, nbOfTraject and nbBeingStart
void getDataForTFromPreTreatment(const char* input, char** city, int* nbOfTraject, int* nbBeingStart);

#endif