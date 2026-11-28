//
// Created by mikwagen on 24.11.26.
//

#include "fileHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void createFile(char* argv[]) {
    FILE* fd_in;
    if (!(fd_in = fopen(argv[1], "w"))) {
        perror("failed to open input file");
        exit(EXIT_FAILURE);
    }else {
        printf("create input file\n");
        fclose(fd_in);
    }


}

void writeToFile(char* argv[], int argc) {
    FILE* fd_out;
    if (!(fd_out = fopen(argv[1], "a"))) {
        perror("failed to open output file");
        exit(EXIT_FAILURE);
    }else {
        for (int i = 2; i < argc; i++) {
            fprintf(fd_out, "%s ", argv[i]);
        }
        fclose(fd_out);
    }
}

URLS* readFromFile(char* argv[]) {
    FILE* fd_in;
    if (!(fd_in = fopen(argv[1], "r"))) {
        perror("failed to open input file");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    while (fgets(line, sizeof line, fd_in)) {

        line[strcspn(line, "\r\n")] = '\0';
    }
}
