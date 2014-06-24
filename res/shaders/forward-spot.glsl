/*
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "common.glh"
#include "forwardlighting.glh"

#if defined(VS_BUILD)
#include "forwardlighting.vsh"
#elif defined(FS_BUILD)

#include "lighting.glh"

uniform vec3 C_eyePos;
uniform float specularIntensity;
uniform float specularPower;

uniform SpotLight R_spotLight;

vec4 CalcLightingEffect(vec3 normal, vec3 worldPos)
{
	vec3 lightDirection = normalize(worldPos - R_spotLight.pointLight.position);
    float spotFactor = dot(lightDirection, R_spotLight.direction);
    
    vec4 color = vec4(0,0,0,0);
    
    if(spotFactor > R_spotLight.cutoff)
    {
        color = CalcPointLight(R_spotLight.pointLight, normal, worldPos, 
                               specularIntensity, specularPower, C_eyePos) *
                (1.0 - (1.0 - spotFactor)/(1.0 - R_spotLight.cutoff));
    }
    
    return color;
}

#include "lightingMain.fsh"
#endif
