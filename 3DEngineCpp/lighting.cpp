#include "lighting.h"
#include "renderingEngine.h"
#include "forwardDirectional.h"
#include "forwardPoint.h"
#include "forwardSpot.h"

void BaseLight::AddToRenderingEngine(RenderingEngine* renderingEngine)
{
	renderingEngine->AddLight(this);
}

DirectionalLight::DirectionalLight(const Vector3f& color, float intensity, const Vector3f& direction) :
	BaseLight(color, intensity),
	direction(direction.Normalized()) 
{
	SetShader(ForwardDirectional::GetInstance());
}

PointLight::PointLight(const Vector3f& color, float intensity, const Attenuation& atten, const Vector3f& position, float range) :
	BaseLight(color, intensity),
	atten(atten),
	position(position),
	range(range) 
{
	SetShader(ForwardPoint::GetInstance());
}

SpotLight::SpotLight(const Vector3f& color, float intensity, const Attenuation& atten, const Vector3f& position, float range, const Vector3f& direction, float cutoff) :
	PointLight(color, intensity, atten, position, range),
	direction(direction),
	cutoff(cutoff) 
{
	SetShader(ForwardSpot::GetInstance());
}
