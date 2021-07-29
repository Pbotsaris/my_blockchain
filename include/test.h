#ifndef TEST_H
#define TEST_H
#include "./option.h"

 char *get_input(char *input, int *input_index);
 option_t get_option(input_t *input);
 char *clean_std_in(char *std_in);
bool_t check_block_impact(char *std_in);

#endif

