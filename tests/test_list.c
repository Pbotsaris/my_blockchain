#include <check.h>

//#include "../include/test.h"
#include "../include/list.h"


#define BUFF_SIZE 100

START_TEST (test_add_node_to_head)
{
    node_t *n =    NULL;
    n = add_node(n, 2);
    n = add_node(n, 3);
    ck_assert_ptr_nonnull(n); 
    ck_assert_int_eq(n->nid, 3);
    ck_assert_int_eq(n->next->nid, 2);
    ck_assert_int_eq(n->blocks->maxlen, BLOCKS_INIT_MAX_LEN);
    ck_assert_int_eq(n->blocks->index, 0);
    free_list(n);
}
END_TEST

START_TEST (test_add_block_to_node)
{
    node_t *n = NULL;
    n = add_node(n, 2);
    n = add_block(n, "cat", 2);
    ck_assert_str_eq(n->blocks->bids[0], "cat");
    free_list(n);
}
END_TEST


START_TEST (test_add_many_blocks_to_node)
{
    node_t *n = NULL;
    n = add_node(n, 2);
    n = add_block(n, "cat", 2);
    n = add_block(n, "dogs", 2);
    ck_assert_str_eq(n->blocks->bids[0], "cat");
    ck_assert_str_eq(n->blocks->bids[1], "dogs");
    free_list(n);
}
END_TEST


START_TEST (test_add_dup_block_to_node)
{
    node_t *n = NULL;
    n = add_node(n, 2);
    n = add_block(n, "cat", 2);
    n = add_block(n, "cat", 2);
    ck_assert_str_eq(n->blocks->bids[0], "cat");
    ck_assert_str_eq(n->blocks->bids[1], "\0");
    free_list(n);
}
END_TEST




START_TEST (test_remove_node)
{
    node_t *n = NULL;
    n = add_node(n, 3);
    n = add_node(n, 2);
    n = add_node(n, 1);
    ck_assert_int_eq(n->next->nid, 2);
    /* remove from mid */
    n = remove_node(n, 2);
    ck_assert_int_eq(n->next->nid, 3);
    /* remove from head */
    n = add_node(n, 2);
    n = remove_node(n, 2);
    ck_assert_int_eq(n->nid, 1);
    /* remove from tail */
    n = add_node(n, 2);
    n = remove_node(n, 3);
    ck_assert_int_eq(n->next->nid, 1);

    free_list(n);
}
END_TEST


START_TEST (test_remove_til_empty)
{
    node_t *n =  NULL;

    n = add_node(n, 3);
    n = add_node(n, 2);
    n = add_node(n, 1);
    n = remove_node(n, 2);
    n = remove_node(n, 3);
    n = remove_node(n, 1);
    ck_assert_ptr_null(n); 
}
END_TEST


START_TEST (test_remove_block)
{
    node_t *n = NULL;

    n = add_node(n, 3);
    n = add_node(n, 2);
    n = add_node(n, 1);
    n = add_block(n, "cat", 1);
    n = add_block(n, "dog", 1);
    n = add_block(n, "camel", 1);
    n = add_block(n, "cow", 1);

    /* remove first node */
    n = remove_block(n , "cat", 1);
    ck_assert_str_eq(n->blocks->bids[0], "dog");
    ck_assert_str_eq(n->blocks->bids[3], "\0");


    n = remove_block(n , "cow", 1);

    ck_assert_str_eq(n->blocks->bids[2], "\0");
    ck_assert_str_eq(n->blocks->bids[1], "camel");

    free_list(n);
}
END_TEST



START_TEST (test_node_exists)
{
    node_t *n =    NULL;

    n = add_node(n, 4);
    n = add_node(n, 3);
    n = add_node(n, 2);
    n = add_node(n, 1);

    /* return pos in list counting from 0  */
    int count = node_exists(n, 4);
    ck_assert_int_eq(count, 3);

    count = node_exists(n, 1);
    ck_assert_int_eq(count, 0);

    /* not found  */
    count = node_exists(n, 10);
    ck_assert_int_eq(count, -1);

    free_list(n);
}
END_TEST
//
START_TEST (test_block_exists)
{
    node_t *n =   NULL; 
    n = add_node(n, 4);
    n = add_node(n, 3);
    n = add_node(n, 2);
    n = add_node(n, 1);


    n = add_block(n,"dog", 1);
    n = add_block(n,"cat", 1);

    /* Found Match  */
    bool_t result = block_exists(n, "dog", 1);
    ck_assert_int_eq(result, TRUE);


    /* No match  */
    result = block_exists(n, "camel", 1);
    ck_assert_int_eq(result, FALSE);


    /* Node not found  */
    result = block_exists(n, "dog", 10);
    ck_assert_int_eq(result, FALSE);

    free_list(n);
}
END_TEST


START_TEST (test_add_block_til_grow)
{
    node_t *n =   NULL; 
    n = add_node(n, 1);

    n = add_block(n,"dog", 1);
    n = add_block(n,"cat", 1);
    n = add_block(n,"camel", 1);
    n = add_block(n,"cow", 1);
    n = add_block(n,"dolphin", 1);
    n = add_block(n,"giraffe", 1);

    ck_assert_int_eq(n->blocks->maxlen, 10);
    /* index is set for the next entry */
    ck_assert_int_eq(n->blocks->index, 6);

    ck_assert_str_eq(n->blocks->bids[5], "giraffe");
    ck_assert_str_eq(n->blocks->bids[4], "dolphin");
    print_block_list(n);
//
    free_list(n);
}
END_TEST



Suite * test_list(void)
{
    Suite       *suite;
    TCase       *core;

    suite = suite_create("Test List");
    core = tcase_create("Core");

    tcase_add_test(core, test_add_node_to_head);
    tcase_add_test(core, test_add_block_to_node);
    tcase_add_test(core, test_add_many_blocks_to_node);
    tcase_add_test(core, test_add_dup_block_to_node);
    tcase_add_test(core, test_remove_node);
    tcase_add_test(core, test_remove_til_empty);
    tcase_add_test(core, test_remove_block);
    tcase_add_test(core, test_node_exists);
    tcase_add_test(core, test_block_exists);
    tcase_add_test(core, test_add_block_til_grow);
    suite_add_tcase(suite, core);

    return(suite);
}


int main(void)
{
    int       failed;
    Suite     *suite;
    SRunner   *runner;

    suite = test_list();
    runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return(failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);

}

