#include "avlS.h"
#include "avlT.h"
#include "inputFile.h"

void processS(){
    char bufferb[4096]; // Assuming a reasonable buffer size

    FILE *fptr;

    // Open a file in read mode
    char buffer[100];
    fptr = fopen("../data/data10k.csv", "r"); 
    if(fptr==NULL) {
        printf("NULL\n");
        exit(0);
    }

    int route_id;
    float distance;
    fgets(buffer, sizeof(buffer), fptr); //get first line
    NodeS* root = NULL;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
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
    printf("aaaaaa\n");
    printf("height:%d\n",heightS(root));
    int count;
    NodeS** maxRangesArray = getMaxRanges(root, &count);
    qsort(maxRangesArray, 50, sizeof(NodeS*), compareRanges);

   
    printf("count:%d\n",count);

     // Access the nodes with the highest ranges using maxRangesArray[i]
    for (int i = 0; i < count; ++i) {
        printf("Node %d with range %d\n", maxRangesArray[i]->key, maxRangesArray[i]->max - maxRangesArray[i]->min);
    }

    printf("yoooo\n");


    

    
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

    fgets(buffer, sizeof(buffer), fptr); //get first line
    printf("aaa\n");
    NodeT* root = NULL;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        getDataForTFromPreTreatment(buffer, &city, &num_steps, &num_firsts);
        //printf("%s %d %d\n", city, num_steps, num_firsts);
        if(size_avl<10 || num_steps > min){
            if(size_avl<10)size_avl+=1;
            if(num_steps>min)min=num_steps;
            root = addNodeT(root,city,num_steps,num_firsts);
        }
        free(city);
        city = NULL;
    }
    printf("zzz\n");
    inOrderT(root);
    
}