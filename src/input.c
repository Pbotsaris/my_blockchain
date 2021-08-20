#include "../include/input.h"

void free_input(input_t *input)
{
    free(input->buffer);

    free(input->typ);
    free(input->cmd);

    free(input->bid);
    free(input->nid);
    free(input->impact_bid);

    free(input);
}


input_t *init_input(void)
{
    input_t *input = (input_t*)malloc(sizeof(input_t));
    input->option = NONE;
    input->is_synced = FALSE;
    input->head = NULL;

    input->buffer = (char*)malloc(sizeof(char)*INPUT_BUFFER_SIZE);
    input->typ = (char*)malloc(sizeof(char)*INPUT_BUFFER_SIZE);
    input->cmd = (char*)malloc(sizeof(char)*INPUT_BUFFER_SIZE);
    input->nid = (char*)malloc(sizeof(char)*INPUT_BUFFER_SIZE);
    input->bid = (char*)malloc(sizeof(char)*INPUT_BUFFER_SIZE);
    input->impact_bid = (char*)malloc(sizeof(char)*INPUT_BUFFER_SIZE);

    return input;
}

