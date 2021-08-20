#include "../include/my_blockchain.h"
#include "../include/messages.h"

char *output_merge(char *status, int added_nodes){

    char *output = malloc(sizeof(char)*BUFSIZ);

    char enter_boarder[] = "[";
    char end_boarder[] = "]> ";

    strcpy(output, enter_boarder);
    strcat(output, status);
    char temp[100];
    sprintf(temp, "%d", added_nodes);
    temp[strlen(temp)] = '\0';
    strcat(output, temp);
    strcat(output, end_boarder);

    return output;
}

void prompt_display(input_t *input){

     static char status[3];
     char *output = NULL;


    if(is_list_synced(input->head))
        strcpy(status, "s");
    else
        strcpy(status, "-");

    if(input->option == SYNC)
    {
        if(input->is_synced)
            print_message(NOSYNC_MSG);
        else
          status[0] = 's';
    }

    output = output_merge(status, count_nodes(input->head));
    write(0, output, strlen(output));
    free(output);

}
