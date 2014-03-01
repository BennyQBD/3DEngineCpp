#ifndef LIGHTING_H
#define LIGHTING_H

#include "vector3f.h"

struct BaseLight
{
	Vector3f color;
	float intensity;

	BaseLight(const Vector3f& color = Vector3f(0,0,0), float intensity = 0) :
		color(color),
		intensity(intensity) {}
};

struct DirectionalLight
{
	BaseLight base;
	Vector3f direction;

	DirectionalLight(const BaseLight& base = BaseLight(), Vector3f direction = Vector3f(0,0,0)) :
		base(base),
		direction(direction) {}
};

struct Attenuation
{
	float constant;
	float linear;
	float exponent;

	Attenuation(float constant = 0, float linear = 0, float exponent = 1) :
		constant(constant),
		linear(linear),
		exponent(exponent) {}
};

struct PointLight
{
	BaseLight base;
	Attenuation atten;
	Vector3f position;
	float range;

	PointLight(const BaseLight& base = BaseLight(), const Attenuation& atten = Attenuation(), const Vector3f& position = Vector3f(), float range = 0) :
		base(base),
		atten(atten),
		position(position),
		range(range) {}
};

struct SpotLight
{
	PointLight pointLight;
	Vector3f direction;
	float cutoff;

	SpotLight(const PointLight& pointLight = PointLight(), const Vector3f& direction = Vector3f(), float cutoff = 0) :
		pointLight(pointLight),
		direction(direction),
		cutoff(cutoff) {}
};

#endif
