#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "camera.h"
#include "lighting.h"
#include "mappedValues.h"
#include "material.h"
#include "mesh.h"
#include "window.h"
#include <vector>
#include <map>
class GameObject;

class RenderingEngine : public MappedValues
{
public:
	RenderingEngine(const Window& window);
	virtual ~RenderingEngine() {}
	
	void Render(const GameObject& object, const Camera& mainCamera);
	
	inline void AddLight(const BaseLight& light) { m_lights.push_back(&light); }
//	inline void AddCamera(const Camera& camera) { m_mainCamera = &camera; }
	
	virtual void UpdateUniformStruct(const Transform& transform, const Material& material, const Shader& shader, 
		const std::string& uniformName, const std::string& uniformType) const
	{
		throw uniformType + " is not supported by the rendering engine";
	}
	
//	inline const Camera& GetMainCamera()                               const { return *m_mainCamera; }
	inline const BaseLight& GetActiveLight()                           const { return *m_activeLight; }
	inline unsigned int GetSamplerSlot(const std::string& samplerName) const { return m_samplerMap.find(samplerName)->second; }
	inline const Matrix4f& GetLightMatrix()                            const { return m_lightMatrix; }
	
protected:
	inline void SetSamplerSlot(const std::string& name, unsigned int value) { m_samplerMap[name] = value; }
private:
	static const int NUM_SHADOW_MAPS = 10;
	static const Matrix4f BIAS_MATRIX;

	Transform                           m_planeTransform;
	Mesh                                m_plane;
	
	const Window*                       m_window;
	Texture                             m_tempTarget;
	Material                            m_planeMaterial;
	Texture                             m_shadowMaps[NUM_SHADOW_MAPS];
	Texture                             m_shadowMapTempTargets[NUM_SHADOW_MAPS];
	
	Shader                              m_defaultShader;
	Shader                              m_shadowMapShader;
	Shader                              m_nullFilter;
	Shader                              m_gausBlurFilter;
	Shader                              m_fxaaFilter;
	Matrix4f                            m_lightMatrix;
	
	Transform                           m_altCameraTransform;
	Camera                              m_altCamera;
	const BaseLight*                    m_activeLight;
	std::vector<const BaseLight*>       m_lights;
	std::map<std::string, unsigned int> m_samplerMap;
	
	void BlurShadowMap(int shadowMapIndex, float blurAmount);
	void ApplyFilter(const Shader& filter, const Texture& source, const Texture* dest);
	
	RenderingEngine(const RenderingEngine& other) :
		m_altCamera(Matrix4f(),0){}
	void operator=(const RenderingEngine& other) {}
};

#endif // RENDERINGENGINE_H
