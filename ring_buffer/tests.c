#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "ring_buffer.h"
#include "tests.h"
/** ------------------------------
 *  Ring buffer init test section
 *  ------------------------------
 */

void test_rb_init() {
    RingBuffer_t rb;
    
    rb_init(&rb);
    
    assert(rb.head == 0);
    assert(rb.tail == 0);

    assert(rb.count == 0);
}

/** ------------------------------
 *  Ring buffer write test section
 *  ------------------------------
 */

// 1) try to write to a full buffer

void rb_write_logic_test() {
    RingBuffer_t rb;

    rb_init(&rb);
    rb_write(&rb, 112);
    
    assert(rb.count == 1);
    assert(rb.head == 1);
    assert(rb.tail == 0);
    
    printf("Basic write logic test is passed successfully.\n");
}

void rb_write_test_overflow() {
    RingBuffer_t rb;

    rb_init(&rb);

    for (int i = 0; i < RB_BUFFER_SIZE; ++i) {
        rb_write(&rb, 1);
    }

    assert(rb_write(&rb, 1) == RB_Status_Full);

    printf("Buffer overflow test is passed successfully.\n");
}

/** ------------------------------
 *  Ring buffer read test section
 *  ------------------------------
 */

// 1) try reading from empty buffer
// 2) try this again with buffer that performed some actions

void rb_read_logic_test() {
    RingBuffer_t rb;

    rb_init(&rb);

    rb_write(&rb, 1);
    rb_write(&rb, 1);

    uint8_t data;
    rb_read(&rb, &data);

    assert(data == 1);
    
    assert(rb.head == 2);
    assert(rb.tail == 1);

    assert(rb.count == 1);

    printf("Basic read logic test is passed successfully.\n");
}

void rb_read_empty_test() {
    RingBuffer_t rb;

    rb_init(&rb);

    uint8_t data;
    assert(rb_read(&rb, &data) == RB_Status_Empty);

    printf("Read empty buffer test is passed successfully\n");
}

void rb_state_helpers_test() {
    RingBuffer_t rb;

    rb.count = 0;
    assert(rb_is_empty(&rb)    == true);
    assert(rb_is_full(&rb)     == false);
    assert(rb_get_state(&rb)   == RB_Status_Empty);

    rb.count = RB_BUFFER_SIZE;
    assert(rb_is_full(&rb)     == true);
    assert(rb_is_empty(&rb)    == false);
    assert(rb_get_state(&rb)   == RB_Status_Full);

    rb.count = 3;
    assert(rb_is_empty(&rb)    == false);
    assert(rb_is_full(&rb)     == false);
    assert(rb_get_state(&rb)   == RB_Status_Ok);

    assert(rb_get_state(NULL)  == RB_Status_Null);
    assert(rb_is_empty(NULL)   == false);
    assert(rb_is_full(NULL)    == false);

    printf("All helper functions are passed tests successfully.\n");
}


/*General test */
void rb_general_test() {
    test_rb_init();

    rb_write_logic_test();
    rb_write_test_overflow();

    rb_read_logic_test();
    rb_read_empty_test();

    rb_state_helpers_test();

    printf("\nAll tests are passed successfully.\n");
}
