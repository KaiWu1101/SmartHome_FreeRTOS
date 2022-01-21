#ifndef _DRIVER_RINGBUFFER_H_
#define _DRIVER_RINGBUFFER_H_

#include <stdbool.h>

#define BUFFER_SIZE 1024

typedef struct {
    unsigned char buffer[BUFFER_SIZE];
    volatile unsigned int pW;
    volatile unsigned int pR;
} ring_buffer;

void ringbuffer_init(ring_buffer* dst_rb);
bool is_rb_full(ring_buffer* dst_rb);
bool is_rb_empty(ring_buffer* dst_rb);
unsigned int ringbuffer_WriteDate(unsigned char c, ring_buffer* dst_rb);
int ringbuffer_ReadDate(unsigned char *c, ring_buffer* dst_rb);
unsigned int display_rb_data(ring_buffer* dst_rb);

#endif //_DRIVER_RINGBUFFER_H_
