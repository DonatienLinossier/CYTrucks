#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct route {
    int routeID;
    int stepID;
    char* townA;
    char* townB;
    float distance;
    char* driverName;
} Route; 


Route* createRouteFromString(const char* input) {
    Route* ptrNewRoute= malloc(sizeof(Route));

    // Tokenize the input string using strtok
    char* token = strtok((char*)input, ";");

    // Convert and assign values to struct members
    //ptrNewRoute->routeID = atoi(token);

    token = strtok(NULL, ";");
    //ptrNewRoute->stepID = atoi(token);

    token = strtok(NULL, ";");
    //ptrNewRoute->townA = strdup(token);

    token = strtok(NULL, ";");
    //ptrNewRoute->townB = strdup(token);

    token = strtok(NULL, ";");
    ptrNewRoute->distance = atof(token);

    token = strtok(NULL, ";");
    ptrNewRoute->driverName = strdup(token);

    return ptrNewRoute;
}

// Function to free memory allocated for a Route struct
void freeRoute(Route* route) {
    free(route->townA);
    free(route->townB);
    free(route->driverName);
}

int main() {

    FILE *fptr;

    // Open a file in read mode
    char buffer[1000];
    fptr = fopen("../data.csv", "r"); 
    if(fptr==NULL) {
        exit(0);
    }

    Route* r ;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        r = createRouteFromString(buffer);
        if(r==NULL) {
            break;
        }

        // Display the struct members
        /*printf("Route ID: %d\n", r->routeID);
        printf("Step ID: %d\n", r->stepID);
        printf("Town A: %s\n", r->townA);
        printf("Town B: %s\n", r->townB);
        printf("Distance: %.2f\n", r->distance);
        printf("Driver Name: %s\n", r->driverName)*/;
    }
    
    fclose(fptr);
    return 0;
}