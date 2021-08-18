#include <list.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * @brief element in a list that holds the data
 * @param p_data data the node holds
 * @param p_prev pointer to the previous element
 * @param p_next pointer to the next element
 */
struct elem {
    const void * p_data;
    struct elem * p_prev;
    struct elem * p_next;
};

/*
 * @brief list data type
 * @param size the number of elements in the list
 * @param p_destroy user defined function destroy the data in the list
 * @param p_compare user defined function to compare the data in the list
 * @param p_head pointer to the first element in the list
 * @param p_tail pointer to the last element in the list
 */
struct list {
    int32_t size;
    void (* p_destroy)(void * p_data);
    void (* p_compare)(const void * p_key1, const void * p_key2);
    elem * p_head;
    elem * p_tail;
};

// setup functions

/*
 * @brief creates and initializes a new list
 * @param p_destroy user defined function destroy the data in the list
 * @param p_compare user defined function to compare the data in the list
 * @return pointer to the new list or NULL on error
 */
list * list_init(void (* p_destroy)(void * p_data), void (* p_compare)(const void * p_key1, const void * p_key2))
{
    // create the list
    list * p_list = calloc(1, sizeof(*p_list));
    // if there was an error creating the list then return NULL
    if (NULL == p_list){
        perror("List: ");
        return NULL;
    }
    // set the initial values of the list
    p_list->size = 0;
    p_list->p_destroy = p_destroy;
    p_list->p_compare = p_compare;
    p_list->p_head = NULL;
    p_list->p_tail = NULL;
    return p_list;
}

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
