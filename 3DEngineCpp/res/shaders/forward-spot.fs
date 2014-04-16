#version 120
#include "lighting.fsh"

uniform SpotLight R_spotLight;

vec4 CalcLightingEffect(vec3 normal, vec3 worldPos)
{
	return CalcSpotLight(R_spotLight, normal, worldPos);
}

#include "lightingMain.fsh"
