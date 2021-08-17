#ifndef LIST_H
#define LIST_H

#define SELLECT_ALL "*"
#define BLOCKS_INIT_MAX_LEN 5
#include "my_blockchain.h"

typedef struct node_s {
    int nid;
    struct block_s *blocks;
    struct node_s *next; 
}node_t;

void make_bid_buffer(char *bid, node_t *node);

node_t *copy_list(node_t *src, node_t *dest);
node_t *init_list(char *bid, int nid);
node_t *add_node(node_t *head, int nid);
node_t *add_block(node_t *head, char *bid, int nid);
void add_block_all(node_t *head, char *bid);

node_t *remove_block(node_t *head, char *bid, int nid);
node_t *remove_node(node_t *head, int nid);

int node_exists(node_t *head, int nid);

bool_t block_exists(node_t *head, char *bid, int nid);
node_t *find_node(node_t *head, int nid);

void print_list(node_t *head);
void print_block_list(node_t *head);

void free_list(node_t *head);

#endif

