#ifndef _LIST_H
#define _LIST_H
#include <stdint.h>
typedef struct elem elem;
typedef struct list list;
// setup
list * list_init(void (* p_destroy)(void * p_data), int8_t (* p_compare)(const void * p_key1, const void * p_key2));
void list_destroy(list * p_list);
// adding data
elem * list_append(list * p_list, const void * p_data);
elem * list_prepend(list * p_list, const void * p_data);
elem * list_ins_next(list * p_list, elem * p_elem, const void * p_data);
// removing data
int8_t list_delete(list * p_list, elem * p_elem);
int8_t list_rm_next(list * p_list, elem * p_elem);
elem * list_remove(list * p_list, const void * p_data);
// getters
elem * list_head(list * p_list);
elem * list_tail(list * p_list);
int32_t list_size(list * p_list);
const void * list_data(elem * p_elem);
#endif
