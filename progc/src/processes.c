#include "../include/processes.h"

void processS(char * link){
    char bufferb[4096]; // Assuming a reasonable buffer size

    FILE *fptr;

    // Open a file in read mode
    char buffer[100];
    fptr = fopen(link, "r"); 
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
        
        root = addNodeS(root,route_id,distance);
    }

    int count;
    NodeS** maxRangesArray = getMaxRanges(root, &count);
    qsort(maxRangesArray, 50, sizeof(NodeS*), compareRanges);

   
     // Access the nodes with the highest ranges using maxRangesArray[i]
    for (int i = 0; i < count; ++i) {
        printf("%d;%d;%f;%f;%f;%f\n",i+1,maxRangesArray[i]->key, maxRangesArray[i]->min,maxRangesArray[i]->total/maxRangesArray[i]->num_steps,maxRangesArray[i]->max, maxRangesArray[i]->max - maxRangesArray[i]->min);
    }

    fclose(fptr);
    return;
}

void processT(char * link){
    char bufferb[4096]; // Assuming a reasonable buffer size

    FILE *fptr;

    // Open a file in read mode
    char buffer[100];
    //fptr = fopen("sample.csv", "r"); 
    fptr = fopen(link, "r"); 
    if(fptr==NULL) {
        printf("NULL");
        exit(0);
    }


    int num_steps = 0;
    int num_firsts = 0;
    char* city = NULL;
    int values[10]={0};
    int min=0;
    int size_avl=0;

    fgets(buffer, sizeof(buffer), fptr); //get first line
    NodeT* root = NULL;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        getDataForTFromPreTreatment(buffer, &city, &num_steps, &num_firsts);
        if(size_avl<10 || num_steps > values[min]){
            size_avl+=1;
            if(num_steps>values[min]){
                values[min]=num_steps;
                min=getMin(values,10);
            }
            root = addNodeT(root,city,num_steps,num_firsts);
        }
        free(city);
        city = NULL;
    }
    int count=0;
    inOrderT(root,&count);
    
    freeNodeT(root);
    fclose(fptr);
}