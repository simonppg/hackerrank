#include "Queue.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

enum tokens {
    LESS_THAN, GREATER_THAN, EQUAL, SLASH,
    STRING, DOT, TILDE, ENTER,
};

enum Tag_types{
    ROOT, TAG
};

typedef struct Attr {
    char *name;
    char *value;
    Attr *next;
}Attr;

typedef struct Tag {
    char *name;
    Tag *child;
    Tag *next;
    Tag *parent;
    int type;
    bool is_close;
    Queue *attr_queue;
}Tag;

typedef struct Token{
    int type;
    char *str;
    const char *lexem;
    Token *next;
}Token;

bool is_digit(char *c) {
    return (*c >= '0' && *c <= '9');
}

bool is_alpha(char *c) {
    return (*c >= 'a' && *c <= 'z') ||
        (*c >= 'A' && *c <= 'Z') ||
        *c == '_';
}

bool is_alpha_numeric(char *c) {
    return is_digit(c) || is_alpha(c);
}

Tag* new_tag(int type, char *name) {
    Tag *t = (Tag *) malloc(sizeof(Tag));
    t->child = t->next = t->parent = NULL;
    t->type = type;
    t->name = name;
    t->attr_queue = NULL;
    t->is_close = false;
    return t;
}

Attr* new_attr(char *name, char *value) {
    Attr *attr = (Attr *) malloc(sizeof(Attr));
    attr->name = name;
    attr->value = value;
    attr->next = NULL;
    return attr;
}

void free_attr(void *n) {
    Attr *attr = (Attr *)n;
    free(attr->name);
    free(attr->value);
    free(attr);
}

void print_attr(void *n) {
    Attr *attr = (Attr *)n;
    printf("[%s=%s]", attr->name, attr->value);
}

void free_tag(Tag *t) {
    free_queue(t->attr_queue, free_attr);
    free(t->name);
    free(t);
}

void free_tree(Tag *tree) {
    Tag* current = tree;
    Tag *freeme = current;
    while (current)
    {
        if(current != NULL && current->child) {
            current = current->child;
        } else {
            freeme = current;

            if(current->parent != NULL) {
                if(current->next) {
                    current->parent->child = current->next;
                } else {
                    current->parent->child = NULL;
                }
            }
            current = current->parent;
            //printf("free %s", freeme->name);
            free_tag(freeme);
        }
    }
}

Token* new_token(int type, char const *lexem, char *str) {
    Token *t = (Token *) malloc(sizeof(Token));
    t->type = type;
    t->str = str;
    t->lexem = lexem;
    t->next = NULL;
    return t;
}

void print_token(void *n) {
    Token *t = (Token *)n;
    printf("[%s]", t->lexem);
}

void print_token_debug(void *n) {
    Token *t = (Token *)n;
    printf("[%s]", t->str ? t->str : t->lexem);
}

void free_token(void *data) {
    Token *t = (Token *)data;
    if(t->type == STRING) {
        free(t->str);
    }
    free(t);
}

bool is_a_tag(Queue *q) {
    return ((Token*)q->front->data)->type == LESS_THAN &&
        ((Token*)q->front->next->data)->type == STRING &&
        ((Token*)q->rear->data)->type == GREATER_THAN;
}

bool is_a_closing_tag(Queue *q) {
    return ((Token*)q->front->data)->type == LESS_THAN &&
        ((Token*)q->front->next->data)->type == SLASH;
}

void insert_tag(Tag *tree, Tag *t) {
    Tag *current = tree;

    while(current->child) {
        if(current->is_close)
            break;
        current = current->child;
        while(current->next) {
            current = current->next; 
        }
    }

    //printf("current is: %s ", current->is_close ? "close" : "open");
    //printf("%s adopted %s", current->name, t->name);
    if(current->is_close) {
        while(current->next) {
            current = current->next; 
        }
        current->next = t;
        t->parent = current->parent;
    } else {
        current->child = t;
        t->parent = current;
    }
}

void close_tag(Tag *tree, char *name) {
    Tag *current = tree;
    while (current)
    {
        if(strcmp(current->name, name) == 0) {
            current->is_close = true;
            break;
        }
        if(current->child) {
            current = current->child;
        } else {
            if(current->next) {
                current = current->next;
            } else {
                current = current->parent->next;
            }
        }
    }
}

void print_tree(Tag *tree) {
    Tag* current = tree;
    printf("_\n");
    while (current)
    {
        if(current->name) {
            printf("%s, ", current->name);
            printf(current->is_close ? "true " : "false ");
            printf("parent: %s ", current->parent ? current->parent->name : NULL);
            printf("next: %s ", current->next? current->next->name : NULL);
            print_queue(current->attr_queue, print_attr);
            printf("\n");
        }
        else
            printf("name null");

        if(current != NULL && current->child) {
            current = current->child;
        } else {
            if(current->next) {
                current = current->next;
            } else {
                current = current->parent->next;
            }
        }
    }
    printf("_\n");
}

void scan(Queue *pQueue, char *line) {
    char *c = line;
    char *str = NULL;
    int count = 0;

    while(*c != '\0') {

        switch(*c) {
            case '<':
                enqueue(pQueue, new_token(LESS_THAN, "<", NULL));
                break;
            case '>':
                enqueue(pQueue, new_token(GREATER_THAN, ">", NULL));
                break;
            case '/':
                enqueue(pQueue, new_token(SLASH, "/", NULL));
                break;
            case '=':
                enqueue(pQueue, new_token(EQUAL, "=", NULL));
                break;
            case '.':
                enqueue(pQueue, new_token(DOT, ".", NULL));
                break;
            case '~':
                enqueue(pQueue, new_token(TILDE, "~", NULL));
                break;
            case ' ':
            case '\t':
                //Ignore space, tabs
                break;
            case '"':
                count = 0;
                c++;
                while(*c != '"' && *c != '\0') {
                    count++;
                    c++;
                }

                str = (char *) malloc(sizeof(char) * count + 1);
                memcpy(str, (c - count), count);
                str[count] = '\0';
                enqueue(pQueue, new_token(STRING, "str", str));
                break;
            default:
                if(is_alpha_numeric(c)) {
                    count = 0;
                    while(is_alpha_numeric(c) && *c != ' ' && *c != '\0') {
                        count++;
                        c++;
                    }

                    str = (char *) malloc(sizeof(char) * count + 1);
                    memcpy(str, (c - count), count);
                    str[count] = '\0';
                    enqueue(pQueue, new_token(STRING, "str",  str));
                    // We are ahead, we need to take a step back
                    c--;
                } else {
                    printf("Unknow character: %c", *c);
                }
        }
        c++;
        //printf("%c", *c);
    }
    //enqueue(pQueue, new_token(ENTER, "\n", NULL));
}
void parse(Tag *tree, Queue *q) {
    Tag *tag;
    if(is_a_tag(q)) {
        Token *t = (Token *)q->front->next->data;
        char *name;
        int size = strlen(t->str) + 1;
        name = (char *) malloc(sizeof(char) * size);
        strcpy(name, t->str);
        tag = new_tag(TAG, name);
        insert_tag(tree, tag);
        Node *attr = q->front->next->next;
        if(((Token *)q->front->next->next->data)->type == STRING) {
            tag->attr_queue = new_queue();
        }

        while(((Token*)attr->data)->type == STRING &&
                ((Token*)attr->next->data)->type == EQUAL &&
                ((Token*)attr->next->next->data)->type == STRING) {
            char *name, *value, *tmp;

            tmp = ((Token*)attr->data)->str;
            int size = strlen(tmp) + 1;
            name = (char *) malloc(sizeof(char) * size);
            strcpy(name, tmp);

            tmp = ((Token*)attr->next->next->data)->str;
            size = strlen(tmp) + 1;
            value = (char *) malloc(sizeof(char) * size);
            strcpy(value, tmp);

            enqueue(tag->attr_queue, new_attr(name, value));

            attr = attr->next->next->next;
        }
    } else if(is_a_closing_tag(q)) {
        //printf("closing tag %s\n", ((Token *)q->front->next->next->data)->str);
        close_tag(tree, ((Token *)q->front->next->next->data)->str);
    }
    //print_tree(tree);
}

Tag* find_tag2(Tag *tree, char *tag) {
    Tag *t = NULL;
    Tag* current = tree;
    while (current)
    {
        if(strcmp(current->name, tag) == 0) {
            t = current;
            break;
        }

        if(current != NULL && current->child) {
            current = current->child;
        } else {
            if(current->next) {
                current = current->next;
            } else {
                current = current->parent->next;
            }
        }
    }
    return t;
}

Tag* find_tag(Tag *tree, char *tag) {
    Tag *current = tree;
    Tag *t = NULL;
    while(current->child) {
        if(strcmp(current->name, tag) == 0) {
            t = current;
            break;
        }
        current = current->child;
        if(strcmp(current->name, tag) == 0) {
            t = current;
            break;
        }
        while(current->next) {
            if(strcmp(current->name, tag) == 0) {
                t = current;
                break;
            }
            current = current->next; 
        }
    }
    return t;
}

bool has_child(Tag *tree, char *parent, char *child) {
    Tag *parent_tag = find_tag(tree, parent);
    Tag *child_tag = NULL;
    if(!parent_tag)
        return false;

    child_tag = parent_tag->child;
    while(child_tag) {
        if(strcmp(child_tag->name, child) == 0)
            return true;
        child_tag = child_tag->next;
    }

    return false;
}

Attr* get_attr(Tag *tree, char *name, char *key) {
    Tag *tag = find_tag2(tree, name);
    if(!tag)
        return NULL;
    if(!tag->attr_queue)
        return NULL;

    Node *current = tag->attr_queue->front;

    do {
        if(strcmp(((Attr *)current->data)->name, key) == 0) {
            //printf("%s found!!! :-)", name);
            return (Attr *)current->data;
        }
        current = current->next;
    } while(current);

    return NULL;
}

void query(Tag *tree, Queue *q) {
    Node *current = (Node *) q->front;
    char *parent = ((Token *)q->front->data)->str;
            char *child = NULL;

    //print_queue(q, print_token_debug);
    //printf("\n");

    while(current) {
        if(((Token *)current->data)->type == STRING &&
                current->next &&
                ((Token *)current->next->data)->type == DOT) {
            parent = ((Token *)current->data)->str;
            child = ((Token *)current->next->next->data)->str;
            if(has_child(tree, parent, child)) {
                //printf("%s is parent of %s\n", parent, child);
                parent = child;
            } else {
                printf("Not Found!\n");
                break;
            }
            //printf("%s \n", parent);
        }
        if(((Token *)current->data)->type == STRING &&
                current->next &&
                ((Token *)current->next->data)->type == TILDE) {
            Attr* attr;
            char *key = ((Token *)current->next->next->data)->str;
            if(child)
                attr = get_attr(tree, child, key);
            else
            {
                child = ((Token* )current->data)->str;
                if(strcmp(child, tree->child->name) == 0) {
                    attr = get_attr(tree, child, key);
                }else
                    attr = NULL;
            }
            if(attr)
                printf("%s\n", attr->value);
            else
                printf("Not Found!\n");
        }
        current = current->next;
    }
    //printf("\n");
}

int main() {
    int n, m;
    char *name = (char *) malloc(sizeof(char) * 10);
    strcpy(name, "Hello\0");
    Tag *tree = new_tag(ROOT, name);
    scanf("%d %d ", &n, &m);

    for(int i = 0; i < n; i++) {
        Queue *queue = new_queue();
        char *line = readline();
        //printf("%s\n", line);
        scan(queue, line);
        parse(tree, queue);
        //print_queue(queue, print_token);
        free_queue(queue, free_token);
        free(line);
    }
    //print_tree(tree);

    for(int i = 0; i < m; i++) {
        Queue *queue = new_queue();
        char *line = readline();
        //printf("%s\n", line);
        scan(queue, line);
        query(tree, queue);
        //print_queue(queue, print_token);
        free_queue(queue, free_token);
        free(line);
    }
    //printf("\n");

    free_tree(tree);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = (char *) malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = (char *) realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }   

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }   

    data = (char *) realloc(data, data_length);

    return data;
}

