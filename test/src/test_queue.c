#include <check.h>
#include <test_queue.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static queue * p_queue = NULL;
static int8_t num1 = 10;
static int8_t num2 = 20;
static int8_t num3 = 30;
static int8_t num4 = 40;
static int8_t num5 = 50;

static int8_t test_compare(const void * key1, const void * key2)
{
    int num1 = *(int *)key1;
    int num2 = *(int *)key2;
    return (num1 < num2) ? -1: ((num1 == num2) ? 0: 1);
}

static void start_queue(void)
{
    p_queue = queue_init(NULL, test_compare); 
    queue_enqueue(p_queue, &num1);
    queue_enqueue(p_queue, &num2);
    queue_enqueue(p_queue, &num3);
    queue_enqueue(p_queue, &num4);
    queue_enqueue(p_queue, &num5);
}

static void teardown_queue(void)
{
    queue_destroy(p_queue);
}

START_TEST(test_queue_init){
    queue * p_queue1 = queue_init(NULL, NULL);
    ck_assert(NULL != p_queue1);
    queue_destroy(p_queue1);
} END_TEST

START_TEST(test_queue_size){
    ck_assert_int_eq(5, queue_size(p_queue));
} END_TEST

START_TEST(test_queue_peek){
    ck_assert_int_eq(10, *(int8_t *)queue_data(queue_peek(p_queue)));
} END_TEST

START_TEST(test_queue_dequeue){
    queue_dequeue(p_queue);
    ck_assert_int_eq(20, *(int8_t *)queue_data(queue_peek(p_queue)));
} END_TEST

// create suite
Suite * suite_queue(void)
{
    Suite * p_suite = suite_create("Queue");
    TCase * p_core = tcase_create("Core");
    // add test cases 
    tcase_add_checked_fixture(p_core, start_queue, teardown_queue);
    tcase_add_test(p_core, test_queue_init);
    tcase_add_test(p_core, test_queue_size);
    tcase_add_test(p_core, test_queue_peek);
    tcase_add_test(p_core, test_queue_dequeue);
    // add core to suite
    suite_add_tcase(p_suite, p_core);
    return p_suite;
}

