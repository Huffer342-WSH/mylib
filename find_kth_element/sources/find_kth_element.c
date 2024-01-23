#include "find_kth_element.h"
#include <stdio.h>
/**
 * @brief 查找从小到大数第N个数(从0开始)
 * 
 * @details 数组中的数会发生位置交换，保证带查找数的左边都比它小，右边都比它大
 *  时间复杂度：O(n)
 * @param arr 带查找数组数组
 * @param len 数组长度
 * @param rk 待查找数的序号，正序排列
 * @return elm 
 */
elm find_kth_element(elm arr[], unsigned int len, unsigned int rk)
{
	elm key;
	elm left, right;
	elm start, end;

	start = left = 0;
	end = right = len - 1;
	do {
		key = arr[start];
		while (right != left) {
			while (right > left && arr[right] >= key) {
				--right;
			}
			arr[left] = arr[right];
			while (left < right && arr[left] <= key) {
				left++;
			}
			arr[right] = arr[left];
		}
		arr[left] = key;

		if (left == rk) {
			break;
		} else if (left > rk) {
			left = start;
			end = --right;
		} else {
			right = end;
			start = ++left;
		}

	} while (1);
	return key;
}
