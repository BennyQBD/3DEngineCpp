#ifndef CAMERA_H
#define CAMERA_H

#include "math3d.h"
#include "gameComponent.h"

class Camera : public GameComponent
{
public:
	Camera(const Matrix4f& projection);
	
	Matrix4f GetViewProjection() const;
	virtual void AddToEngine(CoreEngine* engine);
	
	inline void SetProjection(const Matrix4f& projection) { m_projection = projection; }
protected:
private:
	Matrix4f m_projection;
};

#endif
