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
//    char    *current = malloc(sizeof(char)),
//            *nid = malloc(sizeof(char)*BUFSIZ),
//            *bid = malloc(sizeof(char)*BUFSIZ);
//    
//    if(file < 0)
//        return NULL;
//    
//    while(read(file, current, 1) > 0){
//
//        if(current[0] == ' ')
//            continue;
//
//        if(current[0] != ':' && skip == 0)
//            strcat(nid, current);
//        else if(current[0] == ':'){
//            skip++;
//            continue;
//        }
//
//        if(current[0] != ',' && skip == 1){
//            strcat(bid, current);
//        }else if(current[0] == ','){
//            skip = 0;
//            head = add_node(head, bid, atoi(nid));
//            nid[0] = '\0';
//            bid[0] = '\0';
//        }
//    }
//
//    free(current);
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

    head =impact_all_nodes(head);

    return head;
}
