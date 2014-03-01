#include "basicShader.h"
#include "util.h"

BasicShader::BasicShader()
{
	AddVertexShaderFromFile("basicVertex.vs");
	AddFragmentShaderFromFile("basicFragment.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	CompileShader();

	AddUniform("transform");
	AddUniform("color");
	//addUniform("sampler2D");
}

static unsigned char whitePixel[] = {0xFF, 0xFF, 0xFF, 0xFF};

void BasicShader::UpdateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, const Material& material)
{
	static Texture WHITE(1,1,whitePixel);

	if(material.texture != NULL)
		material.texture->Bind();
	else
		WHITE.Bind();

	SetUniform("transform", projectedMatrix);
	SetUniform("color", material.color);
}
