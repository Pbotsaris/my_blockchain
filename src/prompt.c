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

int count_nodes(node_t *head)
{
    if(head == NULL)
        return 0;

    int count = 0;
    node_t *current = head;
    while (current)
    {
        current = current->next;
        count++;
    }
    return count;
} 

void prompt_display(input_t *input){

    static char status[] = "s"; 
    static int prev_node_count = 0;
    static int entries = 0;

    if(entries == 0){
        print_message(LAUNCH_MSG);
        prev_node_count = count_nodes(input->unsynced);
        entries++;
    }
    
    char *output = malloc(sizeof(char)*BUFSIZ);

    if(count_nodes(input->unsynced) != prev_node_count){
        status[0] = '-';
        prev_node_count = count_nodes(input->unsynced);
    }

    if(input->option == SYNC)
        status[0] = 's';


    output = output_merge(output, status, count_nodes(input->unsynced));
    write(0, output, sizeof(output));
    free(output);
}
