#include <stdint.h>

struct queue {
	uint32_t in;
	uint32_t out;
	uint32_t size;
	void *buf;
	uint8_t elmSize;
};

void queue_init(struct queue *f, void *buf, uint32_t size, uint8_t elmSize);
void queue_pop(struct queue *f, void *res);
void queue_push(struct queue *f, void *elm);
void queue_clear(struct queue *f);
int queue_isEmpty(struct queue *f);
int queue_isFull(struct queue *f);
