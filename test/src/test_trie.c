#include <check.h>
#include <test_trie.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static trie * p_trie = NULL;

static int8_t test_compare(const void * key1, const void * key2)
{
    int num1 = *(int *)key1;
    int num2 = *(int *)key2;
    return (num1 < num2) ? -1: ((num1 == num2) ? 0: 1);
}

static void start_trie(void)
{
    p_trie = trie_init(NULL, test_compare); 
}

static void teardown_trie(void)
{
    trie_destroy(p_trie);
}

START_TEST(test_trie_init){
    trie * p_trie1 = trie_init(NULL, test_compare);
    ck_assert(NULL != p_trie1);
    trie_destroy(p_trie1);
    trie * p_trie2 = trie_init(NULL, NULL);
    ck_assert(NULL == p_trie2);
} END_TEST

// create suite
Suite * suite_trie(void)
{
    Suite * p_suite = suite_create("Trie");
    TCase * p_core = tcase_create("Core");
    // add test cases 
    tcase_add_checked_fixture(p_core, start_trie, teardown_trie);
    tcase_add_test(p_core, test_trie_init);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}

