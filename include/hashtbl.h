#ifndef _HASHTBL_H
#define _HASHTBL_H
#include <stdint.h>
#include <list.h>
typedef struct hashtbl hashtbl;
typedef struct hashtbl_elem hashtbl_elem;
hashtbl * hashtbl_init(int64_t buckets,
                       int64_t (* p_hash)(const void * p_key),
                       void (* p_destroy)(void * p_data),
                       int8_t (* p_compare)(const void * p_key1,
                                            const void * p_key2));
void hashtbl_destroy(hashtbl * p_hashtbl);
int64_t hashtbl_size(hashtbl * p_hashtbl);
hashtbl_elem * hashtbl_insert(hashtbl * p_hashtbl, const void * p_key,
                              const void * p_value);
const void * hashtbl_data(hashtbl_elem * p_hashtbl_elem);
#endif
