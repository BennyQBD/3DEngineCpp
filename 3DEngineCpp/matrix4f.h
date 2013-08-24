#ifndef MATRIX4F_H
#define MATRIX4F_H

#include "vector3f.h"

class Matrix4f 
{
public:
	void initIdentity();
	void initScaleTransform(float scaleX, float scaleY, float scaleZ);
    void initRotateTransform(float rotateX, float rotateY, float rotateZ);
    void initTranslationTransform(float x, float y, float z);
    void initCameraTransform(const Vector3f& target, const Vector3f& up);
    void initPersProjTransform(float fov, float width, float height, float zNear, float zFar);

	inline Matrix4f operator*(const Matrix4f& right) const;
	const float* operator[](int index) const;
	float* operator[](int index);

protected:
private:
	float m[4][4];
	
};


#endif