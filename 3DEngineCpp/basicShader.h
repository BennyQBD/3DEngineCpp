#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "shader.h"

class BasicShader : public Shader
{
public:
	static BasicShader* getInstance()
	{
		static BasicShader instance;
		return &instance;
	}

	virtual void updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, Material& material);
protected:
private:
	BasicShader();
	~BasicShader();

	BasicShader(BasicShader const&){}// Don't Implement
	void operator=(BasicShader const&){} // Don't implement
};

#endif