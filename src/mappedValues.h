#ifndef MAPPEDVALUES_H_INCLUDED
#define MAPPEDVALUES_H_INCLUDED

#include <map>
#include <string>

#include "texture.h"

class MappedValues
{
public:
	virtual ~MappedValues()
	{
		//Delete all textures
		std::map<std::string, Texture*>::iterator it;
		for(it = m_textureMap.begin(); it != m_textureMap.end(); it++)
			if(it->second) delete it->second;
	}

	inline void SetVector3f(const std::string& name, Vector3f value) { m_vector3fMap[name] = value; }
	inline void SetFloat(const std::string& name, float value) { m_floatMap[name] = value; }
	inline void SetTexture(const std::string& name, Texture* value) { m_textureMap[name] = value; }
	
	inline Vector3f GetVector3f(const std::string& name) const
	{
		std::map<std::string, Vector3f>::const_iterator it = m_vector3fMap.find(name);
		if(it != m_vector3fMap.end())
			return it->second;
			
		return Vector3f(0,0,0);
	}
	
	inline float GetFloat(const std::string& name) const
	{
		std::map<std::string, float>::const_iterator it = m_floatMap.find(name);
		if(it != m_floatMap.end())
			return it->second;
			
		return 0;
	}
	
	inline Texture* GetTexture(const std::string& name) const
	{
		std::map<std::string, Texture*>::const_iterator it = m_textureMap.find(name);
		if(it != m_textureMap.end())
			return it->second;
			
		return 0;
	}
protected:
private:
	std::map<std::string, Vector3f> m_vector3fMap;
	std::map<std::string, float> m_floatMap;
	std::map<std::string, Texture*> m_textureMap;
};

#endif // MAPPEDVALUES_H_INCLUDED
