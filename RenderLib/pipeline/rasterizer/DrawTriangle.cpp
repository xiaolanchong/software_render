#include "stdafx.h"
#include "DrawTriangle.h"


void	BresenhamDraw(int x0, int y0, int x1, int y1, int* pArr)
{
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep)
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
	}
	//	int xstep, ystep;
	int deltax = abs(x1 - x0);
	int deltay = abs(y1 - y0);
	int error = 0;
	int deltaerr = deltay;
	int x = x0;
	int y = y0;
	int xstep = (x0 < x1) ? 1 : -1;
	int ystep = (y0 < y1) ? 1 : -1;

	if (steep)	pArr[x] = y;
	else		pArr[y] = x;

	for (; x != x1; )
	{
		x += xstep;
		error += deltaerr;
		if (2 * error >= deltax)
		{
			y += ystep;
			error -= deltax;
		}
		if (steep)	pArr[x] = y;
		else		pArr[y] = x;
	}
}