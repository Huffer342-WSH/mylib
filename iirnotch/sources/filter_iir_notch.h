#ifndef _FILITER_IIR_NOTCH_H_
#define _FILITER_IIR_NOTCH_H_
#include "filter_iir.h"

#include <math.h>
// b[0] = gain;
// b[1] = -2.0 * gain * cos(w0);
// b[2] = gain;
// a[0] = 1.0;
// a[1] = -2.0 * gain * cos(w0);
// a[2] = 2.0 * gain - 1.0;
// double _w0 = (2 * (double)(w0) / (double)(fs) * 3.1415926535897932384626433832795); \
// double _gain = (1.0 / (1.0 + ((sqrt(1.0 - (1.0 / sqrt(2)) * (1.0 / sqrt(2))) / (1.0 / sqrt(2))) *  tan(((2 * (double)(w0) / (double)(fs) * 3.1415926535897932384626433832795) / (double)(Q)) / 2.0))));
#define DESIGN_NOTCH_FILTER_B0(w0, Q, fs)                                                      \
	((1.0 /                                                                                \
	  (1.0 + ((sqrt(1.0 - (1.0 / sqrt(2)) * (1.0 / sqrt(2))) / (1.0 / sqrt(2))) *          \
		  tan(((2 * (double)(w0) / (double)(fs) * 3.1415926535897932384626433832795) / \
		       (double)(Q)) /                                                          \
		      2.0)))))

#define DESIGN_NOTCH_FILTER_B1(w0, Q, fs)                                                      \
	(-2.0 * cos(2 * (double)(w0) / (double)(fs) * 3.1415926535897932384626433832795) *     \
	 (1.0 /                                                                                \
	  (1.0 + ((sqrt(1.0 - (1.0 / sqrt(2)) * (1.0 / sqrt(2))) / (1.0 / sqrt(2))) *          \
		  tan(((2 * (double)(w0) / (double)(fs) * 3.1415926535897932384626433832795) / \
		       (double)(Q)) /                                                          \
		      2.0)))))

#define DESIGN_NOTCH_FILTER_B2(w0, Q, fs) (DESIGN_NOTCH_FILTER_B0(w0, Q, fs))
#define DESIGN_NOTCH_FILTER_A0(w0, Q, fs) (1.0)
#define DESIGN_NOTCH_FILTER_A1(w0, Q, fs) (DESIGN_NOTCH_FILTER_B1(w0, Q, fs))
#define DESIGN_NOTCH_FILTER_A2(w0, Q, fs)                                                         \
	(2.0 * (1.0 / (1.0 + ((sqrt(1.0 - (1.0 / sqrt(2)) * (1.0 / sqrt(2))) / (1.0 / sqrt(2))) * \
			      tan(((2 * (double)(w0) / (double)(fs) *                             \
				    3.1415926535897932384626433832795) /                          \
				   (double)(Q)) /                                                 \
				  2.0)))) -                                                       \
	 1.0)

#ifdef __cplusplus
extern "C" {
#endif
void design_notch_peak_filter(double w0, double Q, char *ftype, double fs, double *b, double *a);

#ifdef __cplusplus
}
#endif
#endif /* _FILITER_IIR_NOTCH_H_ */
