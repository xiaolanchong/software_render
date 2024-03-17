#pragma once

#include "../math/Vector.h"
#include "../geometry/IGeoSolid.h"

class RenderEngine;
class Matrix;
class IPropertyMap;

/*
struct RenderEntity
{
	IGeoSolid::Solid_t m_faces;
	Matrix m_localToWorld;
	Vector m_diffuseColor;
};
*/

//using GetRenderEntity = std::function<RenderEntity()>;

class ISceneSolid
{
public:
	virtual ~ISceneSolid() {};

	virtual Vector	GetDiffuse(IPropertyMap& propMap) = 0;
	virtual void	AddGeometry( RenderEngine& re, const Matrix& MatWorld, IPropertyMap& propMap) = 0;
};

class DodecahedronSceneSolid : public ISceneSolid
{
	virtual Vector	GetDiffuse(IPropertyMap& propMap) override;
	virtual void	AddGeometry( RenderEngine& re, const Matrix& MatWorld, IPropertyMap& propMap) override;

private:
	IGeoSolid::Faces m_faces;
};

class CylinderSceneSolid : public ISceneSolid
{
	virtual Vector	GetDiffuse(IPropertyMap& propMap) override;
	virtual void	AddGeometry( RenderEngine& re, const Matrix& MatWorld, IPropertyMap& propMap) override;

private:
	IGeoSolid::Faces m_faces;
	size_t m_lastSegments = 0;
};

class SphereSceneSolid : public ISceneSolid
{
	virtual Vector	GetDiffuse(IPropertyMap& propMap) override;
	virtual void	AddGeometry(RenderEngine& re, const Matrix& MatWorld, IPropertyMap& propMap) override;

private:
	IGeoSolid::Faces m_faces;
	size_t m_lastSegments = 0;
};

class TorusSceneSolid : public ISceneSolid
{
	virtual Vector	GetDiffuse(IPropertyMap& propMap) override;
	virtual void	AddGeometry( RenderEngine& re, const Matrix& MatWorld, IPropertyMap& propMap) override;

private:
	IGeoSolid::Faces m_faces;
	size_t m_lasRings = 0;
	size_t m_lastSegments = 0;
};

class PointLightSolid : public ISceneSolid
{
	virtual Vector	GetDiffuse(IPropertyMap& propMap) ;
	virtual void	AddGeometry( RenderEngine& re, const Matrix& MatWorld, IPropertyMap& propMap) override;

private:
	IGeoSolid::Faces m_faces;
};
