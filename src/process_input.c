#include "../include/my_blockchain.h"

#define BUFF_SIZE 100

static option_t basic_commands(input_t *input)
{
    if((strcmp(input->buffer, "sync")) == 0)
        return SYNC;
    else if((strcmp(input->buffer, "quit")) == 0)
        return QUIT;
    else if((strcmp(input->buffer, "ls")) == 0)
        return LS_NID;
    else if((strcmp(input->buffer, "ls -l")) == 0)
        return LS_NID_BID;
    else if((strcmp(input->buffer, "ls -x")) == 0)
        return LS_UNS;
    
    return NONE;
}

option_t process_input(int std_in, input_t *input){
    option_t option = NONE;


    int read_ret = read(std_in, input->buffer, BUFF_SIZE);
    input->buffer[read_ret - 1] = '\0';

    option = basic_commands(input);

    return option;
}

