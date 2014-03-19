#include "lighting.h"
#include "renderingEngine.h"
#include "forwardDirectional.h"
#include "forwardPoint.h"
#include "forwardSpot.h"

#define COLOR_DEPTH 256

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

PointLight::PointLight(const Vector3f& color, float intensity, const Attenuation& atten) :
	BaseLight(color, intensity),
	atten(atten)
{
	float a = atten.exponent;
	float b = atten.linear;
	float c = atten.constant - COLOR_DEPTH * intensity * color.Max();
	
	range = (-b + sqrtf(b*b - 4*a*c))/(2*a);

	SetShader(ForwardPoint::GetInstance());
}

SpotLight::SpotLight(const Vector3f& color, float intensity, const Attenuation& atten, const Vector3f& direction, float cutoff) :
	PointLight(color, intensity, atten),
	direction(direction),
	cutoff(cutoff) 
{
	SetShader(ForwardSpot::GetInstance());
}
