#include "renderingEngine.h"
#include "forwardAmbient.h"
#include "forwardDirectional.h"
#include "window.h"
#include "gameObject.h"
#include <GL/glew.h>

RenderingEngine::RenderingEngine() :
	m_mainCamera(ToRadians(70.0f), Window::GetAspect(), 0.01f, 1000.0f),
	m_ambientLight(0.1f, 0.1f, 0.1f),
	m_directionalLight(BaseLight(Vector3f(1,1,1),0.8f), Vector3f(1,1,1))
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

void RenderingEngine::Input(float delta)
{
	m_mainCamera.Input(delta);
}

void RenderingEngine::Render(GameObject* object)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	object->Render(ForwardAmbient::GetInstance(), this);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);
	
	object->Render(ForwardDirectional::GetInstance(), this);
	
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
}
