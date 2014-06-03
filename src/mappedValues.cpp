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
