#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "shader.h"

class BasicShader : public Shader
{
public:
	static BasicShader* GetInstance()
	{
		static BasicShader instance;
		return &instance;
	}

	virtual void UpdateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, const Material& material);
protected:
private:
	BasicShader();

	BasicShader(BasicShader const&){}// Don't Implement
	void operator=(BasicShader const&){} // Don't implement
};

#endif
