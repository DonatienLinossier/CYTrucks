#include "../include/inputFile.h"




void getDataForTFromPreTreatment(const char* input, char** city, int* nbOfTraject, int* nbBeingStart) {
    char* token = strtok((char*)input, ";");
    *nbOfTraject = atoi(token);

    token = strtok((char*)NULL, ";");
    *nbBeingStart = atoi(token);

    token = strtok((char*)NULL, ";");
    *city = strdup(token);

    //Replace the parsed '\n' by '\0'
    int len = strlen(*city);
    if (len > 0) {
        (*city)[len - 1] = '\0';  // Replace the last character with null terminator
    }
}

void getDataForSbis(const char* input, int* routeID, float* dist) {
    // Parse routeID directly without tokenization
    *routeID = atoi(input);

    // Skip to the position after the third semicolon
    int semicolonCount = 0;
    while (*input != '\0' && semicolonCount <= 3) {
        if (*input == ';') {
            ++semicolonCount;
        }
        ++input;
    }

    // Parse dist directly without tokenization
    *dist = strtof(input, NULL);
}


//Deprecated - is slower than getDataForSbis
void getDataForS(const char* input, int* routeID, float* dist) {
    char* token = strtok((char*)input, ";");//route ID
    *routeID = atoi(token);

    strtok(NULL, ";"); //StepID
    strtok(NULL, ";"); //townA
    strtok(NULL, ";"); //townB

    token = strtok(NULL, ";"); //Dist
    *dist = strtof(token, NULL);
}

void getDataForT(const char* input, char** cityA, char** cityB, int* isFirst) {
    char* token = strtok((char*)input, ";");//route ID


    token = strtok((char*)NULL, ";");
    *isFirst = atoi(token) == 1;

    token = strtok((char*)NULL, ";");
    *cityA = strdup(token);

    token = strtok((char*)NULL, ";");
    *cityB = strdup(token);
}





/*
#########################################"
# Exemple of usage
##########################################
int main() {

    char bufferb[4096];

    FILE *fptr;

    // Open a file in read mode
    char buffer[100];
    fptr = fopen("sample.csv", "r"); 
    if(fptr==NULL) {
        printf("NULL");
        exit(0);
    }

    char* cityA = NULL;
    char* cityB = NULL;
    int isFirst = 0;
    fgets(buffer, sizeof(buffer), fptr); //get first line
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        getDataForT(buffer, &cityA, &cityB, &isFirst);
        printf("%s %s %d\n", cityA, cityB, isFirst);

        #/!\ Free cityA and cityB /!\
        if(cityA!=NULL) {
            free(cityA);
            cityA = NULL;
        }
        if(cityB!=NULL) {
            free(cityB);
            cityB = NULL;
        }
    }
    

    
    fclose(fptr);
    return 0;
}*/