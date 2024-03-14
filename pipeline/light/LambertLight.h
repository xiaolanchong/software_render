#ifndef _LAMBERT_LIGHT_4403499311454775_
#define _LAMBERT_LIGHT_4403499311454775_

#include "ILightEngine.h"

//! \brief ��������� �� ��������.
//	intensity = Ambient + Diffuse * LightColor * Atten * cos(n, L),
//	��� n - ������� � �����.
//		L - ����������� �� ����
//		����� - �������������
//		Diffuse - ��������� ���� ���������
//		LightColor - ���� ���������
//		Ambient - ���������� ���� ���������
//	��������� ��������� �� ���� �����.
//	
//! \author 
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

class LambertLight : public ILightEngineAdvance
{

public:
	LambertLight(	std::auto_ptr<ILightType> dir,
					const Vector& clLight,
					const Vector& clDiffuse,
					const Vector& clAmbient);
	virtual ~LambertLight();

	
	virtual void	Shade(	const Face& f, 
							Vector& cl1, Vector& cl2, Vector& cl3 ) ;
};

#endif // _LAMBERT_LIGHT_4403499311454775_