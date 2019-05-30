#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include "Node.hpp"

typedef struct Queue{
    Node *rear;
    Node *front;
}Queue;

Queue* new_queue();
void* dequeue(Queue *q);
void enqueue(Queue *q, void* node);
void free_queue(Queue *q, void (*free_node)(void *t));
void print_queue(Queue *q, void (*print_node)(void *t));

#endif //__QUEUE_HPP__
