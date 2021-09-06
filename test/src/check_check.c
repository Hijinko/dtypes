#include <check.h>
#include <stdlib.h>
#include <test_list.h>
#include <test_set.h>
#include <test_queue.h>
#include <test_trie.h>
#include <test_stack.h>
#include <test_hashtbl.h>

int main(void)
{
    int num_failed = 0;
    // create the test suites
    Suite * p_list = suite_list();
    Suite * p_set = suite_set();
    Suite * p_queue = suite_queue();
    Suite * p_trie = suite_trie();
    Suite * p_stack = suite_stack();
    Suite * p_hashtbl = suite_hashtbl();
    // create and add to suite runner
    SRunner * p_srunner = srunner_create(p_list);
    srunner_add_suite(p_srunner, p_set);
    srunner_add_suite(p_srunner, p_queue);
    srunner_add_suite(p_srunner, p_trie);
    srunner_add_suite(p_srunner, p_stack);
    srunner_add_suite(p_srunner, p_hashtbl);
    srunner_set_fork_status(p_srunner, CK_NOFORK);
    // run all test
    srunner_run_all(p_srunner, CK_VERBOSE);
    // save the number of test failed
    num_failed = srunner_ntests_failed(p_srunner);
    srunner_free(p_srunner);
    return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
// end of source
