#ifndef CAMERA_H
#define CAMERA_H

#include "math3d.h"
#include "gameComponent.h"

class Camera : public GameComponent
{
public:
	Camera(float fov, float aspect, float zNear, float zFar);
	
	Matrix4f GetViewProjection() const;
	virtual void AddToEngine(CoreEngine* engine);
protected:
private:
	Matrix4f m_projection;
};

#endif
