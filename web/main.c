#include "include/web_request.h"
#include "helper/fileHandler.h"
#include <pthread.h>
#include <stdio.h>
#include "queue/queue.h"

void *arbeiter(void *arg) {
    int nr = *(int*)arg;
    printf("Thread %d läuft\n", nr);
    return NULL;
}
int main(int argc, char* argv[]) {
    pthread_t t[3];
    int nr[3];


    for (int i = 0; i < 3; i++) {
        nr[i] = i + 1;
        pthread_create(&t[i], NULL, queue_pop, &nr[i]);
    }
    for (int i = 0; i < 3; i++) pthread_join(t[i], NULL);
    return 0;

    return 0;
}
