#pragma once

#include	"Vector.h"

class Matrix
{
public:
	float x [4][4];

	Matrix() = default;
	Matrix ( float );

	Matrix& operator += ( const Matrix& );
	Matrix& operator -= ( const Matrix& );
	Matrix& operator *= ( const Matrix& );
	Matrix& operator *= ( float );

	void	Invert ();
	void	Transpose ();
	void	Clear();
	friend	Matrix operator + ( const Matrix&, const Matrix& );
	friend	Matrix operator - ( const Matrix&, const Matrix& );
	friend	Matrix operator * ( const Matrix&, float );
	friend	Matrix operator * ( const Matrix&, const Matrix& );
	friend	Vector operator * ( const Matrix&, const Vector& );
};

Matrix	Translate ( const Vector& );
Matrix	Scale     ( const Vector& );
Matrix	RotateX   ( float );
Matrix	RotateY   ( float );
Matrix	RotateZ   ( float );
Matrix	MirrorX   ();
Matrix	MirrorY   ();
Matrix	MirrorZ   ();
