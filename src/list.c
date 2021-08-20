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
 * @param p_compare user defined function to compare the data in the list
 * @param p_destroy user defined function destroy the data in the list
 * @param p_head pointer to the first element in the list
 * @param p_tail pointer to the last element in the list
 */
struct list {
    int32_t size;
    int8_t (* p_compare)(const void * p_key1, const void * p_key2);
    void (* p_destroy)(void * p_data);
    elem * p_head;
    elem * p_tail;
};

/*
 * @brief create and initialize a list element
 * @param p_data the data for the element
 * @return pointer to the new element else NULL on error
 */
static elem * list_init_elem(const void * p_data)
{
    // an element needs to be created for the data
    elem * p_elem = calloc(1, sizeof(*p_elem));
    if (NULL == p_elem){
        perror("list_init ");
        return NULL;
    }
    // the values for the element need to be set
    p_elem->p_data = p_data;
    p_elem->p_prev = NULL;
    p_elem->p_next = NULL;
    return p_elem;
}

// setup functions

/*
 * @brief creates and initializes a new list
 * @param p_destroy user defined function destroy the data in the list
 * @param p_compare user defined function to compare the data in the list
 * @return pointer to the new list or NULL on error
 */
list * list_init(void (* p_destroy)(void * p_data), int8_t (* p_compare)(const void * p_key1, const void * p_key2))
{
    // create the list
    list * p_list = calloc(1, sizeof(*p_list));
    // if there was an error creating the list then return NULL
    if (NULL == p_list){
        perror("list_init ");
        return NULL;
    }
    // set the initial values of the list
    p_list->size = 0;
    p_list->p_compare = p_compare;
    p_list->p_destroy = p_destroy;
    p_list->p_head = NULL;
    p_list->p_tail = NULL;
    return p_list;
}

/*
 * @brief destroys a list and frees all the allocated memory
 * @param p_list the list to destroy
 */
void list_destroy(list * p_list)
{
    // cant destroy a NULL list
    if (NULL == p_list){
        return;
    }
    // iterate through the list and destroy all the elements
    while (0 < p_list->size){
        list_rm_next(p_list, NULL);
    }
    // the memory for the list has to be freed
    free(p_list);
}

// adding data

/*
 * @brief adds data to the end of a list
 * @param p_list the list to append to
 * @param p_data the data to append to the list
 * @return pointer to the new element in the list else NULL on error
 */
elem * list_append(list * p_list, const void * p_data)
{
    // running the list_ins_next function with list tail as the element
    // adds a new tail element
    return list_ins_next(p_list, p_list->p_tail, p_data);
}

/*
 * @brief adds a new element to the beginning of a list
 * @param p_list the list to prepend to
 * @param p_data the data in the new element
 * @return pointer to the new element else NULL on error
 */
elem * list_prepend(list * p_list, const void * p_data)
{
    // running the list_ins_next function with NULL as the element
    // adds a new head element
    return list_ins_next(p_list, NULL, p_data);
}

/*
 * @brief adds a new element after the element passed in
 * @param p_list the list to insert a new element into
 * @param p_elem the element to insert after
 * @param p_data the data in the new element
 * @return pointer to the newly created element else NULL on error
 */
elem * list_ins_next(list * p_list, elem * p_elem, const void * p_data)
{
    // cant insert into a NULL list or from NULL data
    if ((NULL == p_list) || (NULL == p_data)){
        return NULL;
    }
    // an element needs to be created for the data
    elem * p_new_elem = list_init_elem(p_data); 
    if (NULL == p_new_elem){
        return NULL;
    }
    // if the passed in element is NULL then the user is 
    // inserting at the head of the list
    if (NULL == p_elem){
        // if this is not the first element then the previous head needs to
        // set its prev value
        if (0 != p_list->size){
            p_list->p_head->p_prev = p_new_elem;
        }
        p_new_elem->p_next = p_list->p_head;    
        p_new_elem->p_prev = NULL;
        p_list->p_head = p_new_elem;
    }
    else {
        p_new_elem->p_next = p_elem->p_next;
        p_elem->p_next = p_new_elem;
        p_new_elem->p_prev = p_elem;
    }
    // check if inserting the new tail
    if (p_list->p_tail == p_elem){
        p_list->p_tail = p_new_elem;
    }
    p_list->size++;
    return p_new_elem;
}
// removing data

/*
 * @brief deletes and frees the element passed in
 * @param p_list the list the element to delete is in
 * @param p_elem the element to delete
 * @return -1 on error else 0
 */
int8_t list_delete(list * p_list, elem * p_elem)
{
    // cant delete an element from a NULL or empty list or from NULL data
    if ((NULL == p_list) || (0 >= p_list->size) || (NULL == p_elem)){
        return -1; 
    }
    // if the element to be removed is the head then ensure a new head is updated
    if (p_list->p_head == p_elem){
        p_list->p_head = p_elem->p_next;
    }
    // if the element to be removed is the tail then ensure a new head is updated
    if (p_list->p_tail == p_elem){
        p_list->p_tail = p_elem->p_prev;
    }
    // get the pointers to the next and previous elements
    elem * p_prev_elem = p_elem->p_prev;
    elem * p_next_elem = p_elem->p_next;
    // cant set the next pointer of a NULL element
    if (NULL != p_prev_elem){
        p_prev_elem->p_next = p_next_elem;
    }
    // cant set the prev pointer of a NULL element
    if (NULL != p_next_elem){
        p_next_elem->p_prev = p_prev_elem;
    }
    // if the user defined a destroy function for the data then destroy the data
    if (NULL != p_list->p_destroy){
        p_list->p_destroy((void *)p_elem->p_data);
    }
    // free the element
    free(p_elem);
    // the size of the list has to be decreased
    p_list->size--;
    return 0;
}

/*
 * @brief delete the element after the passed in element
 * @param p_list the list to delete the element from
 * @param p_elem the element before the element to delete 
 * @return -1 on error else 0
 */
int8_t list_rm_next(list * p_list, elem * p_elem)
{
    // cant delete an element from a NULL or empty list
    if ((NULL == p_list) || (0 == p_list->size)){
        return -1;
    }
    elem * p_old_elem = NULL;
    // if the element is NULL then the head is to be removed
    if (NULL == p_elem){
        p_old_elem = p_list->p_head;
    }
    else {
        p_old_elem = p_elem->p_next;
    }
    // delete and remove the old element from the list
    return list_delete(p_list, p_old_elem);
}

elem * list_remove(list * p_list, const void * p_data);
// getters

/*
 * @brief gets the head of a list
 * @param p_list the list to get the head from
 * @return pointer to the head of the list or NULL on error
 */
elem * list_head(list * p_list)
{
    // cant get the head of a NULL list
    if (NULL == p_list){
        return NULL;
    }
    return p_list->p_head;
}

/*
 * @brief gets the tail of a list
 * @param p_list the list to get the tail from
 * @return pointer to the tail of the list or NULL on error
 */
elem * list_tail(list * p_list)
{
    // cant get the tail of a NULL list
    if (NULL == p_list){
        return NULL;
    }
    return p_list->p_tail;
}

/*
 * @brief gets the next element of another element 
 * @param p_list the list to get the next element from
 * @return pointer to the next element or NULL on error
 */
elem * list_next(elem * p_elem)
{
    // cant get the next element of a NULL element 
    if (NULL == p_elem){
        return NULL;
    }
    return p_elem->p_next;
}

/*
 * @brief gets the previous element of another element 
 * @param p_list the list to get the previous element from
 * @return pointer to the previous element or NULL on error
 */
elem * list_prev(elem * p_elem)
{
    // cant get the next element of a NULL element 
    if (NULL == p_elem){
        return NULL;
    }
    return p_elem->p_prev;
}

/*
 * @brief searches a list for a specified value
 * @param p_list the list to search in
 * @param p_data the data to search for
 * @return pointer to the element that contains the data else NULL on error
 */
elem * list_search(list * p_list, const void * p_data)
{
    // cant search in a NULL or empty list or from NULL data 
    if ((NULL == p_list) || (0 == p_list->size) || (NULL == p_data)){
        return NULL;
    }
    // iterate through the list and compare the values
    elem * p_elem = p_list->p_head;
    for (; p_elem != NULL; p_elem = p_elem->p_next){
        // equal values should return 0
        if (0 == p_list->p_compare(p_elem->p_data, p_data)){
            return p_elem;
        }
    }
    // the full list was iterated through and no value matched so it doesn't exits
    // in the list
    return NULL;
}

/*
 * @brief gets the size of a list
 * @param p_list the list to get the size from
 * @return size of the list or -1 on error
 */
int32_t list_size(list * p_list)
{
    // cant get the size of a NULL list
    if (NULL == p_list){
        return -1;
    }
    return p_list->size;
}

/*
 * @breif gets the data in a list element
 * @param p_elem the element to get the data from
 * @return pointer to the data in the element or NULL on error
 */
const void * list_data(elem * p_elem)
{
    // cant get the data from a NULL element
    if (NULL == p_elem){
        return NULL;
    }
    return p_elem->p_data;
}

/*
 * @brief iterates through a list and runs a user defined function on each elements data
 * @param p_list the list to iterate through
 * @param p_func the function to run on the data
 */
void list_iter(list * p_list, void (* p_func)(const void * p_data))
{
    // cant run a function on a NULL or empty list or a NULL function
    if ((NULL != p_list) && (0 < p_list->size) && (NULL != p_func)){
        // iterate through the list and run the function 
        elem * p_elem = p_list->p_head;
        for (; p_elem != NULL; p_elem = p_elem->p_next){
            p_func(p_elem->p_data);
        }
    }
}

/*
 * @brief copies the values of a list to a new list
 * @param p_list the list to copy 
 * @param p_destroy user defined function destroy the data in the list
 * @return pointer to a new list or NULL on error
 */
list * list_copy(list * p_list, void (* p_destroy)(void * p_data))
{
    // cant copy from a NULL element
    if (NULL == p_list){
        return NULL;
    }
    list * p_list_copy = list_init(p_destroy, p_list->p_compare);
    if (NULL == p_list){
        return NULL;
    }
    // iterate through the list and create a new element in the list copy 
    elem * p_elem = p_list->p_head;
    for (; p_elem != NULL; p_elem = p_elem->p_next){
        list_ins_next(p_list_copy, p_list_copy->p_tail, p_elem->p_data);
    }
    return p_list_copy;
}
