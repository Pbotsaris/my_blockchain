#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdio.h>

typedef struct node_s {
    int value;
    struct node_s *next; 
    }node_t;

node_t *init_list(int value);
node_t *add_to_head(node_t *head, int value);
void print_list(node_t *head);
void free_list(node_t *head);

#endif
