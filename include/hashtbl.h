#ifndef _HASHTBL_H
#define _HASHTBL_H
#include <stdint.h>
typedef struct hashtbl hashtbl;
hashtbl * hashtbl_init(uint64_t buckets,
                       uint64_t (* p_hash)(const void * p_key),
                       void (* p_destroy)(const void * p_data),
                       int8_t (* p_compare)(const void * p_key1,
                                            const void * p_key2));
void hashtbl_destroy(hashtbl * p_hashtbl);
#endif
