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


int main(void)
{
    input_t *input = init_input();
    input->head = get_synced_nodes(input->head);
    print_message(LAUNCH_MSG);

    while(input->option != QUIT){

        prompt_display(input);
        input->option = process_input(STDIN_FILENO,input); 

        switch(input->option){
            case SYNC:
                input->head = sync_nodes(input->head);
                print_message(SYNC_MSG);
                break;

            case LS_NID:
                print_message(LS_MSG);
                print_list(input->head);
                break;

            case LS_NID_BID:
                print_message(LS_L_MSG);
                print_block_list(input->head);
                break;

            case QUIT:
                write_nodes(input->head);
                print_message(QUIT_MSG);
                break;

            default:
                process_commands(input);
                break;
        }
    } 


    free_list(input->head);
    free_input(input);
    return 0;
}

