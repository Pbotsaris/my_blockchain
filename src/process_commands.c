#include "../include/my_blockchain.h"
#include "../include/messages.h"

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

bool_t check_block_impact(char *buffer)
{
    size_t len = strlen(buffer);

    for (int i = len; i >= 0 ; --i) 
        if(buffer[i] == '*')
            return TRUE;

    return FALSE;
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


char *get_input(char *input, int *input_index)
{
    char *ret_command = (char*)malloc(sizeof(char)*100);
    int index = 0;
    bool_t is_reading = FALSE;

    while(input[*input_index]){

        if(is_reading == FALSE && isspace(input[*input_index]))
        {
            (*input_index)++;
            continue;
        }

        is_reading = TRUE;

        if(isspace(input[*input_index]) || input[*input_index] == NEW_LINE)
            break;

        ret_command[index] = input[*input_index];

        index++;
        (*input_index)++;
    }


    ret_command[index] = '\0';

    if(ret_command[0] == '\0')
        return NULL;

    return ret_command;
}


status_t parse_input(input_t *input)
{
    int len_count = 0;

    if((input->cmd = get_input(input->buffer, &len_count)) == NULL)
        return FAIL;

    if((input->typ = get_input(input->buffer, &len_count)) == NULL)
        return FAIL;

    if((strcmp(input->typ, NODE)) == 0){
        if((input->nid = get_input(input->buffer, &len_count)) == NULL
                || (get_input(input->buffer, &len_count)) != NULL)
            return FAIL;
    }
    else if((strcmp(input->typ, BLOCK)) == 0)
    {

        input->bid = get_input(input->buffer, &len_count);
        input->nid = get_input(input->buffer, &len_count); 

        if((strcmp(input->cmd, RM) == 0) && input->nid != NULL){
            return FAIL;
        }else if(input->bid == NULL || input->bid == NULL)
            return FAIL;
    }

    else
        return FAIL;

    return SUCCESS;
}


status_t check_add_block(input_t *input)
{
    if(check_number(input->nid))
    {
        if((node_exists(input->head, atoi(input->nid))) >= 0)
            input->head = add_block(input->head, input->bid, atoi(input->nid));
        else
        {
            print_error(NODE_NOT_EXISTS);
            return FAIL;
        }
    }
    else 
    {
        print_error(INVALID_NODE);
        return FAIL;
    }

    return SUCCESS;
}


status_t check_add_node(input_t *input)
{

    if(check_number(input->nid) == FALSE)
    {
        print_error(INVALID_NODE);
        return FAIL;
    }

    if(node_exists(input->head,atoi(input->nid)) >= 0)
        return FAIL;
    {
        print_error(NODE_EXISTS);
    }

    //    if(input->impact_all)
    //       input->unsynced = add_node(input->unsynced, input->bid, atoi(input->nid)); 
    //  else
      input->head = add_node(input->head, atoi(input->nid));

    return SUCCESS;
}


status_t check_rm_block(input_t *input)
{
    /* Block or node don't exist checked within list implementation */
    input->head = remove_block(input->head, input->bid, atoi(input->nid));

    return SUCCESS;
}

status_t check_rm_node(input_t *input)
{

    if(check_number(input->nid) == FALSE)
    {
        if((strcmp(input->nid, "*")) == 0){
            input->head = NULL;
            return SUCCESS;
        }else{
            print_error(INVALID_NODE);
            return FAIL; 
        }
    }

    if(node_exists(input->head, atoi(input->nid)) >= 0){
        input->head = remove_node(input->head, atoi(input->nid));
        return SUCCESS;
    }
    else
        print_error(NODE_NOT_EXISTS);
    return FAIL;

}

/*
 *      MAIN PUBLIC FUNCTION
 *
 */

void process_commands(input_t *input)
{

    status_t status;

    if((parse_input(input)) == FAIL)
    {
        print_error(CMD_NOT_FOUND);
        return;
    }

    if(is_add(input->cmd) && is_block(input->typ)){
        if((input->impact_all= check_block_impact(input->buffer)))
        {
            //  add_block_all(synced, input->bid);
            //  add_block_all(input->unsynced, input->bid);
        }
        else
            status = check_add_block(input);
    }

    if(is_add(input->cmd) && is_node(input->typ)){
        status = check_add_node(input);
    }

    if(is_rm(input->cmd) && is_block(input->typ))
    {
        input->impact_all= check_block_impact(input->buffer);
        status = check_rm_block(input);
    }

    if(is_rm(input->cmd) && is_node(input->typ))
        status = check_rm_node(input);

    if(status == SUCCESS)
        print_message(OK_MSG);

}
