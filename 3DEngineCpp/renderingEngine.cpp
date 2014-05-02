#include "renderingEngine.h"
#include "window.h"
#include "gameObject.h"
#include "shader.h"
#include <GL/glew.h>
#include "mesh.h"
#include <cstring>

//Temp variables
static Texture* g_tempTarget = 0;
static Mesh* g_mesh = 0;
static Transform g_transform;
static Material* g_material;
static Camera* g_camera = 0;
static GameObject* g_cameraObject = 0;

RenderingEngine::RenderingEngine()
{
	m_samplerMap.insert(std::pair<std::string, unsigned int>("diffuse", 0));
	m_samplerMap.insert(std::pair<std::string, unsigned int>("normalMap", 1));
	m_samplerMap.insert(std::pair<std::string, unsigned int>("dispMap", 2));
	
	AddVector3f("ambient", Vector3f(0.2f, 0.2f, 0.2f));
	m_defaultShader = new Shader("forward-ambient");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	
	//Begin Temp initialization
	if(g_mesh) delete g_mesh;
	if(g_material) delete g_material;
	if(g_cameraObject) delete g_cameraObject;
	
  	int width = Window::GetWidth() / 3;
	int height = Window::GetHeight() / 3;
	int dataSize = width * height * 4;
	
	unsigned char* data = new unsigned char[dataSize];
	memset(data, 0, dataSize);
	
	g_tempTarget = new Texture(width, height, data, GL_TEXTURE_2D, GL_NEAREST, GL_COLOR_ATTACHMENT0);
	
	delete[] data;
	
	Vertex vertices[] = { Vertex(Vector3f(-1,-1,0),Vector2f(1,0)),
	                      Vertex(Vector3f(-1,1,0),Vector2f(1,1)),
	                      Vertex(Vector3f(1,1,0),Vector2f(0,1)),
	                      Vertex(Vector3f(1,-1,0),Vector2f(0,0)) };
	
	int indices[] = { 2, 1, 0,
	                  3, 2, 0 };
	                  
	g_material = new Material(g_tempTarget, 1, 8);
	g_transform.SetScale(0.9f);
	g_mesh = new Mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]), true);
	
	g_camera = new Camera(Matrix4f().InitIdentity());
	g_cameraObject = (new GameObject())->AddComponent(g_camera);
	
	g_camera->GetTransform().Rotate(Vector3f(0,1,0),ToRadians(180.0f));
}

RenderingEngine::~RenderingEngine() 
{
	if(m_defaultShader) delete m_defaultShader;
	
	//Temp destruction
	if(g_mesh) delete g_mesh;
	if(g_material) delete g_material;
	if(g_cameraObject) delete g_cameraObject;
}

void RenderingEngine::Render(GameObject* object)
{
	g_tempTarget->BindAsRenderTarget();

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	object->RenderAll(m_defaultShader, this);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);
	
	for(unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		object->RenderAll(m_activeLight->GetShader(), this);
	}
	
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
	
	//Temp Render
	Window::BindAsRenderTarget();
	
	Camera* temp = m_mainCamera;
	m_mainCamera = g_camera;
	
	glClearColor(0.0f,0.0f,0.5f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_defaultShader->Bind();
	m_defaultShader->UpdateUniforms(g_transform, *g_material, this);
	g_mesh->Draw();
	
	m_mainCamera = temp;
}
