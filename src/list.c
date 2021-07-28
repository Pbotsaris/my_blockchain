#include "../include/list.h"
#include <string.h>

/*
 *
                   PRIVATE
                                             */

static void make_bid_buffer(char *bid, unsynced *node)
{
    size_t len = strlen(bid);

    node->bid = (char *)malloc((len + 2) * sizeof(char));
    strcpy(node->bid, bid);
}

/*
 *
 *
                    PUBLIC
                                             */

unsynced *init_list(char *bid, int nid)
{
    unsynced *head = (unsynced *)malloc(sizeof(unsynced));

    if (head == NULL) return NULL;

    make_bid_buffer(bid, head);
    head->nid = nid;
    head->next = NULL;

    return head;
}

unsynced *add_node(unsynced *head, char *bid, int nid)
{
    unsynced *node = (unsynced *)malloc(sizeof(unsynced));

    make_bid_buffer(bid, node);
    node->nid = nid;
    node->next = head;

    return node;
}

unsynced *remove_node(unsynced *head, int nid)
{

    if (head == NULL) return NULL;
    
    unsynced *current = head;
    unsynced *prev = NULL;

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

unsynced *add_block(unsynced *head, char *bid, int nid)
{

    if (head == NULL) return NULL;

    unsynced *current = head;

    while (current)
    {
        if (nid == current->nid) make_bid_buffer(bid, current);

        current = current->next;
    }

    return head;
}

unsynced *remove_block(unsynced *head, char *bid)
{
    if (head == NULL) return NULL;

    unsynced *current = head;
    while (current)
    {
        if((strcmp(current->bid, bid)) == 0)
            current->bid[0] = '\0';

        current = current->next;
    }

    return head;
}

int node_exists(unsynced *head, int nid)
{
    int count = 0;
    unsynced *current = head;
    while (current)
    {
        if (current->nid == nid) return count;

        current = current->next;
        count++;
    }
    return -1;
}

int block_exists(unsynced *head, char *bid)
{
    int count = 0;
    unsynced *current = head;
    while (current)
    {
        if (strcmp(current->bid, bid) == 0) return count;

        current = current->next;
        count++;
    }
    return -1;
}

void print_list(unsynced *head)
{
    if (head == NULL)
    {
        printf("Empty List\n");
        return;
    }

    unsynced *current = head;
    while (current)
    {
        printf("%i: %s, \n", current->nid, current->bid);
        current = current->next;
    }
}

void print_block_list(unsynced *head, char *bid)
{
    if (head == NULL) return;

    unsynced *current = head;
    while (current)
    {
        if (strcmp(current->bid, bid) == 0)
            printf("%i: %s, \n", current->nid, current->bid);

        current = current->next;
    }
}

void free_list(unsynced *head)
{
    if (head == NULL)
        return;

    unsynced *current = head;
    unsynced *next = NULL;

    while (current)
    {
        next = current->next;
        free(current->bid);
        free(current);
        current = next;
    }
}
