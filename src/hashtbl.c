#include <hashtbl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * @brief hash table structure
 * @param buckets integer that is the allocated number of 
 *  elements in the hashtbl
 * @param p_hash user defined hash function should return an uint64_t 
 * @param p_destroy user defined function to destroy any allocated data
 * @param p_compare user defined function to compare the data in the hashtbl
 *  bin the hashtbl
 * @param p_table an array that holds the data
 */ 
struct hashtbl {
    uint64_t buckets;
    uint64_t (* p_hash)(const void * p_key);
    void (* p_destroy)(const void * p_data);
    int8_t (* p_compare)(const void * p_key1, const void * p_key2);
    const void * p_table;
};

/*
 * @brief creates and initializes a hash table
 * @param buckets uint6_t that is the number of spaces in the hash table
 * @param p_hash a user defined hashing function to classify the data
 * @param p_destroy a user defined function to destroy the data in the hashtbl 
 * @param p_compare a user defined function to compare the data in the hashtbl
 * @return a pointer to a newly allocated hashtable or NULL on error
 */
hashtbl * hashtbl_init(uint64_t buckets,
                       uint64_t (* p_hash)(const void * p_key),
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
    p_hashtbl->p_hash = p_hash;
    p_hashtbl->p_destroy = p_destroy;
    p_hashtbl->p_compare = p_compare;
    p_hashtbl->p_table = NULL;
    return p_hashtbl;
}

void hashtbl_destroy(hashtbl * p_hashtbl)
{
    free(p_hashtbl);
}
