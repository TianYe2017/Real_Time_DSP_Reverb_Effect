#pragma once
#ifndef _FFT_H_
#define _FFT_H_

#include "common.h"
#include "complex_number.h"

extern void fft(COMPLEX *Y, int M, COMPLEX *w);

#endif