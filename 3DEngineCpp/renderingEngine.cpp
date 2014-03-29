#include "renderingEngine.h"
#include "forwardAmbient.h"
#include "forwardPoint.h"
#include "forwardSpot.h"
#include "forwardDirectional.h"
#include "window.h"
#include "gameObject.h"
#include <GL/glew.h>

RenderingEngine::RenderingEngine() :
	//m_mainCamera(ToRadians(70.0f), Window::GetAspect(), 0.01f, 1000.0f),
	m_ambientLight(0.1f, 0.1f, 0.1f)
	//m_ambientLight(0.0f, 0.0f, 0.0f),
	//m_directionalLight(BaseLight(Vector3f(1,1,1), 0.8f), Vector3f(1,1,1)),
	//m_pointLight(BaseLight(Vector3f(0,1,0),0.4f),Attenuation(0,0,1),Vector3f(7,0,7),100),
	//m_spotLight(PointLight(BaseLight(Vector3f(0,1,1),0.4f),Attenuation(0,0,0.1f),Vector3f(0,0,0),100),Vector3f(1,0,0),0.7f)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
}

RenderingEngine::~RenderingEngine()
{
	//dtor
}

void RenderingEngine::Render(GameObject* object)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_lights.clear();
	
	object->AddToRenderingEngine(this);
	object->Render(ForwardAmbient::GetInstance(), this);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);
	
	for(unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		object->Render(m_activeLight->GetShader(), this);
	}
	
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
}
