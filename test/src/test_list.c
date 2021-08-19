#include <check.h>
#include <test_list.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static list * p_list = NULL;
static int8_t test_compare(const void * key1, const void * key2)
{
    return (int8_t)(strcmp((char *)key1, (char *)key2));
}

static void start_list(void)
{
    p_list = list_init(NULL, test_compare); 
    list_append(p_list, "Yo");
    list_append(p_list, "She");
    list_append(p_list, "He");
    list_append(p_list, "They");
}

static void teardown_list(void)
{
    list_destroy(p_list);
}

START_TEST(test_list_size){
    ck_assert_int_eq(4, list_size(p_list));
} END_TEST

START_TEST(test_list_append){
    ck_assert(NULL != list_append(p_list, "HELLO"));
    ck_assert_int_eq(5, list_size(p_list));
} END_TEST

START_TEST(test_list_prepend){
    ck_assert(NULL != list_prepend(p_list, "SUP"));
    ck_assert_int_eq(5, list_size(p_list));
} END_TEST

START_TEST(test_list_ins_next){
    ck_assert(NULL != list_ins_next(p_list, NULL, "Yellow")); 
} END_TEST

START_TEST(test_list_head){ 
    ck_assert_str_eq("Yo", (char *)(list_data(list_head(p_list))));
} END_TEST

// create suite
Suite * suite_list(void)
{
    Suite * p_suite = suite_create("List");
    TCase * p_core = tcase_create("Core");
    // add test cases 
    tcase_add_checked_fixture(p_core, start_list, teardown_list);
    tcase_add_test(p_core, test_list_size);
    tcase_add_test(p_core, test_list_append);
    tcase_add_test(p_core, test_list_prepend);
    tcase_add_test(p_core, test_list_ins_next);
    tcase_add_test(p_core, test_list_head);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}

