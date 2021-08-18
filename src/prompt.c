#include "../include/my_blockchain.h"
#include "../include/messages.h"

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

bool_t prompt_display(input_t *input){

    static char status[] = "s"; 
    char *output = malloc(sizeof(char)*BUFSIZ);

       if(count_nodes(input->head) == 0)  
             print_message(LAUNCH_MSG);

   // static int prev_node_count = 0;
  //  static int entries = 0;

//    if(entries == 0){
//        prev_node_count = count_nodes(input->unsynced);
//        entries++;
//    }
//    
//
//    if(count_nodes(input->unsynced) != prev_node_count){
//        status[0] = '-';
//        needs_sync = TRUE;
//        prev_node_count = count_nodes(input->unsynced);
//    }

    if(input->option == SYNC)
        status[0] = 's';


    output = output_merge(output, status, count_nodes(input->head));
    write(0, output, sizeof(output));
    free(output);

    return is_list_synced(input->head);
}
