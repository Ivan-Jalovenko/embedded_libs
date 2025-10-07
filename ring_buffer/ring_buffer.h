#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define RB_BUFFER_SIZE 16


#ifndef RB_BUFFER_SIZE
    #error "RING_BUFFER_H: RB_BUFFER_SIZE is not defined!" 
#endif

#if RB_BUFFER_SIZE <= 0
    #error "RING_BUFFER_H: RB_BUFFER_SIZE is less or equal to 0!"
#endif



/* Check if RB_BUFFER_SIZE if a power of two */
#if (RB_BUFFER_SIZE & (RB_BUFFER_SIZE - 1)) == 0 && RB_BUFFER_SIZE > 0
    #define BUFFER_WRAP_AROUND_MASK (RB_BUFFER_SIZE - 1)
    
    #define RB_NEW_INDEX(x) (((x) + 1) & BUFFER_WRAP_AROUND_MASK)
#else
    #warning "RING_BUFFER_H: Buffer size is not power of 2\
     so slower indexing module would be used"
    
    #define RB_NEW_INDEX(x) (((x) + 1) % RB_BUFFER_SIZE)
#endif


typedef struct {
    uint8_t buffer[RB_BUFFER_SIZE];
    size_t head, tail;
    size_t count;
} RingBuffer_t;

typedef enum {
    RB_Status_Ok          = 0,
    RB_Status_Empty       = 1,
    RB_Status_Full        = 2,
    RB_Status_Null        = 4,
    RB_Status_Error       = 5,
    RB_Status_InvalidArg  = 6,
} RB_Status_t;


RB_Status_t rb_init(RingBuffer_t* rb);

RB_Status_t rb_write(RingBuffer_t* rb, uint8_t data);

RB_Status_t rb_read(RingBuffer_t* rb, uint8_t* data);


static inline bool rb_is_empty(RingBuffer_t* rb) {
    return rb && (rb->count == 0);
}

static inline bool rb_is_full(RingBuffer_t* rb) {
    return rb && (rb->count == RB_BUFFER_SIZE);
}

static inline size_t rb_space(RingBuffer_t* rb) {
    return rb ? rb->count : 0;
}

static inline RB_Status_t rb_get_state(RingBuffer_t* rb) {
    if (rb == NULL) {
        return RB_Status_Null;
    } else if (rb->count == 0) {
        return RB_Status_Empty;
    } else if (rb->count == RB_BUFFER_SIZE) {
        return RB_Status_Full;
    } 
    return RB_Status_Ok;
}


#endif // RING_BUFFER_H
