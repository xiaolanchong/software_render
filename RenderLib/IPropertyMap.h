#pragma once

#include <memory>
#include <optional>
#include <stdexcept>

using PropertyId = unsigned int;

// geometry
const PropertyId		prop_geo_dodecahedron_enable    = 1;
const PropertyId		prop_geo_dodecahedron_color     = 2;

const PropertyId		prop_geo_cylinder_enable        = 10;
const PropertyId		prop_geo_cylinder_color         = 11;
const PropertyId		prop_geo_cylinder_segments      = 12;

const PropertyId		prop_geo_torus_enable           = 20;
const PropertyId		prop_geo_torus_color            = 21;
const PropertyId		prop_geo_torus_rings            = 22;
const PropertyId		prop_geo_torus_segments         = 23;

const PropertyId		prop_geo_wireframe              = 30;
const PropertyId		prop_geo_fill                   = 31;
const PropertyId		prop_geo_fill_and_textures      = 32;

// light
const PropertyId		prop_light_lambert              = 100;
const PropertyId		prop_light_gouraud              = 101;
const PropertyId		prop_light_phong                = 102;

const PropertyId		prop_light_direct				= 110;
const PropertyId		prop_light_point				= 111;
const PropertyId		prop_light_spot					= 112;

const PropertyId		prop_light_intensity			= 120;
const PropertyId		prop_light_color				= 121;
const PropertyId		prop_light_pos_x				= 122;
const PropertyId		prop_light_pos_y				= 123;
const PropertyId		prop_light_pos_z				= 124;

// rotation & scaling
const PropertyId		prop_rs_rotate_x				= 200;
const PropertyId		prop_rs_rotate_y				= 201;
const PropertyId		prop_rs_rotate_z				= 202;
const PropertyId		prop_rs_scale_x					= 203;
const PropertyId		prop_rs_scale_y					= 204;
const PropertyId		prop_rs_scale_z					= 205;

const PropertyId		prop_rs_periodic				= 206;
const PropertyId		prop_rs_frequence				= 207;

class IPropertyMap
{
public:
	class NoSuchProperty : public std::runtime_error 
	{
	public:
		NoSuchProperty(PropertyId id)
			: std::runtime_error(std::string("No such property: ") + std::to_string(id))
		{}
	};

	virtual ~IPropertyMap() = default;
	
	/// @throw NoSuchProperty if no property with the given id found
	virtual float GetNumericProperty(PropertyId Id)	= 0;
	virtual std::string GetStringProperty(PropertyId Id) = 0;

	std::int64_t GetIntProperty(PropertyId Id )
	{
		return static_cast<std::int64_t>(GetNumericProperty( Id ));
	}

	bool GetBoolProperty(PropertyId Id )
	{
		return GetNumericProperty( Id ) != 0;
	}

	float GetFloatProperty(PropertyId Id)
	{
		return GetNumericProperty(Id);
	}
};

/// Interface to create a property map from dynamic handlers instead of direct get/set operations
class IComposePropertyMap
{
public:

	class IPropertyHandler
	{
	public:
		virtual ~IPropertyHandler() = default;
		virtual void Notify(PropertyId dwID) = 0;
		virtual std::optional<float> GetNumericProperty(PropertyId Id) = 0;
		virtual std::string	GetStringProperty(PropertyId Id) = 0;
	};

	using IPropertyHandlerPtr = std::shared_ptr<IPropertyHandler>;
	using IPropertyHandlerWeakPtr = std::weak_ptr<IPropertyHandler>;

	virtual void	AddHandler(IPropertyHandlerWeakPtr p) = 0;
	virtual void	Notify(PropertyId Id) = 0;
};
