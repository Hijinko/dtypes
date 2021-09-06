#include <hashtbl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <list.h>
#include <string.h>

static const int mult = 31;

/*
 * @brief the element in the hash table that holds each key and value pair
 * @param p_key a unique key for each data in the table
 * @param p_value the data that the key points to
 */
struct hashtbl_elem {
    const void * p_key;
    const void * p_value;
};

/*
 * @brief hash table structure
 * @param buckets integer that is the allocated number of 
 *  elements in the hashtbl
 * @param size the number of elements in the hash table
 * @param p_hash user defined hash function should return an uint64_t 
 * @param p_destroy user defined function to destroy any allocated data
 * @param p_compare user defined function to compare the data in the hashtbl
 *  bin the hashtbl
 * @param pp_table an array of lists that holds all the data
 */ 
struct hashtbl {
    int64_t buckets;
    int64_t size;
    int64_t (* p_hash)(const void * p_key);
    void (* p_destroy)(void * p_data);
    int8_t (* p_compare)(const void * p_key1, const void * p_key2);
    list ** pp_table;
};

/*
 * @brief hash function for single characters default hash
 *  if no hash is specified
 * @param p_key the word to hash
 * @return the hash key integer or -1 on error
 */
static int64_t hash_string(const void * p_key)
{
    // cant get the hash of a NULL value
    if (NULL == p_key){
        return -1;
    }
    // this hash is for strings so convert the data to a string
    char * data = (char *)p_key;
    int64_t retval = 0;
    int8_t curval = data[0];
    for (size_t pos = 1; pos < strlen(data); pos++){
        retval = mult * retval + curval;
    }
    return retval;
}

static hashtbl_elem * hashtbl_lookup(hashtbl * p_hashtbl, const void * p_key)
{
    // hash the key to get the correct bucket
    int64_t bucket = p_hashtbl->p_hash(p_key) % p_hashtbl->buckets;
    list * p_list = p_hashtbl->pp_table[bucket];
    // if the list is NULL then no data exists for the key
    if (NULL == p_list){
        return NULL;
    }
    // iterate through the list and search for the key that matches
    elem * p_elem = list_head(p_list);
    for (;NULL != p_elem; p_elem = list_next(p_elem)){
        hashtbl_elem * p_hashtbl_elem = (hashtbl_elem *)list_data(p_elem);
        if (p_key == p_hashtbl_elem->p_key){
            return p_hashtbl_elem;        
        }
    }
    // no key was found that matches
    return NULL;
}

/*
 * @brief creates and initializes a hash table
 * @param buckets int6_t that is the number of spaces in the hash table
 * @param p_hash a user defined hashing function to classify the data
 * @param p_destroy a user defined function to destroy the data in the hashtbl 
 * @param p_compare a user defined function to compare the data in the hashtbl
 * @return a pointer to a newly allocated hashtable or NULL on error
 */
hashtbl * hashtbl_init(int64_t buckets,
                       int64_t (* p_hash)(const void * p_key),
                       void (* p_destroy)(void * p_data),
                       int8_t (* p_compare)(const void * p_key1,
                                            const void * p_key2))
{
    // cant create a hash table that has no buckets
    if (0 == buckets){
        return NULL;
    }
    // a hashtbl has to be initialized
    hashtbl * p_hashtbl = calloc(1, sizeof(*p_hashtbl));
    // ensure that a hashtbl was able to be allocated 
    if (NULL == p_hashtbl){
        perror("hashtbl_init ");
        return NULL;
    }
    // set the values of the hashtbl
    p_hashtbl->buckets = buckets;
    p_hashtbl->size = 0;
    // a list will be created just to allocate space in the table
    list * p_temp_list = list_init(NULL, NULL);
    p_hashtbl->pp_table = calloc(p_hashtbl->buckets + 1, sizeof(p_temp_list));
    // the temp list is no longer needed
    list_destroy(p_temp_list);
    // if the table cannot be allocated then the hashtbl needs to be freed
    if (NULL == p_hashtbl->pp_table){
        free(p_hashtbl);
        perror("hashtbl_init ");
        return NULL;
    }
    // if no hash is given then use the hash_string as the default hash
    if (NULL == p_hash){
        p_hashtbl->p_hash = hash_string;
    }
    else {
        p_hashtbl->p_hash = p_hash;
    }
    p_hashtbl->p_destroy = p_destroy;
    p_hashtbl->p_compare = p_compare;
    return p_hashtbl;
}

/*
 * @brief tears down a hash table and frees any allocated memory
 * @param p_hashtbl the hash table to free
 */
void hashtbl_destroy(hashtbl * p_hashtbl)
{
    // cant free a NULL hash table
    if (NULL == p_hashtbl){
        return;
    }
    // iterate through the hash table and destroy any allocated list
    for(int64_t bucket = 0; bucket < p_hashtbl->buckets; bucket++){
        if (NULL != p_hashtbl->pp_table[bucket]){
            list_destroy(p_hashtbl->pp_table[bucket]);
        }
    }
    free(p_hashtbl->pp_table);
    free(p_hashtbl);
}

/*
 * @brief gets the number of elements in the hash table
 * @param p_hashtbl the hash table to get the size of
 * @return the number of elements in the table or -1 on error
 */
int64_t hashtbl_size(hashtbl * p_hashtbl) 
{
    // cant get the size of a NULL hash table
    if (NULL == p_hashtbl){
        return -1;
    }
    return p_hashtbl->size;
}

hashtbl_elem * hashtbl_insert(hashtbl * p_hashtbl, const void * p_key, 
                      const void * p_value)
{
    // can't insert into a NULL hash table or from NULL key
    if ((NULL == p_hashtbl) || (NULL == p_key)){
        return NULL;
    }
    // compute the hash of the key 
    int64_t bucket = p_hashtbl->p_hash(p_key) % p_hashtbl->buckets;
    // if the bucket in the table is NULL then a new list has to be initialized
    if (NULL == p_hashtbl->pp_table[bucket]){
        p_hashtbl->pp_table[bucket] = list_init(p_hashtbl->p_destroy,
                                                p_hashtbl->p_compare);
    }
    // if a list already exists check if the key is already in the list
    else if(NULL != hashtbl_lookup(p_hashtbl, p_key)){
        // can only have unique keys in a hash table
        return NULL;
    }
    // a hashtbl element has to be allocated with the new data
    hashtbl_elem * p_hashtbl_elem = calloc(1, sizeof(*p_hashtbl_elem));
    if (NULL == p_hashtbl_elem){
        return NULL;
    }
    // the data can now be inserted into the list at the bucket in the table
    p_hashtbl_elem->p_key = p_key;
    p_hashtbl_elem->p_value = p_value;
    elem * p_elem = list_prepend(p_hashtbl->pp_table[bucket], p_hashtbl_elem);
    // the size of the hash table has to be increased
    p_hashtbl->size++;
    return (hashtbl_elem *)list_data(p_elem);
}

/*
 * @brief gets the value from a hashtbl_elem structure
 * @param p_hashtble_elem the element to get the value from
 * @return the value in the hashtble_elem structure
 */
const void * hashtbl_data(hashtbl_elem * p_hashtbl_elem)
{
    // cant get the value from a NULL element
    if (NULL == p_hashtbl_elem){
        return NULL;
    }
    return p_hashtbl_elem->p_value;
}

/*
 * @brief gets the value from a hash table given the key
 * @param p_hashtbl the hash table to get the value from
 * @param p_key the key that points to the data in the table
 * @return the value that corresponds to the key in the hash table
 */
const void * hashtbl_value(hashtbl * p_hashtbl, const void * p_key)
{
    // cant get the value from a NULL or empty hash table or from a NULL key
    if ((NULL == p_hashtbl) || (0 == p_hashtbl->size) || (NULL == p_key)){
        return NULL;
    }
    return hashtbl_lookup(p_hashtbl, p_key)->p_value;
}
