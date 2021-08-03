#ifndef LIST_H
#define LIST_H

typedef struct node_s {
    int nid;
    char *bid;
    struct node_s *next; 
}node_t;

node_t *add_node(node_t *head, char *bid, int nid);
node_t *add_block(node_t *head, char *bid, int nid);
node_t *remove_node(node_t *head, int nid);
node_t *remove_node_block(node_t *head, char *bid, int nid);
node_t *remove_block(node_t *head, char *bid);

int node_exists(node_t *head, int nid);
int block_exists(node_t *head, char *bid);
node_t *find_node(node_t *head, int nid);

void print_list(node_t *head);
void print_block_list(node_t *head, char *bid);

void free_list(node_t *head);

#endif
