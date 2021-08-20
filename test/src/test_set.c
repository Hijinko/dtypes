#include <check.h>
#include <test_set.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static set * p_set = NULL;
static int8_t num1 = 10;
static int8_t num2 = 20;
static int8_t num3 = 30;
static int8_t num4 = 40;

static int8_t test_compare(const void * key1, const void * key2)
{
    int num1 = *(int *)key1;
    int num2 = *(int *)key2;
    return (num1 < num2) ? -1: ((num1 == num2) ? 0: 1);
}

static void start_set(void)
{
    p_set = set_init(NULL, test_compare); 
    set_add(p_set, &num1);
    set_add(p_set, &num2);
    set_add(p_set, &num3);
    set_add(p_set, &num4);
}

static void teardown_set(void)
{
    set_destroy(p_set);
}

START_TEST(test_set_size){
    ck_assert_int_eq(4, set_size(p_set));
} END_TEST

// create suite
Suite * suite_set(void)
{
    Suite * p_suite = suite_create("Set");
    TCase * p_core = tcase_create("Core");
    // add test cases 
    tcase_add_checked_fixture(p_core, start_set, teardown_set);
    tcase_add_test(p_core, test_set_size);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}

