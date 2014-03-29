#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"
#include "math3d.h"
#include <map>

class Material
{
public:
	Material() {}
	
	virtual ~Material()
	{
		//Delete all textures
		std::map<std::string, Texture*>::iterator it;
		for(it = m_textureMap.begin(); it != m_textureMap.end(); it++)
			if(it->second) delete it->second;
	}
	
	Material(Texture* diffuse, float specularIntensity, float specularPower)
	{
		AddTexture("diffuse", diffuse);
		AddFloat("specularIntensity", specularIntensity);
		AddFloat("specularPower", specularPower);
	}
	
	inline void AddTexture(const std::string& name, Texture* value) { m_textureMap.insert(std::pair<std::string, Texture*>(name, value)); }
	inline void AddVector3f(const std::string& name, Vector3f value) { m_vector3fMap.insert(std::pair<std::string, Vector3f>(name, value)); }
	inline void AddFloat(const std::string& name, float value) { m_floatMap.insert(std::pair<std::string, float>(name, value)); }
	
	inline Texture* GetTexture(const std::string& name) const
	{
		std::map<std::string, Texture*>::const_iterator it = m_textureMap.find(name);
		if(it != m_textureMap.end())
			return it->second;
			
		return 0;
	}
	
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
	
protected:
private:
	Material(const Material& other) {}
	void operator=(const Material& other) {}

	std::map<std::string, Texture*> m_textureMap;
	std::map<std::string, Vector3f> m_vector3fMap;
	std::map<std::string, float> m_floatMap;
};

#endif
