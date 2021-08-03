#include "../include/my_blockchain.h"
#define BUFF_SIZE 100

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

option_t process_input(int std_in, char *buffer){
    // check for basic commands
    option_t option = NONE;

    int read_ret = read(std_in, buffer, BUFF_SIZE);
    buffer[read_ret-1] = '\0';

    if((option = basic_commands(buffer)) != NONE)
        free(buffer);
    
        return option;
}
