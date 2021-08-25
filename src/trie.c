#include <trie.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct node {
    const void * p_data;
    struct node * p_parent;
    struct node * p_left;
    struct node * p_right;
};

struct trie {
    int64_t size;
    node * p_root;
    void (* destroy)(const void *p_data);
    int8_t (* compare)(const void *p_key1, const void *p_key2);
};

trie * trie_init(void (* destroy)(const void *p_data),
                int8_t (* compare)(const void *p_key1, const void *p_key2))
{
    // cant start a trie without knowing how to compare the data
    if (NULL == compare){
        return NULL;
    }
    // a trie structure needs to be created and initialized
    trie * p_trie = calloc(1, sizeof(*p_trie));
    if (NULL == p_trie){
        perror("trie init ");
        return NULL;
    }
    p_trie->size = 0;
    p_trie->p_root = NULL;
    p_trie->destroy = destroy;
    p_trie->compare = compare;
    return p_trie;
}

void trie_destroy(trie * p_trie)
{
    // cant tear down a trie that is NULL
    if (NULL == p_trie){
        return;
    }
    free(p_trie);
}
