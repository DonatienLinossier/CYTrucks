#include "avl.S"
#include "avl.T"
#include "avl.T2"
#include "temp.c"

#define NUM_CITIES 10

void processT()
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
    fptr = fopen("data/sample.csv", "r"); 
    //fptr = fopen("temp/tmpD1.csv", "r"); 
    if(fptr==NULL) {
        printf("NULL");
        exit(0);
    }

    char* cityA = NULL;
    char* cityB = NULL;
    int isFirst = 0;

    nodeT* root_t = NULL;

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


        addStepT(root_t, cityB, isFirst);
    }

    nodeT*[NUM_CITIES] max_through;
    for (int i=0; i<NUM_CITIES; i++){
        max_through[i]=
    }

    
    
    fclose(fptr);
    return 0;