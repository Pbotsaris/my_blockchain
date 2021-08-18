#include "../include/my_blockchain.h"

//node_t *get_synced_nodes(node_t *head){
//    
//    int file = open("./bin/saved_nodes.txt", O_RDWR),
//        skip = 0;
//
//    if(file < 0){
//        file = open("./bin/saved_nodes.txt", O_CREAT | O_RDWR);
//        if(file < 0)
//            return NULL;
//    }
//
//    char    *temp = malloc(sizeof(char)),
//            *nid = malloc(sizeof(char)*BUFSIZ),
//            *bid = malloc(sizeof(char)*BUFSIZ);
//    
//    if(file < 0)
//        return NULL;
//    
//    while(read(file, temp, 1) > 0){
//
//        if(temp[0] == ' ')
//            continue;
//
//        if(temp[0] != ':' && skip == 0)
//            strcat(nid, temp);
//        else if(temp[0] == ':'){
//            skip++;
//            continue;
//        }
//
//        if(temp[0] != ',' && skip == 1){
//            strcat(bid, temp);
//        }else if(temp[0] == ','){
//            skip = 0;
//            head = add_node(head, bid, atoi(nid));
//            nid[0] = '\0';
//            bid[0] = '\0';
//        }
//    }
//
//    free(temp);
//    free(nid);
//    free(bid);
//    return head;
//}
//
//void write_nodes(node_t *synced){
//
//    int file = open("./bin/saved_nodes.txt", O_RDWR);
//
//    if(file < 0){
//        file = open("./bin/saved_nodes.txt", O_CREAT | O_RDWR);
//        if(file < 0)
//            return;
//    }
//
//    
//    char *nid_str = malloc(sizeof(char)*BUFSIZ);
//
//    while(synced){
//        sprintf(nid_str, "%d", synced->nid);
//        write(file, nid_str, strlen(nid_str));
//        write(file, ": ", strlen(": "));
//        write(file, synced->bid, strlen(synced->bid));
//        write(file, ",\n", strlen(",\n"));
//
//        synced = synced->next;
//    }
//
//    free(nid_str);
//}
node_t* impact_prev_nodes(node_t *head){

    node_t *first_node = malloc(sizeof(node_t*));
    first_node = head;
 
    printf("first node %d\n", first_node->nid);

    node_t *current = malloc(sizeof(node_t*));
    current = head;

    while(current){
        for(int i = 0; first_node->blocks->bids[i][0] != '\0'; i++){
            if(!(bid_exists(current->blocks, first_node->blocks->bids[i]))){
                add_bid (current->blocks, first_node->blocks->bids[i]);
            }
        }
        current = current->next;
    }

    return head;
}

node_t* sync_nodes(node_t *head){

    node_t *temp = malloc(sizeof(node_t*));
    temp = head;

    while(temp){
        if(temp->next != NULL)
            for(int i = 0 ; temp->next->blocks->bids[i][0] != '\0'; i++)
                if(!(bid_exists(temp->blocks, temp->next->blocks->bids[i])))
                    add_bid(temp->blocks, temp->next->blocks->bids[i]);
                
        temp = temp->next;
    }

    head =impact_prev_nodes(head);

    return head;
}
