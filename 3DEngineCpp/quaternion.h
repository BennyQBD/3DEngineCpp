#ifndef QUATERNION_H
#define QUATERNION_H

#include "vector3f.h"

class Quaternion
{
public:
    float x, y, z, w;

    Quaternion(float _x, float _y, float _z, float _w);

    void normalize();

    Quaternion conjugate();  

	Quaternion operator*(const Quaternion& r);
	Quaternion operator*(const Vector3f& v);
 };



#endif