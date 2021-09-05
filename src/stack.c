#include <stack.h>
#include <list.h>
#include <stdlib.h>

/*
 * @brief removes the last member in the stack from the stack but does not
 *  free any allocated data
 * @param p_stack the stack to pop a member from
 * @return a pointer to the data that was popped from the stack
 */
const void * stack_pop(stack * p_stack)
{
    // cant pop from a Null or empty stack
    if ((NULL == p_stack) || (0 == stack_size(p_stack))){
        return NULL;
    }
    return list_remove(p_stack, stack_data(stack_peek(p_stack)));
}
