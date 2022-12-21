#pragma once

class Vector
{
public:
	double x = {}, y = {}, z = {};
	Vector() {}
	Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	void operator +=(float value);
};

