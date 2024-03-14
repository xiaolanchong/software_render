#include "stdafx.h"
#include "Matrix.h"
#include "MatrixUtil.h"

void	PerspectiveFov( Matrix& m, float fovy, float Aspect, float zn, float zf )
{
//	see gluPerspective  & D3DXMatrixPerspectiveFovLH 
//	xScale     0          0              0
//		0        yScale       0              0
//		0        0        zf/(zn-zf)        -1
//		0        0        zn*zf/(zn-zf)      0
//where:
//	yScale = cot(fovY/2)
//	xScale = aspect ratio * yScale

	m.Clear();
	m.x[1][1] = 1.0f/tan( fovy/2 );
	m.x[0][0] = m.x[1][1] / Aspect;
	m.x[2][2] = -zf/ (zn-zf);
	m.x[3][2] = - zn * zf/ (zn-zf);
	m.x[2][3] = 1;
}

void	OrthoOffCenter ( Matrix& m, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf )
{
//	2/(r-l)      0            0           0
//		0            2/(t-b)      0           0
//		0            0            1/(zn-zf)   0
//		(l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1 

	m.Clear();
	m.x[0][0]	= 2/(r - l);
	m.x[1][1] = 2/(t - b);
	m.x[2][2] = 1/(zn - zf);
	m.x[3][0] = ( l + r )/( l - r );
	m.x[3][1] = ( t + b )/( t - b );
	m.x[3][2] = zn/( zn - zf );
	m.x[3][3] = 1;
}

void	LookAt( Matrix& m, const Vector& vEye, const Vector& vAt, const Vector& vUp )
{
//	zaxis = normal(Eye - At)
//		xaxis = normal(cross(Up, zaxis))
//		yaxis = cross(zaxis, xaxis)
//
//		xaxis.x           yaxis.x           zaxis.x          0
//		xaxis.y           yaxis.y           zaxis.y          0
//		xaxis.z           yaxis.z           zaxis.z          0
//		-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1
	Vector zaxis = -Normalize(vEye - vAt);
	Vector xaxis = Normalize(vUp ^ zaxis);
	Vector yaxis = zaxis ^ xaxis;
	
	m.x[0][0] = xaxis.x;
	m.x[0][1] = yaxis.x;
	m.x[0][2] = zaxis.x;
	m.x[0][3] = 0;

	m.x[1][0] = xaxis.y;
	m.x[1][1] = yaxis.y;
	m.x[1][2] = zaxis.y;
	m.x[1][3] = 0;

	m.x[2][0] = xaxis.z;
	m.x[2][1] = yaxis.z;
	m.x[2][2] = zaxis.z;
	m.x[2][3] = 0;

	m.x[3][0] = - xaxis & vEye;
	m.x[3][1] = - yaxis & vEye;
	m.x[3][2] = - zaxis & vEye;
	m.x[3][3] = 1;
}