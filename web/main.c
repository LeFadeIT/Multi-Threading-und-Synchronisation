#include <stdio.h>
#include <stdlib.h>
#include "helper/createfile.h"

typedef struct {
    char* url;
    struct URLS* next;
} URLS;



int main(int argc, char* argv[]) {
    createFile(&argv[1]);
    return 0;
}
