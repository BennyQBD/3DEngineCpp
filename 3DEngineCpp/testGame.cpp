#include "testGame.h"

void TestGame::Init()
{
	m_mesh = new Mesh("./res/models/plane3.obj");
	m_texture = new Texture("test.png");
	m_material = Material(m_texture, Vector3f(1,1,1), 1, 8);
	
	m_meshRenderer = new MeshRenderer(*m_mesh, m_material);
	m_planeObject.AddComponent(m_meshRenderer);
	m_planeObject.GetTransform().SetPos(Vector3f(0, -1, 5));
	m_planeObject.GetTransform().SetScale(4.0f);
	
	m_directionalLight = DirectionalLight(BaseLight(Vector3f(1,1,1), 0.8f), Vector3f(1,1,1));
	m_directionalLightObject.AddComponent(&m_directionalLight);
	
	m_pointLight = PointLight(BaseLight(Vector3f(0,1,0),0.4f),Attenuation(0,0,1),Vector3f(7,0,7),100);
	m_pointLightObject.AddComponent(&m_pointLight);
	
	AddToScene(m_planeObject);
	AddToScene(m_directionalLightObject);
	AddToScene(m_pointLightObject);
}

TestGame::~TestGame()
{
	if(m_texture) delete m_texture;
	if(m_mesh) delete m_mesh;
	if(m_meshRenderer) delete m_meshRenderer;
}
