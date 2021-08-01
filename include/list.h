#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include "option.h"

#endif


#ifndef LIST_H
#define LIST_H

#define SELLECT_ALL "*"

typedef struct node_s {
    int nid;
    char *bid;
    struct node_s *next; 
}unsynced;

unsynced *init_list(char *bid, int nid);
unsynced *add_node(unsynced *head, char *bid, int nid);
unsynced *add_block(unsynced *head, char *bid, int nid);
unsynced *remove_node(unsynced *head, int nid);
unsynced *remove_block(unsynced *head, char *bid);

int node_exists(unsynced *head, int nid);
int block_exists(unsynced *head, char *bid);
unsynced *find_node(unsynced *head, int nid);

void print_list(unsynced *head);
void print_block_list(unsynced *head, char *bid);

void free_list(unsynced *head);

#endif
