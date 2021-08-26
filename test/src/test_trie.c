#include <check.h>
#include <test_trie.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static trie * p_trie = NULL;

static int8_t test_compare(const void * key1, const void * key2)
{
    char * str1 = (char *)key1;
    char * str2 = (char *)key2;
    return strcmp(str1, str2);
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

START_TEST(test_trie_insert){
    ck_assert(NULL != trie_insert(p_trie, "a"));
} END_TEST

// create suite
Suite * suite_trie(void)
{
    Suite * p_suite = suite_create("Trie");
    TCase * p_core = tcase_create("Core");
    // add test cases 
    tcase_add_checked_fixture(p_core, start_trie, teardown_trie);
    tcase_add_test(p_core, test_trie_init);
    tcase_add_test(p_core, test_trie_insert);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}

