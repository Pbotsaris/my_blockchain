#include "../include/blocks.h"

block_t *create_blocks(int maxlen)
{
    block_t *blocks = (block_t *)malloc(sizeof(block_t));
    blocks->maxlen = maxlen;
    blocks->index = 0;
    blocks->bids = (char**)malloc(maxlen * sizeof(char*)); 

    for(int i = 0; i < maxlen; i++)
    {
        blocks->bids[i] = (char*)malloc(MAX_BID_SIZE * sizeof(char));
        strcpy(blocks->bids[i], "\0");
    }


    return blocks;
}


void free_blocks(block_t *blocks)
{
    for(int i = 0; i < blocks->maxlen; i++)
        free(blocks->bids[i]);

    free(blocks->bids);
    free(blocks);
}

// grow blocks array by twice size
block_t *grow_blocks(block_t *blocks)
{
    block_t *new_blocks = create_blocks(blocks->maxlen * 2);

    for(int i = 0; i <= blocks->index; i++)
        strcpy(new_blocks->bids[i], blocks->bids[i]);

    new_blocks->maxlen = blocks->maxlen * 2;
    new_blocks->index = blocks->index;

    free_blocks(blocks);

    return new_blocks;
}


 bool_t bid_exists(block_t *blocks, char *bid)
{
    for(int i = 0; i <= blocks->index; i++)
        if(strcmp(blocks->bids[i], bid) == 0)
            return TRUE;

    return FALSE;
}


block_t *add_bid(block_t *blocks, char *bid)
{

    if(blocks->index >= blocks->maxlen - 1)
      blocks = grow_blocks(blocks);
    
      strcpy(blocks->bids[blocks->index], bid);
      blocks->index++;

      return blocks;
}

block_t *remove_bid(block_t *blocks, char *bid)
{

    int index = 0;

    /* find bid pos to delete */
    for(int i = 0; i <= blocks->index; i++)
        if(strcmp(blocks->bids[i], bid) == 0)
            index = i;

    /* remove bid and shift subsequent bids backwards */
    for(int i = index + 1; i <= blocks->index; i++)
        strcpy(blocks->bids[i - 1], blocks->bids[i]);

    strcpy(blocks->bids[blocks->index], "\0");

    blocks->index--;

    return blocks;
}

bool_t compare_blocks(block_t *b1, block_t *b2)
{
    bool_t result = FALSE;
    if(b1->index != b2->index)
        return FALSE;

    for(int i = 0; i < b1->index; i++)
    {
        for(int j = 0; i < b2->index; i++)
        {
            if((strcmp(b1->bids[i], b2->bids[j])) == 0)
            {
                 result = TRUE;
            }
        }

        if(result == FALSE)
            return FALSE;

        result = FALSE;
    }

    return TRUE;
}


char *concat_blocks(block_t *blocks)
{
    char *buffer = (char*) malloc((blocks->maxlen*MAX_BID_SIZE) * sizeof(char));

    for(int i = 0; i < blocks->index; i++)
    {
        if(i < blocks->index - 1)
        {
            strcat(buffer, blocks->bids[i]);    
            strcat(buffer, ", ");    
        }
        else
            strcat(buffer, blocks->bids[i]);    
    }

    return buffer;
}

