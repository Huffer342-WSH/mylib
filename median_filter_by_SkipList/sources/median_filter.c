/**
 * @file median_filter.c
 * @author Huffer342-WSH (718007138@qq.com)
 * @brief 中值滤波器，基于循环队列和链表实现
 * 循环队列用于保存数据，实现动态窗口
 * 有序链表用于快速查找中值，属于一种特殊的二阶跳表
 * 输入新值时，将新值插入链表，并根据新值插入的位置找到中值的位置
 * 当前版本使用双向链表，
 * @version 0.1
 * @date 2024-01-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "median_filter.h"
#include <stdint.h>

void OLL_init(OLL_t *list)
{
	list->in = 0;
	list->out = 0;
	list->head = 0;
	list->length = 0;
}

void OLL_add(OLL_t *list, elm node)
{
	uint16_t left, right, cur;
	cur = list->in;

	if (list->length == LIST_SIZE - 1) {
		OLL_remove(list);
	}

	/* 循环队列入队 */
	list->node_value[cur] = node;
	list->in = (list->in + 1) % LIST_SIZE;
	list->length++;

	if (list->length == 1) {
		//第一个节点 特例
		list->head = cur;
		list->tail = cur;
		list->mid = cur;
		list->left_half = 0;
		list->next_node[cur] = LIST_SIZE;
		list->prev_node[cur] = LIST_SIZE;
		list->mid_value = node;
		return;
	}

	/* 更新链表，保持链表有序 */
	if (node <= list->node_value[list->head]) {
		//新节点小于等于链表头 新节点作为新的链表头
		list->prev_node[list->head] = cur;
		list->next_node[cur] = list->head;
		list->prev_node[cur] = LIST_SIZE;
		list->head = cur;
		list->left_half++;
	} else if (node >= list->node_value[list->tail]) {
		//新节点大于链表尾，添加到链表尾部
		list->next_node[list->tail] = cur;
		list->prev_node[cur] = list->tail;
		list->next_node[cur] = LIST_SIZE;
		list->tail = cur;
	} else {
		//新节点在链表中间
		if (node < list->mid_value) {
			//新节点在前一半，从头开始找
			right = list->head;
			list->left_half++;
		} else {
			//新节点大于等于中值，从mid开始找
			right = list->mid;
		}
		do {
			//遍历到合适的位置
			left = right;
			right = list->next_node[right];
		} while (node > list->node_value[right]);
		//找到合适的位置，插入到中间
		list->next_node[left] = cur;
		list->prev_node[cur] = left;
		list->next_node[cur] = right;
		list->prev_node[right] = cur;
	}

	//更新mid
	int temp = list->length - (list->left_half << 1);
	if (temp > 1) {
		list->mid = list->next_node[list->mid];
		list->left_half++;
	} else if (temp < 0) {
		list->mid = list->prev_node[list->mid];
		list->left_half--;
	}
	list->mid_value = list->node_value[list->mid];
}

void OLL_remove(OLL_t *list)
{
	uint16_t left, right, cur;
	elm node;
	node = list->node_value[list->out];
	cur = list->out;

	/* 循环队列出队 */
	if (list->length == 0) {
		return;
	}

	list->out = (list->out + 1) % LIST_SIZE;
	list->length--;

	if (list->length == 0) {
		return;
	}

	/* 更新链表，保持链表有序 */
	if (cur == list->head) {
		//删除的节点为链表头
		list->head = list->next_node[cur];
		list->prev_node[list->head] = LIST_SIZE;
		list->left_half--;
	} else if (cur == list->tail) {
		//删除的节点为链表尾
		list->tail = list->prev_node[cur];
		list->next_node[cur] = LIST_SIZE;
	} else {
		if (node < list->mid_value) {
			//删除的值在前一半
			list->left_half--;
		} else if (cur == list->mid) {
			//删除的是中值，必须更新中值
			list->mid = list->next_node[list->mid];
		} else if (node == list->mid_value) {
			//删除的点等于中值，需要遍历一半等于中值的点才能判断删除的点在什么位置
			uint16_t t;
			t = list->prev_node[list->mid];
			while (t != cur && list->node_value[t] == list->mid_value) {
				//向前遍历
				t = list->prev_node[t];
			}
			if (t == cur) {
				//在前一半找到被了删除的节点
				list->left_half--;
			}
		}
		left = list->prev_node[cur];
		right = list->next_node[cur];
		list->next_node[left] = right;
		list->prev_node[right] = left;
	}

	//更新mid
	uint16_t temp = list->left_half << 1;
	if (cur == list->mid) {
	} else if (list->length > 1 + temp) {
		list->left_half++;
		list->mid = list->next_node[list->mid];
	} else if (list->length < temp) {
		list->left_half--;
		list->mid = list->prev_node[list->mid];
	}
	list->mid_value = list->node_value[list->mid];
}

uint16_t OLL_getList(OLL_t *list, elm arr[])
{
	uint16_t t = list->head;
	uint16_t i = 0;
	while (1) {
		arr[i] = list->node_value[t];

		if (t == list->tail) {
			break;
		} else {
			t = list->next_node[t];
			i++;
		}
	}
	return i;
}

elm OLL_getMid(OLL_t *list)
{
	return list->mid_value;
}
