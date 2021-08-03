#include "../include/my_blockchain.h"
#define BUFF_SIZE 100

option_t basic_commands(char *cmd, node_t *head)
{
    if((strcmp(cmd, "sync")) == 0){
        printf("sync\n");
        return SYNC;
    }else if((strcmp(cmd, "quit")) == 0){
        printf("Quiting program successful.\n");
        return QUIT;
    }else if((strcmp(cmd, "ls")) == 0){
        print_list(head);
        return LS_NID;
    }else if((strcmp(cmd, "ls -l")) == 0){
        print_block_list(head);
        return LS_NID_BID;
    }
    return NONE;
}

option_t process_input(int std_in, input_t *input){
    // check for basic commands
    option_t option = NONE;
    input->buffer = malloc(sizeof(char)*BUFF_SIZE);
    int read_ret = read(std_in, input->buffer, BUFF_SIZE);
    input->buffer[read_ret-1] = '\0';

    option = basic_commands(input->buffer, input->unsynced);

    return option;
}
