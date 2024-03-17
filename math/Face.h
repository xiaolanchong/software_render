#pragma once

#include "vector.h"

struct Face
{
	Vector   v[3];  /// vertices
	Vector   n[3];  /// normal
	Vector2D t[3];  /// texture coordinates

	Vector& operator[](size_t i)
	{
		ASSERT( i < 3 );
		return v[i];	
	}

	const Vector& operator[](size_t i) const
	{
		ASSERT( i < 3 );
		return v[i];	
	}

	Face(	const Vector& v1, const Vector& v2, const Vector& v3,
			const Vector& n1, const Vector& n2, const Vector& n3,
			const Vector2D& t1 = Vector2D(0.0f), 
			const Vector2D& t2 = Vector2D(0.0f), 
			const Vector2D& t3 = Vector2D(0.0f))
	{
		v[0] = v1;
		v[1] = v2;
		v[2] = v3;

		n[0] = n1;
		n[1] = n2;
		n[2] = n3;

		t[0] = t1;
		t[1] = t2;
		t[2] = t3;
 	}
};
