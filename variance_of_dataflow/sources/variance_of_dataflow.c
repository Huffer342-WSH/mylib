

#include "variance_of_dataflow.h"
#include <stdint.h>

void VAR_Init(VAR_t *v, uint64_t *QSBuf, int32_t *sumBuf, uint16_t size, uint8_t cellElmNum)
{
	v->QS = QSBuf;
	v->sum = sumBuf;
	v->size = size;
	v->cellElmNum = cellElmNum;
	v->in = v->out = 0;
	v->cellQS = 0;
	v->cellSum = 0;
}

void VAR_addNum(VAR_t *v, int32_t num)
{
	v->cellSum += num;
	v->cellQS += num * num;
	v->cellElmCnt++;
	if (v->cellElmCnt == v->cellElmNum) {
		uint16_t prevIn = (v->in + v->size - 1) % v->size;
		//一个单元已经满，放入缓存
		v->sum[v->in] = v->sum[prevIn] + v->cellSum;
		v->QS[v->in] = v->QS[prevIn] + v->cellQS;
		v->in = (v->in + 1) % v->size;

		//重置cell
		v->cellSum = 0;
		v->cellQS = 0;
		v->cellElmCnt = 0;
	}
}

uint64_t VAR_GetVar(VAR_t *v, uint16_t len)
{
	uint64_t QS;
	int32_t sum;
	uint16_t cellNum;
	uint16_t end;
	uint16_t start;
	cellNum = len / v->cellElmNum;
	end = (v->in + v->size - 1) % v->size;
	start = (end + v->size - cellNum) % v->size;
	len = cellNum * v->cellElmNum; //实际上的数量
	QS = v->QS[end] - v->QS[start];
	sum = v->sum[end] - v->sum[start];
	return (QS - (int64_t)sum * (int64_t)sum / len) / len;
}
