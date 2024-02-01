#include "processes.h"
#include "inputFile.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <arg1> <arg2>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[2], "0") == 0) {
        processS(argv[1]);
    }
    else if (strcmp(argv[2], "1") == 0) {
        processT(argv[1]);
    }
    else {
        printf("Invalid argument\n");
    }

    return 0;
}
