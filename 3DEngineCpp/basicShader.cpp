#include "basicShader.h"
#include "util.h"

BasicShader::BasicShader()
{
	addVertexShaderFromFile("basicVertex.vs");
	addFragmentShaderFromFile("basicFragment.fs");
	compileShader();

	addUniform("transform");
	addUniform("color");
	//addUniform("sampler2D");
}

BasicShader::~BasicShader()
{

}

static unsigned char whitePixel[] = {0xFF, 0xFF, 0xFF, 0xFF};

void BasicShader::updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, Material& material)
{
	static Texture WHITE = Texture(1,1,whitePixel);

	if(material.texture != NULL)
		material.texture->bind();
	else
		WHITE.bind();

	setUniform("transform", projectedMatrix);
	setUniform("color", material.color);
}