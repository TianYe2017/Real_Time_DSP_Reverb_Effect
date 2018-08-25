#pragma once
#ifndef _COMPLEX_NUMBER_H_
#define _COMPLEX_NUMBER_H_

#include "common.h"

struct cmpx
{
	float real;
	float imag;
};
typedef struct cmpx COMPLEX;

extern COMPLEX conv_from_polar(float r, float theta);

extern COMPLEX c_add(COMPLEX a, COMPLEX b);

extern COMPLEX c_mul(COMPLEX a, COMPLEX b);

#endif