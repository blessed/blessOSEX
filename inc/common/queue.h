/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#ifndef QUEUE_H
#define QUEUE_H

typedef struct byte_queue
{
    int front;
    int back;
    char *data;
    int max_size;
    int size;
} byte_queue_t;

int init_byte_queue(byte_queue_t *queue);


#endif // QUEUE_H
