//
// Created by mikwagen on 28.11.26.
//

/**************************************************************
* queue.c
* Funktion: erstellt eine Queue und verwaltet diese
* Autor: Eileen Heptner, Mike Wagener
* Historie:
* 2026/11/24: Queue erstellen, Queue_push, queue_pop, queue_finish. queue_delete
* To Do:
*************************************************************/

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


queue* queue_init(void) {
    queue* q;
    q = (queue*)malloc(sizeof(queue));
    if (q == NULL) {
        perror("Queue init failed");
        exit(1);
    }
    q->count = 0;
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

void queue_push (queue *q, char* url) {
    pthread_mutex_lock (q->mut);
    while (q->count == QUEUE_SIZE) {
        pthread_cond_wait(q->notFull, q->mut);
    }
    q->buf[q->tail] = url;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
    q->count++;
    pthread_mutex_unlock (q->mut);
    pthread_cond_signal (q->notEmpty);
}

char* queue_pop (queue *q) {
    char* URL;
    pthread_mutex_lock (q->mut);
    while (!q->done && q->count == 0) {
     pthread_cond_wait(q->notEmpty, q->mut);
    }
    if (q->count == 0) {
        pthread_mutex_unlock (q->mut);
        return NULL;
    }

    URL = q->buf[q->head];
    q->head = (q->head + 1) % QUEUE_SIZE;
    q->count--;
    pthread_mutex_unlock (q->mut);
    pthread_cond_signal (q->notFull);
    return URL;
}

void queue_finish(queue *q) {
    pthread_mutex_lock (q->mut);
    q->done = 1;
    pthread_mutex_unlock (q->mut);
    pthread_cond_broadcast (q->notEmpty);
}

void queue_delete(queue *q) {
    pthread_mutex_destroy (q->mut);
    pthread_cond_destroy (q->notEmpty);
    pthread_cond_destroy (q->notFull);
    free(q->mut);
    free(q->notFull);
    free(q->notEmpty);
    free(q);
}