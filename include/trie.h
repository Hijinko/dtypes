#include <stdint.h>
typedef struct trie trie;
typedef struct node node;

trie * trie_init(void (* destroy)(const void * p_data),
                int8_t (* compare)(const void *p_key1, const void * p_key2));
void * trie_destroy(trie * p_trie);
