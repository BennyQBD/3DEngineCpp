#ifndef LIGHTING_H
#define LIGHTING_H

#include "vector3f.h"

struct BaseLight
{
	Vector3f color;
	float intensity;

	BaseLight(Vector3f color = Vector3f(0,0,0), float intensity = 0)
	{
		this->color = color;
		this->intensity = intensity;
	}
};

struct DirectionalLight
{
	BaseLight base;
	Vector3f direction;

	DirectionalLight(BaseLight base = BaseLight(), Vector3f direction = Vector3f(0,0,0))
	{
		this->base = base;
		this->direction = direction;
	}
};

struct Attenuation
{
	float constant;
	float linear;
	float exponent;

	Attenuation(float constant = 0, float linear = 0, float exponent = 1)
	{
		this->constant = constant;
		this->linear = linear;
		this->exponent = exponent;
	}
};

struct PointLight
{
	BaseLight base;
	Attenuation atten;
	Vector3f position;
	float range;

	PointLight(BaseLight base = BaseLight(), Attenuation atten = Attenuation(), Vector3f position = Vector3f(), float range = 0)
	{
		this->base = base;
		this->atten = atten;
		this->position = position;
		this->range = range;
	}
};

struct SpotLight
{
	PointLight pointLight;
	Vector3f direction;
	float cutoff;

	SpotLight(PointLight pointLight = PointLight(), Vector3f direction = Vector3f(), float cutoff = 0)
	{
		this->pointLight = pointLight;
		this->direction = direction;
		this->cutoff = cutoff;
	}
};

#endif