#ifndef ERR_H
#define ERR_H

typedef enum err {NO_RESOURCE, NODE_EXISTS, BLOCK_EXISTS, NODE_NOT_EXISTS, BLOCK_NOT_EXISTS, CMD_NOT_FOUND, INVALID_NODE} err_t;
void print_error(err_t tyoe);

#endif
