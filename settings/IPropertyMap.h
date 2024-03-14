#ifndef _I_PROPERTY_MAP_9101285664872632_
#define _I_PROPERTY_MAP_9101285664872632_

#include "../math/Vector.h"

//! \brief Not available
//! \author Eugene Gorbachev (Eugene.Gorbachev@biones.com)
//! \date   01.12.2005
//! \version 1.0
//! \bug 
//! \todo 

//geometry
const DWORD		prop_geo_dodecahedron_enable	= 1;
const DWORD		prop_geo_dodecahedron_color		= 2;

const DWORD		prop_geo_cylinder_enable		= 3;
const DWORD		prop_geo_cylinder_color			= 4;
const DWORD		prop_geo_cylinder_segments		= 5;

const DWORD		prop_geo_torus_enable			= 6;
const DWORD		prop_geo_torus_color			= 7;
const DWORD		prop_geo_torus_rings			= 8;
const DWORD		prop_geo_torus_segments			= 9;

const DWORD		prop_geo_wireframe				= 10;

//light
const DWORD		prop_light_lambert				= 21;
const DWORD		prop_light_gouraud				= 22;
const DWORD		prop_light_phong				= 23;

const DWORD		prop_light_direct				= 24;
const DWORD		prop_light_point				= 25;
const DWORD		prop_light_spot					= 26;

const DWORD		prop_light_intensity			= 27;
const DWORD		prop_light_color				= 28;
const DWORD		prop_light_pos_x				= 29;
const DWORD		prop_light_pos_y				= 30;
const DWORD		prop_light_pos_z				= 31;

//rotate & scale
const DWORD		prop_rs_rotate_x				= 40;
const DWORD		prop_rs_rotate_y				= 41;
const DWORD		prop_rs_rotate_z				= 42;
const DWORD		prop_rs_scale_x					= 43;
const DWORD		prop_rs_scale_y					= 44;
const DWORD		prop_rs_scale_z					= 45;

const DWORD		prop_rs_periodic				= 46;
const DWORD		prop_rs_frequence				= 47;

class IPropertyMap
{
public:

	class IPropertyHandler 
	{
	public:
		virtual void						Notify( DWORD dwID )			= 0;
		virtual std::pair<bool, float>		GetNumericProperty(DWORD Id)	= 0;
		virtual std::pair<bool, CString>	GetStringProperty(DWORD Id)		= 0;
	};

	class NoSuchProperty : std::exception {};
	virtual ~IPropertyMap() {};

	virtual float		GetNumericProperty(DWORD Id)	= 0;
	virtual CString		GetStringProperty(DWORD Id)		= 0;

	COLORREF	GetColorProperty( DWORD Id )
	{
		return (COLORREF)GetNumericProperty( Id );
	}
	__int64		GetIntProperty( DWORD Id )
	{
		return (__int64)GetNumericProperty( Id );
	}

	bool		GetBoolProperty( DWORD Id )
	{
		return GetNumericProperty( Id ) != 0;
	}

	virtual void	AddHandler( IPropertyHandler * p) = 0;
	virtual void	Notify( DWORD Id ) = 0;

};

IPropertyMap* GetPropertyMap();

inline bool	BoolProperty( DWORD Id )
{
	return GetPropertyMap()->GetBoolProperty( Id );
}

inline __int64	IntProperty( DWORD Id )
{
	return GetPropertyMap()->GetIntProperty( Id );
}

inline float	FloatProperty( DWORD Id )
{
	return GetPropertyMap()->GetNumericProperty( Id );
}


inline Vector GetColorVector( DWORD Id )
{
	COLORREF cl = (COLORREF)IntProperty( Id );
	return Vector( GetRValue(cl)/255.0f, GetGValue(cl)/255.0f, GetBValue(cl)/255.0f ); 
}

#endif // _I_PROPERTY_MAP_9101285664872632_