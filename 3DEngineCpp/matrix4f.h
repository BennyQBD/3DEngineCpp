#ifndef MATRIX4F_H
#define MATRIX4F_H

#include "vector3f.h"

class Matrix4f 
{
public:
	void InitIdentity();
	void InitScaleTransform(float scaleX, float scaleY, float scaleZ);
    void InitRotateTransform(float rotateX, float rotateY, float rotateZ);
    void InitTranslationTransform(float x, float y, float z);
    void InitCameraTransform(const Vector3f& target, const Vector3f& up);
    void InitPersProjTransform(float fov, float width, float height, float zNear, float zFar);

	inline Matrix4f operator*(const Matrix4f& right) const
	{
		Matrix4f ret;
		for (unsigned int i = 0 ; i < 4 ; i++) 
		{
			for (unsigned int j = 0 ; j < 4 ; j++) 
			{
				ret.m[i][j] = m[i][0] * right.m[0][j] +
							  m[i][1] * right.m[1][j] +
							  m[i][2] * right.m[2][j] +
							  m[i][3] * right.m[3][j];
			}
		}
		return ret;
	}
	
	inline const float* operator[](int index) const { return m[index]; }
	inline float* operator[](int index) { return m[index]; }
protected:
private:
	float m[4][4];
	
};


#endif
