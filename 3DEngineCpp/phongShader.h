#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "shader.h"
#include "lighting.h"

class PhongShader : public Shader
{
public:
	static PhongShader* getInstance()
	{
		static PhongShader instance;
		return &instance;
	}

	virtual void updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, Material& material);

	static Vector3f& getAmbientLight();
	static DirectionalLight& getDirectionalLight();

	static void setAmbientLight(const Vector3f& ambientLight);
	static void setDirectionalLight(const DirectionalLight& directionalLight);
	static void setPointLights(PointLight* pointLights, int arraySize);
	static void setSpotLights(SpotLight* spotLights, int arraySize);
protected:
private:
	static const int MAX_POINT_LIGHTS = 4;
	static const int MAX_SPOT_LIGHTS = 4;
	static Vector3f m_ambientLight;
	static DirectionalLight m_directionalLight;
	static PointLight* m_pointLights;
	static SpotLight* m_spotLights;
	static int m_numPointLights;
	static int m_numSpotLights;

	PhongShader();
	~PhongShader();

	PhongShader(PhongShader const&){}// Don't Implement
	void operator=(PhongShader const&){} // Don't implement
};

#endif