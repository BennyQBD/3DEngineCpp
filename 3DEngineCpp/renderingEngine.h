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
	inline BaseLight* GetActiveLight() { return m_activeLight; }
	
	inline void AddLight(BaseLight* light) { m_lights.push_back(light); }
	
	virtual ~RenderingEngine();
protected:
private:
	RenderingEngine(const RenderingEngine& other) :
		m_mainCamera(ToRadians(70.0f), 1.0f, 0.01f, 1000.0f) {}
	void operator=(const RenderingEngine& other) {}
	
	Camera m_mainCamera;
	Vector3f m_ambientLight;
	
	BaseLight* m_activeLight;
	std::vector<BaseLight*> m_lights;
};

#endif // RENDERINGENGINE_H
