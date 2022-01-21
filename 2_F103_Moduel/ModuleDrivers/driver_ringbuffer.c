#include "driver_ringbuffer.h"

/*
 * @Author       : your name
 * @Date         : 2022-01-21 09:45:30
 * @LastEditTime : 2022-01-21 12:56:30
 * @LastEditors  : Please set LastEditors
 * @Description  : 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath     : /cm3/home/kaiw/testland/c/ring_buffer/test.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void ringbuffer_init(ring_buffer* dst_rb)
{
    dst_rb->pR = 0;
    dst_rb->pW = 0;
}

bool is_rb_full(ring_buffer* dst_rb)
{
    return (((dst_rb->pW + 1)%BUFFER_SIZE) == dst_rb->pR);
}

bool is_rb_empty(ring_buffer* dst_rb)
{
    return (dst_rb->pR == dst_rb->pW);
}

unsigned int ringbuffer_WriteDate(unsigned char c, ring_buffer* dst_rb)
{
    if(is_rb_full(dst_rb)) {return 1;}
    dst_rb->buffer[dst_rb->pW] = c;
    dst_rb->pW = ((dst_rb->pW + 1)%BUFFER_SIZE);
}

int ringbuffer_ReadDate(unsigned char *c, ring_buffer* dst_rb)
{
    if(is_rb_empty(dst_rb)) {return -1;}
    (*c) = dst_rb->buffer[dst_rb->pR];
    dst_rb->pR = (dst_rb->pR + 1)%BUFFER_SIZE;
		return 0;
}

unsigned int display_rb_data(ring_buffer* dst_rb)
{
    if(is_rb_empty(dst_rb)) {printf("RB EMPTY\n"); return 1;}
    for(int i = dst_rb->pR ; i < dst_rb->pW; i++)
    {
        printf("rb data [%d] = %c\n", i, dst_rb->buffer[i]);
    }
}

