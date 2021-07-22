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

int main(void)
{
    /* Init list with 1 items. List functions ALWAYS return the head */
    node_t *head = init_list("cat", 0); 

    int i;

    for (i = 1; i < 5; ++i) 
        head = add_node(head, "dog", i);

    for (i = 5; i < 10; ++i) 
        head = add_node(head, "sheep", i);

    printf("------ Complete List ------\n");
    print_list(head);

    printf("------ Remove node ------\n");
    /* this removes a node by the nid one at time. */
    head = remove_node(head, 4);
    head = remove_node(head, 0);
    print_list(head);

    /* add a block to a given node */
    printf("------ Add Block  ------\n");
    head = add_block(head,"giraffe", 7);
    print_list(head);

    printf("------ Remove block ------\n");

    /* this will remove all nodes with a matching bid */
    head = remove_block(head, "sheep");
    
    /* Only sheeps will survive the slaugther -> see output */
    print_list(head);
    free_list(head);


    return 0;
}
