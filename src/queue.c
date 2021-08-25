#include <queue.h>
#include <stdlib.h>

static inline void queue_delete(queue * p_queue, member * p_member)
{
    list_delete(p_queue, p_member);
}

void queue_dequeue(queue * p_queue)
{
    // cant dequeue a NULL or empyt queue
    if ((NULL == p_queue) || (0 >= queue_size(p_queue))){
        return;
    }
    member * p_member = queue_peek(p_queue);
    queue_delete(p_queue, p_member);
}
