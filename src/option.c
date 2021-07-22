#include "../include/list.h"

static bool_t check_number(char *input)
{
    int index = 0,
        flag = 0,
        size = strlen(input)-1;

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

static char *get_input(char *input, int relative)
{
    char *ret_command = malloc(sizeof(char)*100);
    int index = 0;
    char space = ' ';
    
    while(input[relative]){

        if(input[relative] == space)
            break;

        ret_command[index] =  input[relative];
        index++;
        relative++;
    }
    
    ret_command[index] = '\0';
    return ret_command;
}

static option_t check_add(input_t *input)
{

    if((strcmp(input->type, "node")) == 0){
        return ADDNID;
    }else if((strcmp(input->type, "block")) == 0){
        return ADDBID;
    }
    return ERROROPT;
}

static option_t check_rm(input_t *input)
{

    if((strcmp(input->type, "node")) == 0){
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

    read(file, input, sizeof(input));

    input_t *arg = NULL;

    /*TODO: if arg == NULL return error  */
    arg = (input_t*)malloc(sizeof(input_t));

    arg->command = get_input(input, 0);
    arg->type = get_input(input, strlen(arg->command)+1);

    printf("%s\n", arg->command);
    printf("%s\n", arg->type);
    
    char *nid_bid = get_input(input, (strlen(arg->command)+1)+(strlen(arg->type)+1));
    
    if((strcmp(arg->type, "node")) == 0){
        if((check_number(nid_bid)) == TRUE)
            arg->nid = atoi(nid_bid);
        else
            printf("Error, you are trying to add a non numerical node\n");

    }else if((strcmp(arg->type, "block")) == 0){
        arg->bid = nid_bid;
        printf("%s\n", arg->bid);
    }

    return arg;
}


option_t check_option(input_t *input){

    option_t option = ERROROPT;

    if(input->type == NULL){
        if((strcmp(input->command, "ls")) == 0){
            option = LS;
        }else if((strcmp(input->command, "sync"))==0){
            option = SYNC;
        }else if((strcmp(input->command, "QUIT")) == 0){
            option = QUIT;
        }
    }

    if((strcmp(input->command, "add")) == 0){
        option = check_add(input);
    }

    if((strcmp(input->command, "rm"))== 0){
        option = check_rm(input);
    }

    return option;
}

