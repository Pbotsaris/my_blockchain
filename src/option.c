#include "../include/list.h"
#define SPACE ' '
#define NODE "node"
#define BLOCK "block"
#define ADD "add"
#define RM "rm"
#define BUFF_SIZE 100
#define NEW_LINE '\n'
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

        if(input[*input_index] == SPACE || input[*input_index] == NEW_LINE)
            break;

        ret_command[index] = input[*input_index];
        index++;
        (*input_index)++;
    }

    (*input_index)++;
    ret_command[index] = '\0';
    
    if(ret_command[0] == '\0')
        return NULL;

    return ret_command;
}

// TODO: CHECK FOR RANDOM INPUT: if doesn't start with add or rm -> error

char *clean_std_in(char *std_in)
{

    int index = 1,
        flag_space = 2;

    char *ret_str = malloc(sizeof(char)*strlen(std_in));

    while(std_in[index]){
        if(std_in[index] == SPACE)
            flag_space--;

        if(flag_space == 0)
            break;

        index++;
    }

    if(std_in[index] == '\0' || std_in[index] == '\n')
        return NULL;
    
    int current = index+1;
    index = 0;
    while(std_in[current]){

        ret_str[index] = std_in[current];

        index++;
        current++;
    }

    ret_str[index] = '\0';

    if(ret_str[0] == '\0')
        return NULL;

    return ret_str;
}

status_t parse_input(input_t *input, char *buffer){

    int len_count = 0;

    input->cmd = get_input(buffer, &len_count);
    input->typ = get_input(buffer, &len_count);

    if((input->buffer = clean_std_in(buffer)) == NULL)
        return FAIL;

    return SUCCESS;
}

bool_t is_add(char *cmd){

    if((strcmp(cmd, ADD)) == 0)
        return TRUE;
    return FALSE;
}

bool_t is_rm(char *cmd){

    if((strcmp(cmd, RM)) == 0)
        return TRUE;
    return FALSE;
}

bool_t is_node(char *type){

    if((strcmp(type, NODE)) == 0)
        return TRUE;
    return FALSE;
}

bool_t is_block(char *type){

    if((strcmp(type, BLOCK)) == 0)
        return TRUE;
    return FALSE;
}

bool_t check_block_impact(char *std_in)
{
    if(std_in[strlen(std_in)-2] == '*')
        return TRUE;
    else return FALSE;
}


bool_t check_number(char* input)
{

    int index = 0,
        flag = 0;

    while(input[index]){
        if(isdigit(input[index]))
            flag++;

        index++;
    }

    return flag == index;
}

void print_status(status_t status){
    if(status == SUCCESS)
        printf("status: Success!\n");
    else printf("status: Failed!\n");
}

/*
 *
 *
 *       ADD NODE
 *                                                      */

status_t check_add_block(input_t *input, node_t *unsynced)
{
    int len_count = 0;

    if(input->impact_all == TRUE) 
    {
        // TODO function that changes the previous passed nodes
        input->bid = get_input(input->buffer, &len_count);
        return SUCCESS;
    }

    input->one_time_bid = get_input(input->buffer, &len_count);
    if((input->nid = get_input(input->buffer, &len_count)) == NULL)
        return FAIL;

    if(check_number(input->nid) == TRUE){

        unsynced = add_block(unsynced, input->one_time_bid, atoi(input->nid));
        free(input->one_time_bid);
        return SUCCESS;

    }else{

        printf("Error, trying to add non numerical node or a null\n");
        return FAIL;
    }


    return SUCCESS;
}

status_t check_add_node(input_t *input, node_t *unsynced)
{

    if(check_number(input->buffer) == FALSE)
        return FAIL;

    if(input->impact_all == TRUE){
        unsynced = add_node(unsynced, input->bid, atoi(input->buffer)); 
        return SUCCESS;
    }else{
        // TODO pass a null bid 
        unsynced = add_node(unsynced, " ", atoi(input->buffer));
        return SUCCESS;

    }

    return FAIL;
}
/*

 *
 *        Remove NODE
 *                                                      */

status_t check_rm_block(input_t *input, node_t *unsynced){

    int len_count = 0;

    if(input->impact_all == TRUE){
        // TODO function that changes the previous passed nodes
        input->bid = get_input(input->buffer, &len_count);
    }else{
        input->one_time_bid = get_input(input->buffer, &len_count);
        if((input->nid = get_input(input->buffer, &len_count)) == NULL)
            return FAIL;

        if(check_number(input->nid) == TRUE){
            unsynced = remove_block(unsynced, input->one_time_bid);
            free(input->one_time_bid);
            return SUCCESS;
        }else{
            printf("Error, trying to add non numerical node or a null\n");
            return FAIL;
        }
    }

    return SUCCESS;
}

status_t check_rm_node(input_t *input, node_t *unsynced){

    if(check_number(input->buffer) == FALSE)
        return FAIL;

    if(input->impact_all == TRUE){
        // TODO to pass BLOCK in the function to remove node
        unsynced = remove_node(unsynced, atoi(input->buffer));
        return SUCCESS;
    }else{
        unsynced = remove_node(unsynced, atoi(input->buffer));
        return SUCCESS;
    }

    return FAIL;
}

/*
 *
 PUBLIC 

*/

// TODO add functions under each case unless quit

option_t basic_commands(char *cmd)
{

    if((strcmp(cmd, "sync")) == 0){
        printf("sync\n");
        return SYNC;
    }else if((strcmp(cmd, "quit")) == 0){
        printf("Quiting program successful.\n");
        return QUIT;
    }else if((strcmp(cmd, "ls")) == 0){
        printf("ls\n");
        /* print_list(unsynced); */
        return LS_NID;
    }else if((strcmp(cmd, "ls -l")) == 0){
        printf("ls -l\n");
        return LS_NID_BID;
    }

    return NONE;
}

option_t process_input(int std_in, node_t *unsynced){

    // check for basic commands
    option_t option = NONE;
    status_t status = FAIL;

    char *buffer = malloc(sizeof(char)*BUFF_SIZE);

    int read_ret = read(std_in, buffer, BUFF_SIZE);
    buffer[read_ret-1] = '\0';

    if((option = basic_commands(buffer)) != NONE){
        free(buffer);
        return option;
    }

    // if it's not a basic command // ls -l / quit / sync

    input_t *input = malloc(sizeof(input_t));

    if((parse_input(input, buffer)) == FAIL)
    {
        printf("Error! input doesn't seem to be a valid command.\n");
        return ERROR_OPTION;
    }

    if(is_add(input->cmd) && is_block(input->typ)){
        input->impact_all= check_block_impact(input->buffer);
        status = check_add_block(input, unsynced);

    }

    if(is_add(input->cmd) && is_node(input->typ))
        status = check_add_node(input, unsynced);

    if(is_rm(input->cmd) && is_block(input->typ))
    {
        input->impact_all= check_block_impact(input->buffer);
        status = check_rm_block(input, unsynced);
    }

    if(is_rm(input->cmd) && is_node(input->typ))
        status = check_rm_node(input, unsynced);


    print_status(status);
    // TODO Free input_t
    /* free_input(input); */
    free(buffer);
    return NONE;
}
