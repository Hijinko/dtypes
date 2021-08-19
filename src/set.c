#include <set.h>
#include <stdlib.h>

/*
 * @brief adds a new member to the set
 * @param p_set the set to add to
 * @param p_data the data to add to the set
 * @return pointer to the new data else NULL on error
 */
static inline member * set_insert(set * p_set, const void * p_data)
{
    // add a new member to the end of the set
    return list_append(p_set, p_data);
}

/*
 * @brief copies the data in a set to another set
 * @param p_set the set to copy
 * @return pointer to the new set or NULL on error
 */
static inline set * set_copy(set * p_set)
{
    // copy the set
    return list_copy(p_set, NULL, NULL);
}

/*
 * @brief gets the first element in the set
 * @param p_set the set to get the element from
 * @return pointer to the first element in the set else NULL
 */
static inline member * set_head(set * p_set)
{
    // get the head of the set
    return list_head(p_set);
}

/*
 * @brief gets the next member of the passed in member in a set
 * @param p_member the member to get the next member from
 * @return pointer to the next member else NULL
 */
static inline member * set_next(member * p_member)
{
    // get the next member
    return list_next(p_member);
}

static inline member * set_search(set * p_set, const void * p_data)
{
    // search the set for the value
    return list_search(p_set, p_data);
}

/*
 * @brief gets the union of two sets
 * @param p_set1 the first set in the union
 * @param p_set2 the second set in the union
 * @return a union of the two sets
 */
set * set_union(set * p_set1, set * p_set2)
{
    // cant get union of NULL sets
    if ((NULL == p_set1) || (NULL == p_set2)){
        return NULL;
    }
    // a copy of the first set with the second sets data
    // added will be the new union set
    set * p_union_set = set_copy(p_set1);
    // iterate through set2 and add any new element
    member * p_member = set_head(p_set2);
    for (; NULL != p_member; p_member = set_next(p_member)){
        set_add(p_union_set, set_data(p_member));
    }
    return p_union_set;
}
set * set_intersect(set * p_set1, set * p_set2);
set * set_difference(set * p_set1, set * p_set2);

/*
 * @brief adds a new element to a set
 * @param p_set the set to add an element to
 * @param p_data the data to add to the set
 * @return pointer to the new element in the set else NULL on error
 */
member * set_add(set * p_set, const void * p_data)
{
    // cant add to a NULL set or from NULL data
    if ((NULL == p_set) || (NULL == p_data)){
        return NULL;
    }
    // new members can only be added to the set if the data doesn't already exist in the set
    if (false == set_is_member(p_set, p_data)){
        return set_insert(p_set, p_data);
    }
    // the member was in the set or there was an error
    return NULL;
}

/*
 * @brief checks if data is a member in a set
 * @param p_set the set to check in
 * @param p_data the data to check for in the set
 * @return true if data is in the set else false
 */
bool set_is_member(set * p_set, const void * p_data)
{
    // cant get members in a NULL set or from NULL data
    if ((NULL == p_set) || (NULL == p_data)){
        return false;
    }
    return (NULL == set_search(p_set, p_data) ? false : true);
}

bool set_is_subset(set * p_org_set, set * p_sub_set);
