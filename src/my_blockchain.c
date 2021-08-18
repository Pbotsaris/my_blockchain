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
#include "../include/messages.h"
#define BUFF_SIZE 100

void free_struct(input_t *input){
    free(input->bid);
    free(input->buffer);
    free(input->cmd);
    free(input->typ);
    free(input->nid);
    free_list(input->head);
    free(input);
}

int main(void)
{

   input_t *input = malloc(sizeof(input_t));
   input->option = NONE;
   input->is_synced = FALSE;
   node_t *head = NULL;

//   synced = get_synced_nodes(synced);
//   input->unsynced = copy_list(synced, input->unsynced);

   while(input->option != QUIT){

       prompt_display(input);
       input->option = process_input(STDIN_FILENO,input); 

       switch(input->option){
           case SYNC:
               print_message(SYNC_MSG);
             //  synced = copy_list(input->unsynced, synced);
               break;

           case LS_NID:
               print_message(LS_MSG);
               print_list(head);
               break;

           case LS_NID_BID:
               print_message(LS_L_MSG);
               print_block_list(head);
               break;

           case QUIT:
 //              write_nodes(head);
               free_list(head);
               free_struct(input);
               print_message(QUIT_MSG);
               break;

           default:
               process_commands(input);
               break;
       }
   } 

    return 0;
}

