#ifndef _SET_H
#define _SET_H
#include <list.h>
#include <stdbool.h>
typedef struct list set;
typedef struct elem member;
set * set_union(set * p_set1, set * p_set2);
set * set_intersect(set * p_set1, set * p_set2);
set * set_difference(set * p_set1, set * p_set2);
member * set_add(set * p_set, const void * p_data);
bool set_is_member(set * p_set, const void * p_data);
bool set_is_subset(set * p_org_set, set * p_sub_set);
#define set_init list_init
#define set_destroy list_destroy
#define set_remove list_remove
#define set_delete list_delete
#define set_data list_data
#define set_size list_size
#endif
