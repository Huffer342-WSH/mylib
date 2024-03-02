#include "../sources/median_filter.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
OLL_t list;
int arr[LIST_SIZE];
int arr2[LIST_SIZE];

// 比较函数，用于qsort排序
int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int main(int argc, char const *argv[])
{
	int a;
	OLL_init(&list);
	while (1) {
		// scanf("%d", &a);
		a = rand();
		OLL_add(&list, a);
		int in, out, num, j = 0;
		in = list.in;
		out = list.out;
		num = list.length;
		while (in != out) {
			arr[j] = list.node_value[out];
			out = (out + 1) % LIST_SIZE;
			j++;
		}
		// 排序数组
		qsort(arr, num, sizeof(int), compare);
		printf("快速排序结果：\t");
		for (int i = 0; i < num; i++) {
			printf("%d ", arr[i]);
		}
		printf("  mid:%d\n", arr[num / 2]);
		OLL_getList(&list, arr2);
		printf("有序链表中值滤波结果：\t");
		for (int i = 0; i < num; i++) {
			printf("%d ", arr2[i]);
		}
		printf("  mid:%d left:%d right:%d", list.node_value[list.mid], list.left_half,
		       list.length - list.left_half);
		assert(list.mid_value == arr[num / 2]);
		uint16_t t = list.head;
		int i = 0, acturl_left;
		while (1) {
			printf("%d ", t);
			if (t == list.mid) {
				acturl_left = i;
			}
			if (t == list.tail) {
				break;
			} else {
				t = list.next_node[t];
				i++;
			}
		}
		printf("acturl_left:%d \n", acturl_left);
		if (acturl_left != list.left_half) {
			assert(0);
		}
		for (int i = 0; i < num; i++) {
			assert(arr[i] == arr2[i]);
		}
	}

	return 0;
}
