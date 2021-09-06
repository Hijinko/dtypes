#include <check.h>
#include <test_hashtbl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static * p_hashtbl = NULL;

static void start_hashtbl(void)
{
    p_hashtbl = hashtbl_init(NULL, NULL, NULL, NULL); 
}

static void teardown_hashtbl(void)
{
    hashtbl_destroy(p_hashtbl);
}

START_TEST(test_hashtbl_init)
{
    ck_assert(NULL != p_hashtbl);
} END_TEST

// create suite
Suite * suite_hashtbl(void)
{
    Suite * p_suite = suite_create("Hash Table");
    TCase * p_core = tcase_create("Core");
    // add test cases 
    tcase_add_checked_fixture(p_core, start_hashtbl, teardown_hashtbl);
    tcase_add_test(p_core, test_hashtbl_init);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}
