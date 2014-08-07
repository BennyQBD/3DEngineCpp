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

#ifndef MAPPEDVALUES_H_INCLUDED
#define MAPPEDVALUES_H_INCLUDED

#include <map>

#include "../rendering/texture.h"
#include "math3d.h"

class MappedValues
{
public:
	MappedValues() :
		m_defaultTexture(Texture("defaultTexture.png")),
		m_defaultVector3f(Vector3f(0,0,0)) {}

	inline void SetVector3f(const std::string& name, const Vector3f& value) { m_vector3fMap[name] = value; }
	inline void SetFloat(const std::string& name, float value)              { m_floatMap[name] = value; }
	inline void SetTexture(const std::string& name, const Texture& value)   { m_textureMap[name] = value; }
	
	const Vector3f& GetVector3f(const std::string& name) const;
	float GetFloat(const std::string& name)              const;
	const Texture& GetTexture(const std::string& name)   const;
protected:
private:
	std::map<std::string, Vector3f> m_vector3fMap;
	std::map<std::string, float> m_floatMap;
	std::map<std::string, Texture> m_textureMap;
	
	Texture m_defaultTexture;
	Vector3f m_defaultVector3f;
};

#endif // MAPPEDVALUES_H_INCLUDED
