#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SELLECT_ALL "*"

typedef struct node_s {
    int nid;
    char *bid;
    struct node_s *next; 
}node_t;

node_t *init_list(char *bid, int nid);
node_t *add_node(node_t *head, char *bid, int nid);
node_t *add_block(node_t *head, char *bid, int nid);
node_t *remove_node(node_t *head, int nid);
node_t *remove_block(node_t *head, char *bid);

void print_list(node_t *head);
void free_list(node_t *head);

#endif
