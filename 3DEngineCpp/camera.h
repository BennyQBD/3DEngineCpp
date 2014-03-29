#ifndef CAMERA_H
#define CAMERA_H

#include "math3d.h"
#include "gameComponent.h"

class Camera : public GameComponent
{
public:
	Camera(float fov, float aspect, float zNear, float zFar);

	void Input(float delta);
	void Move(const Vector3f& direction, float amt);
//	void RotateY(float angle);
//	void RotateX(float angle);
	
	Matrix4f GetViewProjection() const;
	virtual void AddToRenderingEngine(RenderingEngine* renderingEngine);
protected:
private:
	Matrix4f m_projection;
};

#endif
