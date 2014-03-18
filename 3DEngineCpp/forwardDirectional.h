#ifndef FORWARDDIRECTIONAL_H
#define FORWARDDIRECTIONAL_H

#include "shader.h"

class ForwardDirectional : public Shader
{
public:
	static ForwardDirectional* GetInstance()
	{
		static ForwardDirectional instance;
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine);
protected:
private:
	ForwardDirectional();

	ForwardDirectional(ForwardDirectional const&){}// Don't Implement
	void operator=(ForwardDirectional const&){} // Don't implement
};

#endif // FORWARDDIRECTIONAL_H
