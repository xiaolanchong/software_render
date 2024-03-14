//////////////////////////////////////////////////////////
// basic vector library                                 //
//    all major operators overloaded to support vectors //
//////////////////////////////////////////////////////////

#ifndef	__VECTOR__
#define	__VECTOR__

#include	<math.h>

class	Vector
{
public:
	float	x, y, z;

	Vector () {};
	Vector ( float v ) { x = y = z = v; };
	Vector ( const Vector& v ) { x = v.x; y = v.y; z = v.z; };
	Vector ( float vx, float vy, float vz ) { x = vx; y = vy; z = vz; };

	Vector&	operator = ( const Vector& v ) { x = v.x; y = v.y; z = v.z; return *this; };
	Vector& operator = ( float f ) { x = y = z = f; return *this; };
	Vector  operator - () const;

	Vector&	operator += ( const Vector& );
	Vector& operator -= ( const Vector& );
	Vector&	operator *= ( const Vector& );
	Vector& operator *= ( float );
	Vector&	operator /= ( float );

	friend	Vector operator + ( const Vector&, const Vector& );
	friend	Vector operator - ( const Vector&, const Vector& );
	friend	Vector operator * ( const Vector&, const Vector& );
	friend	Vector operator * ( float, const Vector&  );
	friend	Vector operator * ( const Vector&, float  );
	friend	Vector operator / ( const Vector&, float  );
	friend	Vector operator / ( const Vector&, const Vector& );
	friend	float operator & ( const Vector& u, const Vector& v ) { return u.x*v.x + u.y*v.y + u.z*v.z; };
	friend	Vector operator ^ ( const Vector&, const Vector& );

	float	operator !  () const { return (float) sqrt ( x*x + y*y + z*z ); };
	float&	operator [] ( int n ) { return * ( &x + n ); };
	int	operator <  ( float v ) { return x < v && y < v && z < v; };
	int	operator >  ( float v ) { return x > v && y > v && z > v; };
};

struct Vector2D
{
	float	x, y;

	Vector2D () {};
	Vector2D ( float v ) { x = y = v; };
	Vector2D ( const Vector2D& v ) { x = v.x; y = v.y; };
	Vector2D ( float vx, float vy ) { x = vx; y = vy; };

};

//////////////////// implementation /////////////////////////

inline	Vector	Vector :: operator - () const
{
	return Vector ( -x, -y, -z );
}

inline	Vector	operator + ( const Vector& u, const Vector& v )
{
	return Vector ( u.x + v.x, u.y + v.y, u.z + v.z );
}

inline	Vector	operator - ( const Vector& u, const Vector& v )
{
	return Vector ( u.x - v.x, u.y - v.y, u.z - v.z );
}

inline	Vector	operator * ( const Vector& u, const Vector& v )
{
	return Vector ( u.x * v.x, u.y * v.y, u.z * v.z );
}

inline	Vector	operator * ( const Vector& u, float f )
{
	return Vector ( u.x * f, u.y * f, u.z * f );
}

inline	Vector	operator * ( float f, const Vector& v )
{
	return Vector ( f * v.x, f * v.y, f * v.z );
}

inline	Vector	operator / ( const Vector& v, float f )
{
	return Vector ( v.x / f, v.y / f, v.z / f );
}

inline	Vector	operator / ( const Vector& u, const Vector& v )
{
	return Vector ( u.x / v.x, u.y / v.y, u.z / v.z );
}

inline	Vector&	Vector :: operator += ( const Vector& v )
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

inline	Vector&	Vector :: operator -= ( const Vector& v )
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

inline	Vector&	Vector :: operator *= ( float v )
{
	x *= v;
	y *= v;
	z *= v;

	return *this;
}

inline	Vector&	Vector :: operator *= ( const Vector& v )
{
	x *= v.x;
	y *= v.y;
	z *= v.z;

	return *this;
}

inline	Vector&	Vector :: operator /= ( float v )
{
	x /= v;
	y /= v;
	z /= v;

	return *this;
}

/////////////////////////// Functions /////////////////////////////////

inline	Vector	Normalize ( const Vector& v ) { return v / !v; };
Vector	RndVector ();
Vector&	Clip ( Vector& );
#endif
