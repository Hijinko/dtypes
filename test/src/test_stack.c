#include <check.h>
#include <test_stack.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static stack * p_stack = NULL;
int num = 1;

static int8_t test_compare(const void * key1, const void * key2)
{
    int num1 = *(int *)key1;
    int num2 = *(int *)key2;
    return (num1 < num2) ? -1: ((num1 == num2) ? 0: 1);
}

static void start_stack(void)
{
    p_stack = stack_init(NULL, test_compare); 
    stack_push(p_stack, &num);
}

static void teardown_stack(void)
{
    stack_destroy(p_stack);
}

START_TEST(test_stack_init)
{
    ck_assert(NULL != p_stack);
} END_TEST

START_TEST(test_stack_push)
{
    int num10 = 10;
    ck_assert(NULL != stack_push(p_stack, &num10));
    ck_assert_int_eq(10, *(int *)(stack_data(stack_peek(p_stack))));
} END_TEST

START_TEST(test_stack_pop)
{
    ck_assert_int_eq(num, *(int *)(stack_pop(p_stack)));
} END_TEST

// create suite
Suite * suite_stack(void)
{
    Suite * p_suite = suite_create("Stack");
    TCase * p_core = tcase_create("Core");
    // add test cases 
    tcase_add_checked_fixture(p_core, start_stack, teardown_stack);
    tcase_add_test(p_core, test_stack_init);
    tcase_add_test(p_core, test_stack_push);
    tcase_add_test(p_core, test_stack_pop);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}
