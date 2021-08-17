#ifndef BLOCK_H
#define BLOCK_H

#include "my_blockchain.h"

#define MAX_BID_SIZE 100

typedef struct block_s {
    char **bids;
    int index; 
    int maxlen;
}block_t;


block_t *create_blocks(int maxlen);
void free_blocks(block_t *blocks);
block_t *grow_blocks(block_t *blocks);
bool_t bid_exists(block_t *blocks, char *bid);
block_t *add_bid(block_t *blocks, char *bid);
block_t *remove_bid(block_t *blocks, char *bid);

char *concat_blocks(block_t *blocks);


#endif
