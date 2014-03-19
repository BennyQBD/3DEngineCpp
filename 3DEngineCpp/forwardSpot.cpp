#include "forwardSpot.h"

ForwardSpot::ForwardSpot()
{
	AddVertexShaderFromFile("forward-spot.vs");
	AddFragmentShaderFromFile("forward-spot.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);
	CompileShader();

	AddUniform("model");
	AddUniform("MVP");
	
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
		
	AddUniform("spotLight.pointLight.base.color");
	AddUniform("spotLight.pointLight.base.intensity");
	AddUniform("spotLight.pointLight.atten.constant");
	AddUniform("spotLight.pointLight.atten.linear");
	AddUniform("spotLight.pointLight.atten.exponent");
	AddUniform("spotLight.pointLight.position");
	AddUniform("spotLight.pointLight.range");
	AddUniform("spotLight.direction");
	AddUniform("spotLight.cutoff");
}

void ForwardSpot::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.texture->Bind();

	SetUniform("model", worldMatrix);
	SetUniform("MVP", projectedMatrix);
	
	SetUniform("eyePos", renderingEngine->GetMainCamera().GetPos());
	SetUniformf("specularIntensity", material.specularIntensity);
	SetUniformf("specularPower", material.specularPower);
	
	SpotLight spotLight = *(SpotLight*)renderingEngine->GetActiveLight();
	
	SetUniform("spotLight.pointLight.base.color", spotLight.color);
	SetUniformf("spotLight.pointLight.base.intensity", spotLight.intensity);
	SetUniformf("spotLight.pointLight.atten.constant", spotLight.atten.constant);
	SetUniformf("spotLight.pointLight.atten.linear", spotLight.atten.linear);
	SetUniformf("spotLight.pointLight.atten.exponent", spotLight.atten.exponent);
	SetUniform("spotLight.pointLight.position", spotLight.GetTransform().GetPos());
	SetUniformf("spotLight.pointLight.range", spotLight.range);
	SetUniform("spotLight.direction", spotLight.direction);
	SetUniformf("spotLight.cutoff", spotLight.cutoff);
}
