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


void getDataForS(const char* input, int* routeID, float* dist) {
    char* token = strtok((char*)input, ";");//route ID
    *routeID = atoi(token);

    token = strtok((char*)NULL, ";"); //StepID
    token = strtok((char*)NULL, ";"); //townA
    token = strtok((char*)NULL, ";"); //townB

    token = strtok((char*)NULL, ";"); //Dist
    *dist = strtof(token, NULL);
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