#include "renderingEngine.h"
#include "window.h"
#include "gameObject.h"
#include "shader.h"
#include <GL/glew.h>
#include "mesh.h"
#include <cstring>

const Matrix4f RenderingEngine::s_biasMatrix = Matrix4f().InitScale(Vector3f(0.5, 0.5, 0.5)) * Matrix4f().InitTranslation(Vector3f(1.0, 1.0, 1.0));

RenderingEngine::RenderingEngine()
{
	m_samplerMap.insert(std::pair<std::string, unsigned int>("diffuse", 0));
	m_samplerMap.insert(std::pair<std::string, unsigned int>("normalMap", 1));
	m_samplerMap.insert(std::pair<std::string, unsigned int>("dispMap", 2));
	m_samplerMap.insert(std::pair<std::string, unsigned int>("shadowMap", 3));
	
	SetVector3f("ambient", Vector3f(0.2f, 0.2f, 0.2f));
	SetTexture("shadowMap", new Texture(1024, 1024, 0, GL_TEXTURE_2D, GL_NEAREST, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, true, GL_DEPTH_ATTACHMENT));
	m_defaultShader = new Shader("forward-ambient");
	m_shadowMapShader = new Shader("shadowMapGenerator");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);

	m_altCamera = new Camera(Matrix4f().InitIdentity());
	m_altCameraObject = (new GameObject())->AddComponent(m_altCamera);
	m_altCamera->GetTransform().Rotate(Vector3f(0,1,0),ToRadians(180.0f));
	
  	int width = Window::GetWidth();
	int height = Window::GetHeight();

	m_tempTarget = new Texture(width, height, 0, GL_TEXTURE_2D, GL_NEAREST, GL_RGBA, GL_RGBA, false, GL_COLOR_ATTACHMENT0);
	                  
	m_planeMaterial = new Material(m_tempTarget, 1, 8);
	m_planeTransform.SetScale(1.0f);
	m_planeTransform.Rotate(Quaternion(Vector3f(1,0,0), ToRadians(90.0f)));
	m_planeTransform.Rotate(Quaternion(Vector3f(0,0,1), ToRadians(180.0f)));
	m_plane = new Mesh("./res/models/plane.obj");
}

RenderingEngine::~RenderingEngine() 
{
	if(m_defaultShader) delete m_defaultShader;
	if(m_altCameraObject) delete m_altCameraObject;
	if(m_planeMaterial) delete m_planeMaterial;
	if(m_plane) delete m_plane;
}

void RenderingEngine::Render(GameObject* object)
{
	Window::BindAsRenderTarget();
	//m_tempTarget->BindAsRenderTarget();

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	object->RenderAll(m_defaultShader, this);
	
	for(unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		ShadowInfo* shadowInfo = m_activeLight->GetShadowInfo();
		
		GetTexture("shadowMap")->BindAsRenderTarget();
		glClear(GL_DEPTH_BUFFER_BIT);
		
		if(shadowInfo)
		{
			m_altCamera->SetProjection(shadowInfo->GetProjection());
			m_altCamera->GetTransform().SetPos(m_activeLight->GetTransform().GetTransformedPos());
			m_altCamera->GetTransform().SetRot(m_activeLight->GetTransform().GetTransformedRot());
			
			m_lightMatrix = s_biasMatrix * m_altCamera->GetViewProjection();
			
			SetVector3f("shadowTexelSize", Vector3f(1.0f/1024.0f, 1.0f/1024.0f, 0.0f));
			SetFloat("shadowBias", shadowInfo->GetBias()/1024.0f);
			bool flipFaces = shadowInfo->GetFlipFaces();
			
			Camera* temp = m_mainCamera;
			m_mainCamera = m_altCamera;
			
			if(flipFaces) glCullFace(GL_FRONT);
			object->RenderAll(m_shadowMapShader, this);
			if(flipFaces) glCullFace(GL_BACK);
			
			m_mainCamera = temp;
		}
	
		Window::BindAsRenderTarget();
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);

		object->RenderAll(m_activeLight->GetShader(), this);
		
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);
	}
	
//	//Temp Render
//	Window::BindAsRenderTarget();
//	
//	Camera* temp = m_mainCamera;
//	m_mainCamera = m_altCamera;
//	
//	glClearColor(0.0f,0.0f,0.5f,1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	m_defaultShader->Bind();
//	m_defaultShader->UpdateUniforms(m_planeTransform, *m_planeMaterial, this);
//	m_plane->Draw();
//	
//	m_mainCamera = temp;
}
