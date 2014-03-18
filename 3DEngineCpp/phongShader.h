#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "shader.h"
#include "lighting.h"

class PhongShader : public Shader
{
public:
	static PhongShader* GetInstance()
	{
		static PhongShader instance;
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine);

	static inline Vector3f& GetAmbientLight() { return s_ambientLight; }
	static inline DirectionalLight& GetDirectionalLight() { return s_directionalLight; }

	static inline void SetAmbientLight(const Vector3f& ambientLight) { s_ambientLight = ambientLight; }
	static void SetDirectionalLight(const DirectionalLight& directionalLight);
	static void SetPointLights(PointLight* pointLights, int arraySize);
	static void SetSpotLights(SpotLight* spotLights, int arraySize);
protected:
private:
	static const int MAX_POINT_LIGHTS = 4;
	static const int MAX_SPOT_LIGHTS = 4;
	static Vector3f s_ambientLight;
	static DirectionalLight s_directionalLight;
	static PointLight* s_pointLights;
	static SpotLight* s_spotLights;
	static int s_numPointLights;
	static int s_numSpotLights;

	PhongShader();

	PhongShader(PhongShader const&){}// Don't Implement
	void operator=(PhongShader const&){} // Don't implement
};

#endif
