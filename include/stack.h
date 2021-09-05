#ifndef _STACK_H
#define _STACK_H
#include <list.h>
typedef struct list stack;
#define stack_init list_init
#define stack_destroy list_destroy
#endif
