#pragma once

#include <math.h>

class Point2D
{
public:
	Point2D() : x(0.0f), y(0.0) { }
	Point2D(float x_, float y_) : x(x_), y(y_) { }

	float x;
	float y;

};

