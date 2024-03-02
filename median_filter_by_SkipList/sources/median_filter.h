#ifndef _ORDERED_LINKED_LIST_H_
#define _ORDERED_LINKED_LIST_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#define LIST_SIZE 256

typedef int elm;

typedef struct {
	elm node_value[LIST_SIZE];
	elm next_node[LIST_SIZE];
	elm prev_node[LIST_SIZE];
	elm mid_value;
	uint16_t in, out;
	uint16_t head, tail, mid, length, left_half;
} OLL_t;

void OLL_init(OLL_t *list);
void OLL_add(OLL_t *list, elm node);
void OLL_remove(OLL_t *list);
uint16_t OLL_getList(OLL_t *list, elm arr[]);
elm OLL_getMid(OLL_t *list);

#ifdef __cplusplus
}
#endif
#endif /* _ORDERED_LINKED_LIST_H_ */
