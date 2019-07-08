#pragma once

class WorldCanvas
{
public:
	virtual void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;
	virtual void setPixel(unsigned x, unsigned y) = 0;
	virtual void plotCircle(int xm, int ym, int r) = 0;
	virtual void plotLine(int x0, int y0, int x1, int y1) = 0;

};