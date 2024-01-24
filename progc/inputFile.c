#include "inputFile.h"

void getDataForT(const char* input, char** cityA, char** cityB, int* isFirst) {
    char* token = strtok((char*)input, ";");//route ID


    token = strtok((char*)NULL, ";");
    *isFirst = atoi(token) == 1;

    token = strtok((char*)NULL, ";");
    *cityA = strdup(token);

    token = strtok((char*)NULL, ";");
    *cityB = strdup(token);
}


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


void getDataForS(const char* input, int* routeID, float* dist) {
    char* token = strtok((char*)input, ";");//route ID
    *routeID = atoi(token);

    strtok(NULL, ";"); //StepID
    strtok(NULL, ";"); //townA
    strtok(NULL, ";"); //townB

    token = strtok(NULL, ";"); //Dist
    *dist = strtof(token, NULL);
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
    //printf("%s", input);
    *dist = strtof(input, NULL);
}

/*
#########################################"
# Exemple of usage
##########################################
int main() {

    char bufferb[4096]; // Assuming a reasonable buffer size

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


//Bordel, ne plus lire a partir d'ici

    /*while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        D1* d1 = createD1fromLine(buffer);
        printf("%s %d\n", d1->driverName, d1->routeID);

    }*/

/*typedef struct D1 {
    char* driverName;
    int routeID;
} D1;

typedef struct D2 {
    char* driverName;
    int distance;
} D2;

D1* createD1fromLine(const char* input) {
    D1* d1= malloc(sizeof(D1));

    // Tokenize the input string using strtok
    char* token = strtok((char*)input, ";");
    d1->driverName = strdup(token);

    token = strtok(NULL, ";");
    d1->routeID = atoi(token);

    return d1;
}

D2* createD2fromLine(const char* input) {
    D2* d2= malloc(sizeof(D1));

    // Tokenize the input string using strtok
    char* token = strtok((char*)input, ";");
    d2->driverName = strdup(token);

    token = strtok(NULL, ";");

    d2->distance = atoi(token);

    return d2;
}*/