#include "filter_iir_notch.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define M_PI 3.14159265358979323846
void design_notch_peak_filter(double w0, double Q, char *ftype, double fs, double *b, double *a)
{
	// Guarantee that the inputs are floats

	w0 = 2 * w0 / fs;

	// Checks if w0 is within the range
	if (w0 > 1.0 || w0 < 0.0) {
		printf("w0 should be such that 0 < w0 < 1");
		return;
	}

	// Get bandwidth
	double bw = w0 / Q;

	// Normalize inputs
	bw = bw * M_PI;
	w0 = w0 * M_PI;

	// Compute -3dB attenuation
	double gb = 1 / sqrt(2);

	double beta;

	if (strcmp(ftype, "notch") == 0) {
		// Compute beta
		beta = (sqrt(1.0 - gb * gb) / gb) * tan(bw / 2.0);
	} else if (strcmp(ftype, "peak") == 0) {
		// Compute beta
		beta = (gb / sqrt(1.0 - gb * gb)) * tan(bw / 2.0);
	} else {
		printf("Unknown ftype.");
		return;
	}

	// Compute gain
	double gain = 1.0 / (1.0 + beta);

	// Compute numerator b and denominator a
	if (strcmp(ftype, "notch") == 0) {
		b[0] = gain;
		b[1] = -2.0 * gain * cos(w0);
		b[2] = gain;
	} else {
		b[0] = 1.0 - gain;
		b[1] = 0.0;
		b[2] = -(1.0 - gain);
	}
	a[0] = 1.0;
	a[1] = -2.0 * gain * cos(w0);
	a[2] = 2.0 * gain - 1.0;
}

void design_notch_filter(double w0, double Q, double fs, double *b, double *a)
{
	// Guarantee that the inputs are floats

	w0 = 2 * w0 / fs;

	// Get bandwidth
	double bw = w0 / Q;

	// Normalize inputs
	bw = bw * 3.14159265358979323846;
	w0 = w0 * 3.14159265358979323846;

	// Compute -3dB attenuation
	double gb = 1 / sqrt(2);

	double beta;

	beta = (sqrt(1.0 - gb * gb) / gb) * tan(bw / 2.0);

	// Compute gain
	double gain = 1.0 / (1.0 + beta);

	// Compute numerator b and denominator a
	b[0] = gain;
	b[1] = -2.0 * gain * cos(w0);
	b[2] = gain;
	a[0] = 1.0;
	a[1] = -2.0 * gain * cos(w0);
	a[2] = 2.0 * gain - 1.0;
}
