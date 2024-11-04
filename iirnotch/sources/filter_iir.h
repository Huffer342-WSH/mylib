#ifndef _FILTER_IIR_H_
#define _FILTER_IIR_H_

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define IIR_FILTER_MAX_STAGES (8)
/**
 * 
 * a[0]*y[n] = b[0]*x[n] + b[1]*x[n-1] + ... + b[M]*x[n-M]
 *                       - a[1]*y[n-1] - ... - a[N]*y[n-N]
*/
typedef struct {
	int32_t b[IIR_FILTER_MAX_STAGES + 1];
	int32_t a[IIR_FILTER_MAX_STAGES + 1];
	uint8_t numStages;
} IirFilter_Coef_Q27_t;

typedef struct {
	int32_t x[IIR_FILTER_MAX_STAGES];
	int32_t y[IIR_FILTER_MAX_STAGES];
} IirFilter_Buffer_Q27_t;

/* 公共变量 ---------------------*/
// 声明变量
extern const struct IIR_Coef_Q12 iircoef_2;
extern const struct IIR_Coef_Q12 iircoef_3;
extern const struct IIR_Coef_Q12 iircoef_4;
extern const struct IIR_Coef_Q12 iircoef_5;

/* 公共函数 ---------------------*/
int32_t filter_iir(IirFilter_Coef_Q27_t *coef, IirFilter_Buffer_Q27_t *buffer, int32_t newInput);
#ifdef __cplusplus
}
#endif

#endif /* _FILTER_IIR_H_ */
