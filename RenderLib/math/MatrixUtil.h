#pragma once

class Matrix;
class Vector;

/// Math matrix utility functions
void	PerspectiveFov( Matrix& m, float fovy, float Aspect, float zn, float zf );
void	OrthoOffCenter ( Matrix& m, float l, float r, float b, float t, float zn, float zf );

void	LookAt( Matrix& m, const Vector& vEye, const Vector& vAt, const Vector& vUp );
