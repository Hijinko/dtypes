#include <check.h>
#include <test_hashtbl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static hashtbl * p_hashtbl = NULL;

static void start_hashtbl(void)
{
    p_hashtbl = hashtbl_init(10, NULL, NULL, NULL); 
}

static void teardown_hashtbl(void)
{
    hashtbl_destroy(p_hashtbl);
}

START_TEST(test_hashtbl_init)
{
    ck_assert(NULL != p_hashtbl);
} END_TEST

START_TEST(test_hashtbl_size)
{
    ck_assert_int_eq(0, hashtbl_size(p_hashtbl));
} END_TEST

START_TEST(test_hashtbl_insert)
{
    ck_assert_int_eq(0, strcmp("Hello", 
                              (char *)hashtbl_data(hashtbl_insert(p_hashtbl, 
                                                                  "Hello"))));     
    ck_assert_int_eq(1, hashtbl_size(p_hashtbl));
} END_TEST

// create suite
Suite * suite_hashtbl(void)
{
    Suite * p_suite = suite_create("Hash Table");
    TCase * p_core = tcase_create("Core");
    // add test cases 
    tcase_add_checked_fixture(p_core, start_hashtbl, teardown_hashtbl);
    tcase_add_test(p_core, test_hashtbl_init);
    tcase_add_test(p_core, test_hashtbl_size);
    tcase_add_test(p_core, test_hashtbl_insert);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}
