#include "include/web_request.h"
#include "helper/fileHandler.h"
int main(int argc, char* argv[]) {

    webreq_init(argc, argv);


    createFile(argv);
    writeToFile(argv, argc);
    return 0;
}
