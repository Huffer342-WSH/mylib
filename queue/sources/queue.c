#include "queue.h"
#include <string.h>
static inline uint32_t next_index(uint32_t i, uint32_t size)
{
	i++;
	return i >= size ? i - size : i;
}

void queue_init(struct queue *f, void *buf, uint32_t size, uint8_t elmSize)
{
	f->in = 0;
	f->out = 0;
	f->size = size;
	f->elmSize = elmSize;
	f->buf = buf;
}

void queue_pop(struct queue *f, void *res)
{
	memcpy(res, f->buf + f->out * f->elmSize, f->elmSize);
	f->out = next_index(f->out, f->size);
}

void queue_push(struct queue *f, void *elm)
{
	memcpy(f->buf + f->in * f->elmSize, elm, f->elmSize);
	f->in = next_index(f->in, f->size);
}

void queue_clear(struct queue *f)
{
	f->in = f->out = 0;
}

int queue_isEmpty(struct queue *f)
{
	return f->in == f->out;
}

int queue_isFull(struct queue *f)
{
	return f->out == next_index(f->in, f->size);
}
