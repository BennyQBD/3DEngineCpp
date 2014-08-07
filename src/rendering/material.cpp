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

#include "material.h"
#include <iostream>
#include <cassert>

std::map<std::string, MaterialData*> Material::s_resourceMap;

Material::Material(const std::string& materialName) :
	m_materialName(materialName)
{
	if(materialName.length() > 0)
	{
		std::map<std::string, MaterialData*>::const_iterator it = s_resourceMap.find(materialName);
		if(it == s_resourceMap.end())
		{
			std::cerr << "Error: Material " << materialName << " has not been initialized!" << std::endl;
			assert(0 != 0);
		}
	
		m_materialData = it->second;
		m_materialData->AddReference();
	}
}

Material::Material(const Material& other) :
	m_materialData(other.m_materialData),
	m_materialName(other.m_materialName) 
{
	m_materialData->AddReference();
}

Material::~Material()
{
	if(m_materialData && m_materialData->RemoveReference())
	{
		if(m_materialName.length() > 0)
		{
			s_resourceMap.erase(m_materialName);
		}
			
		delete m_materialData;
	}
}

Material::Material(const std::string& materialName, const Texture& diffuse, float specularIntensity, float specularPower,
		const Texture& normalMap,
		const Texture& dispMap, float dispMapScale, float dispMapOffset) :
		m_materialName(materialName)
{
	m_materialData = new MaterialData();
	s_resourceMap[m_materialName] = m_materialData;

	m_materialData->SetTexture("diffuse", diffuse);
	m_materialData->SetFloat("specularIntensity", specularIntensity);
	m_materialData->SetFloat("specularPower", specularPower);
	m_materialData->SetTexture("normalMap", normalMap);
	m_materialData->SetTexture("dispMap", dispMap);
	
	float baseBias = dispMapScale/2.0f;
	m_materialData->SetFloat("dispMapScale", dispMapScale);
	m_materialData->SetFloat("dispMapBias", -baseBias + baseBias * dispMapOffset);
}
