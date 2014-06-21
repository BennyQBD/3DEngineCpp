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

#include "mappedValues.h"

const Vector3f& MappedValues::GetVector3f(const std::string& name) const
{
	std::map<std::string, Vector3f>::const_iterator it = m_vector3fMap.find(name);
	if(it != m_vector3fMap.end())
	{
		return it->second;
	}
		
	return m_defaultVector3f;
}

float MappedValues::GetFloat(const std::string& name) const
{
	std::map<std::string, float>::const_iterator it = m_floatMap.find(name);
	if(it != m_floatMap.end())
	{
		return it->second;
	}
		
	return 0;
}

const Texture& MappedValues::GetTexture(const std::string& name) const
{
	std::map<std::string, Texture>::const_iterator it = m_textureMap.find(name);
	if(it != m_textureMap.end())
	{
		return it->second;
	}
		
	return m_defaultTexture;
}
