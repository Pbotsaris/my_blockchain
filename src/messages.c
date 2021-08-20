#include <stdio.h>
#include "../include/messages.h"

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


void print_message(msg_t type)
{
    char messages[][100] = {
        "Program starting...\n",
        "NOK: Nothing to sync.\n",
        "OK: Syncing...\n",
        "OK: Synced nodes:\n",
        "OK: Synced nodes and blocks:\n",
        "OK: Quitting program successful.\n",
        "OK: Unsynced nodes:\n",
        "OK\n",
    };

    printf("%s", messages[type]);
}

