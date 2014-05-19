#include "lighting.h"
#include "renderingEngine.h"
#include "shader.h"
#include "coreEngine.h"

#define COLOR_DEPTH 256

void BaseLight::AddToEngine(CoreEngine* engine)
{
	engine->GetRenderingEngine()->AddLight(this);
}

BaseLight::~BaseLight()
{
	if(m_shader) delete m_shader;
	if(m_shadowInfo) delete m_shadowInfo;
}

void BaseLight::SetShader(Shader* shader)
{
	if(m_shader) delete m_shader;
	m_shader = shader; 
}

void BaseLight::SetShadowInfo(ShadowInfo* shadowInfo)
{
	if(m_shadowInfo) delete m_shadowInfo;
	m_shadowInfo = shadowInfo; 
}

DirectionalLight::DirectionalLight(const Vector3f& color, float intensity) :
	BaseLight(color, intensity)
{
	SetShader(new Shader("forward-directional"));
	SetShadowInfo(new ShadowInfo(Matrix4f().InitOrthographic(-40, 40, -40, 40, -40, 40)));
}

PointLight::PointLight(const Vector3f& color, float intensity, const Attenuation& atten) :
	BaseLight(color, intensity),
	atten(atten)
{
	float a = atten.exponent;
	float b = atten.linear;
	float c = atten.constant - COLOR_DEPTH * intensity * color.Max();
	
	range = (-b + sqrtf(b*b - 4*a*c))/(2*a);

	SetShader(new Shader("forward-point"));
}

SpotLight::SpotLight(const Vector3f& color, float intensity, const Attenuation& atten, float cutoff) :
	PointLight(color, intensity, atten),
	cutoff(cutoff) 
{
	SetShader(new Shader("forward-spot"));
}
