#ifndef TEST_H
#define TEST_H
#include "./list.h"
char *get_input(char *input, int *input_index);
option_t basic_commands(char *buffer);
char *clean_std_in(char *std_in);
bool_t check_block_impact(char *std_in);
status_t check_add_block(input_t *input, char* std_in, node_t *data);
bool_t check_number(char* input);
status_t check_add_node(input_t *input, char *std_in, node_t *data);

#endif

