#ifndef MESSAGES_H
#define MESSAGES_H

typedef enum err{
    NO_RESOURCE,
    NODE_EXISTS,
    BLOCK_EXISTS,
    NODE_NOT_EXISTS,
    BLOCK_NOT_EXISTS,
    CMD_NOT_FOUND,
    INVALID_NODE,
    BAD_COMMAND,
    BAD_TYPE,
} err_t;


typedef enum msg{
    LAUNCH_MSG,
    NOSYNC_MSG,
    SYNC_MSG,
    LS_MSG,
    LS_L_MSG,
    QUIT_MSG,
    LS_X_MSG,
    OK_MSG
}msg_t;

void print_error(err_t type);
void print_message(msg_t type);


#endif
