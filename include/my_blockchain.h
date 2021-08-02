#ifndef MY_BLOCKCHAIN_H
#define MY_BLOCKCHAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include "option.h"
#include "list.h"

#define SELLECT_ALL "*"
option_t process_input(int std_in, char *buffer);

#endif
