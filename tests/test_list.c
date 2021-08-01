#include "../include/list.h"
#include <check.h>

#include "../include/test.h"


#define BUFF_SIZE 100

START_TEST (test_init_list)
{
    unsynced *n =     init_list("dog", 1);
    /* ck_assert_ptr_nonnull(n); */
    ck_assert_str_eq(n->bid, "dog");
    ck_assert_int_eq(n->nid, 1);
    free_list(n);
}
END_TEST

START_TEST (test_add_unsyncedo_head)
{
    unsynced *n =     init_list("dog", 1);
    n = add_node(n, "cat", 2);
    /* ck_assert_ptr_nonnull(n); */
    ck_assert_str_eq(n->bid, "cat");
    ck_assert_int_eq(n->nid, 2);
    /* ck_assert_ptr_nonnull(n->next); */
    ck_assert_str_eq(n->next->bid, "dog");
    ck_assert_int_eq(n->next->nid, 1);
    free_list(n);
}
END_TEST

START_TEST (test_add_block_to_node)
{
    unsynced *n =     init_list("dog", 1);
    n = add_node(n, "cat", 2);
    n = add_block(n, "giraffe", 1);
    n = add_block(n, "zebra", 2);
    /* ck_assert_ptr_nonnull(n); */
    ck_assert_str_eq(n->bid, "zebra");
    ck_assert_str_eq(n->next->bid, "giraffe");
    free_list(n);
}
END_TEST

START_TEST (test_remove_node)
{
    unsynced *n =     init_list("dog", 3);
    n = add_node(n, "cat", 2);
    n = add_node(n, "zebra", 1);
    ck_assert_int_eq(n->next->nid, 2);
    /* remove from mid */
    n = remove_node(n, 2);
    ck_assert_int_eq(n->next->nid, 3);
    /* remove from head */
    n = add_node(n, "cat", 2);
    n = remove_node(n, 2);
    ck_assert_int_eq(n->nid, 1);
    /* remove from tail */
    n = add_node(n, "cat", 2);
    n = remove_node(n, 3);
    ck_assert_int_eq(n->next->nid, 1);

    free_list(n);
}
END_TEST

START_TEST (test_remove_til_empty)
{
    unsynced *n =     init_list("dog", 3);
    n = add_node(n, "cat", 2);
    n = add_node(n, "zebra", 1);
    n = remove_node(n, 2);
    n = remove_node(n, 3);
    n = remove_node(n, 1);
    /* ck_assert_ptr_ne(n); */
}
END_TEST


START_TEST (test_remove_block)
{
    unsynced *n =     init_list("cat", 3);
    n = add_node(n, "cat", 2);
    n = add_node(n, "cat", 1);
    n = remove_block(n , "cat");

    ck_assert_int_eq(n->bid[0], 0);
    ck_assert_int_eq(n->next->bid[0], 0);
    ck_assert_int_eq(n->next->next->bid[0], 0);
    /* ck_assert_ptr_nonnull(n); */

    free_list(n);
}
END_TEST


START_TEST (test_node_exists)
{
    unsynced *n =     init_list("cat", 4);
    n = add_node(n, "cat", 3);
    n = add_node(n, "cat", 2);
    n = add_node(n, "cat", 1);

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

START_TEST (test_block_exists)
{
    unsynced *n =     init_list("dog", 4);
    n = add_node(n, "dog", 3);
    n = add_node(n, "cat", 2);
    n = add_node(n, "cat", 1);

    /* return the pos of first found  */
    int count = block_exists(n, "dog");
    ck_assert_int_eq(count, 2);

    count = block_exists(n, "cat");
    ck_assert_int_eq(count, 0);

    /* not found  */
    count = block_exists(n, "zebra");
    ck_assert_int_eq(count, -1);

    free_list(n);
}
END_TEST


Suite * test_list(void)
{
    Suite       *suite;
    TCase       *core;

    suite = suite_create("Test List");
    core = tcase_create("Core");

    tcase_add_test(core, test_init_list);
    tcase_add_test(core, test_add_unsyncedo_head);
    tcase_add_test(core, test_add_block_to_node);
    tcase_add_test(core, test_remove_node);
    tcase_add_test(core, test_remove_til_empty);
    tcase_add_test(core, test_remove_block);
    tcase_add_test(core, test_node_exists);
    tcase_add_test(core, test_block_exists);
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

