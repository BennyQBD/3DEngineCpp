#ifndef VECTOR2F_H
#define VECTOR2F_H

class Vector2f
{
public:
    float x;
    float y;

    Vector2f(float x = 0.0f, float y = 0.0f)
    {
        this->x = x;
        this->y = y;
    }

	Vector2f& operator+=(const Vector2f& r);
    Vector2f& operator-=(const Vector2f& r);
    Vector2f& operator*=(float f);
	Vector2f& operator/=(float f);

	Vector2f operator+(const Vector2f& r) const;
	Vector2f operator-(const Vector2f& r) const;
	Vector2f operator*(float f) const;
	Vector2f operator/(float f) const;

	inline bool operator==(const Vector2f& r) const;
	inline bool operator!=(const Vector2f& r) const;
protected:
private:
};

#endif