#include <hashtbl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <list.h>
#include <string.h>

static const int mult = 31;

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
    void (* p_destroy)(const void * p_data);
    int8_t (* p_compare)(const void * p_key1, const void * p_key2);
    list ** pp_table;
};

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
                       void (* p_destroy)(const void * p_data),
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

elem * hashtbl_insert(hashtbl * p_hashtbl, const void * p_data)
{
    return NULL;
}
