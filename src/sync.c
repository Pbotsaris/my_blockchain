#include "../include/my_blockchain.h"

void read_nodes(int nid, char* bid, node_t **head){
   
    node_t *node = malloc(sizeof(node_t));
    make_bid_buffer(bid, node);
    node->nid = nid;
    node->next = NULL;

    if(*head == NULL){
        *head = node;
    }
    else{
        node_t *last_node = *head;

        while(last_node->next != NULL)
            last_node = last_node->next;
        
        last_node->next = node;
    }
}

node_t *get_synced_nodes(node_t *head){
    
    int file = open("./bin/saved_nodes.txt", O_RDWR),
        skip = 0;

    char    *temp = malloc(sizeof(char)),
            *nid = malloc(sizeof(char)*100),
            *bid = malloc(sizeof(char)*100);
    
    if(file < 0)
        return NULL;
    
    while(read(file, temp, 1) > 0){

        if(temp[0] != ':' && skip == 0)
            strcat(nid, temp);
        else if(temp[0] == ':'){
            skip++;
            continue;
        }

        if(temp[0] != ',' && skip == 1){
            strcat(bid, temp);
        }else if(temp[0] == ','){
            skip = 0;
            read_nodes(atoi(nid), bid, &head);
            nid[0] = '\0';
            bid[0] = '\0';
        }
    }

    free(temp);
    free(nid);
    free(bid);
    return head;
}

void write_nodes(node_t *synced){

    int file = open("./bin/saved_nodes.txt", O_RDWR);
    
    char *nid_str = malloc(sizeof(char)*BUFSIZ);

    while(synced){
        sprintf(nid_str, "%d", synced->nid);
        write(file, nid_str, strlen(nid_str));
        write(file, ": ", strlen(": "));
        write(file, synced->bid, strlen(synced->bid));
        write(file, ",\n", strlen(",\n"));

        synced = synced->next;
    }

    write(file, "\0", sizeof("\0"));

    free(nid_str);
}
