#ifndef OPTION_H
#define OPTION_H

#define MAX_OPT_LEN 6

typedef enum{
    FALSE,
    TRUE,
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

#endif

