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

// FXAA shader, GLSL code adapted from:
// http://horde3d.org/wiki/index.php5?title=Shading_Technique_-_FXAA
// Whitepaper describing the technique:
// http://developer.download.nvidia.com/assets/gamedev/files/sdk/11/FXAA_WhitePaper.pdf


#include "common.glh"

varying vec2 texCoord0;

#if defined(VS_BUILD)
#include "filter.vsh"
#elif defined(FS_BUILD)

uniform sampler2D R_filterTexture;
uniform vec3 R_inverseFilterTextureSize;
uniform float R_fxaaSpanMax;
uniform float R_fxaaReduceMin;
uniform float R_fxaaReduceMul;

DeclareFragOutput(0, vec4);
void main()
{
	vec2 texCoordOffset = R_inverseFilterTextureSize.xy;
	
	vec3 luma = vec3(0.299, 0.587, 0.114);	
	float lumaTL = dot(luma, texture2D(R_filterTexture, texCoord0.xy + (vec2(-1.0, -1.0) * texCoordOffset)).xyz);
	float lumaTR = dot(luma, texture2D(R_filterTexture, texCoord0.xy + (vec2(1.0, -1.0) * texCoordOffset)).xyz);
	float lumaBL = dot(luma, texture2D(R_filterTexture, texCoord0.xy + (vec2(-1.0, 1.0) * texCoordOffset)).xyz);
	float lumaBR = dot(luma, texture2D(R_filterTexture, texCoord0.xy + (vec2(1.0, 1.0) * texCoordOffset)).xyz);
	float lumaM  = dot(luma, texture2D(R_filterTexture, texCoord0.xy).xyz);

	vec2 dir;
	dir.x = -((lumaTL + lumaTR) - (lumaBL + lumaBR));
	dir.y = ((lumaTL + lumaBL) - (lumaTR + lumaBR));
	
	float dirReduce = max((lumaTL + lumaTR + lumaBL + lumaBR) * (R_fxaaReduceMul * 0.25), R_fxaaReduceMin);
	float inverseDirAdjustment = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);
	
	dir = min(vec2(R_fxaaSpanMax, R_fxaaSpanMax), 
		max(vec2(-R_fxaaSpanMax, -R_fxaaSpanMax), dir * inverseDirAdjustment));
	
	dir.x = dir.x * step(1.0, abs(dir.x));
	dir.y = dir.y * step(1.0, abs(dir.y));
	
	//float dirStep = max(step(1.0, abs(dir.x)), step(1.0, abs(dir.y)));
	//dir.x = dir.x * dirStep;
	//dir.y = dir.y * dirStep;
	
	dir = dir * texCoordOffset;

	vec3 result1 = (1.0/2.0) * (
		texture2D(R_filterTexture, texCoord0.xy + (dir * vec2(1.0/3.0 - 0.5))).xyz +
		texture2D(R_filterTexture, texCoord0.xy + (dir * vec2(2.0/3.0 - 0.5))).xyz);

	vec3 result2 = result1 * (1.0/2.0) + (1.0/4.0) * (
		texture2D(R_filterTexture, texCoord0.xy + (dir * vec2(0.0/3.0 - 0.5))).xyz +
		texture2D(R_filterTexture, texCoord0.xy + (dir * vec2(3.0/3.0 - 0.5))).xyz);

	float lumaMin = min(lumaM, min(min(lumaTL, lumaTR), min(lumaBL, lumaBR)));
	float lumaMax = max(lumaM, max(max(lumaTL, lumaTR), max(lumaBL, lumaBR)));
	float lumaResult2 = dot(luma, result2);
	
	if(lumaResult2 < lumaMin || lumaResult2 > lumaMax)
		SetFragOutput(0, vec4(result1, 1.0));
	else
		SetFragOutput(0, vec4(result2, 1.0));
}
#endif
