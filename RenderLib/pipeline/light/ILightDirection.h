﻿#pragma once

#include "../../math/Vector.h"

/// Модель интенсивности и направления света
class ILightType
{
public:
	virtual std::pair<Vector,float>	GetDirection(const Vector& v) = 0;
	virtual ~ILightType() = default;
};

using ILightTypePtr = std::unique_ptr<ILightType>;

//! направленнный свет с постоянной интенсивностью
class DirectLight : public ILightType
{
	Vector	m_LightDirection;
public:
	DirectLight( const Vector& v ) : m_LightDirection( v )
	{
		Normalize(m_LightDirection) ;
	}
	std::pair<Vector,float>	GetDirection(const Vector& /*v*/) 
	{
		return std::make_pair( m_LightDirection, 1.0f );
	}
};

//! точечный источник с постоянной интенсивностью
class PointLight : public ILightType
{
	Vector	m_LightPosition;
public:
	PointLight( const Vector& v ) : m_LightPosition(v){}
	std::pair<Vector,float>	GetDirection(const Vector& v) 
	{
		return std::make_pair( Normalize( m_LightPosition - v ), 1.0f );
	}
};

//! точечный источник с линейно уменьшающейся интенсивностью
class PointLightWithAttenuation : public ILightType
{
	Vector	m_LightPosition;
	float	m_Atten0;
	float	m_Atten1;
	//	float	m_Atten2;
public:
	PointLightWithAttenuation( const Vector& v, float Atten1 ) : 
	  m_LightPosition(v),
		  m_Atten0(1.0f),
		  m_Atten1(Atten1)
	  {}
	  std::pair<Vector,float>	GetDirection(const Vector& v) 
	  {
		  Vector dist = m_LightPosition - v ;
		  float Atten = 1.0f/( m_Atten1 * !dist + m_Atten0 );
		  return std::make_pair( Normalize( dist), Atten );
	  }
};

class SpotLight : public ILightType
{
	Vector	m_LightPosition;
	Vector  m_LightDirection;
	float	m_Atten0;
	float	m_Atten1;
	float	m_Atten2;
	float	m_Theta;
	float	m_Phi;
	float	m_Falloff;

	float	GetSpotLightFactor(float rho)
	{
		float innerCone = cosf( Deg2Rad( m_Theta/2 ) );
		float outerCone = cosf( Deg2Rad( m_Phi/2 ) );
		if		( rho > innerCone )		return 1.0f;
		else if	( rho < outerCone )		return 0.0f;
		else	
		{
			float f = ( rho - outerCone ) / ( innerCone - outerCone );
			f =  expf( m_Falloff * logf( f ) );
			return f;
		}
	}
public:
	SpotLight(	const Vector& vPos, const Vector& vDir, 
				float Atten1, float Theta, float Phi, float Falloff) : 
		m_LightPosition(vPos ),
		m_LightDirection( -Normalize(vDir)),
		m_Atten0(1.0f),
		m_Atten1(Atten1),
		m_Atten2(0.0f),
		m_Theta( Theta ),
		m_Phi( Phi ),
		m_Falloff( Falloff )
	  {
		  assert( Falloff > 0.0f );
		  assert( Theta >= 0.0f	&& Theta < 180.0f );
		  assert( Phi >= 0.0f	&& Phi < 180.0f );
		  assert( Theta <= Phi );
	  }

	  std::pair<Vector,float>	GetDirection(const Vector& v) 
	  {
		  Vector dist = m_LightPosition - v ;
		  Vector dir = Normalize( dist);
		  float rho = m_LightDirection & dir;
		  float Atten = 1.0f/( m_Atten1 * !dist + m_Atten0 );
		  return std::make_pair( Normalize( dist), Atten * GetSpotLightFactor( rho ) );
	  }
};
