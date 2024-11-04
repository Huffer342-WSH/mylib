
#include "filter_iir.h"

/**
 * @brief 实现IIR（无限冲激响应）滤波器的函数。
 * 	该函数根据IIR滤波器的系数和输入样本，计算并返回滤波器的输出
 * 	它使用了延迟线（buffer）来存储过去的输入和输出值，以便在计算当前输出时使用。
 * @param coef 指向包含IIR滤波器系数的结构体的指针。这些系数决定了滤波器的特性和功能。
 * @param buffer 指向包含滤波器延迟线的结构体的指针。延迟线用于存储过去的输入和输出样本。
 * @param newInput 新的输入样本值，将被滤波器处理并返回输出。
 * @return int32_t 返回滤波器的输出值，为32位整数。
 * 
 * @note  计算方式：
 * 	      a[0]*y[n] = b[0]*x[n] + b[1]*x[n-1] + ... + b[M]*x[n-M]
 *                         	    - a[1]*y[n-1] - ... - a[N]*y[n-N] 
 * 		  
 */
int32_t filter_iir(IirFilter_Coef_Q27_t *coef, IirFilter_Buffer_Q27_t *buffer, int32_t newInput)
{
	int64_t acc;
	int32_t *pA, *pB, ret;
	pA = &(coef->a[1]);
	pB = &(coef->b[1]);

	acc = (int64_t)coef->b[0] * newInput; //b[0]*x[n]
	//buffer.x[k] 存储x[n-1+k]，应该与coef.a[1+k]相乘
	for (int i = 0; i < coef->numStages; i++) {
		acc += (int64_t)(pB[i]) * buffer->x[i];
		acc -= (int64_t)(pA[i]) * buffer->y[i];
	}

	for (int i = coef->numStages - 1; i >= 1; i--) {
		buffer->x[i] = buffer->x[i - 1];
		buffer->y[i] = buffer->y[i - 1];
	}
	ret = (int32_t)(acc >> 27);
	buffer->x[0] = newInput;
	buffer->y[0] = ret;
	return ret;
}
