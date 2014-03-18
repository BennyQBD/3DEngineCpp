#ifndef TESTGAME_H
#define TESTGAME_H

#include "3DEngine.h"

class TestGame : public Game
{
public:
	TestGame() {}
	
	virtual void Init();
	
	virtual ~TestGame();
protected:
private:
	TestGame(const TestGame& other) {}
	void operator=(const TestGame& other) {}
	
	GameObject m_planeObject;
	GameObject m_directionalLightObject;
	GameObject m_pointLightObject;
	GameObject m_spotLightObject;
	
	DirectionalLight* m_directionalLight;
	PointLight* m_pointLight;
	SpotLight* m_spotLight;
	
	Material m_material;
	Mesh* m_mesh;
	Texture* m_texture;
	MeshRenderer* m_meshRenderer;
};

#endif // TESTGAME_H
