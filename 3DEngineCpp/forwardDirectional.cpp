#include "forwardDirectional.h"

ForwardDirectional::ForwardDirectional() : Shader("forward-directional")
{
//	AddVertexShaderFromFile("forward-directional.vs");
//	AddFragmentShaderFromFile("forward-directional.fs");
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
//	AddUniform("R_directionalLight.base.color");
//	AddUniform("R_directionalLight.base.intensity");
//	AddUniform("R_directionalLight.direction");
}

void ForwardDirectional::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.GetTexture("diffuse")->Bind(0);

	SetUniform("T_model", worldMatrix);
	SetUniform("T_MVP", projectedMatrix);
	
	SetUniform("C_eyePos", renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));
	
	DirectionalLight directionalLight = *(DirectionalLight*)renderingEngine->GetActiveLight();
	
	SetUniform("R_directionalLight.direction", directionalLight.GetTransform().GetTransformedRot().GetForward());
	SetUniform("R_directionalLight.base.color", directionalLight.color);
	SetUniformf("R_directionalLight.base.intensity", directionalLight.intensity);
}
