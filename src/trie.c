#include <trie.h>
#include <hashtbl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * @brief trie node structure
 * @param p_data pointer to the data the node holds
 * @param p_parent the parent node of the current node
 * @param p_nodes a hash table of node children that the current
 *  node is a parent of
 */
struct node {
    const void * p_data;
    struct node * p_parent;
    hashtbl * p_nodes;
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
 * @brief trie compare function for the hashtble 
 * @param p_key1 The first key to compare
 * @param p_key2 the second key to compare
 * @return -1, 0, 1 if key1 is less than equal to or greater than key2
 */
static int8_t trie_compare(const void * p_key1, const void * p_key2)
{
    node * p_node1 = (void *)p_key1;   
    node * p_node2 = (void *)p_key2;   
    return (p_node1 < p_node2) ? -1 : ((p_node1 == p_node2) ? 0 : 1);
}

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
    p_node->p_nodes = hashtbl_init(255, NULL, free, trie_compare);
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
    p_trie->p_root = node_init("*");
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
    node * p_cur_node = p_trie->p_root;
    // TODO loop through each node and free its data
    // to solve memory leak
    hashtbl_destroy(p_cur_node->p_nodes);
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
    // cant insert into a NULL trie or from NULL data
    if ((NULL == p_trie) || (NULL == p_data)){
        return NULL;
    }
    node * p_cur_node = p_trie->p_root;
    node * p_temp_node = NULL;
    char * data = calloc(strlen(p_data) + 1, sizeof(char));
    strcpy(data, p_data);
    for (size_t curval = 0; curval < strlen(p_data); curval++){
        // if a value doesnt exist than create it
        if (NULL == hashtbl_value(p_cur_node->p_nodes, &(data[curval]))){
            node * p_node = node_init(&(data[curval])); 
            p_temp_node = (void *)hashtbl_data(hashtbl_insert(
                                               p_cur_node->p_nodes,
                                               &(data[curval]), p_node));
        }
        else {
            p_temp_node = (void *)hashtbl_value(p_cur_node->p_nodes,
                                                &(data[curval]));
        }
        p_cur_node = p_temp_node;
    }
    hashtbl_insert(p_cur_node->p_nodes, &((data)[0]), p_data);
    free(data);
    p_trie->size++;
    return p_cur_node;
}
