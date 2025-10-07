#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

#define Q_BUFFER_SIZE 16

#ifndef Q_BUFFER_SIZE
    #error "RING_BUFFER_H: Q_BUFFER_SIZE is not defined!" 
#endif

#if Q_BUFFER_SIZE <= 0
    #error "RING_BUFFER_H: Q_BUFFER_SIZE is less or equal to 0!"
#endif


/* Check if Q_BUFFER_SIZE if a power of two */
#if (Q_BUFFER_SIZE & (Q_BUFFER_SIZE - 1)) == 0 && Q_BUFFER_SIZE > 0
    #define BUFFER_WRAP_AROUND_MASK (Q_BUFFER_SIZE - 1)
    
    #define Q_NEW_INDEX(x) (((x) + 1) & BUFFER_WRAP_AROUND_MASK)
#else
    #warning "RING_BUFFER_H: Buffer size is not power of 2\
     so slower indexing module would be used"
    
    #define Q_NEW_INDEX(x) (((x) + 1) % Q_BUFFER_SIZE)
#endif

typedef struct{
    uint8_t buffer[QUEUE_SIZE * MAX_ITEM_SIZE];
    size_t head, tail;
    size_t count;
    size_t item_size;
} Queue_t;  

typedef enum {
    QueueStatus_Ok = 0,
    QueueStatus_Empty,
    QueueStatus_Full,
    QueueStatus_Null,
    QueueStatus_InvalidArg,
    QueueStatus_Timeout,
    QueueStatus_Error
} QueueStatus_t;

QueueStatus_t queue_init(Queue_t* q);

QueueStatus_t enqueue(Queue_t* q, void* item);
QueueStatus_t dequeue(Qeuee_t* q, void** item);

#endif // QUEUE_H
