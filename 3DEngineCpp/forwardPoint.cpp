#include "forwardPoint.h"

ForwardPoint::ForwardPoint()
{
	AddVertexShaderFromFile("forward-point.vs");
	AddFragmentShaderFromFile("forward-point.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);
	CompileShader();

	AddUniform("model");
	AddUniform("MVP");
	
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
		
	AddUniform("pointLight.base.color");
	AddUniform("pointLight.base.intensity");
	AddUniform("pointLight.atten.constant");
	AddUniform("pointLight.atten.linear");
	AddUniform("pointLight.atten.exponent");
	AddUniform("pointLight.position");
	AddUniform("pointLight.range");
}

void ForwardPoint::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.texture->Bind();

	SetUniform("model", worldMatrix);
	SetUniform("MVP", projectedMatrix);
	
	SetUniform("eyePos", renderingEngine->GetMainCamera().GetPos());
	SetUniformf("specularIntensity", material.specularIntensity);
	SetUniformf("specularPower", material.specularPower);
	
	SetUniform("pointLight.base.color", renderingEngine->GetPointLight().base.color);
	SetUniformf("pointLight.base.intensity", renderingEngine->GetPointLight().base.intensity);
	SetUniformf("pointLight.atten.constant", renderingEngine->GetPointLight().atten.constant);
	SetUniformf("pointLight.atten.linear", renderingEngine->GetPointLight().atten.linear);
	SetUniformf("pointLight.atten.exponent", renderingEngine->GetPointLight().atten.exponent);
	SetUniform("pointLight.position", renderingEngine->GetPointLight().position);
	SetUniformf("pointLight.range", renderingEngine->GetPointLight().range);
}
