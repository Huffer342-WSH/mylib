#include "filter_iir_comb.h"
/**
 * 
 * a[0]*y[n] = b[0]*x[n] + b[1]*x[n-1] + ... + b[M]*x[n-M]
 *                       - a[1]*y[n-1] - ... - a[N]*y[n-N]
*/

static inline void combfilter_updateEarliest(CombFiliter_t *combfilter)
{
	uint8_t temp = combfilter->latest + COMB_FILTER_MAX_STAGES - combfilter->numStages;
	if (temp >= COMB_FILTER_MAX_STAGES) {
		temp -= COMB_FILTER_MAX_STAGES;
	}
	combfilter->earliest = temp;
}

static inline void combfilter_nextLatest(CombFiliter_t *combfilter)
{
	uint8_t temp = combfilter->latest + 1;
	if (temp >= COMB_FILTER_MAX_STAGES) {
		temp = 0;
	}
	combfilter->latest = temp;
}

void combfilter_filled(CombFiliter_t *combfilter, int32_t x, int post_shift)
{
	x <<= post_shift;

	combfilter->x_fifo[combfilter->latest] = x;
	combfilter->y_fifo[combfilter->latest] = x;
	combfilter_nextLatest(combfilter);
	combfilter_updateEarliest(combfilter);
}
int32_t combfilter_new_input(CombFiliter_t *combfilter, int32_t xn, int post_shift)
{
	int64_t acc;
	int32_t yn;

	xn <<= post_shift;
	acc = (int64_t)combfilter->b0 * xn;
	acc += (int64_t)combfilter->bn * combfilter->x_fifo[combfilter->earliest];
	acc -= (int64_t)combfilter->an * combfilter->y_fifo[combfilter->earliest];
	yn = (int32_t)(acc >> 27);

	combfilter->x_fifo[combfilter->latest] = xn;
	combfilter->y_fifo[combfilter->latest] = yn;
	combfilter_nextLatest(combfilter);
	combfilter_updateEarliest(combfilter);
	return yn >> post_shift;
}

void iircomb(float w0, float Q, float fs, float *b, float *a)
{
	// Compute the order of the filter
	int N = (int)(fs / w0);

	w0 = (2 * 3.141592653589793 * w0) / fs;
	float w_delta = w0 / Q;

	// float beta = tanf(N * w_delta / 4);
	float beta = tanf(1.5707963267948966 / Q);

	float ax = (1 - beta) / (1 + beta);
	float bx = 1.0 / (1 + beta);
	float cx = 1.0 / (1 + beta);

	b[0] = bx;
	b[1] = cx;

	a[0] = 1.0f;
	a[1] = ax;
}
