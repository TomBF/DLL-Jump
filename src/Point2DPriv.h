#pragma once

#include "../../../src/Point2DPriv.h"
#include <ctime>
#include <random>

float rand01() { return float(rand()) / float(RAND_MAX); }
Point2D randP2() { return Point2D(float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX)); }

Point2D operator*(const Point2D &lhd, const Point2D& rhd)
{
	return Point2D(lhd.x * rhd.x, lhd.y * rhd.y);
}
Point2D operator*(const Point2D &lhd, float v)
{
	return Point2D(lhd.x * v, lhd.y * v);
}
Point2D operator-(const Point2D &lhd, const Point2D& rhd)
{
	return Point2D(lhd.x - rhd.x, lhd.y - rhd.y);
}
Point2D operator+(const Point2D &lhd, const Point2D& rhd)
{
	return Point2D(lhd.x + rhd.x, lhd.y + rhd.y);
}

float mag(const Point2D& rhd)
{
	return sqrt(rhd.x*rhd.x + rhd.y*rhd.y);
}

float clamp(float minv, float maxv, float v)
{
	if (v > maxv)
		return maxv;
	if (v < minv)
		return minv;
	return v;
}