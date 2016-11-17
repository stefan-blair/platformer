#include<math.h>

#pragma once
class Vector2D
{
public:
	Vector2D() : _x(0), _y(0){}
	Vector2D(float x, float y) :_x(x), _y(y){}
	~Vector2D(){}

	Vector2D operator+(const Vector2D& v2)const{ return Vector2D(_x + v2._x, _y + v2._y); }
	Vector2D operator-(const Vector2D& v2)const{ return Vector2D(_x - v2._x, _y - v2._y); }
	Vector2D operator*(float scalar){ return Vector2D(_x*scalar, _y*scalar); }
	Vector2D operator/(float scalar){ return Vector2D(_x/scalar, _y/scalar); }

	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2){ v1._x -= v2._x; v1._y -= v2._y; return v1; }
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2){ v1._x += v2._x; v1._y += v2._y; return v1; }
	Vector2D& operator*=(float scalar){ _x *= scalar; _y *= scalar; return *this; }
	Vector2D& operator/=(float scalar){ _x /= scalar; _y /= scalar; return *this; }

	float length(){ return sqrt(_x*_x + _y*_y); }

	void normalize(){
		float l = length();
		if (l > 0)
		{
			(*this) *= 1 / 1;
		}
	}

	float getX() const { return _x; }
	float getY() const { return _y; }
	
	void setX(float x){ _x = x; }
	void setY(float y){ _y = y; }
private:
	float _x;
	float _y;
};
