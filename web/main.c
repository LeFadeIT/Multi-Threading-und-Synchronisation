#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "include/web_request.h"
#include "queue/queue.h"


typedef struct {
    FILE* file;
    queue* q;
} reader_arg;

typedef struct {

    int nr;
    queue* q;

}client_arg;


void *reader(void *arg) {
    reader_arg *ra = (reader_arg *)arg;
    char line[1024];
    while (fgets(line, sizeof line, ra->file)) {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0]=='\0') continue;
        if (strncmp(line, "http", 4) != 0) continue;
        queue_push(ra->q, strdup(line));
    }
    queue_finish(ra->q);
    return NULL;
}

 // oben bei den Includes ergänzen



void *client(void *arg) {
    client_arg *ca = (client_arg *)arg;
    int j = 0;
    char *url;
    printf("[Client %d] gestartet\n", ca->nr);
    while ((url = queue_pop(ca->q)) != NULL) {
        char *rest;
        char *kopie = strdup(url);
        char name[256];
        strtok_r(kopie, "/", &rest);
        char *host = strtok_r(NULL, "/", &rest);
        if (host == NULL) {
            fprintf(stderr, "[Client %d] ungueltige URL: %s\n", ca->nr, url);
        } else {
            snprintf(name, sizeof name, "%d_%d_%s.html", ca->nr, ++j, host);
            printf("[Client %d] START %s -> %s\n", ca->nr, url, name);
            int res = webreq_download(url, name);
            if (res < 0)
                fprintf(stderr, "[Client %d] FEHLER %s: %s\n", ca->nr, url, webreq_error(res));
            else if (res != WEBREQ_HTTP_OK)
                fprintf(stderr, "[Client %d] HTTP %d bei %s\n", ca->nr, res, url);
            else
                printf("[Client %d] DONE  %s -> %s\n", ca->nr, url, name);
        }
        free(kopie);
        free(url);
    }
    printf("[Client %d] beendet (%d Downloads)\n", ca->nr, j);
    return NULL;
}

int main(int argc, char *argv[]) {
    int clients = 5;
    if (argc < 2) { fprintf(stderr, "Usage: %s file\n", argv[0]); return 1; }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) { perror("fopen"); return 1; }

    if (argv[2] != NULL) {
        clients = atoi(argv[2]);
    }
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double start = tv.tv_sec * 1000 + tv.tv_usec / 1000;

    webreq_init(argc, argv);
    queue *q = queue_init();

    pthread_t ct[clients], rt;
    client_arg ca[clients];
    for (int i = 0; i < clients; i++) {
        ca[i].nr = i + 1;
        ca[i].q = q;
        pthread_create(&ct[i], NULL, client, &ca[i]);
    }
    reader_arg ra = { f, q };
    pthread_create(&rt, NULL, reader, &ra);

    pthread_join(rt, NULL);
    for (int i = 0; i < clients; i++) pthread_join(ct[i], NULL);

    fclose(f);
    webreq_cleanup();
    queue_delete(q);

    gettimeofday(&tv, NULL);
    double end = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    printf("Duration: %5.2f s\n", (end - start) / 1000);
    return 0;
}
