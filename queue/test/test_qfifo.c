#include "../sources/qfifo.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_QFIFO_EXP 8
QFIFO_Declare(qfifo_t, TEST_QFIFO_EXP, uint16_t, int);

uint16_t in[2000], out[2000];
int in_cnt = 0, out_cnt = 0;

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
	srand(time(NULL));
	qfifo_t q = { .in = 0, .out = 0 };

	/* 数据输入*/
	while (!QFIFO_isFull(q)) {
		uint16_t t = rand();
		QFIFO_Push(q, t);
		in[in_cnt] = t;
		in_cnt++;
	}

	/*数据输出*/
	while (!QFIFO_isEmpty(q)) {
		if (rand() % 3) {
			uint16_t t;
			t = QFIFO_Pop(q);
			out[out_cnt] = t;
			out_cnt++;
		} else if (!QFIFO_isFull(q)) {
			uint16_t t = rand();
			QFIFO_Push(q, t);
			in[in_cnt] = t;
			in_cnt++;
		}
	}

	printf("total in:%d, total out:%d\n", in_cnt, out_cnt);
	for (int i = 0; i < in_cnt; i++) {
		if (in[i] != out[i]) {
			printf("error\n");
			return 0;
		}
	}
	printf("test success");
	return 0;
}
