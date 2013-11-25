/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#include <common/circular_buffer.h>
#include <common/printk.h>

void cb_init(circ_buf_t *buf)
{
    int i;

    if (!buf)
    {
        printk(KERN_EMERG "Can't initialize an nonexistent buffer\n");
        return;
    }

    for (i = 0; i < MAX_CB_SIZE; ++i)
    {
        buf->data[i] = 0;
    }

    buf->back = 0;
    buf->front = 0;
}

s8int cb_push(circ_buf_t *buf, u32int data)
{
    if (cb_isfull(buf))
        return -1;

    buf->data[buf->front] = data;
    buf->front++;

    // make sure the size doesn't go past
    // the maximum size (works only for powers of 2)
    buf->front &= MAX_CB_SIZE - 1;

    return 0;
}

u32int cb_pop(circ_buf_t *buf)
{
    if (cb_isempty(buf))
    {
        printk(KERN_ERR "Buffer is empty\n");
        return (u32int)-1;
    }

    u32int tmp = buf->data[buf->back];
    buf->back++;
    buf->back &= MAX_CB_SIZE - 1;

    return tmp;
}

int cb_isfull(circ_buf_t *buf)
{
    if ((buf->back - buf->front - 1) & (MAX_CB_SIZE - 1))
        return 0;
    else
        return 1;
}

int cb_isempty(circ_buf_t *buf)
{
    if (buf->front == buf->back)
        return 1;
    else
        return 0;
}

int cb_size(circ_buf_t *buf)
{
    return (buf->front - buf->back);
}
