#include "../include/my_blockchain.h"

char *output_merge(char* output,char *status, int added_nodes){
    
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

void prompt_display(option_t option){
    
    static int added_nodes = 0;
    static char status[] = "s"; 
   
    char *output = malloc(sizeof(char)*106);

    if(option == SYNC)
        status[0] = 's';

    if(option == ADD_NID){
        status[0] = '-';
        added_nodes++;
    }
    
    output = output_merge(output, status, added_nodes);
    write(0, output, sizeof(output));
    free(output);
}
