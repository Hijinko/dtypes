#include <check.h>
#include <test_set.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static set * p_set1 = NULL;
static set * p_set2 = NULL;
static int8_t num1 = 10;
static int8_t num2 = 20;
static int8_t num3 = 30;
static int8_t num4 = 40;
static int8_t num5 = 50;
static int8_t num6 = 60;
static int8_t num7 = 70;

static int8_t test_compare(const void * key1, const void * key2)
{
    int num1 = *(int *)key1;
    int num2 = *(int *)key2;
    return (num1 < num2) ? -1: ((num1 == num2) ? 0: 1);
}

static void start_set(void)
{
    p_set1 = set_init(NULL, test_compare); 
    p_set2 = set_init(NULL, test_compare); 

    set_add(p_set1, &num1);
    set_add(p_set1, &num2);
    set_add(p_set1, &num3);
    set_add(p_set1, &num4);
    set_add(p_set1, &num7);
    
    set_add(p_set2, &num4);
    set_add(p_set2, &num5);
    set_add(p_set2, &num6);
    set_add(p_set2, &num7);
}

static void teardown_set(void)
{
    set_destroy(p_set1);
    set_destroy(p_set2);
}

START_TEST(test_set_size){
    ck_assert_int_eq(5, set_size(p_set1));
    ck_assert_int_eq(4, set_size(p_set2));
} END_TEST

START_TEST(test_set_add){    
    ck_assert(NULL == set_add(p_set1, &num1));
} END_TEST

START_TEST(test_set_union){
    set * p_set = set_union(p_set1, p_set2);
    ck_assert_int_eq(7, set_size(p_set));
    set_destroy(p_set);
} END_TEST

START_TEST(test_set_difference){
    set * p_set = set_difference(p_set1, p_set2);
    ck_assert_int_eq(5, set_size(p_set));
    set_destroy(p_set);
} END_TEST

START_TEST(test_set_is_member){
    ck_assert(true == set_is_member(p_set1, &num1));
    ck_assert(false == set_is_member(p_set2, &num1));
} END_TEST

// create suite
Suite * suite_set(void)
{
    Suite * p_suite = suite_create("Set");
    TCase * p_core = tcase_create("Core");
    // add test cases 
    tcase_add_checked_fixture(p_core, start_set, teardown_set);
    tcase_add_test(p_core, test_set_size);
    tcase_add_test(p_core, test_set_add);
    tcase_add_test(p_core, test_set_union);
    tcase_add_test(p_core, test_set_difference);
    tcase_add_test(p_core, test_set_is_member);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}

