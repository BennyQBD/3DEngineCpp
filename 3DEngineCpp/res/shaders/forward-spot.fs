#version 120
#include "lighting.glh"

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;

uniform sampler2D diffuse;
uniform SpotLight R_spotLight;

void main()
{
    gl_FragColor = texture2D(diffuse, texCoord0.xy) * CalcSpotLight(R_spotLight, normalize(normal0), worldPos0);
}
