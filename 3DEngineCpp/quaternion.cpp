#include "quaternion.h"
#include <math.h>

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

void Quaternion::normalize()
{
    float length = sqrtf(x * x + y * y + z * z + w * w);

    x /= length;
    y /= length;
    z /= length;
    w /= length;
}


Quaternion Quaternion::conjugate()
{
    Quaternion ret(-x, -y, -z, w);
    return ret;
}

Quaternion Quaternion::operator*(const Quaternion& r)
{
    const float _w = (w * r.w) - (x * r.x) - (y * r.y) - (z * r.z);
    const float _x = (x * r.w) + (w * r.x) + (y * r.z) - (z * r.y);
    const float _y = (y * r.w) + (w * r.y) + (z * r.x) - (x * r.z);
    const float _z = (z * r.w) + (w * r.z) + (x * r.y) - (y * r.x);

    Quaternion ret(_x, _y, _z, _w);

    return ret;
}

Quaternion Quaternion::operator*(const Vector3f& v)
{
    const float _w = - (x * v.x) - (y * v.y) - (z * v.z);
    const float _x =   (w * v.x) + (y * v.z) - (z * v.y);
    const float _y =   (w * v.y) + (z * v.x) - (x * v.z);
    const float _z =   (w * v.z) + (x * v.y) - (y * v.x);

    Quaternion ret(_x, _y, _z, _w);

    return ret;
}