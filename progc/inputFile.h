#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



//Return the stepID, the cityA and the cityB from an input line
void getDataForT(const char* input, char** cityA, char** cityB, int* isFirst);

//Return the routeID and dist from an input line
void getDataForS(const char* input, int* routeID, float* dist);



#endif //#ifndef INPUTSFILE_H