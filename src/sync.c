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
