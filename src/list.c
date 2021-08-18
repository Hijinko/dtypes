#include <list.h>
#include <stdint.h>

/*
 * @brief element in a list that holds the data
 * @param p_data data the node holds
 */
struct elem {
    const void * p_data;
    struct elem * p_prev;
    struct elem * p_next;
};

struct list {
    int32_t size;
    void (* p_destroy)(void * p_data);
    void (* p_compare)(const void * p_key1, const void * p_key2);
    elem * p_head;
    elem * p_tail;
};

// setup
list * list_init(void (* p_destroy)(void * p_data), void (* p_compare)(const void * p_key1, const void * p_key2));
int8_t list_destroy(list * p_list);
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
