#include "../include/my_blockchain.h"
#define BUFF_SIZE 100

option_t basic_commands(input_t *input)
{
    if((strcmp(input->buffer, "sync")) == 0){
        return SYNC;
    }else if((strcmp(input->buffer, "quit")) == 0){
        return QUIT;
    }else if((strcmp(input->buffer, "ls")) == 0){
        return LS_NID;
    }else if((strcmp(input->buffer, "ls -l")) == 0){
        return LS_NID_BID;
    }else if((strcmp(input->buffer, "ls -x")) == 0){
        return LS_UNS;
    }
    return NONE;
}

option_t process_input(int std_in, input_t *input){
    // check for basic commands
    option_t option = NONE;
    input->buffer = malloc(sizeof(char)*BUFF_SIZE);
    int read_ret = read(std_in, input->buffer, BUFF_SIZE);
    input->buffer[read_ret-1] = '\0';

    option = basic_commands(input);

    return option;
}
