#include "inputFile.h"

int main() {

    char bufferb[4096]; // Assuming a reasonable buffer size

    FILE *fptr;

    // Open a file in read mode
    char buffer[100];
    //fptr = fopen("sample.csv", "r"); 
    fptr = fopen("TtempC.txt", "r"); 
    if(fptr==NULL) {
        printf("NULL");
        exit(0);
    }


    int routeID = 0;
    float dist = 0;

    int a = 0;
    int b = 0;
    char* city = NULL;

    printf("TEST");
    fgets(buffer, sizeof(buffer), fptr); //get first line
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        getDataForTFromPreTreatment(buffer, &city, &a, &b);
        printf("%s %d %d\n", city, a, b);
        //getDataForSbis(buffer, &routeID, &dist);
        free(city);
        city = NULL;
    }

    /*char* cityA = NULL;
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
    }*/
      
    fclose(fptr);
    return 0;
}