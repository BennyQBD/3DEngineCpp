#ifndef FORWARDAMBIENT_H
#define FORWARDAMBIENT_H

#include "shader.h"

class ForwardAmbient : public Shader
{
public:
	static ForwardAmbient* GetInstance()
	{
		static ForwardAmbient instance;
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine);
protected:
private:
	ForwardAmbient();

	ForwardAmbient(ForwardAmbient const&){}// Don't Implement
	void operator=(ForwardAmbient const&){} // Don't implement
};

#endif // FORWARDAMBIENT_H
