#include "vector2f.h"

Vector2f& Vector2f::operator+=(const Vector2f& r)
{
    x += r.x;
    y += r.y;

    return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& r)
{
    x -= r.x;
    y -= r.y;

    return *this;
}

Vector2f& Vector2f::operator*=(float f)
{
    x *= f;
    y *= f;

    return *this;
}

Vector2f& Vector2f::operator/=(float f)
{
    x /= f;
    y /= f;

    return *this;
}

Vector2f Vector2f::operator+(const Vector2f& r) const 
{
	Vector2f ret(x + r.x,
				 y + r.y);

	return ret;
}

Vector2f Vector2f::operator-(const Vector2f& r) const 
{
	Vector2f ret(x - r.x,
				 y - r.y);
	return ret;
}

Vector2f Vector2f::operator*(float f) const
{
	Vector2f ret(x * f,
				 y * f);
	return ret;
}

Vector2f Vector2f::operator/(float f) const 
{
	Vector2f ret(x / f,
				 y / f);
	return ret;
}

inline bool Vector2f::operator==(const Vector2f& r) const
{
	return x == r.x && y == r.y;
}

inline bool Vector2f::operator!=(const Vector2f& r) const
{
	return !operator==(r);
}