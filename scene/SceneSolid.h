#ifndef _SCENE_SOLID_8464013731116032_
#define _SCENE_SOLID_8464013731116032_

#include "../math/Vector.h"

class RenderEngine;
class Matrix;

class ISceneSolid
{
public:
	virtual ~ISceneSolid() {};

	virtual Vector	GetDiffuse() = 0;
	virtual void	AddGeometry( RenderEngine& re, const Matrix& MatWorld ) = 0;
};

class DodecahedronSceneSolid : public ISceneSolid
{
	virtual Vector	GetDiffuse() ;
	virtual void	AddGeometry( RenderEngine& re, const Matrix& MatWorld );
};

class CylinderSceneSolid : public ISceneSolid
{
	virtual Vector	GetDiffuse() ;
	virtual void	AddGeometry( RenderEngine& re, const Matrix& MatWorld );
};

class TorusSceneSolid : public ISceneSolid
{
	virtual Vector	GetDiffuse() ;
	virtual void	AddGeometry( RenderEngine& re, const Matrix& MatWorld );
};

class PointLightSolid : public ISceneSolid
{
	virtual Vector	GetDiffuse() ;
	virtual void	AddGeometry( RenderEngine& re, const Matrix& MatWorld );
};

#endif // _SCENE_SOLID_8464013731116032_