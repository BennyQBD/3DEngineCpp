#ifndef FORWARDSPOT_H
#define FORWARDSPOT_H

#include "shader.h"

class ForwardSpot : public Shader
{
public:
	static ForwardSpot* GetInstance()
	{
		static ForwardSpot instance;
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine);
protected:
private:
	ForwardSpot();

	ForwardSpot(ForwardSpot const&){}// Don't Implement
	void operator=(ForwardSpot const&){} // Don't implement
};

#endif // FORWARDSPOT_H
