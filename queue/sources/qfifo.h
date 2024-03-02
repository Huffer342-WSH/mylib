/**
 * @file qfifo.h
 * @author Huffer342-WSH (718007138@qq.com)
 * @brief 快速FIFO,深度为2的幂
 * @note 在单片机中常用，全部由宏实现，执行速度快
 * @example 
 * #include "qfifo.h"
 * QFIFO_Declare(qfifo_t, 5, uint16_t, int);//声明类型;
 * qfifo_t f = { .in = 0, .out = 0 };
 * if(!(QFIFO_isFull))	QFIFO_Push(10);
 * int res = QFIFO_Pop(f);
 * 
 * @version 0.1
 * @date 2024-03-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _QFIFO_H_
#define _QFIFO_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define typecheck(type, x)                     \
	({                                     \
		type __dummy;                  \
		typeof(x) __dummy2;            \
		(void)(&__dummy == &__dummy2); \
		1;                             \
	})

/**
 * @brief QFIFO结构体声明
 * @param name 结构体名字
 * @param exp  fifo深度的2的对数，例如深度32对应exp=5
 * @param indextype 索引变量in和out的变量类型
 * @param elmtype fifo内部元素的数据类型
 * 
 */
#define QFIFO_Declare(name, exp, indextype, elmtype) \
	typedef struct _##name {                     \
		volatile indextype in;               \
		volatile indextype out;              \
		elmtype data[1 << exp];              \
	} name

#define QFIFO_Size(fifo) ((typeof(fifo.in))(sizeof(fifo.data) / sizeof(fifo.data[0]))) //fifo大小
#define QFIFO_Mask(fifo) ((typeof(fifo.in))(QFIFO_Size(fifo) - 1)) //fifo索引掩码

#define QFIFO_New(type, name) type name = { .in = 0, .out = 0 } //创建QFIFO
#define QFIFO_Init(name) \
	(name.in = name.out = 0) //初始化QFIFO，使用QFIFO_New创建的QFIFO不需要初始化

#define QFIFI_NextIn(fifo) ((fifo.in + 1) & QFIFO_Mask(fifo)) //QFIFO in指针的下一位
#define QFIFI_NextOut(fifo) ((fifo.out + 1) & QFIFO_Mask(fifo)) //QFIFO out指针的下一位

#define QFIFO_isEmpty(fifo) (fifo.in == fifo.out) //QFIFO是否为空
#define QFIFO_isFull(fifo) (QFIFI_NextIn(fifo) == fifo.out) //QFIFO是否为满

#define QFIFO_Push(fifo, elm) \
	(fifo.data[fifo.in] = elm, fifo.in = (fifo.in + 1) & QFIFO_Mask(fifo)) //QFIFO入队
#define QFIFO_ForcePush(fifo, elm) \
	(QFIFO_Push(fifo, elm),    \
	 if (fifo.in == fifo.out) fifo.out = QFIFI_NextOut(fifo)) //QFIFO强制入队

#define QFIFO_Pop(fifo)                                                \
	({                                                             \
		typeof(fifo.data[fifo.out]) tmp = fifo.data[fifo.out]; \
		fifo.out = (fifo.out + 1) & QFIFO_Mask(fifo);          \
		tmp;                                                   \
	}) //QFIFO出队

#define QFIFO_Clear(fifo) (fifo.out = fifo.in) //QFIFO清空

#ifdef __cplusplus
}
#endif
#endif /* _QFIFO_H_ */
