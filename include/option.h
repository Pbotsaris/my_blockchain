#define MAX_OPT_LEN 6

typedef enum{
    FALSE,
    TRUE,
    ERRORBOOL,
} bool_t;


typedef enum{
    ADDNID, /* These are really hard to understand */
    ADDBID, /* These are really hard to understand */
    RMNID, /* These are really hard to understand */
    RMBID, /* These are really hard to understand */
    LS,
    SYNC,
    QUIT,
    NONE,
    ERROROPT, /* These are really hard to understand */
} option_t;

typedef struct input{
    char *cmd;
    char *type;
    char *bid;
    int nid;
} input_t;

input_t* process_input(int file);
option_t check_option(input_t *input);
