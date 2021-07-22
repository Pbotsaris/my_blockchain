#include "../include/list.h"

bool_t check_number(char *input){

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

char *get_input(char *input, int relative){

    char *ret_command = malloc(sizeof(char)*100);

    int index = 0;
    
    char space = ' ';
    
    while(input[relative]){

        printf("%c \n", input[relative]);
        if(input[relative] == space)
            break;

        ret_command[index] =  input[relative];
        index++;
        relative++;
    }
    
    ret_command[index] = '\0';
    return ret_command;
}

input_split* process_input(int file){

    char *input = malloc(sizeof(char)*100);

    read(file, input, sizeof(input));

    input_split *argument;

    argument = malloc(sizeof(input_split));

    argument->command = get_input(input, 0);
    argument->type = get_input(input, strlen(argument->command)+1);

    printf("%s\n", argument->command);
    printf("%s\n", argument->type);
    
    char *nid_bid = get_input(input, (strlen(argument->command)+1)+(strlen(argument->type)+1));
    
    if((strcmp(argument->type, "node")) == 0){
        if((check_number(nid_bid)) == TRUE)
            argument->nid = atoi(nid_bid);
        else
            printf("Error, you are trying to add a non numerical node\n");

    }else if((strcmp(argument->type, "block")) == 0){
        argument->bid = nid_bid;
        printf("%s\n", argument->bid);
    }

    return argument;
}

option_t check_add(input_split *input){
    

    if((strcmp(input->type, "node")) == 0){
        return ADDNID;
    }else if((strcmp(input->type, "block")) == 0){
        return ADDBID;
    }
    return ERROROPT;
}

option_t check_rm(input_split *input){

    if((strcmp(input->type, "node")) == 0){
        return RMNID;
    }else if((strcmp(input->type, "block")) == 0){
        return RMBID;
    }
    return ERROROPT;
}

option_t check_option(input_split *input){

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

