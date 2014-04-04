#include "forwardAmbient.h"

ForwardAmbient::ForwardAmbient() : Shader("forward-ambient")
{
//	AddVertexShaderFromFile("forward-ambient.vs");
//	AddFragmentShaderFromFile("forward-ambient.fs");
//
//	SetAttribLocation("position", 0);
//	SetAttribLocation("texCoord", 1);
//	CompileShader();
//
//	AddUniform("T_MVP");
//	AddUniform("R_ambient");
}

void ForwardAmbient::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	material.GetTexture("diffuse")->Bind(0);

	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;

	SetUniform("T_MVP", projectedMatrix);
	SetUniform("R_ambient", renderingEngine->GetAmbientLight());
}
