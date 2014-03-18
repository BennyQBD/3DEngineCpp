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

	virtual void UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine);
protected:
private:
	BasicShader();

	BasicShader(BasicShader const&){}// Don't Implement
	void operator=(BasicShader const&){} // Don't implement
};

#endif
