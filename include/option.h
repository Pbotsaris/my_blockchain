#define MAX_OPT_LEN 6

typedef enum{
    FALSE,
    TRUE,
    ERRORBOOL,
} bool_t;

typedef enum{
    ADDNID,
    ADDBID,
    RMNID,
    RMBID,
    LS,
    SYNC,
    QUIT,
    NONE,
    ERROROPT,
} option_t;

typedef struct input_split{
    char *command;
    char *type;
    char *bid;
    int nid;
} input_split;

input_split* process_input(int file);
option_t check_option(input_split *input);
