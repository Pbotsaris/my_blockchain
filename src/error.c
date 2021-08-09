#include <stdio.h>
#include "../include/err.h"

void print_error(err_t type)
{
    char error_messages[][100] = {
        "no more resources available on the computer.\n",
        "this node already exists.\n",
        "This block already exists.\n",
        "Node doesn't exist.\n",
        "Block doesn't exists.\n",
        "Command not found.\n",
        "Node must be a number.\n"
    };

    printf("NOK: %s", error_messages[type]);
}

