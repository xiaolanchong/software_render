#ifndef _FACE_8984650245740868_
#define _FACE_8984650245740868_

#include "vector.h"

//! \brief Треугольная грань
//! \author Eugene Gorbachev (Eugene.Gorbachev@biones.com)
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

#if 1
struct Face
{
	Vector		x[3];
	Vector		n[3];
	Vector2D	t[3];

	Vector& operator[](size_t i)
	{
		ASSERT( i < 3 );
		return x[i];	
	}

	const Vector& operator[](size_t i) const
	{
		ASSERT( i < 3 );
		return x[i];	
	}

	Face(	const Vector& v1, const Vector& v2, const Vector& v3,
			const Vector& n1, const Vector& n2, const Vector& n3,
			const Vector2D& t1 = Vector2D(0.0f), 
			const Vector2D& t2 = Vector2D(0.0f), 
			const Vector2D& t3 = Vector2D(0.0f))
	{
		x[0] = v1;
		x[1] = v2;
		x[2] = v3;

		n[0] = n1;
		n[1] = n2;
		n[2] = n3;

		t[0] = t1;
		t[1] = t2;
		t[2] = t3;
 	}
};

#else
typedef Vector	Face[3];
#endif

#endif // _FACE_8984650245740868_