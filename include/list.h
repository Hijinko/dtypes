#ifndef _LIST_H
#define _LIST_H
#include <stdint.h>
typedef struct node node;
typedef struct list list;
// setup
list * list_init(void (* p_destroy)(const void * p_data), void (* p_compare)(void * p_key1, void * p_key2));
int8_t list_destroy(list * p_list);
// adding data
node * list_append(list * p_list, const void * p_data);
node * list_prepend(list * p_list, const void * p_data);
node * list_ins_next(list * p_list, node * p_node, const void * p_data);
// removing data
int8_t list_delete(list * p_list, node * p_node);
int8_t list_rm_next(list * p_list, node * p_node);
node * list_remove(list * p_list, const void * p_data);
// getters
node * list_head(list * p_list);
node * list_tail(list * p_list);
int32_t list_size(list * p_list);
#endif
