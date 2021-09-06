#include <check.h>
#include <test_hashtbl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static hashtbl * p_hashtbl = NULL;

static int8_t test_compare(const void * p_key1, const void * p_key2)
{
    hashtbl_elem * p_data1 = (void *)p_key1;
    hashtbl_elem * p_data2 = (void *)p_key2;
    return (p_data1 < p_data2) ? -1 : ((p_data1 == p_data2) ? 0 : 1);
}

static void start_hashtbl(void)
{
    p_hashtbl = hashtbl_init(10, NULL, NULL, test_compare); 
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
                                                                  "greeting",
                                                                  "Hello"))));     
    ck_assert_int_eq(1, hashtbl_size(p_hashtbl));
} END_TEST

START_TEST(test_hashtbl_value)
{
    hashtbl_insert(p_hashtbl, "greeting", "Hello");
    ck_assert_int_eq(0, strcmp("Hello", hashtbl_value(p_hashtbl, "greeting")));
} END_TEST

START_TEST(test_hashtbl_insert_conflict)
{
     ck_assert_int_eq(0, strcmp("Hello", 
                              (char *)hashtbl_data(hashtbl_insert(p_hashtbl,
                                                                  "greeting",
                                                                  "Hello"))));
      ck_assert(NULL == hashtbl_insert(p_hashtbl, "greeting", "Hello"));     
} END_TEST

START_TEST(test_hashtbl_delete)
{
    hashtbl_insert(p_hashtbl, "greeting", "hello");    
    ck_assert_int_eq(1, hashtbl_size(p_hashtbl));
    hashtbl_delete(p_hashtbl, "greeting");
    ck_assert_int_eq(0, hashtbl_size(p_hashtbl));
    ck_assert(NULL == hashtbl_value(p_hashtbl, "greeting"));
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
    tcase_add_test(p_core, test_hashtbl_value);
    tcase_add_test(p_core, test_hashtbl_insert_conflict);
    tcase_add_test(p_core, test_hashtbl_delete);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}
