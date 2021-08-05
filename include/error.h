#ifdef ERROR_H
#define ERROR_H
typedef enum err {NO_RESOURCE, NODE_EXISTS, BLOCK_EXISTS, NODE_NOT_EXISTS, BLOCK_NOT_EXISTS, CMD_NOT_FOUND} err_t;

char err_messages[][100] = {
    "no more resources available on the computer.\n",
    "this node already exists.\n",
    "This block already exists.\n",
    "Node doesn't exist.\n",
    "Block doesn't exists.\n",
    "Command not found\n"
};

void print_error(err_t tyoe)

#endif

