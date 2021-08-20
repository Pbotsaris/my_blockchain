#include "../include/my_blockchain.h"

node_t * write_blocks(node_t *head, char *bids){

    if(bids[0] == '\0')
        return head;

    int buff_index = 0,
        bids_index = 0;

    char buffer[MAX_BID_SIZE];

    while(bids[bids_index])
    {
        if(bids[bids_index] == ' ')
            continue;

        if(bids[bids_index] == ',')
        {
            buffer[buff_index] = '\0';
            head->blocks = add_bid(head->blocks, buffer);
            buff_index = 0;
        } else {
            buffer[buff_index] = bids[bids_index];
            buff_index++;
        }

      bids_index++;
    }

    return head;
}

node_t *get_synced_nodes(node_t *head){

    bool_t     was_nid_read = FALSE;

    int        file,
               nid_index = 0, 
               bids_index = 0; 
    char       current,
               nid[BUFSIZ],
               bids[BUFSIZ];


    if((file = open("./bin/saved_nodes.txt", O_RDWR)) < 0)
        return NULL;

    while(read(file, &current, 1) > 0){

        if(current == ' ')
            continue;

        if(current == ':' && (!was_nid_read))
        {
            nid[nid_index] = '\0';
            was_nid_read = TRUE;
            continue;
        }

        if(!was_nid_read)
        {
            nid[nid_index] = current;
            nid_index++;
        }


        if(was_nid_read)
        {
            bids[bids_index] = current;
            bids_index++;
        }

        if(current == '\n'){
            bids[bids_index] = '\0';

            head = add_node(head, atoi(nid));
            head = write_blocks(head, bids);
            was_nid_read = FALSE;
            bids_index = nid_index = 0;
        }
    }

    return head;
}

void write_nodes(node_t *head){

    int file;
    char nid_str[BUFSIZ];

    if((file = open("./bin/saved_nodes.txt", O_CREAT | O_RDWR)) < 0)
        return;

//    char *nid_str = malloc(sizeof(char)*BUFSIZ);

    while(head)
    {
        sprintf(nid_str, "%d", head->nid);
        write(file, nid_str, strlen(nid_str));
        write(file, ": ", strlen(": "));

        for(int i = 0; i < head->blocks->index; i++){

            write(file, head->blocks->bids[i], strlen(head->blocks->bids[i]));
            write(file, ", ", strlen(", "));

        }
        write(file, "\n", strlen("\n"));

        head = head->next;
    }
}

node_t* impact_all_nodes(node_t *head){

    node_t *current = head->next;

    while(current){
        for(int i = 0; head->blocks->bids[i][0]; i++)
            if(!(bid_exists(current->blocks, head->blocks->bids[i])))
                current->blocks = add_bid(current->blocks, head->blocks->bids[i]); 

        current = current->next;
    }

    return head;
}

node_t* sync_nodes(node_t *head){

    node_t *current = head->next;

    while(current){
        for(int i = 0; current->blocks->bids[i][0] != '\0'; i++){
            if(!(bid_exists(head->blocks, current->blocks->bids[i]))){
                head->blocks = add_bid(head->blocks, current->blocks->bids[i]); 
            }
        }
        current = current->next;
    }

    head = impact_all_nodes(head);

    return head;
}
