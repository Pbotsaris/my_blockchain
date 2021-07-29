#include "../include/list.h"
#define SPACE ' '
#define NODE "node"
#define BLOCK "block"
#define BUFF_SIZE 100

/*
 *
 * PRIVATE FUNCTION
 *
 *                                              */

 char *get_input(char *input, int *input_index)
{
    char *ret_command = (char*)malloc(sizeof(char)*100);
    int index = 0;

    while(input[*input_index]){

        if(input[*input_index] == SPACE)
            break;

        ret_command[index] = input[*input_index];
        index++;
        (*input_index)++;
    }

    (*input_index)++;
    ret_command[index] = '\0';

    return ret_command;
}

static char *clean_std_in(char *std_in){
    
    int index = 0,
        flag_space = 2;
    
    char *ret_str = malloc(sizeof(char)*strlen(std_in));

    while(std_in[index] || std_in[index] != '\n'){
        if(std_in[index] == SPACE)
            flag_space--;

        if(flag_space == 0)
            break;


        index++;
    }

    int current = index+1;
    index = 0;

    while(std_in[current]){

        ret_str[index] = std_in[current];

        index++;
        current++;
    }

    ret_str[index] = '\0';

    return ret_str;
}

bool_t check_block_impact(char *std_in){
    if(std_in[strlen(std_in)-2] == '*')
        return TRUE;
    else return FALSE;
}

static bool_t check_number(char* input){

    int index = 0,
        flag = 0;

    while(input[index]){
        if(isdigit(input[index]))
            flag++;
        
        index++;
    }
    
    return flag == index-1;
}

/*
 *
 *
 *       ADD NODE
 *                                                      */

static status_t check_add_block(input_t *input, char* std_in, unsynced *data){

    int len_count = 0;

    input->impact_all= check_block_impact(std_in);

    if(input->impact_all == TRUE){
        // TODO function that changes the previous passed nodes
        input->bid = get_input(std_in, &len_count);
    }else{

        input->one_time_bid = get_input(std_in, &len_count);
        input->nid = get_input(std_in, &len_count);

        if(check_number(input->nid) == TRUE){

            data = add_block(data, input->one_time_bid, atoi(input->nid));
            free(input->one_time_bid);
            return SUCCESS;

        }else{

            printf("Error, trying to add non numerical node or a null\n");
            return FAIL;
        }
    }

    return SUCCESS;
}

static status_t check_add_node(input_t *input, char *std_in, unsynced *data){
    
    if(check_number(std_in) == FALSE)
        return FAIL;

    if(input->impact_all == TRUE){
        data = add_node(data, input->bid, atoi(std_in)); 
        return SUCCESS;
    }else{
        // TODO pass a null bid 
        data = add_node(data, " ", atoi(std_in));
        return SUCCESS;

    }

    return FAIL;
}

static status_t process_command_add(input_t *input, char* std_in, unsynced *data){
    
    char  *buffer = NULL;

    if((buffer = clean_std_in(std_in)) == NULL)
        return FAIL;
   
    if((strcmp(input->typ, BLOCK)) == 0){
        if((check_add_block(input, buffer, data)) == SUCCESS){
            return SUCCESS;
        }
        else return FAIL;

    }else if((strcmp(input->typ, NODE)) == 0){
        if((check_add_node(input, buffer, data)) == SUCCESS)
            return SUCCESS;
        else return FAIL;

    }else{
        return FAIL;
    }
}

/*
 *
 *        Remove NODE
 *                                                      */

static status_t check_rm_block(input_t *input, char* std_in, unsynced *data){
    
    int len_count = 0;

    input->impact_all= check_block_impact(std_in);

    if(input->impact_all == TRUE){
        // TODO function that changes the previous passed nodes
        input->bid = get_input(std_in, &len_count);
    }else{
        input->one_time_bid = get_input(std_in, &len_count);
        input->nid = get_input(std_in, &len_count);
        if(check_number(input->nid) == TRUE){
            data = remove_block(data, input->one_time_bid);
            free(input->one_time_bid);
            return SUCCESS;
        }else{
            printf("Error, trying to add non numerical node or a null\n");
            return FAIL;
        }
    }

    return SUCCESS;
}

static status_t check_rm_node(input_t *input, char *std_in, unsynced *data){
    
    if(check_number(std_in) == FALSE)
        return FAIL;

    if(input->impact_all == TRUE){
        // TODO to pass BLOCK in the function to remove node
        data = remove_node(data, atoi(input->nid));
        return SUCCESS;
    }else{
        data = remove_node(data, atoi(input->nid));
        return SUCCESS;
    }

    return FAIL;
}

static status_t process_command_rm(input_t *input, char* std_in, unsynced *data){

    char  *buffer = NULL;

    if((buffer = clean_std_in(std_in)) == NULL)
        return FAIL;


    if((strcmp(input->typ, BLOCK)) == 0){
        if((check_rm_block(input, buffer, data)) == SUCCESS)
            return SUCCESS;
        else return FAIL;

    }else if((strcmp(input->typ, NODE)) == 0){
        if((check_rm_node(input, buffer, data)) == SUCCESS)
            return SUCCESS;
        else return FAIL;

    }else{
        return FAIL;
    }
}

/*
 *
                        PUBLIC 

                                                            */

// TODO add functions under each case unless quit

option_t get_option(input_t *input)
{

    option_t option = NONE;

    if(input->typ == NULL){
        if((strcmp(input->cmd, "sync"))==0){
            option = SYNC;
        }else if((strcmp(input->cmd, "quit")) == 0){
            option = QUIT;
        }else option = ERROR_OPTION;
    }
    
    if((strcmp(input->cmd, "ls")) == 0){
        if(input->typ == NULL)
            option = LS_NID;
        else if((strcmp(input->typ, "-l")) == 0)
            option = LS_NID_BID;
        else option = ERROR_OPTION;
    }

    return option;
}

option_t process_input(int std_in, unsynced *data){

    input_t *input = malloc(sizeof(input_t));
    int len_count = 0;
    char *buffer = malloc(sizeof(char)*BUFF_SIZE);

    int read_ret = read(std_in, buffer, BUFF_SIZE);
    buffer[read_ret] = '\0';

    input->cmd = get_input(buffer, &len_count);
    input->typ = get_input(buffer, &len_count);
    
    if(get_option(input) == QUIT)
        return QUIT;

    if((strcmp(input->cmd, "add")) == 0){
        if(process_command_add(input, buffer, data) == SUCCESS)
            printf("Successful\n");
        else printf("Failed\n");
    }

    if((strcmp(input->cmd, "rm")) == 0){
        if(process_command_rm(input, buffer, data) == SUCCESS)
            printf("Successful\n");
        else printf("Failed\n");
    }

    // TODO Free input_t
    /* free_input(input); */
    free(buffer);
    return NONE;
}
