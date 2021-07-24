#include <check.h>
#include "../include/list.h"

START_TEST (test_init_list)
{
    node_t *n =     init_list("dog", 1);
    ck_assert_ptr_nonnull(n);
    ck_assert_str_eq(n->bid, "dog");
    ck_assert_int_eq(n->nid, 1);
    free_list(n);
}
END_TEST

START_TEST (test_add_node_to_head)
{
    node_t *n =     init_list("dog", 1);
    n = add_node(n, "cat", 2);
    ck_assert_ptr_nonnull(n);
    ck_assert_str_eq(n->bid, "cat");
    ck_assert_int_eq(n->nid, 2);
    ck_assert_ptr_nonnull(n->next);
    ck_assert_str_eq(n->next->bid, "dog");
    ck_assert_int_eq(n->next->nid, 1);
    free_list(n);
}
END_TEST

START_TEST (test_add_block_to_node)
{
    node_t *n =     init_list("dog", 1);
    n = add_node(n, "cat", 2);
    n = add_block(n, "giraffe", 1);
    n = add_block(n, "zebra", 2);
    print_list(n);
    ck_assert_ptr_nonnull(n);
    ck_assert_str_eq(n->bid, "zebra");
    ck_assert_str_eq(n->next->bid, "giraffe");
    free_list(n);
}
END_TEST


Suite * test_list(void)
{
    Suite       *suite;
    TCase       *core;

    suite = suite_create("test List");
    core = tcase_create("Core");

    tcase_add_test(core, test_init_list);
    tcase_add_test(core, test_add_node_to_head);
    tcase_add_test(core, test_add_block_to_node);
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
