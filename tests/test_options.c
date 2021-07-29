#include <check.h>
#include "../include/list.h"
#include "../include/test.h"


#define BUFF_SIZE 100


char* load_from_file(const char *path)
{
   char *buffer = malloc(sizeof(char)*BUFF_SIZE);
   int fd = open(path, O_RDONLY);
   int read_size = read(fd, buffer, BUFF_SIZE);
   buffer[read_size] = '\0';
   close(fd); 

   return buffer;
}


START_TEST (test_get_cmd_type_stdin_buffer)
{
   int len = 0;
   char *buffer = load_from_file("tests/test_commands/add_node.txt");
   char *cmd = get_input(buffer, &len);
   char *type = get_input(buffer, &len);

   ck_assert_str_eq(cmd, "add");
   ck_assert_str_eq(type, "node");
   free(buffer);
}
END_TEST

START_TEST (get_option_from_stdin_buffer)
{
   int len = 0;
   char *buffer = load_from_file("tests/test_commands/add_node.txt");
   input_t input;

   input.cmd = get_input(buffer, &len);
   input.typ = get_input(buffer, &len);
   option_t result = get_option(&input);

   ck_assert_int_eq(result, 4); // NONE

//typedef enum{
//    LS_NID,
//    LS_NID_BID,
//    SYNC,
//    QUIT,
//    NONE,
//    ERROR_OPTION,
//} option_t;
//


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

