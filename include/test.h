#ifndef TEST_H
#define TEST_H
#include "./my_blockchain.h"
char *get_input(char *input, int *input_index);
option_t basic_commands(char *buffer);
char *clean_std_in(char *std_in);
bool_t check_block_impact(char *std_in);
bool_t check_number(char* input);

option_t process_input(int std_in, char *buffer);
status_t parse_input(input_t *input, char *buffer);

node_t *check_add_node(input_t *input, node_t *unsynced);
node_t *check_add_block(input_t *input, node_t *unsynced);

node_t *check_rm_node(input_t *input, node_t *unsynced);
node_t *check_rm_block(input_t *input, node_t *unsynced);

node_t *process_commands(char *buffer);

#endif

