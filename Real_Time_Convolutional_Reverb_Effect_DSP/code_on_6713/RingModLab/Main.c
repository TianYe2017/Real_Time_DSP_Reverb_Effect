// Ring modulator lab template.

// Must include for sine sinf(x) function.
#include <math.h>

// Must include for DSK functionality.
#include "dsk6713_aic23.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "reverb.h"

Uint32 fs=DSK6713_AIC23_FREQ_8KHZ;

#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011
Uint16 inputsource=DSK6713_AIC23_INPUT_MIC;

#define N 210
#define c 0.4735
float buffer1[N];
float buffer2[N];

interrupt void c_int11()         		
{
	int i;
	int input, output;
	short in_sample1, in_sample2;
	short out_sample1, out_sample2;
	float y1 = 0, y2 = 0;
	
	in_sample1 = input_left_sample();
	in_sample2 = input_right_sample();
	//in_sample1 = (short)(0x0000FFFF & input);
	//in_sample2 = (short)(0xFFFF0000 & input);
	
	//printf("%d, %d\n", in_sample1, in_sample2);
	
	buffer1[0] = (float)in_sample1;
	buffer2[0] = (float)in_sample2;
	
	for(i = 0; i < N; i++)
	{
		y1 += Im1[i] * buffer1[i];
		y2 += Im2[i] * buffer2[i];
	}
	
	if(DSK6713_DIP_get(0)==0)
	{
		out_sample1 = (short)(y1 / c);
		out_sample2 = (short)(y2 / c);
	}
	else
	{
		out_sample1 = in_sample1;
		out_sample2 = in_sample2;
	}
	
	for (i = N - 1; i > 0; i--)
	{
		buffer1[i] = buffer1[i - 1];
		buffer2[i] = buffer2[i - 1];
	}
	
	output = (0x0000FFFF & (out_sample1)) | 
    	     (0xFFFF0000 & ((out_sample2) << 16));
	
   	output_sample(output);
   	
	return;
}

void main()
{
  	DSK6713_DIP_init();
  	comm_intr();
	while(1);
}
