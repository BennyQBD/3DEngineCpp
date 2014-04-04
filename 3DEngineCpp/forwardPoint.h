#ifndef FORWARDPOINT_H
#define FORWARDPOINT_H

#include "shader.h"

class ForwardPoint : public Shader
{
public:
	static ForwardPoint* GetInstance()
	{
		static ForwardPoint instance;
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine);
protected:
private:
	ForwardPoint();

	ForwardPoint(ForwardPoint const&) : Shader("") {}// Don't Implement
	void operator=(ForwardPoint const&){} // Don't implement
};

#endif // FORWARDPOINT_H
