#include <stdint.h>

#include "queue.h"


QueueStatus_t queue_init(Queue_t* q, const size_t item_size) {
    if (q == NULL) { return QueueStatus_Null; }
    
    q->head = 0;
    q->tail = 0;
    
    q->count = 0;

    q->item_size = item_size;

    return ExitCode_Success; 
}


QueueStatus_t enqueue(Queue_t* q, const void* item) {
    if (q == NULL)          { return QueueStatus_Null; }
    if (item == NULL)       { return QueueStatus_InvalidArg; }

    if (q->count == Q_BUFFER_SIZE) {
        return QueueStatus_Full;
    }

    memcpy(q->buffer[head], item, q->item_size);
    q->head = Q_NEW_INDEX(q->head);

    ++q->count;

    return QueueStatus_Ok;
}

QueueStatus_t dequeue(Queue_t* q, void* item) {
    if (q == NULL)          { return QueueStatus_Null; }
    if (item == NULL)       { return QueueStatus_InvalidArg; }

    if (q->count == 0) {
        return QueueStatus_Empty;
    }

    memcpy(item, q->buffer[tail], q->item_size);
    q->tail = Q_NEW_INDEX(q->tail);

    --q->count;

    return QueueStatus_Ok;
}