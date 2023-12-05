#include <stdio.h>
#include <stdlib.h>







int main() {

    FILE *fptr;

    // Open a file in read mode
    fptr = fopen("sample.csv", "r"); 
    if(fptr==NULL) {
        exit(0);
    }
    fclose(fptr);
    return 0;
}