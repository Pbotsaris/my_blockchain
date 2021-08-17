#include <check.h>
#include "../include/test.h"
#include "../include/list.h"

//void free_input(input_t *input, char type)
//{
//    free(input->buffer);
//    free(input->cmd);
//    free(input->typ);
//
//    if(type == 'b' || type == 'n')
//         free(input->nid);
//    if(type == 'b')
//        free(input->bid);
//}
//
//START_TEST (test_get_cmd_type_stdin_buffer)
//{
//    int len = 0;
//    char buffer[] = "add node 12\n";
//    char *cmd = get_input(buffer, &len);
//    char *type = get_input(buffer, &len);
//    char *nid = get_input(buffer, &len);
//
//    ck_assert_str_eq(cmd, "add");
//    ck_assert_str_eq(type, "node");
//    ck_assert_str_eq(nid, "12");
//
//    len = 0;
//
//    char buffer2[] = "   add   node   12\n";
//    cmd = get_input(buffer2, &len);
//    type = get_input(buffer2, &len);
//    nid = get_input(buffer2, &len);
//
//    ck_assert_str_eq(cmd, "add");
//    ck_assert_str_eq(type, "node");
//    ck_assert_str_eq(nid, "12");
//
//    len = 0;
//
//    char buffer3[] = "add block cat 12\n";
//    cmd = get_input(buffer3, &len);
//    type = get_input(buffer3, &len);
//    char *bid = get_input(buffer3, &len);
//    nid = get_input(buffer3, &len);
//
//    ck_assert_str_eq(cmd, "add");
//    ck_assert_str_eq(type, "block");
//    ck_assert_str_eq(bid, "cat");
//    ck_assert_str_eq(nid, "12");
//
//}
//END_TEST
//
//
//START_TEST (test_process_input)
//{
//    input_t input; 
//    input.option = NONE;
//    input.unsynced = NULL;
//
//    int fd = open("tests/test_commands/quit", O_RDWR);
//    option_t option =  process_input(fd, &input);
//    option_t test_option = QUIT;
//    ck_assert_int_eq(option, test_option); 
//    close(fd);
//
//    fd = open("tests/test_commands/none", O_RDWR);
//
//    option = process_input(fd, &input);
//    test_option = NONE;
//    ck_assert_int_eq(option, test_option); 
//
//    close(fd);
//    fd = open("tests/test_commands/ls", O_RDWR);
//
//    option = process_input(fd, &input);
//    test_option = LS_NID;
//    ck_assert_int_eq(option, test_option); 
//
//    close(fd);
//    fd = open("tests/test_commands/ls_l", O_RDWR);
//
//    option = process_input(fd, &input);
//    test_option = LS_NID_BID;
//    ck_assert_int_eq(option, test_option); 
//
//    close(fd);
//    fd = open("tests/test_commands/sync", O_RDWR);
//
//    option = process_input(fd, &input);
//    test_option = SYNC;
//    ck_assert_int_eq(option, test_option); 
//
//    close(fd);
//}
//END_TEST
//
//
//START_TEST (test_check_impact)
//{
//    char buffer[] = "add block 21 *\n";
//
//    bool_t result = check_block_impact(buffer);
//    ck_assert_int_eq(result, TRUE);
//
//    char buffer2[] = "add block 21\n";
//    result = check_block_impact(buffer2);
//    ck_assert_int_eq(result, FALSE);
//}
//END_TEST
//
//
//START_TEST (test_check_number)
//{
//    bool_t status = check_number("10");
//    ck_assert_int_eq(status, TRUE);
//
//    status = check_number("cat");
//    ck_assert_int_eq(status, FALSE);
//
//}
//END_TEST
//
//
//START_TEST (test_parse_input)
//{
//    input_t input; 
//    input.option = NONE;
//    input.buffer = (char*)malloc(100 * sizeof(char));
//
//    strcpy(input.buffer, "add node 10\n");
//
//    status_t result = parse_input(&input); 
//    ck_assert_int_eq(result, SUCCESS);
//    ck_assert_str_eq(input.cmd, "add");
//    ck_assert_str_eq(input.typ, "node");
//    ck_assert_str_eq(input.nid, "10");
//
//    strcpy(input.buffer, "add block cat 3\n");
//    result = parse_input(&input); 
//    ck_assert_int_eq(result, SUCCESS);
//    ck_assert_str_eq(input.cmd, "add");
//    ck_assert_str_eq(input.typ, "block");
//    ck_assert_str_eq(input.bid, "cat");
//    ck_assert_str_eq(input.nid, "3");
//
//    strcpy(input.buffer, "&   %$\n");
//    result = parse_input(&input); 
//    ck_assert_int_eq(result, FAIL);
//
//    free(input.buffer);
//    free(input.typ);
//    free(input.cmd);
//
//}
//END_TEST
//
//
//START_TEST (test_check_add_block)
//{
//    input_t input; 
//    input.option = NONE;
//    input.unsynced = NULL;
//    input.buffer = (char*)malloc(100 * sizeof(char));
//    strcpy(input.buffer, "add block cat 1\n");
//    input.unsynced = add_node(input.unsynced, "\0", 1);
//
//    parse_input(&input);
//
//    check_add_block(&input);
//    ck_assert_str_eq(input.unsynced->bid, "cat");
//    free_input(&input, 'b');
//    free_list(input.unsynced);
//}
//END_TEST
//
//START_TEST (test_check_add_block_when_empty)
//{
//    input_t input; 
//    input.option = NONE;
//    input.unsynced = NULL;
//    input.buffer = (char*)malloc(100 * sizeof(char));
//    strcpy(input.buffer, "add block cat 1\n");
//
//    parse_input(&input);
//
//    check_add_block(&input);
//    ck_assert_str_eq(input.unsynced->bid, "cat");
//    free_input(&input, 'b');
//    free_list(input.unsynced);
//}
//END_TEST
//
//
//
//START_TEST (test_check_add_node)
//{
//    input_t input; 
//    input.unsynced = NULL;
//    input.buffer = (char*)malloc(100 * sizeof(char));
//    strcpy(input.buffer, "add node 2\n");
//    parse_input(&input);
//
//    check_add_node(&input);
//    ck_assert_int_eq(input.unsynced->nid, 2);
//
//    strcpy(input.buffer, "add node 1\n");
//    parse_input(&input);
//    check_add_node(&input);
//    ck_assert_int_eq(input.unsynced->nid, 1);
//
//    free_input(&input, 'n');
//    free_list(input.unsynced);
//}
//
//
//START_TEST (test_check_rm_node)
//{
//    input_t input; 
//    input.unsynced = NULL;
//    input.buffer = (char*)malloc(100 * sizeof(char));
//    strcpy(input.buffer, "rm node 1\n");
//
//    input.unsynced = add_node(input.unsynced, "\0", 2);
//    input.unsynced = add_node(input.unsynced, "\0", 1);
//
//    parse_input(&input);
//    check_rm_node(&input);
//    ck_assert_int_eq(input.unsynced->nid, 2);
//
//    strcpy(input.buffer, "rm node 2\n");
//    parse_input(&input);
//    check_rm_node(&input);
//
//    ck_assert_ptr_null(input.unsynced); 
//
//    // remove from empty
//    strcpy(input.buffer, "rm node 2\n");
//    parse_input(&input);
//    check_rm_node(&input);
//
//    ck_assert_ptr_null(input.unsynced); 
//
//    free_input(&input, 'n');
//    free_list(input.unsynced);
//}
//
//
//START_TEST (test_check_rm_block)
//{
//
//    input_t input; 
//    input.unsynced = NULL;
//    input.buffer = (char*)malloc(100 * sizeof(char));
//    strcpy(input.buffer, "rm block dog\n");
//
//    input.unsynced = add_node(input.unsynced, "dog", 2);
//    input.unsynced = add_node(input.unsynced, "dog", 1);
//
//     parse_input(&input);
//
//    check_rm_block(&input);
//
//    ck_assert_int_eq(input.unsynced->bid[0], 0);
//    ck_assert_int_eq(input.unsynced->next->bid[0], 0);
//
//    free_input(&input, 'b');
//    free_list(input.unsynced);
//    
//}
//
//START_TEST (test_proces_command)
//{
//
//    input_t input; 
//    input.unsynced = NULL;
//    input.buffer = (char*)malloc(100 * sizeof(char));
//    strcpy(input.buffer, "add node 10\n");
//
//    input.unsynced = NULL;
//
//    process_commands(&input);
//
//    ck_assert_int_eq(input.unsynced->nid, 10);
//
//    free_input(&input, 'n');
//    free_list(input.unsynced);
//    
//}
//


END_TEST

Suite * test_options(void)
{
    Suite       *suite;
    TCase       *core;

    suite = suite_create("Test Options");
    core = tcase_create("Core");

//    tcase_add_test(core, test_process_input);
//    tcase_add_test(core, test_get_cmd_type_stdin_buffer);
//    tcase_add_test(core, test_check_impact);
//    tcase_add_test(core, test_check_number);
//    tcase_add_test(core, test_parse_input);
//    tcase_add_test(core, test_check_add_block);
//    tcase_add_test(core, test_check_add_block_when_empty);
//    tcase_add_test(core, test_check_add_node);
//    tcase_add_test(core, test_check_rm_node);
//    tcase_add_test(core, test_check_rm_block);
//    tcase_add_test(core, test_proces_command);
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

