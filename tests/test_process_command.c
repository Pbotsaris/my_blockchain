#include <check.h>
#include "../include/test.h"
#include "../include/list.h"


/*input_t *create_test_input(char *command)*/
/*{*/
    /*int len = 0;*/
    /*input_t *input = (input_t*)malloc(sizeof(input_t));*/
    /*input->cmd = get_input(command, &len);*/
    /*input->typ = get_input(command, &len);*/

    /*return input;*/
/*}*/

//typedef struct input_split{
//    char *cmd;
//    char *typ;
//    char *bid;
//    char *one_time_bid;
//    char *nid;
//    char *buffer;
//    struct node_s *unsynced;
//    bool_t impact_all;
//    option_t option;
//} input_t;
//


START_TEST (test_get_cmd_type_stdin_buffer)
{
    int len = 0;
    char buffer[] = "add node 12";
    char *cmd = get_input(buffer, &len);
    char *type = get_input(buffer, &len);

    ck_assert_str_eq(cmd, "add");
    ck_assert_str_eq(type, "node");
}
END_TEST


START_TEST (test_process_input)
{
    input_t input; 
    input.option = NONE;
    input.unsynced = NULL;

    int fd = open("tests/test_commands/quit", O_RDWR);
    option_t option =  process_input(fd, &input);
    option_t test_option = QUIT;
    ck_assert_int_eq(option, test_option); 
    close(fd);

    fd = open("tests/test_commands/none", O_RDWR);

    option = process_input(fd, &input);
    test_option = NONE;
    ck_assert_int_eq(option, test_option); 

    close(fd);
    fd = open("tests/test_commands/ls", O_RDWR);

    option = process_input(fd, &input);
    test_option = LS_NID;
    ck_assert_int_eq(option, test_option); 

    close(fd);
    fd = open("tests/test_commands/ls_l", O_RDWR);

    option = process_input(fd, &input);
    test_option = LS_NID_BID;
    ck_assert_int_eq(option, test_option); 

    close(fd);
    fd = open("tests/test_commands/sync", O_RDWR);

    option = process_input(fd, &input);
    test_option = SYNC;
    ck_assert_int_eq(option, test_option); 

    close(fd);
}
END_TEST


START_TEST (test_extract_input_digits)
{
    // get 3 item? 
    char buffer[] = "add node 10";
    char *return_buffer =  extract_input_digits(buffer);
    ck_assert_str_eq(return_buffer, "10");
    free(return_buffer);

    // RANDOS!
    char buffer_error[] = "  rando -d , di, ";
    return_buffer =  extract_input_digits(buffer_error);
    ck_assert_ptr_null(return_buffer);
    free(return_buffer);

    // multiple space case 
    char buffer2[] = "  add    node   10";
    return_buffer =  extract_input_digits(buffer2);
    ck_assert_str_eq(return_buffer, "10");
    free(return_buffer);
}

END_TEST

START_TEST (test_check_impact)
{
    char buffer[] = "add block 21 *\n";

    bool_t result = check_block_impact(buffer);
    ck_assert_int_eq(result, TRUE);

    char buffer2[] = "add block 21\n";
    result = check_block_impact(buffer2);
    ck_assert_int_eq(result, FALSE);
}
END_TEST


START_TEST (test_check_number)
{
    bool_t status = check_number("10");
    ck_assert_int_eq(status, TRUE);

    status = check_number("cat");
    ck_assert_int_eq(status, FALSE);

}
END_TEST


START_TEST (test_check_add_block)
{
    char buffer[] = "add block cat 1";

    input_t *input = malloc(sizeof(input_t));
    node_t *head = NULL;

    parse_input(input, buffer);

    head= check_add_block(input, head);
//    ck_assert_str_eq(head->bid, "cat");
    free(input);

}
END_TEST


START_TEST (test_check_add_node)
{
    char buffer[] = "add node 2";
    input_t *input = malloc(sizeof(input_t));

    node_t *head = NULL;
    parse_input(input, buffer);

    head = check_add_node(input, head);
    ck_assert_int_eq(head->nid, 2);

    free(input);

}

START_TEST (test_check_rm_node)
{
    char buffer[] = "rm node 2";
    input_t *input = malloc(sizeof(input_t));
    node_t *head = NULL;
    head = add_node(head, "\0", 2);
    head = add_node(head, "\0", 1);
    parse_input(input, buffer);

    head = check_rm_node(input, head);
    ck_assert_int_eq(head->nid, 1);

    char buffer2[] = "rm node 1";
    parse_input(input, buffer2);
     
    head = check_rm_node(input, head);
    ck_assert_ptr_null(head);

    free(input);
}


START_TEST (test_check_rm_block)
{
    char buffer[] = "rm block dog";
    input_t *input = malloc(sizeof(input_t));
    node_t *head = NULL;
    head = add_node(head, "dog", 2);
    head = add_node(head, "dog", 1);
    parse_input(input, buffer);

    head = check_rm_block(input, head);

    ck_assert_int_eq(head->bid[0], 0);
    ck_assert_int_eq(head->next->bid[0], 0);
    
    free(input);
}


END_TEST

Suite * test_options(void)
{
    Suite       *suite;
    TCase       *core;

    suite = suite_create("Test Options");
    core = tcase_create("Core");

    tcase_add_test(core, test_process_input);
    tcase_add_test(core, test_get_cmd_type_stdin_buffer);
    tcase_add_test(core, test_extract_input_digits);
    tcase_add_test(core, test_check_impact);
    tcase_add_test(core, test_check_number);
    tcase_add_test(core, test_check_add_block);
    tcase_add_test(core, test_check_add_node);
    tcase_add_test(core, test_check_rm_node);
    tcase_add_test(core, test_check_rm_block);
    suite_add_tcase(suite, core);

    return(suite);
}


int main(void)
{
    int       failed;
    Suite     *suite;
    SRunner   *runner;

    suite = test_options();
    runner = srunner_create(suite);


    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return(failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);

}

