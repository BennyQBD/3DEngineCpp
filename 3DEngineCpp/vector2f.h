#ifndef VECTOR2F_H
#define VECTOR2F_H

class Vector2f
{
public:
    Vector2f(float x = 0.0f, float y = 0.0f) :
		x(x),
		y(y) { }

	inline Vector2f& operator+=(const Vector2f& r)
	{
		x += r.x;
		y += r.y;

		return *this;
	}
	
    inline Vector2f& operator-=(const Vector2f& r)
    {
		x -= r.x;
		y -= r.y;

		return *this;
    }
    
    inline Vector2f& operator*=(float f)
    {
		x *= f;
		y *= f;

		return *this;
    }
    
	inline Vector2f& operator/=(float f)
	{
		x /= f;
		y /= f;

		return *this;
	}

	inline Vector2f operator+(const Vector2f& r) const { return Vector2f(x + r.x, y + r.y); }
	inline Vector2f operator-(const Vector2f& r) const { return Vector2f(x - r.x, y - r.y); }
	inline Vector2f operator*(float f) const { return Vector2f(x * f, y * f); }
	inline Vector2f operator/(float f) const { return Vector2f(x / f, y / f); }

	inline bool operator==(const Vector2f& r) const { return x == r.x && y == r.y; }
	inline bool operator!=(const Vector2f& r) const { return !operator==(r); }
	
	inline float GetX() const { return x; }
	inline float GetY() const { return y; }
protected:
private:
	float x;
    float y;
};

#endif
