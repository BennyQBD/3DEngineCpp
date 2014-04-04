#include "forwardSpot.h"

ForwardSpot::ForwardSpot()
{
	AddVertexShaderFromFile("forward-spot.vs");
	AddFragmentShaderFromFile("forward-spot.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);
	CompileShader();

	AddUniform("T_model");
	AddUniform("T_MVP");
	
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("C_eyePos");
		
	AddUniform("R_spotLight.pointLight.base.color");
	AddUniform("R_spotLight.pointLight.base.intensity");
	AddUniform("R_spotLight.pointLight.atten.constant");
	AddUniform("R_spotLight.pointLight.atten.linear");
	AddUniform("R_spotLight.pointLight.atten.exponent");
	AddUniform("R_spotLight.pointLight.position");
	AddUniform("R_spotLight.pointLight.range");
	AddUniform("R_spotLight.direction");
	AddUniform("R_spotLight.cutoff");
}

void ForwardSpot::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.GetTexture("diffuse")->Bind(0);

	SetUniform("T_model", worldMatrix);
	SetUniform("T_MVP", projectedMatrix);
	
	SetUniform("C_eyePos", renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));
	
	SpotLight spotLight = *(SpotLight*)renderingEngine->GetActiveLight();
	
	SetUniform("R_spotLight.pointLight.base.color", spotLight.color);
	SetUniformf("R_spotLight.pointLight.base.intensity", spotLight.intensity);
	SetUniformf("R_spotLight.pointLight.atten.constant", spotLight.atten.constant);
	SetUniformf("R_spotLight.pointLight.atten.linear", spotLight.atten.linear);
	SetUniformf("R_spotLight.pointLight.atten.exponent", spotLight.atten.exponent);
	SetUniform("R_spotLight.pointLight.position", spotLight.GetTransform().GetTransformedPos());
	SetUniformf("R_spotLight.pointLight.range", spotLight.range);
	SetUniform("R_spotLight.direction", spotLight.GetTransform().GetTransformedRot().GetForward());
	SetUniformf("R_spotLight.cutoff", spotLight.cutoff);
}
