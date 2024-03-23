
#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

inline float Deg2Rad(float d)
{
	return float(M_PI) * d/180;
}

template <typename T>  T clamp( T val, T min, T max)
{ 
	return (((val) > (max)) ? (max) : (((val) < (min)) ? (min) : (val)));
}
