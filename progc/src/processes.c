#include "../include/processes.h"

#define NUM_VALUES_T 10
#define NUM_VALUES_S 50

//Give the results of the process S from the given file
void processS(char * link) {
    char bufferb[4096]; // Assuming a reasonable buffer size

    FILE *fptr;

    // Open a file in read mode
    char buffer[100];
    fptr = fopen(link, "r"); 
    if (fptr == NULL) {
        exit(1);
    }

    int route_id;
    float distance;
    fgets(buffer, sizeof(buffer), fptr); // get first line
    NodeS* root = NULL;

    // Loop through the file and fill AVL tree
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        getDataForS(buffer, &route_id, &distance);
        root = addNodeS(root, route_id, distance);
    }

    int count;
    NodeS** maxRangesArray = getMaxRanges(root, &count);
    qsort(maxRangesArray, NUM_VALUES_S, sizeof(NodeS*), compareRanges);

    // Access the nodes with the highest ranges using maxRangesArray[i]
    for (int i = 0; i < count; ++i) {
        printf("%d;",i);
        printNodeS(maxRangesArray[i]);
    }

    freeNodeS(root);
    fclose(fptr);
    return;
}

//Give the results of the process T from the given file
void processT(char * link) {
    char bufferb[4096]; // Assuming a reasonable buffer size

    FILE *fptr;

    // Open a file in read mode
    char buffer[100];
    fptr = fopen(link, "r"); 
    if (fptr == NULL) {
        exit(1);
    }

    int num_steps = 0;
    int num_firsts = 0;
    char* city = NULL;
    int values[NUM_VALUES_T] = {0};
    int min = 0;
    int size_avl = 0;

    fgets(buffer, sizeof(buffer), fptr); // get first line
    NodeT* root = NULL;

    // Loop through the file and fill AVL T tree
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        getDataForTFromPreTreatment(buffer, &city, &num_steps, &num_firsts);
        if (size_avl < NUM_VALUES_T || num_steps > values[min]) {
            size_avl += 1;
            if (num_steps > values[min]) {
                values[min] = num_steps;
                min = getMin(values, NUM_VALUES_T);
            }
            root = addNodeT(root, city, num_steps, num_firsts);
        }
        free(city);
        city = NULL;
    }

    int count = 0;
    NodeT* results[NUM_VALUES_T];
    inOrderT(root, &count, results);
    qsort(results, NUM_VALUES_T, sizeof(NodeT*), compareT);

    // Print the top NUM_VALUES_T results
    for (int i = 0; i < NUM_VALUES_T; i++) {
        printNodeT(results[i]);
    }

    freeNodeT(root);
    fclose(fptr);
}
