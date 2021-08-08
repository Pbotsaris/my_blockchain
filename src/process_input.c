#include "../include/my_blockchain.h"
#define BUFF_SIZE 100

option_t basic_commands(input_t *input, node_t **synced)
{
    if((strcmp(input->buffer, "sync")) == 0){
        printf("syncing...\n");
        *synced = input->unsynced;
        return SYNC;
    }else if((strcmp(input->buffer, "quit")) == 0){
        printf("Quiting program successful.\n");
        return QUIT;
    }else if((strcmp(input->buffer, "ls")) == 0){
        print_list(*synced);
        return LS_NID;
    }else if((strcmp(input->buffer, "ls -l")) == 0){
        print_block_list(*synced);
        return LS_NID_BID;
    }
    return NONE;
}

option_t process_input(int std_in, input_t *input, node_t **synced){
    // check for basic commands
    option_t option = NONE;
    input->buffer = malloc(sizeof(char)*BUFF_SIZE);
    int read_ret = read(std_in, input->buffer, BUFF_SIZE);
    input->buffer[read_ret-1] = '\0';

    option = basic_commands(input, synced);

    return option;
}
