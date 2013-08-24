#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix4f.h"
#include "vector3f.h"
#include "camera.h"

class Transform
{
public:
	static Camera& getCamera();
	static void setCamera(Camera& camera);
	static void setProjection(float fov, float width, float height, float zNear, float zFar);
	
	Transform(Vector3f pos = Vector3f(0,0,0), Vector3f rot = Vector3f(0,0,0), Vector3f scale = Vector3f(1,1,1));
	~Transform();

	Matrix4f getTransformation();
	Matrix4f getProjectedTransformation();

	Vector3f& getPos();
	Vector3f& getRot();
	Vector3f& getScale();

	void setPos(const Vector3f& pos);
	void setRot(const Vector3f& rot);
	void setScale(const Vector3f& scale);
protected:
private:
	static Camera* m_camera;

	static float m_fov;
	static float m_width;
	static float m_height;
	static float m_zNear;
	static float m_zFar;

	Vector3f m_pos;
	Vector3f m_rot;
	Vector3f m_scale;
};

#endif