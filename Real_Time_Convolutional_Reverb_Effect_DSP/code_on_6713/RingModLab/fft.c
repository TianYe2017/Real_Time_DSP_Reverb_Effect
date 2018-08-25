#include "common.h"
#include "stdlib.h"
#include "fft.h"

void fft(COMPLEX *Y, int M, COMPLEX *w)
{
	COMPLEX temp1, temp2;
	int i, j, k;
	int upper_leg, lower_leg;
	int leg_diff;
	int num_stages = 0;
	int index, step;
	i = 1;
	do
	{
		num_stages += 1;
		i = i * 2;
	} while (i != M);
	leg_diff = M / 2;
	step = 2;
	for (i = 0; i < num_stages; i++)
	{
		index = 0;
		for (j = 0; j<leg_diff; j++)
		{
			for (upper_leg = j; upper_leg<M; upper_leg += (2 * leg_diff))
			{
				lower_leg = upper_leg + leg_diff;
				temp1.real = (Y[upper_leg]).real + (Y[lower_leg]).real;
				temp1.imag = (Y[upper_leg]).imag + (Y[lower_leg]).imag;
				temp2.real = (Y[upper_leg]).real - (Y[lower_leg]).real;
				temp2.imag = (Y[upper_leg]).imag - (Y[lower_leg]).imag;
				(Y[lower_leg]).real = ((temp2.real)*(w[index]).real
					- (temp2.imag)*(w[index]).imag) / 10;
				(Y[lower_leg]).imag = ((temp2.real)*(w[index]).imag
					+ (temp2.imag)*(w[index]).real) / 10;
				(Y[upper_leg]).real = temp1.real;
				(Y[upper_leg]).imag = temp1.imag;
			}
			index += step;
		}
		leg_diff = leg_diff / 2;
		step *= 2;
	}
	j = 0;
	for (i = 1; i<(M - 1); i++)   //bit reversal for resequencing data
	{
		k = M / 2;
		while (k <= j)
		{
			j = j - k;
			k = k / 2;
		}
		j = j + k;
		if (i<j)
		{
			temp1.real = (Y[j]).real;
			temp1.imag = (Y[j]).imag;
			(Y[j]).real = (Y[i]).real;
			(Y[j]).imag = (Y[i]).imag;
			(Y[i]).real = temp1.real;
			(Y[i]).imag = temp1.imag;
		}
	}
	return;
}