/*
 * =====================================================================================
 *
 *       Filename:  my_blockchain.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/21/2021 22:01:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Khalil Marsi, Pedro Botsaris
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/my_blockchain.h"
#define BUFF_SIZE 100

void free_struct(input_t *input){
    free(input->bid);
    free(input->buffer);
    free(input->cmd);
    free(input->typ);
    free(input->nid);
}

int main(void)
{

    input_t *input = malloc(sizeof(input_t));
    input->option = NONE;
    input->unsynced = NULL;

    node_t *synced = NULL;
    synced = get_synced_nodes(synced);
    input->unsynced = copy_list(synced, input->unsynced);

    printf("Program starting...\n");
    while(input->option != QUIT){
        prompt_display(input);
        if((input->option = process_input(STDIN_FILENO,input, &synced)) == NONE)
            process_commands(input);
    } 

    write_nodes(synced);

    free_list(synced);
    free_struct(input);
    return 0;
}

