#include "forwardDirectional.h"

ForwardDirectional::ForwardDirectional()
{
	AddVertexShaderFromFile("forward-directional.vs");
	AddFragmentShaderFromFile("forward-directional.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);
	CompileShader();

	AddUniform("model");
	AddUniform("MVP");
	
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
		
	AddUniform("directionalLight.base.color");
	AddUniform("directionalLight.base.intensity");
	AddUniform("directionalLight.direction");
}

void ForwardDirectional::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.texture->Bind();

	SetUniform("model", worldMatrix);
	SetUniform("MVP", projectedMatrix);
	
	SetUniform("eyePos", renderingEngine->GetMainCamera().GetPos());
	SetUniformf("specularIntensity", material.specularIntensity);
	SetUniformf("specularPower", material.specularPower);
	
	SetUniform("directionalLight.direction", renderingEngine->GetDirectionalLight().direction);
	SetUniform("directionalLight.base.color", renderingEngine->GetDirectionalLight().base.color);
	SetUniformf("directionalLight.base.intensity", renderingEngine->GetDirectionalLight().base.intensity);
}
