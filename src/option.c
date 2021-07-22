#include "../include/list.h"
#define SPACE ' '
#define NODE "node"
#define BLOCK "block"


static char *get_input(char *input, int *input_index)
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

/* Functions in the order of execution */

static bool_t check_number(char *input)
{
    int index = 0,
        flag = 0,
        size = (int)strlen(input) - 1;

    while(input[index]){
        if(isdigit(input[index]) == 0){
            flag++;
        }
        index++;
    }
    printf("flags %d\n", flag);

    if(flag == size)
        return TRUE;
    else 
        return FALSE;
}


static option_t check_add(input_t *input)
{

    if((strcmp(input->type, NODE)) == 0){
        return ADDNID;
    }else if((strcmp(input->type, "block")) == 0){
        return ADDBID;
    }
    return ERROROPT;
}

static option_t check_rm(input_t *input)
{

    if((strcmp(input->type, NODE)) == 0){
        return RMNID;
    }else if((strcmp(input->type, "block")) == 0){
        return RMBID;
    }
    return ERROROPT;
}

/*
 *
                 PUBLIC

 
                                               */

input_t* process_input(int file){

    char *input = malloc(sizeof(char)*100);
    char *nid_bid = NULL;
    int len_count = 0;
    input_t *arg = NULL;

    /* sizeof(input) is of the pointer address not number of chars */
    int nbr = read(file, input, 100);
    /*  extra safety  */
    input[nbr + 1] = '\0';

    printf("input full: %s\n", input) ;

    /*TODO: if arg == NULL return error  */
    arg = (input_t*)malloc(sizeof(input_t));

    arg->cmd = get_input(input, &len_count);
    arg->type = get_input(input, &len_count);

    nid_bid = get_input(input, &len_count);
    printf("len_count: %i, nid_bid %s\n", len_count, nid_bid);
    
    printf("type: %s\n", arg->type) ;

    if((strcmp(arg->type, NODE)) == 0){
        if((check_number(nid_bid)) == TRUE)
            arg->nid = atoi(nid_bid);
        else
            /* TODO: return error */
            printf("Error, you are trying to add a non numerical node\n");
    }

    if((strcmp(arg->type, BLOCK)) == 0){
        arg->bid = nid_bid;
        printf("%s\n", arg->bid);
    }

    /* free functions */
    free(input);

    return arg;
}


option_t check_option(input_t *input){

    option_t option = ERROROPT;

    if(input->type == NULL){
        if((strcmp(input->cmd, "ls")) == 0){
            option = LS;
        }else if((strcmp(input->cmd, "sync"))==0){
            option = SYNC;
        }else if((strcmp(input->cmd, "QUIT")) == 0){
            option = QUIT;
        }
    }

    if((strcmp(input->cmd, "add")) == 0){
        option = check_add(input);
    }

    if((strcmp(input->cmd, "rm"))== 0){
        option = check_rm(input);
    }

    return option;
}

