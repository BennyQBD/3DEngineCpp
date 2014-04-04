#include "forwardPoint.h"

ForwardPoint::ForwardPoint() : Shader("forward-point")
{
//	AddVertexShaderFromFile("forward-point.vs");
//	AddFragmentShaderFromFile("forward-point.fs");
//
//	SetAttribLocation("position", 0);
//	SetAttribLocation("texCoord", 1);
//	SetAttribLocation("normal", 2);
//	CompileShader();
//
//	AddUniform("T_model");
//	AddUniform("T_MVP");
//	
//	AddUniform("specularIntensity");
//	AddUniform("specularPower");
//	AddUniform("C_eyePos");
//		
//	AddUniform("R_pointLight.base.color");
//	AddUniform("R_pointLight.base.intensity");
//	AddUniform("R_pointLight.atten.constant");
//	AddUniform("R_pointLight.atten.linear");
//	AddUniform("R_pointLight.atten.exponent");
//	AddUniform("R_pointLight.position");
//	AddUniform("R_pointLight.range");
}

void ForwardPoint::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.GetTexture("diffuse")->Bind(0);

	SetUniform("T_model", worldMatrix);
	SetUniform("T_MVP", projectedMatrix);
	
	SetUniform("C_eyePos", renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));
	
	PointLight pointLight = *(PointLight*)renderingEngine->GetActiveLight();
	
	SetUniform("R_pointLight.base.color", pointLight.color);
	SetUniformf("R_pointLight.base.intensity", pointLight.intensity);
	SetUniformf("R_pointLight.atten.constant", pointLight.atten.constant);
	SetUniformf("R_pointLight.atten.linear", pointLight.atten.linear);
	SetUniformf("R_pointLight.atten.exponent", pointLight.atten.exponent);
	SetUniform("R_pointLight.position", pointLight.GetTransform().GetTransformedPos());
	SetUniformf("R_pointLight.range", pointLight.range);
}
