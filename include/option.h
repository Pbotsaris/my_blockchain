#ifndef OPTION_H
#define OPTION_H

#define MAX_OPT_LEN 6

typedef enum{
    FALSE,
    TRUE,
    ERROR_BOOL,
} bool_t;

typedef enum{
    LS_NID,
    LS_NID_BID,
    LS_UNS,
    SYNC,
    QUIT,
    NONE,
    ERROR_OPTION,
} option_t;

typedef enum{
    SUCCESS,
    FAIL,
} status_t;

typedef struct input_split{
    char *cmd;
    char *typ;
    char *bid;
    char *nid;
    char *buffer;
    struct node_s *unsynced;
    bool_t impact_all;
    option_t option;
} input_t;

#endif

