#include <check.h>
#include <test_stack.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static stack * p_stack = NULL;

static int8_t test_compare(const void * key1, const void * key2)
{
    int num1 = *(int *)key1;
    int num2 = *(int *)key2;
    return (num1 < num2) ? -1: ((num1 == num2) ? 0: 1);
}

static void start_stack(void)
{
    p_stack = stack_init(NULL, test_compare); 
}

static void teardown_stack(void)
{
    stack_destroy(p_stack);
}

START_TEST(test_stack_init){
    ck_assert(NULL != p_stack);
    queue_destroy(p_stack);
} END_TEST

// create suite
Suite * suite_stack(void)
{
    Suite * p_suite = suite_create("Stack");
    TCase * p_core = tcase_create("Core");
    // add test cases 
    tcase_add_checked_fixture(p_core, start_stack, teardown_stack);
    tcase_add_test(p_core, test_stack_init);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}