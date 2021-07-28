#include "../include/list.h"
#define SPACE ' '
#define NODE "node"
#define BLOCK "block"

static char *get_input(char *input, int *input_index)
{
    char *ret_command = (char*)malloc(sizeof(char)*100);
    static int enteries = 0;
    enteries++;
    int index = 0;

    while(input[*input_index] != '\n'){

        if(input[*input_index] == SPACE && enteries <= 2)
            break;

        ret_command[index] = input[*input_index];
        index++;
        (*input_index)++;
    }

    (*input_index)++;
    ret_command[index] = '\0';

    return ret_command;
}

static bool_t check_number(char* input){
    int index = 0,
        flag = 0;

    while(input[index]){
        if(isdigit(input[index]))
            flag++;
        
        index++;
    }

    return flag == index;
}

int get_nid(char* nid_bid){
    
    char *nid_char = malloc(sizeof(char)*100);
    int index = 0,
        current = 0,
        nid = 0;

    while(nid_bid[current]){
        if(nid_bid[current] == SPACE){
            current++;;
            break;
        }

        current++;
    }

    while(nid_bid[current] || nid_bid[current] == '\n'){
        nid_char[index] = nid_bid[current];     
        index++;
        current++;
    }
    
    nid_char[index] = '\0';
    if((check_number(nid_char)) == TRUE){
        nid = atoi(nid_char);
    }else{
        printf("Error, trying to add non numerical node\n");
        return -1;
    }

    return nid;

}

char *get_bid(char* nid_bid){
    
    int index = 0;
    char *bid = malloc(sizeof(char)*100);

    while(nid_bid[index]){
        if(nid_bid[index] == SPACE){
            bid[index] = nid_bid[index];
            index++;
            if(nid_bid[index] == '*'){
                if(nid_bid[index+1] == '\0'){
                    bid[index] = nid_bid[index];
                    bid[index+1] = '\0';
                    return bid;
                }else{ 
                    printf("Error, provided nid isn't valid\n");
                    return NULL;
                }
            } 
            break;
        }

        
        bid[index] = nid_bid[index];
        index++;
    }

    return bid;
} 

option_t check_add_node(char *nid, char *bid, unsynced *data){

    option_t option = NONE;

    if((check_number(nid)) == TRUE){
            data = add_node(data, bid, atoi(nid));
            option = ADD_NID;
    }else{
        printf("Error, trying to add a non numerical node\n");
        return ERROROPT;
    } 

    return option;
}



option_t check_add_block(int nid, char* bid, unsynced *data){
   
    add_block(data, bid, nid);

    return ADD_BID;
}


static bool_t impact_all(char *bid){

    if((bid[strlen(bid)-1 ]) == '*')
        return TRUE;
    else
        return FALSE;
}

char* bid_clean(char *bid){

    char *ret = malloc(sizeof(char)*strlen(bid)-2);

    int index = 0;

    while(bid[index]){
        if(bid[index] == SPACE){
            index++;
            break;
        }

        ret[index] = bid[index];
        index++;
    } 

    ret[index] = '\0';
    return ret;
}

option_t check_add(char* type, unsynced *data, char *nid_bid, char *bid){
        
    option_t option = NONE;
    
    if ((strcmp(type, NODE)) == 0){ 
        option = check_add_node(nid_bid, bid, data); 
    }else if((strcmp(type, BLOCK)) == 0){
        if((bid = get_bid(nid_bid)) != NULL){
                if(impact_all(bid) == FALSE){
                    int nid = get_nid(nid_bid);
                    option = check_add_block(nid, bid, data);
                    bid = NULL;
                }else{
                    bid = bid_clean(bid);
                    printf("%s\n", bid);
                    }
        } else{
            return ERROROPT;
        }
    }

    return option;
}
/*
 *
                        PUBLIC 

                                                            */


option_t get_option(char* cmd, char* type){

    option_t option = NONE;

    if(type == NULL){
        if((strcmp(cmd, "sync"))==0){
            option = SYNC;
        }else if((strcmp(cmd, "quit")) == 0){
            option = QUIT;
        }else option = ERROROPT;
    }
    
    if((strcmp(cmd, "ls")) == 0){
        if(type == NULL)
            option = LS_NID;
        else if((strcmp(type, "-l")) == 0)
            option = LS_NID_BID;
        else option = ERROROPT;
    }

    return option;
}

option_t process_input(int std_in, unsynced* data){
 
    int len_count = 0;
    option_t option = NONE;

    char *cmd = NULL,
         *type = NULL,
         *nid_bid = NULL,
         *bid = NULL,
         *input = malloc(sizeof(char)*100);

    int nbr = read(std_in, input, 100);
    input[nbr] = '\0';

    cmd = get_input(input, &len_count);  
    type = get_input(input, &len_count);  
    nid_bid = get_input(input, &len_count);
     
    if(nid_bid == NULL)
        return get_option(cmd, type);
    else if((strcmp(cmd, "add")) == 0){
        option = check_add(type, data, nid_bid, bid);
    }
    printf("%s\n", bid);
    return option;
}
