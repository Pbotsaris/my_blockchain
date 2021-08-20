#include "../include/my_blockchain.h"
#include "../include/messages.h"
#include <string.h>



node_t *add_node(node_t *head, int nid)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->blocks = create_blocks(BLOCKS_INIT_MAX_LEN);
    node->nid = nid;
    node->next = head;

    return node;
}

node_t *remove_node(node_t *head, int nid)
{

    if (head == NULL) return NULL;

    node_t *current = head;
    node_t *prev = NULL;

    if (head->nid == nid)
    {
        head = current->next;
        free_blocks(current->blocks);
        free(current);
        return head;
    }

    while (current)
    {
        if (current->nid == nid)
        {
            prev->next = current->next;
            free_blocks(current->blocks);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    return head;
}

node_t *add_block(node_t *head, char *bid, int nid)
{
    bool_t node_not_found = TRUE;
    if (head == NULL) return NULL;

    node_t *current = head;

    while (current)
    {
        if (nid == current->nid)
        {
            if(!bid_exists(current->blocks, bid))
                current->blocks = add_bid(current->blocks, bid); 
            else
                print_error(BLOCK_EXISTS);

            node_not_found = FALSE;
        }

        current = current->next;
    }

    if(node_not_found)
        print_error(NODE_NOT_EXISTS);

    return head;
}


node_t *remove_block(node_t *head, char *bid, int nid)
{
    if (head == NULL) return NULL;

    node_t *current = head;
    while (current)
    {
        if(current->nid == nid)
            current->blocks = remove_bid(current->blocks, bid);

        current = current->next;
    }

    return head;
}

node_t *remove_every_block(node_t *head, char *bid)
{
    if (head == NULL) return NULL;

    bool_t found_block = FALSE;

    node_t *current = head;
    while (current)
    { 
        if(found_block == FALSE)
           found_block = block_exists(current, bid, current->nid);

            current->blocks = remove_bid(current->blocks, bid);

        current = current->next;
    }

    if(found_block)
        print_message(OK_MSG);
    else
        print_error(BLOCK_NOT_EXISTS);


    return head;
}


bool_t is_list_synced(node_t *head)
{

    node_t *current = head;

    while (current)
    {
        if(current->next != NULL && !(compare_blocks(current->blocks, current->next->blocks)))
        {
            return FALSE;
        }
        /* last node compare with head */
        else if(!(compare_blocks(current->blocks, head->blocks)))
            return FALSE;

        current = current->next;
    }

    return TRUE;

}


node_t *find_node(node_t *head, int nid)
{
    node_t *current = head;
    while (current)
    {
        if (current->nid == nid) return current;

        current = current->next;
    }
    return NULL;

}


int count_nodes(node_t *head)
{
    node_t *current = head;
    int count = 0;
    while (current)
    {
        count++;
        current = current->next;
    }
    return count;
}



int node_exists(node_t *head, int nid)
{
    if(head == NULL)
        return -2;

    int count = 0;
    node_t *current = head;
    while (current)
    {
        if (current->nid == nid) return count;

        current = current->next;
        count++;
    }
    return -1;
}

bool_t block_exists(node_t *head, char *bid, int nid)
{

    if(head == NULL)
        return -1;

    int count = 0;
    node_t *current = head;
    while (current)
    {
        if(current->nid == nid)
            return bid_exists(current->blocks, bid);

        current = current->next;
        count++;
    }

    print_error(NODE_NOT_EXISTS);
    return FALSE;
}


void print_list(node_t *head)
{
    if (head == NULL)
    {
        printf("Empty List\n");
        return;
    }

    node_t *current = head;
    while (current)
    {
        printf("%i:\n", current->nid);
        current = current->next;
    }
}

void print_block_list(node_t *head)
{
    if (head == NULL)
    {
        printf("The blockchain is empty\n");
        return;
    }

    node_t *current = head;
    while (current)
    {
        char *blocks_buffer = concat_blocks(current->blocks);
        printf("%i: %s \n", current->nid, blocks_buffer);
        free(blocks_buffer);

        current = current->next;
    }
}

void free_list(node_t *head)
{
    if (head == NULL)
        return;

    node_t *current = head;
    node_t *next = NULL;

    while (current)
    {
        next = current->next;
        free_blocks(current->blocks);
        free(current);
        current = next;
        
    }
}
