#include <hashtbl.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * @brief hash table structure
 * @param buckets integer that is the allocated number of 
 *  elements in the hashtbl
 * @param hash user defined hash function should return an uint64_t 
 * @param p_destroy user defined function to destroy any allocated data
 * @param p_compare user defined function to compare the data in the hashtbl
 *  bin the hashtbl
 */ 
struct hashtbl {
    uint64_t buckets;
    uint64_t (* hash)(const void * p_key);
    void (* destroy)(const void * p_data);
    int8_t (* compare)(const void * p_key1, const void * p_key2);
};

/*
 * @brief creates and initializes a hash table
 * @param buckets uint6_t that is the number of spaces in the hash table
 * @param hash a user defined hashing function to classify the data
 * @param p_destroy a user defined function to destroy the data in the hashtbl 
 * @param p_compare a user defined function to compare the data in the hashtbl
 * @return a pointer to a newly allocated hashtable
 */
hashtbl * hashtbl_init(uint64_t buckets,
                       uint64_t (* hash)(const void * p_key),
                       void (* p_destroy)(const void * p_data),
                       int8_t (* p_compare)(const void * p_key1,
                                            const void * p_key2))
{
    return NULL;
}

void hashtbl_destroy(hashtbl * p_hashtbl)
{
    return;
}
