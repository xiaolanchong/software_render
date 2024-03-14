#ifndef _MATRIX_UTIL_7591505835908090_
#define _MATRIX_UTIL_7591505835908090_

class Matrix;
class Vector;

//! \brief Math matrix utility functions
//! \author 
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

void	PerspectiveFov( Matrix& m, float fovy, float Aspect, float zn, float zf );
void	OrthoOffCenter ( Matrix& m, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf );

void	LookAt( Matrix& m, const Vector& vEye, const Vector& vAt, const Vector& vUp );

#endif // _MATRIX_UTIL_7591505835908090_