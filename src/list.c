#include "../include/my_blockchain.h"
#include <string.h>

/*
 *
 PRIVATE
 */

void make_bid_buffer(char *bid, node_t *node)
{
    int len = (int)strlen(bid);

    node->bid = (char *)malloc((len + 2) * sizeof(char));
    strcpy(node->bid, bid);
}

/*
 *
 *
 PUBLIC
 */

node_t *copy_list(node_t *src, node_t *dest){

    if(src == NULL)
        return NULL;
    else{
        node_t *temp_head = src;

        free_list(dest);
        dest = NULL;

        while(temp_head){
                dest = add_node(dest, temp_head->bid, temp_head->nid);
                temp_head = temp_head->next;
        }
    }
    return dest;

}

node_t *add_node(node_t *head, char *bid, int nid)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));

    make_bid_buffer(bid, node);
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
        free(current->bid);
        free(current);
        return head;
    }

    while (current)
    {
        if (current->nid == nid)
        {
            prev->next = current->next;
            free(current->bid);
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

    if (head == NULL) return NULL;

    node_t *current = head;

    while (current)
    {
        if (nid == current->nid) make_bid_buffer(bid, current);

        current = current->next;
    }

    return head;
}


void add_block_all(node_t *head, char *bid)
{
    node_t *current = head;
      while (current)
    {
        free(current->bid);
        make_bid_buffer(bid, current);

        current = current->next;
    }

}

node_t *remove_node_block(node_t *head, int nid)
{
    if (head == NULL) return NULL;

    node_t *current = head;
    while (current)
    {
        if(current->nid == nid)
            current->bid[0] = '\0';

        current = current->next;
    }

    return head;
}



node_t *remove_block(node_t *head, char *bid)
{
    if (head == NULL) return NULL;

    node_t *current = head;
    while (current)
    {
        if((strcmp(current->bid, bid)) == 0)
            current->bid[0] = '\0';

        current = current->next;
    }

    return head;
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

int block_exists(node_t *head, char *bid)
{

    if(head == NULL)
        return -1;

    int count = 0;
    node_t *current = head;
    while (current)
    {
        if (strcmp(current->bid, bid) == 0) return count;

        current = current->next;
        count++;
    }
    return -1;
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
        printf("Empty List\n");
        return;
    }

    node_t *current = head;
    while (current)
    {
        printf("%i: %s, \n", current->nid, current->bid);

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
        free(current->bid);
        free(current);
        current = next;
    }
}
