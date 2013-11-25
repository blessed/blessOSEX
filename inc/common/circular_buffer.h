/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <common/types.h>

#define MAX_CB_SIZE 1024

typedef struct
{
    u32int front;
    u32int back;
    u32int data[MAX_CB_SIZE];
} circ_buf_t;

void cb_init(circ_buf_t *buf);
s8int cb_push(circ_buf_t *buf, u32int data);
u32int cb_pop(circ_buf_t *buf);

void cb_clear(circ_buf_t *buf);
int cb_isfull(circ_buf_t *buf);
int cb_isempty(circ_buf_t *buf);
int cb_size(circ_buf_t *buf);

#endif // CIRCULAR_BUFFER_H
