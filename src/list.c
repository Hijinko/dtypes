#include <list.h>
#include <stdint.h>
struct node {
    void * p_data;
    struct node * p_prev;
    struct node * p_next;
};

struct list {
    int32_t size;
    void (* p_destroy)(void * p_data);
    void (* p_compare)(const void * p_key1, const void * p_key2);
    node * p_head;
    node * p_tail;
};

// setup
list * list_init(void (* p_destroy)(void * p_data), void (* p_compare)(const void * p_key1, const void * p_key2));
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
