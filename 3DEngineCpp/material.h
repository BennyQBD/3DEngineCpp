#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"
#include "vector3f.h"

struct Material
{
	Texture* texture;
	Vector3f color;
	float specularIntensity;
	float specularPower;

	Material(Texture* texture = NULL, const Vector3f& color = Vector3f(1,1,1), float specularIntensity = 2, float specularPower = 32)
	{
		this->texture = texture;
		this->color = color;
		this->specularIntensity = specularIntensity;
		this->specularPower = specularPower;
	}
};

#endif