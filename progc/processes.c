#include "avlS.h"
#include "avlT.h"
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
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        printf("a1\n");
        getDataForS(buffer, &route_id, &distance);
        printf("a2\n");
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
        printf("a3\n");
    }
    printf("%d\n",heightS(root));

    int* count = 0;
    NodeS* maxRangeNodes[50];
    int maxRangeValues[50];
    printf("a9\n");
    getMaxRangeValues(root, count, maxRangeNodes, maxRangeValues);
    printf("z\n");

    // Print the results
    for (int i = 0; i < *count; i++) {
        printf("NUM=%d :RouteID=%d, max=%d, min=%d, moyenne=%d\n",i, maxRangeNodes[i]->key, maxRangeNodes[i]->max, maxRangeNodes[i]->min, maxRangeNodes[i]->total/maxRangeNodes[i]->num_steps);
    }


    

    
    fclose(fptr);
    return;
}

void processT(){
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


    int num_steps = 0;
    int num_firsts = 0;
    char* city = NULL;
    int min=0;
    int size_avl=0;

    printf("TEST");
    fgets(buffer, sizeof(buffer), fptr); //get first line
    printf("ccc\n");
    NodeT* root = NULL;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        printf("bbb\n");
        getDataForTFromPreTreatment(buffer, &city, &num_steps, &num_firsts);
        printf("%s %d %d\n", city, num_steps, num_firsts);
        if(size_avl<10 || num_steps > min){
            if(size_avl<10)size_avl+=1;
            addNodeT(root,city,num_steps,num_firsts);
            min=getMinT(root);
        }
        free(city);
        city = NULL;
    }
    inOrderT(root);
    
}