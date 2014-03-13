#include "renderingEngine.h"
#include "basicShader.h"
#include <GL/glew.h>

RenderingEngine::RenderingEngine()
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
	object->Render(BasicShader::GetInstance());
}
