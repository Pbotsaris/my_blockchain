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

#include <stdlib.h>
#include  <stdio.h>
#include "../include/list.h"
void free_struct(input_t *input){

    free(input->bid);
    free(input->buffer);
    free(input->cmd);
    free(input->typ);
    free(input->one_time_bid);
    free(input->nid);
    free(input->unsynced);
}

int main(void)
{

    input_t *input = malloc(sizeof(input_t));
    input->option = NONE;
    input->unsynced = NULL;
    
    printf("Program starting...\n");
    while(input->option != QUIT){
        prompt_display(input->option);
        input->option = process_input(STDIN_FILENO, input);
    } 

    free_struct(input);
    free(input);
    return 0;
}
