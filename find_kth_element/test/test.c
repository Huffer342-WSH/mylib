#include "../sources/find_kth_element.h"
#define NUM 100000
int arr[NUM], arr2[NUM];

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// 比较函数，用于qsort排序
int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}
int test(int num, int index)
{
	// 生成num个随机整数

	int res;
	for (int i = 0; i < num; i++) {
		arr[i] = rand();
		arr2[i] = arr[i];
	}

	// 排序数组
	qsort(arr, num, sizeof(int), compare);

	// 打印排序后的数组
	// printf("排序后的数组：");
	for (int i = 0; i < num; i++) {
		// printf("%d ", arr[i]);
	}
	res = find_kth_element(arr2, num, index);

	// printf("%d,%d\n", arr[index], res);
	return (arr[index] == res);
}
int main()
{
	int i = 0;
	while (i < 100 && test(NUM, NUM / 2)) {
		i++;
		printf("%d\n", i);
		if (i == 31) {
			i = 31;
		}
	}
	if (i < 100) {
		printf("error!!!!");
	} else {
		printf("success");
	}
}
