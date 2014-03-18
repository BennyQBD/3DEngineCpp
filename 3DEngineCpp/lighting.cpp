#include "lighting.h"
#include "renderingEngine.h"

void DirectionalLight::AddToRenderingEngine(RenderingEngine* renderingEngine)
{
	renderingEngine->AddDirectionalLight(this);
}

void PointLight::AddToRenderingEngine(RenderingEngine* renderingEngine)
{
	renderingEngine->AddPointLight(this);
}
