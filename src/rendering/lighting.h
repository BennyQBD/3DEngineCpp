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

#ifndef LIGHTING_H
#define LIGHTING_H

#include "shader.h"

#include "../core/math3d.h"
#include "../core/entityComponent.h"

class CoreEngine;

class ShadowCameraTransform
{
public:
	ShadowCameraTransform(const Vector3f& pos, const Quaternion& rot) :
		m_pos(pos),
		m_rot(rot) {}
		
	inline const Vector3f& GetPos()   const { return m_pos; }
	inline const Quaternion& GetRot() const { return m_rot; }
private:
	Vector3f m_pos;
	Quaternion m_rot;
};

class ShadowInfo
{
public:
	ShadowInfo(const Matrix4f& projection = Matrix4f().InitIdentity(), bool flipFaces = false, int shadowMapSizeAsPowerOf2 = 0, float shadowSoftness = 1.0f, float lightBleedReductionAmount = 0.2f, float minVariance = 0.00002f) :
		m_projection(projection),
		m_flipFaces(flipFaces),
		m_shadowMapSizeAsPowerOf2(shadowMapSizeAsPowerOf2),
		m_shadowSoftness(shadowSoftness),
		m_lightBleedReductionAmount(lightBleedReductionAmount),
		m_minVariance(minVariance) {}
		
	inline const Matrix4f& GetProjection()      const { return m_projection; }
	inline bool GetFlipFaces()                  const { return m_flipFaces; }
	inline int GetShadowMapSizeAsPowerOf2()     const { return m_shadowMapSizeAsPowerOf2; }
	inline float GetShadowSoftness()            const { return m_shadowSoftness; }
	inline float GetMinVariance()               const { return m_minVariance; }
	inline float GetLightBleedReductionAmount() const { return m_lightBleedReductionAmount; }
protected:
private:
	Matrix4f m_projection;
	bool m_flipFaces;
	int m_shadowMapSizeAsPowerOf2;
	float m_shadowSoftness;
	float m_lightBleedReductionAmount;
	float m_minVariance;
};

class BaseLight : public EntityComponent
{
public:
	BaseLight(const Vector3f& color, float intensity, const Shader& shader) :
		m_color(color),
		m_intensity(intensity),
		m_shader(shader),
		m_shadowInfo(ShadowInfo()) {}
	
	virtual ShadowCameraTransform CalcShadowCameraTransform(const Vector3f& mainCameraPos, const Quaternion& mainCameraRot) const;
	virtual void AddToEngine(CoreEngine* engine) const;	
	
	inline const Vector3f& GetColor()        const { return m_color; }
	inline const float GetIntensity()        const { return m_intensity; }
	inline const Shader& GetShader()         const { return m_shader; }
	inline const ShadowInfo& GetShadowInfo() const { return m_shadowInfo; }
protected:
	inline void SetShadowInfo(const ShadowInfo& shadowInfo) { m_shadowInfo = shadowInfo; }
private:
	Vector3f    m_color;
	float       m_intensity;
	Shader      m_shader;
	ShadowInfo  m_shadowInfo;
};

class DirectionalLight : public BaseLight
{
public:
	DirectionalLight(const Vector3f& color = Vector3f(0,0,0), float intensity = 0, int shadowMapSizeAsPowerOf2 = 0, 
	                 float shadowArea = 80.0f, float shadowSoftness = 1.0f, float lightBleedReductionAmount = 0.2f, float minVariance = 0.00002f);
	                 
	virtual ShadowCameraTransform CalcShadowCameraTransform(const Vector3f& mainCameraPos, const Quaternion& mainCameraRot) const;
	
	inline float GetHalfShadowArea() const { return m_halfShadowArea; }
private:
	float m_halfShadowArea;
};

class Attenuation
{
public:
	Attenuation(float constant = 0, float linear = 0, float exponent = 1) :
		m_constant(constant),
		m_linear(linear),
		m_exponent(exponent) {}
		
	inline float GetConstant() const { return m_constant; }
	inline float GetLinear()   const { return m_linear; }
	inline float GetExponent() const { return m_exponent; }
private:
	float m_constant;
	float m_linear;
	float m_exponent;
};

class PointLight : public BaseLight
{
public:
	PointLight(const Vector3f& color = Vector3f(0,0,0), float intensity = 0, const Attenuation& atten = Attenuation(), 
	           const Shader& shader = Shader("forward-point"));
	           
	inline const Attenuation& GetAttenuation() const { return m_attenuation; }
	inline const float GetRange()              const { return m_range; }
private:
	Attenuation m_attenuation;
	float m_range;
};

class SpotLight : public PointLight
{
public:
	SpotLight(const Vector3f& color = Vector3f(0,0,0), float intensity = 0, const Attenuation& atten = Attenuation(), float viewAngle = ToRadians(170.0f),
			  int shadowMapSizeAsPowerOf2 = 0, float shadowSoftness = 1.0f, float lightBleedReductionAmount = 0.2f, float minVariance = 0.00002f);
			  
	inline float GetCutoff() const { return m_cutoff; }
private:
	float m_cutoff;
};

#endif
