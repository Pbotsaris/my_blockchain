#include <stdio.h>
#include "../include/error.h"

void print_error(err_t tyoe)
{
    printf("%s", err_messages[tyoe]);
}

