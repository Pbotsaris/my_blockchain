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

int main(int argc, char *argv[])
{
    node_t *head = init_list(0); 

    int i;

    for (i = 1; i < 5; ++i) 
        head = add_to_head(head, i);


    print_list(head);

    free_list(head);

    printf("hello wolrd");
    return 0;
}
