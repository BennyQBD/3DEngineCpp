#include "material.h"

Material::Material(const Texture& diffuse, float specularIntensity, float specularPower,
		const Texture& normalMap,
		const Texture& dispMap, float dispMapScale, float dispMapOffset)
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
