// RenderLib.cpp : Defines the functions for the static library.
//

#include "stdafx.h"
#include "RenderLib.h"
#include "scene/SceneRender.h"

ISceneRenderPtr CreateRender()
{
   return std::make_unique<SceneRender>();
}
