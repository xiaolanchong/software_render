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
const DWORD		prop_geo_dodecahedron_enable		= 1;
const DWORD		prop_geo_dodecahedron_color		= 2;

const DWORD		prop_geo_cylinder_enable			= 13;
const DWORD		prop_geo_cylinder_color				= 14;
const DWORD		prop_geo_cylinder_segments			= 15;

const DWORD		prop_geo_torus_enable			= 26;
const DWORD		prop_geo_torus_color			= 27;
const DWORD		prop_geo_torus_rings			= 28;
const DWORD		prop_geo_torus_segments			= 29;

const DWORD		prop_geo_wireframe				= 90;
const DWORD		prop_geo_fill = 91;
const DWORD		prop_geo_fill_and_textures = 92;

//light
const DWORD		prop_light_lambert				= 121;
const DWORD		prop_light_gouraud				= 122;
const DWORD		prop_light_phong				= 123;

const DWORD		prop_light_direct				= 124;
const DWORD		prop_light_point				= 125;
const DWORD		prop_light_spot					= 126;

const DWORD		prop_light_intensity			= 127;
const DWORD		prop_light_color				= 128;
const DWORD		prop_light_pos_x				= 129;
const DWORD		prop_light_pos_y				= 130;
const DWORD		prop_light_pos_z				= 131;

//rotate & scale
const DWORD		prop_rs_rotate_x				= 240;
const DWORD		prop_rs_rotate_y				= 241;
const DWORD		prop_rs_rotate_z				= 242;
const DWORD		prop_rs_scale_x					= 243;
const DWORD		prop_rs_scale_y					= 244;
const DWORD		prop_rs_scale_z					= 245;

const DWORD		prop_rs_periodic				= 246;
const DWORD		prop_rs_frequence				= 247;

class IPropertyMap
{
public:

	class IPropertyHandler 
	{
	public:
		virtual ~IPropertyHandler() = default;
		virtual void						Notify( DWORD dwID )			= 0;
		virtual std::pair<bool, float>		GetNumericProperty(DWORD Id)	= 0;
		virtual std::pair<bool, CString>	GetStringProperty(DWORD Id)		= 0;
	};

	using IPropertyHandlerPtr = IPropertyHandler*; // std::shared_ptr<IPropertyHandler>;
	using IPropertyHandlerWeakPtr = IPropertyHandler*; // std::weak_ptr<IPropertyHandler>;

	class NoSuchProperty : public std::runtime_error 
	{
	public:
		NoSuchProperty(DWORD id) : std::runtime_error(std::string("No such property: ") + std::to_string(id))
		{}
	};
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

	virtual void	AddHandler(IPropertyHandlerWeakPtr p) = 0;
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