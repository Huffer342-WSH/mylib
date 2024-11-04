#include <stdio.h>

#include "../sources./filter_iir_comb.h"
int main()
{
	float w0 = 100.0f; // 假设的频率
	float Q = 50.0f; // 假设的Q值
	float fs = 1500.0f; // 假设的采样率
	float b[2]; // 用于存储分子系数的数组
	float a[2]; // 用于存储分母系数的数组

	// 调用函数计算滤波器系数
	iircomb(w0, Q, fs, b, a);

	// 打印结果
	printf("Numerator coefficients (b):\n");
	printf("b[0] = %f\n", b[0]);
	printf("b[1] = %f\n", b[1]);

	printf("\nDenominator coefficients (a):\n");
	printf("a[0] = %f\n", a[0]);
	printf("a[1] = %f\n", a[1]);

	// 打印结果
	printf("Numerator coefficients (b):\n");
	printf("b[0] = %f\n", DESIGN_COMB_PZ_FILTER_B0(50));
	printf("b[1] = %f\n", DESIGN_COMB_PZ_FILTER_Bn(50));

	printf("\nDenominator coefficients (a):\n");
	printf("a[0] = %f\n", DESIGN_COMB_PZ_FILTER_A0(50));
	printf("a[1] = %f\n", DESIGN_COMB_PZ_FILTER_An(50));

	printf("Numerator coefficients (b):\n");
	printf("b[0] = %f\n", DESIGN_COMB_FILTER_B0(50));
	printf("b[1] = %f\n", DESIGN_COMB_FILTER_Bn(50));

	printf("\nDenominator coefficients (a):\n");
	printf("a[0] = %f\n", DESIGN_COMB_FILTER_A0(50));
	printf("a[1] = %f\n", DESIGN_COMB_FILTER_An(50));

	return 0;
}
