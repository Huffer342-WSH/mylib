#ifndef _ORDERED_LINKED_LIST_H_
#define _ORDERED_LINKED_LIST_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#define LIST_SIZE 256
typedef struct {
	int32_t cellSum;
	uint64_t cellQS;
	uint8_t cellElmNum;
	uint8_t cellElmCnt;
	uint64_t *QS; //平方和的前缀和
	int32_t *sum; //和的前缀和
	uint16_t in, out, size;
} VAR_t;
void VAR_Init(VAR_t *v, uint64_t *QSBuf, int32_t *sumBuf, uint16_t size, uint8_t cellElmNum);
void VAR_addNum(VAR_t *v, int32_t num);
uint64_t VAR_GetVar(VAR_t *v, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif /* _ORDERED_LINKED_LIST_H_ */
