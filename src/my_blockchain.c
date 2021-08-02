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
#include "../include/my_blockchain.h"
#define MAX_BUFF_SIZE 100

int main(void)
{
    node_t *unsynced = init_list();
    char *input_buffer = malloc(sizeof(char)*MAX_BUFF_SIZE);

    while(process_input(STDIN_FILENO, input_buffer) != QUIT){


    } 




    /* printf("cmd: %s, type: %s, bid: %s, nid: %i\n", input->cmd, input->type, input->bid, input->nid); */

    /* TODO: NEED FUNCTION TO FREE THESE */
 //   free(input->cmd);
  //  free(input->type);
  //  if(input->bid != NULL)
   //     free(input->bid);


    return 0;
}
