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
    node_t *unsynced_head = NULL;
    char *input_buffer = malloc(sizeof(char)*MAX_BUFF_SIZE);

    while(process_input(STDIN_FILENO, input_buffer) != QUIT)
          unsynced_head = process_commands(input_buffer);
           printf("%s\n", input_buffer);

 //   free(input_buffer);
   // free_list(unsynced_head);

    /* printf("cmd: %s, type: %s, bid: %s, nid: %i\n", input->cmd, input->type, input->bid, input->nid); */

    /* TODO: NEED FUNCTION TO FREE THESE */
 //   free(input->cmd);
  //  free(input->type);
  //  if(input->bid != NULL)
   //     free(input->bid);


    return 0;
}
