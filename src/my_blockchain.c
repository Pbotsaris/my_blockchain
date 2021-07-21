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
    node_t *head = init_list("cat", 0); 

    int i;
    for (i = 1; i < 5; ++i) 
        head = add_to_head(head, "dog", i);

    print_list(head);

    printf("------------\n");

   head = remove_node(head, 4);
   head = remove_node(head, 0);
    print_list(head);

    printf("------------\n");
    
    free_list(head);


    return 0;
}
