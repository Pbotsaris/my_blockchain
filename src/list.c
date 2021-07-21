#include "../include/list.h"


node_t *init_list(int value)
{
    node_t *head = (node_t*)malloc(sizeof(node_t));

    if(head == NULL)
        return NULL;
    
    head->value = value;
    head->next = NULL;

    return head;
}

node_t *add_to_head(node_t *head, int value)
{
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->value = value;
    node->next = head; 

    return node;
}

void print_list(node_t *head)
{
    node_t *temp = head;
    while(temp)
    {
        printf("%i\n", temp->value);
        temp = temp->next;
    }
}

void free_list(node_t *head)
{
    node_t *temp = head;
    node_t *next;

    while(temp->next)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }
}





