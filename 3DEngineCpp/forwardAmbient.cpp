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

static unsigned char whitePixel[] = {0xFF, 0xFF, 0xFF, 0xFF};

void ForwardAmbient::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	static Texture WHITE(1,1,whitePixel);

	if(material.texture != NULL)
		material.texture->Bind();
	else
		WHITE.Bind();

	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;

	SetUniform("MVP", projectedMatrix);
	SetUniform("ambientIntensity", renderingEngine->GetAmbientLight());
}
