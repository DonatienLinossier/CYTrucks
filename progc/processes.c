#include "avlS.h"
#include "avlT.h"
#include "avlT2.h"
#include "inputFile.h"

void processS(){
    char bufferb[4096]; // Assuming a reasonable buffer size

    FILE *fptr;

    // Open a file in read mode
    char buffer[100];
    fptr = fopen("/cergy/homee/g/gaudareeli/TPinfo/CYTrucks/CYTrucks/data/data10k.csv", "r"); 
    if(fptr==NULL) {
        printf("NULL\n");
        exit(0);
    }

    int route_id;
    float distance;
    fgets(buffer, sizeof(buffer), fptr); //get first line
    NodeS* root = NULL;
    int aaaa=0;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        //printf("%d\n",aaaa);
        aaaa+=1;
        getDataForS(buffer, &route_id, &distance);
        /*
        if(route_id!=NULL) {
            free(route_id);
            route_id = NULL;
        }
        if(distance!=NULL) {
            free(distance);
            distance = NULL;
        }*/
        root = addNodeS(root,route_id,distance);
    }
    printf("%d\n",heightS(root));

    int count = 0;
    NodeS* maxRangeNodes[10];
    int maxRangeValues[10];

    getMaxRangeValues(root, &count, maxRangeNodes, maxRangeValues);
    printf("z\n");

    // Print the results
    for (int i = 0; i < count; i++) {
        printf("RouteID %d: max=%d, min=%d, moyenne=%d\n", maxRangeNodes[i]->key, maxRangeNodes[i]->max, maxRangeNodes[i]->min, maxRangeNodes[i]->total/maxRangeNodes[i]->num_steps);
    }


    

    
    fclose(fptr);
    return;
}