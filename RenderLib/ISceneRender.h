#pragma once

#include <memory>

class IDeviceContext;
class IPropertyMap;

class ISceneRender
{
public:
    virtual ~ISceneRender() = default;

	virtual void Render(IDeviceContext& dc, unsigned int width, unsigned int height, IPropertyMap& propMap ) = 0;
	virtual void Tick(IPropertyMap& propMap) = 0;	
};

using ISceneRenderPtr = std::unique_ptr<ISceneRender>;
