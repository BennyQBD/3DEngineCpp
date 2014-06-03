#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"
#include "math3d.h"
#include "mappedValues.h"
#include <map>

class Material : public MappedValues
{
public:
	Material() {}
	
	Material(const Texture& diffuse, float specularIntensity, float specularPower,
		const Texture& normalMap = Texture("default_normal.jpg"),
		const Texture& dispMap = Texture("default_disp.png"), float dispMapScale = 0.0f, float dispMapOffset = 0.0f);
protected:
private:
};

#endif
