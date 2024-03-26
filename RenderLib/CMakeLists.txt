project (RenderLib)

set(_sources
	geometry/IGeoSolid.h
	geometry/SolidCylinder.h
	geometry/SolidCylinder.cpp
	geometry/SolidDodecahedron.h
	geometry/SolidDodecahedron.cpp
	geometry/SolidSphere.cpp
	geometry/SolidSphere.h
	geometry/SolidTorus.cpp
	geometry/SolidTorus.h
	
	math/Face.h
	math/MathUtils.h
	math/Matrix.cpp
	math/Matrix.h
	math/MatrixUtil.cpp
	math/MatrixUtil.h
	math/Vector.cpp
	math/Vector.h

	pipeline/light/GouraudLight.cpp
	pipeline/light/GouraudLight.h
	pipeline/light/ILightDirection.h
	pipeline/light/ILightEngine.h
	pipeline/light/LambertLight.cpp
	pipeline/light/LambertLight.h
	pipeline/light/PhongLight.cpp
	pipeline/light/PhongLight.h

	pipeline/rasterizer/DrawTriangle.cpp
	pipeline/rasterizer/DrawTriangle.h
	pipeline/rasterizer/GradientRasterizer.cpp
	pipeline/rasterizer/GradientRasterizer.h
	pipeline/rasterizer/InterpolationRender.cpp
	pipeline/rasterizer/InterpolationRender.h
	pipeline/rasterizer/IRasterizer.h
	pipeline/rasterizer/PixelRasterizer.cpp
	pipeline/rasterizer/PixelRasterizer.h
	pipeline/rasterizer/WireFrameRasterizer.cpp
	pipeline/rasterizer/WireFrameRasterizer.h

	pipeline/texture/Array2D.h
	pipeline/texture/ITextureSource.h
	pipeline/texture/TextureFileSource.cpp
	pipeline/texture/TextureFileSource.h

	pipeline/Color.h
	pipeline/RenderEngine.cpp
	pipeline/RenderEngine.h

	scene/PropertyUtils.h
	scene/SceneRender.cpp
	scene/SceneRender.h
	scene/SceneSolid.cpp
	scene/SceneSolid.h

	IDeviceContext.h
	IPropertyMap.h
	ISceneRender.h
	RenderLib.cpp
	RenderLib.h
	)

add_library(RenderLib ${_sources})
set_property(TARGET RenderLib PROPERTY CXX_STANDARD 17)
target_include_directories (RenderLib PRIVATE ".")
