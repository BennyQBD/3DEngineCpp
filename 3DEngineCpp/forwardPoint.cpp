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
	material.GetTexture("diffuse")->Bind(0);

	SetUniform("model", worldMatrix);
	SetUniform("MVP", projectedMatrix);
	
	SetUniform("eyePos", renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));
	
	PointLight pointLight = *(PointLight*)renderingEngine->GetActiveLight();
	
	SetUniform("pointLight.base.color", pointLight.color);
	SetUniformf("pointLight.base.intensity", pointLight.intensity);
	SetUniformf("pointLight.atten.constant", pointLight.atten.constant);
	SetUniformf("pointLight.atten.linear", pointLight.atten.linear);
	SetUniformf("pointLight.atten.exponent", pointLight.atten.exponent);
	SetUniform("pointLight.position", pointLight.GetTransform().GetTransformedPos());
	SetUniformf("pointLight.range", pointLight.range);
}
