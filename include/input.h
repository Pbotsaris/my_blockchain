#ifndef INPUT_H
#define INPUT_H

#define INPUT_BUFFER_SIZE 100
#include "stdlib.h"
#include "./option.h"

typedef struct input_split{
    char *cmd;
    char *typ;
    char *bid;
    char *nid;
    char *impact_bid;
    char *buffer;
    struct node_s *head;
    bool_t impact_all;
    bool_t is_synced;
    option_t option;
} input_t;


input_t *init_input(void);
void free_input(input_t *input);

#endif
