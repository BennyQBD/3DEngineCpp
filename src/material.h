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
	
	Material(Texture* diffuse, float specularIntensity, float specularPower,
		Texture* normalMap = new Texture("default_normal.jpg"),
		Texture* dispMap = new Texture("default_disp.png"), float dispMapScale = 0.0f, float dispMapOffset = 0.0f)
	{
		SetTexture("diffuse", diffuse);
		SetFloat("specularIntensity", specularIntensity);
		SetFloat("specularPower", specularPower);
		SetTexture("normalMap", normalMap);
		SetTexture("dispMap", dispMap);
		
		float baseBias = dispMapScale/2.0f;
		SetFloat("dispMapScale", dispMapScale);
		SetFloat("dispMapBias", -baseBias + baseBias * dispMapOffset);
	}
protected:
private:
	Material(const Material& other) {}
	void operator=(const Material& other) {}
};

#endif
