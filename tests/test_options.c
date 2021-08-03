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


START_TEST (get_option_from_stdin_buffer)
{

    option_t option =  basic_commands("quit");
    option_t test_option = QUIT;
    ck_assert_int_eq(option, test_option); 

    option = basic_commands("add node 12");
    test_option = NONE;
    ck_assert_int_eq(option, test_option); 

    option = basic_commands("ls");
    test_option = LS_NID;
    ck_assert_int_eq(option, test_option); 

    option = basic_commands("ls -l");
    test_option = LS_NID_BID;
    ck_assert_int_eq(option, test_option); 

    option = basic_commands("sync");
    test_option = SYNC;
    ck_assert_int_eq(option, test_option); 

    // This will will not return ERROR_OPT unless it's passed in process_input function
    /* option = create_test_option("randocommand"); */
    /* test_option = ERROR_OPTION; */
    /* ck_assert_int_eq(option, test_option); */ 

}
END_TEST


START_TEST (test_clean_stdin_buffer)
{

    // get 3 item? 
    char buffer[] = "add node 10";
    char *return_buffer =  clean_std_in(buffer);
    ck_assert_str_eq(return_buffer, "10");

    //  WHEN DOES IT RETURN NULL????
   // char buffer_error[] = "  rando -d , di, ";
   // return_buffer =  clean_std_in(buffer_error);
   // ck_assert_ptr_null(return_buffer);


    // multiple space case 
  //  char buffer2[] = "  add    node   10";
  //  return_buffer =  clean_std_in(buffer2);
  //  ck_assert_str_eq(return_buffer, "10");


    free(return_buffer);

}
END_TEST

START_TEST (test_check_impact)
{

    // get 3 item? 
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

 //printf("--> cmd: %s, typ-> %s, buffer-> %d \n", input->cmd, input->typ, atoi(input->buffer));

    head = check_add_node(input, head);
    ck_assert_int_eq(head->nid, 2);

    free(input);

}
END_TEST

Suite * test_options(void)
{
    Suite       *suite;
    TCase       *core;

    suite = suite_create("Test Options");
    core = tcase_create("Core");

    tcase_add_test(core, test_get_cmd_type_stdin_buffer);
    tcase_add_test(core, get_option_from_stdin_buffer);
    tcase_add_test(core, test_clean_stdin_buffer);
    tcase_add_test(core, test_check_impact);
    tcase_add_test(core, test_check_number);
    tcase_add_test(core, test_check_add_block);
    tcase_add_test(core, test_check_add_node);
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

