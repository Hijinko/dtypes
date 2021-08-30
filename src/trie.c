#include <trie.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * @brief trie node structure
 * @param p_data pointer to the data the node holds
 * @param p_parent the parent node of the current node
 * @param nodes an array of node children that the current node is a parent of
 */
struct node {
    const void * p_data;
    struct node * p_parent;
    node ** nodes;
};

/*
 * @brief a trie structure
 * @param size the number of nodes in the trie
 * @param p_root the root node of the trie
 * @param destroy user defined function to free any allocated data
 * @param compare user defined function to compare to node values
 *  should return -1, 0, 1 if key1 is less than, equal to or greater than key2
 */
struct trie {
    int64_t size;
    node * p_root;
    void (* destroy)(const void *p_data);
    int8_t (* compare)(const void *p_key1, const void *p_key2);
};

/*
 * @brief creates and initializes a trie node
 * @param p_data pointer to the data in the node
 * @return pointer to the newly created node
 */
static node * node_init(const void * p_data)
{
    // allocate a new node
    node * p_node = calloc(1, sizeof(*p_node));
    if (NULL == p_node){
        return NULL;
    }
    // if the data is NULL then we are creating a root node
    if (NULL == p_data){
        p_node->p_data = "*";   
    }
    else {
        p_node->p_data = p_data;
    }
    p_node->p_parent = NULL;    
    p_node->nodes = NULL;
    return p_node;
}

/*
 * @brief creates and initializes a new trie structure
 * @param destroy user defined function to free any allocated data
 * @param compare user defined function to compare to node values
 *  should return -1, 0, 1 if key1 is less than, equal to or greater than key2
 */
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

/*
 * @brief tears down a trie structure and frees any allocated memory
 * @param p_trie the trie to tear down
 */
void trie_destroy(trie * p_trie)
{
    // cant tear down a trie that is NULL
    if (NULL == p_trie){
        return;
    }
    free(p_trie);
}

/*
 * @brief adds a new node to a trie
 * @param p_trie the trie to add a node to
 * @param p_data the data to add to the node 
 * @return pointer to the last node that holds all the data or NULL on error
 */
node * trie_insert(trie * p_trie, const void *p_data)
{
    return NULL;
}
