#version 120
#include "lighting.fsh"

uniform SpotLight R_spotLight;

void main()
{
    gl_FragColor = texture2D(diffuse, texCoord0.xy) * CalcSpotLight(R_spotLight, normalize(normal0), worldPos0);
}
