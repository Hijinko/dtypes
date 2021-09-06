#include <hashtbl.h>
#include <stdint.h>

/*
 *@brief hash table structure
 *@param buckets integer that is the allocated number of 
 * elements in the hashtbl
 *@param hash user defined hash function should return an uint64_t 
 *@param p_destroy user defined function to destroy any allocated data
 *@param p_compare user defined function to compare the data in the hashtbl
 * bin the hashtbl
 */ 
struct hashtbl {
    uint64_t buckets;
    uint64_t hash;
    void (* destroy)(const void * p_data);
    int8_t (* compare)(const void * p_key1, const void * p_key2);
};

hashtbl * hashtbl_init(uint64_t buckets,
                       uint64_t hash(const void * p_key),
                       void (* p_destroy)(const void * p_data),
                       int8_t (* p_compare)(const void * p_key1,
                                            const void * p_key2));
void hashtbl_destroy(hashtbl * p_hashtbl);
