#include "../sources/queue.h"
#include <stdio.h>
int main(int argc, char const *argv[])
{
	printf("A Test for fifo\n");
	struct queue q;
	uint8_t src[] = { 1, 2, 3, 4 };
	uint8_t buf[16];
	q.in = 0;
	queue_init(&q, buf, sizeof(buf) / sizeof(uint8_t), sizeof(uint8_t));
	queue_push(&q, src);
	queue_push(&q, src + 1);
	queue_push(&q, src + 2);
	queue_push(&q, src + 3);
	while (!queue_isEmpty(&q)) {
		uint8_t x;
		queue_pop(&q, &x);
		printf("%d\n", x);
	}

	return 0;
}
