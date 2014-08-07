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

#include "lighting.h"
#include "renderingEngine.h"
#include "../core/coreEngine.h"

#define COLOR_DEPTH 256

void BaseLight::AddToEngine(CoreEngine* engine) const
{
	engine->GetRenderingEngine()->AddLight(*this);
}

ShadowCameraTransform BaseLight::CalcShadowCameraTransform(const Vector3f& mainCameraPos, const Quaternion& mainCameraRot) const
{
	return ShadowCameraTransform(GetTransform().GetTransformedPos(), GetTransform().GetTransformedRot());
}

DirectionalLight::DirectionalLight(const Vector3f& color, float intensity, int shadowMapSizeAsPowerOf2, 
	                 float shadowArea, float shadowSoftness, float lightBleedReductionAmount, float minVariance) :
	BaseLight(color, intensity, Shader("forward-directional")),
	m_halfShadowArea(shadowArea / 2.0f)
{
	if(shadowMapSizeAsPowerOf2 != 0)
	{
		SetShadowInfo(ShadowInfo(Matrix4f().InitOrthographic(-m_halfShadowArea, m_halfShadowArea, -m_halfShadowArea, 
		                                                      m_halfShadowArea, -m_halfShadowArea, m_halfShadowArea), 
								 true, shadowMapSizeAsPowerOf2, shadowSoftness, lightBleedReductionAmount, minVariance));
	}
}


ShadowCameraTransform DirectionalLight::CalcShadowCameraTransform(const Vector3f& mainCameraPos, const Quaternion& mainCameraRot) const
{
	Vector3f resultPos = mainCameraPos + mainCameraRot.GetForward() * GetHalfShadowArea();
	Quaternion resultRot = GetTransform().GetTransformedRot();
	
	float worldTexelSize = (GetHalfShadowArea()*2)/((float)(1 << GetShadowInfo().GetShadowMapSizeAsPowerOf2()));
	
	Vector3f lightSpaceCameraPos = resultPos.Rotate(resultRot.Conjugate());
	
	lightSpaceCameraPos.SetX(worldTexelSize * floor(lightSpaceCameraPos.GetX() / worldTexelSize));
	lightSpaceCameraPos.SetY(worldTexelSize * floor(lightSpaceCameraPos.GetY() / worldTexelSize));
	
	resultPos = lightSpaceCameraPos.Rotate(resultRot);
	
	return ShadowCameraTransform(resultPos, resultRot);
}

PointLight::PointLight(const Vector3f& color, float intensity, const Attenuation& attenuation, const Shader& shader) :
	BaseLight(color, intensity, shader),
	m_attenuation(attenuation)
{
	float a = m_attenuation.GetExponent();
	float b = m_attenuation.GetLinear();
	float c = m_attenuation.GetConstant() - COLOR_DEPTH * intensity * color.Max();
	
	m_range = (-b + sqrtf(b*b - 4*a*c))/(2*a);
}

SpotLight::SpotLight(const Vector3f& color, float intensity, const Attenuation& attenuation, float viewAngle, 
                     int shadowMapSizeAsPowerOf2, float shadowSoftness, float lightBleedReductionAmount, float minVariance) :
	PointLight(color, intensity, attenuation, Shader("forward-spot")),
	m_cutoff(cos(viewAngle/2))
{
	if(shadowMapSizeAsPowerOf2 != 0)
	{
		SetShadowInfo(ShadowInfo(Matrix4f().InitPerspective(viewAngle, 1.0, 0.1, GetRange()), false, shadowMapSizeAsPowerOf2,
		                             shadowSoftness, lightBleedReductionAmount, minVariance));
	}
}
