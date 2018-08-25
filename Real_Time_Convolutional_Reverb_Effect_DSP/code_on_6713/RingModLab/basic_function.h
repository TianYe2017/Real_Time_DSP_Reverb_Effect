#pragma once
#ifndef _BASIC_FUNCTION_H_
#define _BASIC_FUNCTION_H_

#include "common.h"
#include "complex_number.h"
#include "pinv.h"

extern void cosine(COMPLEX* data, COMPLEX *cosine_win, int Len);
extern void m_rec2sq(float(*input)[Max_Dimension], float num[Max_Dimension][Max_Dimension], float h, float w);
extern void m_rec2sq_a(float(*input)[Time * Freq], float num[Max_Dimension][Max_Dimension], float h, int *ind, int ind_size);
extern void m_rec2sq_ad(float(*input)[Time * Freq], float num[Freq][Freq], float h, int *ind, int ind_size);

#endif