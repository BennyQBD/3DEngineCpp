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

#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"
#include "../core/math3d.h"
#include "../core/mappedValues.h"
#include <map>

class MaterialData : public ReferenceCounter, public MappedValues
{
public:
private:
};

class Material
{
public:
	Material(const std::string& materialName = "");
	Material(const Material& other);
	virtual ~Material();
	
	Material(const std::string& materialName, const Texture& diffuse, float specularIntensity, float specularPower,
		const Texture& normalMap = Texture("default_normal.jpg"),
		const Texture& dispMap = Texture("default_disp.png"), float dispMapScale = 0.0f, float dispMapOffset = 0.0f);
		
	inline void SetVector3f(const std::string& name, const Vector3f& value) { m_materialData->SetVector3f(name, value); }
	inline void SetFloat(const std::string& name, float value)              { m_materialData->SetFloat(name, value); }
	inline void SetTexture(const std::string& name, const Texture& value)   { m_materialData->SetTexture(name, value); }
	
	inline const Vector3f& GetVector3f(const std::string& name) const { return m_materialData->GetVector3f(name); }
	inline float GetFloat(const std::string& name)              const { return m_materialData->GetFloat(name); }
	inline const Texture& GetTexture(const std::string& name)   const { return m_materialData->GetTexture(name); }
protected:
private:
	static std::map<std::string, MaterialData*> s_resourceMap;
	MaterialData* m_materialData;
	std::string   m_materialName;
	
	
	void operator=(const Material& other) {}
};

#endif
