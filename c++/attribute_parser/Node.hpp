#ifndef __NODE_HPP__
#define __NODE_HPP__

typedef struct Node{
    Node *next;
    void *data;
    void (*print)(void *data);
    void (*free)(void *data);
}Node;

Node* new_node(void *data);
void print_node(Node *n);
void free_node(Node *n);

#endif // __NODE_HPP__
