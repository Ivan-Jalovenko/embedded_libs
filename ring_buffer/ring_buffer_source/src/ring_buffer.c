#include <stdint.h>

#include "ring_buffer.h"

RB_Status_t rb_init(RingBuffer_t* rb) {
    if (rb == NULL) { return RB_Status_Null; }

    rb->head = 0;
    rb->tail = 0;
    
    rb->count = 0;

    return RB_Status_Ok;
}

RB_Status_t rb_write(RingBuffer_t* rb, uint8_t data) {
    if (rb == NULL ) { return RB_Status_Null; }

    if (rb->count == RB_BUFFER_SIZE) {
        return RB_Status_Full;
    }

    rb->buffer[rb->head] = data;
    rb->head = RB_NEW_INDEX(rb->head);

    ++rb->count;

    return RB_Status_Ok;
}

RB_Status_t rb_read(RingBuffer_t* rb, uint8_t* data) {
    if (rb == NULL) { return RB_Status_Null; }
    else if (data == NULL) { return RB_Status_InvalidArg; }

    if (rb->count == 0) {
        return RB_Status_Empty;
    }

    *data = rb->buffer[rb->tail];
    rb->tail = RB_NEW_INDEX(rb->tail);
    
    --rb->count;
    
    return RB_Status_Ok;
}
