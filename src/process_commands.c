#include "../include/my_blockchain.h"

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

status_t parse_input(input_t *input, char *buffer)
{

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
    if(std_in[strlen(std_in)-1] == '*')
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
 *       ADD BLOCK TO NODE
 *                                                      */

void check_add_block(input_t *input)
{
    int len_count = 0;

    // TODO function that changes the previous passed nodes
    if(input->impact_all)
        input->bid = get_input(input->buffer, &len_count);
    else
        input->one_time_bid = get_input(input->buffer, &len_count);

    // TODO: add if statement +  error handling function
    input->nid = get_input(input->buffer, &len_count);

    if(check_number(input->nid))
    {
        if((node_exists(input->unsynced, atoi(input->nid))) >= 0)
            input->unsynced = add_block(input->unsynced, input->one_time_bid, atoi(input->nid));
        else
            input->unsynced = add_node(input->unsynced,input->one_time_bid, atoi(input->nid));
    }

}

/*
 *
 *       ADD A NODE 
 *                                                      */

void check_add_node(input_t *input)
{
    // TODO add error handling function
    if(check_number(input->buffer) == FALSE)
        return;

    if(input->impact_all)
        input->unsynced = add_node(input->unsynced, input->bid, atoi(input->buffer)); 
    else
        input->unsynced = add_node(input->unsynced, "\0", atoi(input->buffer));

    input->option = ADD_NID;
}

/*
 *
 *        REMOVE A BLOCK FROM A NODE
 *                                                      */

void check_rm_block(input_t *input)
{
    int len_count = 0;

    // TODO function that changes the previous passed nodes
    if(input->impact_all)
        input->bid = get_input(input->buffer, &len_count);

    input->one_time_bid = get_input(input->buffer, &len_count);

    if((block_exists(input->unsynced, input->one_time_bid)) >= 0)
        input->unsynced = remove_block(input->unsynced, input->one_time_bid);
    else
        // TODO Error handling: list is empty
        return;
}

/*
 *
 *        REMOVE A NODE
 *                                                      */

void check_rm_node(input_t *input)
{
    if(check_number(input->buffer) == FALSE)
        return; 
    // TODO Error handling function 

    // if(input->impact_all)
    // TODO to pass BLOCK in the function to remove node

    if(node_exists(input->unsynced, atoi(input->buffer)) >= 0)
        input->unsynced = remove_node(input->unsynced, atoi(input->buffer));
    else
        // TODO Error handling: list is empty
        return;
}

/*
 *
 *      MAIN PUBLIC FUNCTION
 *
 *
 */

void process_commands(input_t *input)
{
    if((parse_input(input, input->buffer)) == FAIL)
        // printf("Error! input doesn't seem to be a valid command.\n");
        return;
        // TODO: FUNCTION for error handling

    if(is_add(input->cmd) && is_block(input->typ)){
        input->impact_all= check_block_impact(input->buffer);
        check_add_block(input);
    }

    if(is_add(input->cmd) && is_node(input->typ)){
        check_add_node(input);
    }

    if(is_rm(input->cmd) && is_block(input->typ))
    {
        input->impact_all= check_block_impact(input->buffer);
        check_rm_block(input);
    }

    if(is_rm(input->cmd) && is_node(input->typ))
        check_rm_node(input);
}
