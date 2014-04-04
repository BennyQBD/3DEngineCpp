#version 120
#include "lighting.glh"

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;

uniform sampler2D diffuse;
uniform DirectionalLight R_directionalLight;

void main()
{
    gl_FragColor = texture2D(diffuse, texCoord0.xy) * CalcDirectionalLight(R_directionalLight, normalize(normal0), worldPos0);
}
