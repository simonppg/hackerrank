#include "Node.hpp"

#include <stdlib.h>

Node* new_node(void *data) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

void print_node(Node *n) {
    n->print(n->data);
}

void free_node(Node *n) {
    n->free(n->data);
}
