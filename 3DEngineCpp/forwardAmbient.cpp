#include "forwardAmbient.h"

ForwardAmbient::ForwardAmbient()
{
	AddVertexShaderFromFile("forward-ambient.vs");
	AddFragmentShaderFromFile("forward-ambient.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	CompileShader();

	AddUniform("MVP");
	AddUniform("ambientIntensity");
}

void ForwardAmbient::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	material.GetTexture("diffuse")->Bind(0);

	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;

	SetUniform("MVP", projectedMatrix);
	SetUniform("ambientIntensity", renderingEngine->GetAmbientLight());
}
