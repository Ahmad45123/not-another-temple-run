#pragma once
#include <glut.h>
class Vector
{
public:
	GLdouble x = {}, y = {}, z = {};
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}

	void operator +=(float value);
};

