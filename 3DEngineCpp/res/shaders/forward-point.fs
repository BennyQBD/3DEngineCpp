#version 120
#include "lighting.fsh"

uniform PointLight R_pointLight;

void main()
{
    gl_FragColor = texture2D(diffuse, texCoord0.xy) * CalcPointLight(R_pointLight, normalize(normal0), worldPos0);
}
