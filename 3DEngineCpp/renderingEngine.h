#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "camera.h"
#include "lighting.h"
#include <vector>
class GameObject;

class RenderingEngine
{
public:
	RenderingEngine();
	
	void Input(float delta);
	void Render(GameObject* object);
	
	inline Camera& GetMainCamera() { return m_mainCamera; }
	inline void SetMainCamera(const Camera& camera) { m_mainCamera = camera; }
	
	inline Vector3f& GetAmbientLight() { return m_ambientLight; }
	inline DirectionalLight& GetDirectionalLight() { return *m_activeDirectionalLight; }
	inline PointLight& GetPointLight() { return *m_activePointLight; }
	inline SpotLight& GetSpotLight() { return m_spotLight; }
	
	inline void AddDirectionalLight(DirectionalLight* directionalLight) { m_directionalLights.push_back(directionalLight); }
	inline void AddPointLight(PointLight* pointLight) { m_pointLights.push_back(pointLight); }
	
	virtual ~RenderingEngine();
protected:
private:
	RenderingEngine(const RenderingEngine& other) :
		m_mainCamera(ToRadians(70.0f), 1.0f, 0.01f, 1000.0f) {}
	void operator=(const RenderingEngine& other) {}
	
	Camera m_mainCamera;
	Vector3f m_ambientLight;
//	DirectionalLight m_directionalLight;
//	PointLight m_pointLight;
	SpotLight m_spotLight;
	
	DirectionalLight* m_activeDirectionalLight;
	PointLight* m_activePointLight;
	
	std::vector<DirectionalLight*> m_directionalLights;
	std::vector<PointLight*> m_pointLights;
};

#endif // RENDERINGENGINE_H
