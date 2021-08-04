#ifndef TEST_H
#define TEST_H
#include "./my_blockchain.h"


/* HELPER process_input */
option_t basic_commands(char *buffer);

/* HELPER process_commands */
//char *extract_input_digits(char *stdin_buffer);
bool_t check_block_impact(char *std_in);
bool_t check_number(char* input);
char *get_input(char *input, int *input_index);
status_t parse_input(input_t *input);

/* IMPLEMENTATION process_commands */
void check_add_node(input_t *input);
void check_add_block(input_t *input);

void check_rm_node(input_t *input);
void check_rm_block(input_t *input);

/* PUBLIC */
void process_commands(input_t *input);
option_t process_input(int std_in, input_t *input);

#endif

