//
// Created by mikwagen on 28.11.26.
//

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>



queue* queue_init(void) {
    queue* q;
    q = (queue*)malloc(sizeof(queue));
    if (q == NULL) {
        perror("Queue init failed");
        exit(1);
    }
    q->count = 1;
    q->done = 0;
    q->head = 0;
    q->tail = 0;
    q->mut = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t));
    pthread_mutex_init (q->mut, NULL);
    q->notFull = (pthread_cond_t *) malloc (sizeof (pthread_cond_t));
    pthread_cond_init (q->notFull, NULL);
    q->notEmpty = (pthread_cond_t *) malloc (sizeof (pthread_cond_t));
    pthread_cond_init (q->notEmpty, NULL);

    return q;
}

void queue_push (queue *q, void *data) {

}

void *queue_pop (void *data) {

}
