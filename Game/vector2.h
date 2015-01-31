#pragma once

//our vector class that we use

class Vector2
{
public:
	double x;
	double y;
	Vector2() : x(0), y(0)	//default constructor
	{
	}
	Vector2(double x, double y) : x(x), y(y)  //constructor
	{
	}
	Vector2 operator+(const Vector2& rhs)
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}
	Vector2 operator-(const Vector2& rhs)
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}
};

