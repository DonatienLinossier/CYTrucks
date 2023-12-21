#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void getDataForT(const char* input, char* cityA, char* cityB, char* isFirst) {
    char* token = strtok((char*)input, ";");//route ID

    token = strtok((char*)input, ";");
    *isFirst = atoi(token);

    token = strtok((char*)input, ";");
    cityA = strdup(token);(token);

    token = strtok((char*)input, ";");
    cityB = strdup(token);(token);
}

int main() {

    char bufferb[4096]; // Assuming a reasonable buffer size

    if (getcwd(bufferb, sizeof(bufferb)) != NULL) {
        printf("Current working directory: %s\n", bufferb);
    } else {
        perror("getcwd() error");
        return 1;
    }

    FILE *fptr;

    // Open a file in read mode
    char buffer[100];
    fptr = fopen("sample.csv", "r"); 
    //fptr = fopen("temp/tmpD1.csv", "r"); 
    if(fptr==NULL) {
        printf("NULL");
        exit(0);
    }

    char* cityA;
    char* cityB;
    char isFirst;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        getDataForT(buffer, cityA, cityB, &isFirst);
        printf("%s %s %c", cityA, cityB, isFirst);

    }
    
    /*while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        D1* d1 = createD1fromLine(buffer);
        printf("%s %d\n", d1->driverName, d1->routeID);

    }*/
    
    fclose(fptr);
    return 0;
}




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