//
// Created by mikwagen on 28.11.26.
//

#ifndef BLATT6_QUEUE_H
#define BLATT6_QUEUE_H
#define QUEUE_SIZE 10
#include <pthread.h>

typedef struct {
    char* buf[QUEUE_SIZE];
    long head, tail;
    int done , count;
    pthread_mutex_t *mut;
    pthread_cond_t *notFull, *notEmpty;
} queue;


queue* queue_init(void);
void queue_push(queue *q, char* url);
char* queue_pop(queue *q);
void queue_finish(queue *q);
void queue_delete(queue *q);

#endif //BLATT6_QUEUE_H
