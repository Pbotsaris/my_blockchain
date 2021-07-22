#include "../include/list.h"

/*
 *
   PRIVATE
                                             */

static char *make_bid_buffer(char *bid)
{

    char *buffer =(char*)malloc((strlen(bid) + 1) * sizeof(char));
    strcpy(buffer, bid);

    return buffer;
}

/*
 *
   PUBLIC 
                                             */


node_t *init_list(char *bid, int nid)
{
    node_t *head = (node_t*)malloc(sizeof(node_t));

    char *buffer = make_bid_buffer(bid);
    if(head == NULL)
        return NULL;

    head->bid = buffer;
    head->nid = nid;
    head->next = NULL;

    return head;
}

node_t *add_node(node_t *head, char *bid, int nid)
{
    char *buffer = make_bid_buffer(bid);

    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->nid = nid;
    node->bid = buffer;
    node->next = head; 

    return node;
}

node_t *remove_node(node_t *head, int nid)
{
    node_t *current = head;
    node_t *prev = NULL;

    if(head->nid == nid)
    { 
        head = current->next;
        free(current->bid);
        free(current);
        return head;
    }

    while(current)
    {
        if(current->nid == nid)
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
    node_t *current = head;

    char *buffer = make_bid_buffer(bid);

    while(current)
    {
        if(nid == current->nid)
            current->bid = buffer;
        current = current->next;
    }

    return head;
}

node_t *remove_block(node_t *head, char *bid)
{
    if(head == NULL)
        return NULL;

    node_t *current = head;

    while(current)
    {
        if(strcmp(current->bid, bid) == 0)
            current->bid[0] = '\0';
            current = current->next;
    }

    return head;
}

int node_exists(node_t *head, int nid)
{
    int count = 0;
    node_t *current = head;
    while(current)
    {
        if(current->nid == nid)
            return count;

        current = current->next;
        count++;
    }
    return -1;
}

int block_exists(node_t *head, char *bid)
{
    int count = 0;
    node_t *current = head;
    while(current)
    {
        if(strcmp(current->bid, bid) == 0)
            return count;

        current = current->next;
        count++;
    }
    return -1;
}

void print_list(node_t *head)
{
    if(head == NULL)
    {
        printf("Empty List\n");
        return;
    }

    node_t *current = head;
    while(current)
    {
        printf("%i: %s, \n", current->nid, current->bid);
        current = current->next;
    }
}

void print_block_list(node_t *head, char *bid)
{
    if(head == NULL)
    {
        printf("Empty List\n");
        return;
    }

    node_t *current = head;
    while(current)
    {
        if(strcmp(current->bid, bid) == 0)
            printf("%i: %s, \n", current->nid, current->bid);

        current = current->next;
    }
}

void free_list(node_t *head)
{
    if(head == NULL)
        return;

    node_t *current = head;
    node_t *next = NULL;
    while(current->next)
    {
        next = current->next;
        free(current->bid);
        free(current);
        current = next;
    }
}

