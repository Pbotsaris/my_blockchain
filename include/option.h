#define MAX_OPT_LEN 6

typedef enum{
    FALSE,
    TRUE,
    ERRORBOOL,
} bool_t;


typedef enum{
    ADD_NID, /* These are really hard to understand */
    ADD_BID, /* These are really hard to understand */
    RM_NID, /* These are really hard to understand */
    RM_BID, /* These are really hard to understand */
    ADD_BID_ALL,
    RM_BID_ALL,
    LS_NID,
    LS_NID_BID,
    SYNC,
    QUIT,
    NONE,
    ERROROPT, /* These are really hard to understand */
} option_t;

