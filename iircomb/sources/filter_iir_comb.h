/**
 * @file filiter_iir_comb.h
 * @author Huffer342-WSH (718007138@qq.com)
 * @brief Q2.14梳状滤波器
 * @version 0.1
 * @date 2024-05-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdint.h>
#include <math.h>
// N = ((int)((fs) / (w0)))
//  w0_val = ((2 * M_PI * (w0)) / (fs))
//w_delta = (w0_val) / (Q);
// beta = (tan(1.5707963267948966 / (Q)))
#define COMB_FILTER_BETA(Q) (tan(1.5707963267948966 / (Q)))
#define DESIGN_COMB_PZ_FILTER_B0(Q) (1.0 / (1.0 + COMB_FILTER_BETA(Q)))
#define DESIGN_COMB_PZ_FILTER_Bn(Q) DESIGN_COMB_PZ_FILTER_B0(Q)
#define DESIGN_COMB_PZ_FILTER_A0(Q) (1.0)
#define DESIGN_COMB_PZ_FILTER_An(Q) ((1.0 - COMB_FILTER_BETA(Q)) / (1.0 + COMB_FILTER_BETA(Q)))

#define DESIGN_COMB_FILTER_B0(Q) (1.0 / (1.0 + COMB_FILTER_BETA(Q)))
#define DESIGN_COMB_FILTER_Bn(Q) (-DESIGN_COMB_FILTER_B0(Q))
#define DESIGN_COMB_FILTER_A0(Q) 1.0
#define DESIGN_COMB_FILTER_An(Q) ((COMB_FILTER_BETA(Q) - 1.0) / (1.0 + COMB_FILTER_BETA(Q)))
/**
 * 
 * a[0]*y[n] = b[0]*x[n] + b[1]*x[n-1] + ... + b[M]*x[n-M]
 *                       - a[1]*y[n-1] - ... - a[N]*y[n-N]
*/
#define COMB_FILTER_MAX_STAGES 40
typedef int32_t q27_t;
typedef struct {
	q27_t a0, an, b0, bn; //有符号Q2.14，一般来说a0等于1，其他值小于1
	int32_t x_fifo[COMB_FILTER_MAX_STAGES];
	int32_t y_fifo[COMB_FILTER_MAX_STAGES];
	uint8_t latest, earliest;
	uint8_t numStages;
} CombFiliter_t;

void combfilter_filled(CombFiliter_t *combfilter, int32_t x, int post_shift);
int32_t combfilter_new_input(CombFiliter_t *combfilter, int32_t xn, int post_shift);
void iircomb(float w0, float Q, float fs, float *b, float *a);
