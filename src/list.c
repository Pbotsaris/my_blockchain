#include "../include/list.h"


node_t *init_list(char *bid, int nid)
{
    node_t *head = (node_t*)malloc(sizeof(node_t));

    if(head == NULL)
        return NULL;

    head->bid = bid;
    head->nid = nid;
    head->next = NULL;

    return head;
}

node_t *add_to_head(node_t *head, char *bid, int nid)
{
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->nid = nid;
    node->bid = bid;
    node->next = head; 

    return node;
}


node_t *remove_node(node_t *head, int nid)
{
    node_t *current = head;
    node_t *node_to_remove = NULL;

    if(head->nid == nid)
    { 
        head = current->next;
        free(current);
        return head;
    }

    while(current->next)
    {
        if(current->next->nid == nid)
        {
            node_to_remove = current->next;
            current->next = current->next->next;
            free(node_to_remove);
            break;
        }

        current = current->next;
    }

    return head;
}

node_t *remove_block(node_t *head, char *bid)
{
    if(head == NULL)
        return NULL;

    node_t *current = head;
    node_t *prev = NULL;

    while(current)
    {
        node_t *node_to_remove = NULL;

        if(strcmp(current->bid, bid) == 0)
        {
            node_to_remove = current;

            if (current == head)
                current = head = current->next; 
            else 
            {
                current->next = current->next;
                current = prev->next;
            }
            free(node_to_remove);
            continue;
        }
        prev = current;
        current = current->next;
    }

    return head;
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
        printf("%s: %i\n", current->bid,current->nid);
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
        free(current);
        current = next;
    }
}





