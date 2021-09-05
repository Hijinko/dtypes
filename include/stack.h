#ifndef _STACK_H
#define _STACK_H
#include <list.h>
typedef struct list stack;
typedef struct elem member;
const void * stack_pop(stack * p_stack);
#define stack_init list_init
#define stack_destroy list_destroy
#define stack_push list_append
#define stack_data list_data
#define stack_peek list_tail
#define stack_size list_size
#endif
