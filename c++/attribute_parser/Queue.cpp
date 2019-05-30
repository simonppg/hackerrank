#include "Queue.hpp"
#include "Node.hpp"

#include <stdio.h>
#include <stdlib.h>

void enqueue(Queue *q, void *data) {
    Node *n = new_node(data);
    if(q->rear == NULL && q->front == NULL) {
        q->front = n;
    } else {
        q->rear->next = n;
    }

    q->rear = n;
}

void* dequeue(Queue *q) {
    void *data = NULL;
    Node *n = NULL;
    if(q && q->front) {
        n = q->front;
        q->front = n->next;
        n->next = NULL;
        data = n->data;
    }
    free(n);
    return data;
}


void print_queue(Queue *q, void (*print_node)(void *t)) {
    if(q == NULL || q->front == NULL)
        return;

    Node *n = q->front;

    while(n) {
        print_node(n->data);
        n = n->next;
    }
}

Queue* new_queue() {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    q->rear = NULL;
    q->front = NULL;
    return q;
}

void free_queue(Queue *q, void (*free_node)(void *t)) {
    void *t;
    t = dequeue(q);
    while(t) {
        free_node(t);
        t = dequeue(q);
    }
    free(q);
}
