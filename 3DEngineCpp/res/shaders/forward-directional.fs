#version 120
#include "lighting.fsh"

uniform DirectionalLight R_directionalLight;

void main()
{
    gl_FragColor = texture2D(diffuse, texCoord0.xy) * CalcDirectionalLight(R_directionalLight, normalize(normal0), worldPos0);
}
