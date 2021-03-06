#pragma once

#include <math.h>

class Vector2
{
public:
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2() : x(0), y(0) {}

	double getLength()
	{
		return sqrt(pow(x, 2) + pow(y,  2));
	}

	void normalize()
	{
		x = x / getLength();
		y = y / getLength();
	}

	Vector2 operator* (Vector2 param) {
		Vector2 temp;
		temp.x = x * param.x;
		temp.y = y * param.y;
		return (temp);
	}

	Vector2 operator* (double param) {
		Vector2 temp;
		temp.x = x * param;
		temp.y = y * param;
		return (temp);
	}

	Vector2 operator- (Vector2 param) {
		Vector2 temp;
		temp.x = x - param.x;
		temp.y = y - param.y;
		return (temp);
	}

	Vector2 operator-= (Vector2 param) {
		x -= param.x;
		y -= param.y;
		return (*this);
	}

	Vector2 operator+= (Vector2 param) {
		x += param.x;
		y += param.y;
		return (*this);
	}

	Vector2 operator/ (double param) {
		Vector2 temp;
		temp.x = x / param;
		temp.y = y / param;
		return (temp);
	}

	float x, y;
};
