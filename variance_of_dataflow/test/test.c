#include "../sources/variance_of_dataflow.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

uint64_t buf1[20];
int32_t buf2[20];
VAR_t v;

int main(int argc, char const *argv[])
{
	VAR_Init(&v, buf1, buf2, 20, 4);
	for (int32_t i = 0; i < 100; i++) {
		VAR_addNum(&v, i);
		printf("var = %ld\n", VAR_GetVar(&v, 40));
	}

	return 0;
}
