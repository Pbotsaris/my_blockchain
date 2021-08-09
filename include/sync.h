#ifndef MY_SYNC_H
#define MY_SYNC_H
#include "list.h"

node_t *get_synced_nodes(node_t *head);
node_t *sync_nodes(node_t *head);
void write_nodes(node_t *synced);

#endif
