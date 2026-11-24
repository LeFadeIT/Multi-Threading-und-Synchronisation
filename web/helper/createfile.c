//
// Created by mikwagen on 24.11.26.
//

#include "createfile.h"

#include <stdio.h>
#include <stdlib.h>

void createFile(char* argv) {
    FILE* fd_in;
    if (!(fd_in = fopen(argv, "r"))) {
        perror("failed to open input file");
        exit(EXIT_FAILURE);
    }else {
        printf("create input file\n");
    }




}
