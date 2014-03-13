#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "gameObject.h"

class RenderingEngine
{
public:
	RenderingEngine();
	
	void Render(GameObject* object);
	
	virtual ~RenderingEngine();
protected:
private:
	RenderingEngine(const RenderingEngine& other) {}
	void operator=(const RenderingEngine& other) {}
};

#endif // RENDERINGENGINE_H
