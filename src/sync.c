#include "../include/my_blockchain.h"

node_t * write_blocks(node_t *head, char *bids){

    if(bids[0] == '\0')
        return head;

    int index = 0,
        i = 0,
        current = 0;

    char *buffer = malloc(sizeof(char*)*MAX_BID_SIZE);

    while(bids[current]){
        if(bids[current] == ' ') continue;

        if(bids[current] == ','){
            buffer[index] = '\0';
            head->blocks = add_bid(head->blocks, buffer);
            i++;
            index = -1;
        }

        buffer[index] = bids[current];
        current++;
        index++;
    }

    return head;
}

node_t *get_synced_nodes(node_t *head){
    
    int file = open("./bin/saved_nodes.txt", O_RDWR),
        skip = 0;

    if(file < 0){
        file = open("./bin/saved_nodes.txt", O_CREAT | O_RDWR);
        if(file < 0)
            return NULL;
    }

    char    *current = malloc(sizeof(char)),
            *nid = malloc(sizeof(char)*BUFSIZ),
            *bids = malloc(sizeof(char)*BUFSIZ);
    
    if(file < 0)
        return NULL;
    
    while(read(file, current, 1) > 0){

        if(current[0] == ' ')
            continue;

        if(current[0] != ':' && skip == 0)
            strcat(nid, current);
        else if(current[0] == ':'){
            skip++;
            continue;
        }

        if(skip == 1)
            strcat(bids, current);

        if(current[0] == '\n'){
            head = add_node(head, atoi(nid));
            strcat(bids, "\0");
            head = write_blocks(head, bids);
            skip = 0;
            nid[0] = '\0';
            bids[0] = '\0';
        }

    }
    free(current);
    free(nid);
    free(bids);
    return head;
}

void write_nodes(node_t *head){

    int file = open("./bin/saved_nodes.txt", O_RDWR);

    if(file < 0){
        file = open("./bin/saved_nodes.txt", O_CREAT | O_RDWR);
        if(file < 0)
            return;
    }

    char *nid_str = malloc(sizeof(char)*BUFSIZ);

    while(head){
        sprintf(nid_str, "%d", head->nid);
        write(file, nid_str, strlen(nid_str));
        write(file, ": ", strlen(": "));
        for(int i = 0; head->blocks->bids[i][0]; i++){
            write(file, head->blocks->bids[i], strlen(head->blocks->bids[i]));
            write(file, ", ", strlen(", "));
        }
        write(file, "\n", strlen("\n"));

        head = head->next;
    }

    free(nid_str);
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
