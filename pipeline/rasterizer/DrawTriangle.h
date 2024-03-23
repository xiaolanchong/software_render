#pragma once

template <class ScreenPlotter, typename DrawValue>
void	DrawLine(ScreenPlotter& dc, int x1, int x2, int y, 
		         DrawValue cl1, DrawValue cl2 )
{
	if( x2 == x1 ) 
	{
		dc.Plot( x1, y, cl1 );
		return;
	}
	if( x2 < x1 )
	{
		std::swap(x1, x2);
		std::swap(cl1, cl2);
	}
	for( int x = x1; x <= x2; ++x )
	{
		DrawValue cl = dc.Interpolate( x1, x, x2, cl1, cl2 );
		dc.Plot( x, y, cl )	;
	}
}

void	BresenhamDraw(int x0, int y0, int x1, int y1, int* pArr);

constexpr int c_nMaxResolution = 10000;

template <class ScreenPlotter, typename DrawValue>
void	DrawAlignTriangle(	ScreenPlotter& dc, 
						  int x1, int y1, int x2, int y2, int x3,
						  DrawValue cl1, DrawValue cl2, DrawValue cl3   )
{
	int buf_edge1to2[c_nMaxResolution];
	int buf_edge1to3[c_nMaxResolution];
	int* edge1to2 = buf_edge1to2 + c_nMaxResolution/2;
	int* edge1to3 = buf_edge1to3 + c_nMaxResolution/2;

	//! draw in memory
	BresenhamDraw( x1, y1, x2, y2, edge1to2 );
	BresenhamDraw( x1, y1, x3, y2, edge1to3 );

	bool bSwap = false;
	if( y1 > y2 )
	{
		std::swap( y1, y2);
		bSwap = true;
	}
	DrawValue cl1to2;
	DrawValue cl1to3;
	if( y2 == y1 ) 
	{
		DrawLine( dc,  x1, x2, y1, cl1,  cl2 );
		return;
	}

	if( bSwap )
		for( int y = y1; y <= y2; ++y  )
		{
			cl1to2 = dc.Interpolate( y1, y, y2, cl2, cl1 );
			cl1to3 = dc.Interpolate( y1, y, y2, cl3, cl1 );
			DrawLine( dc,  edge1to2[y], edge1to3[y], y, cl1to2,  cl1to3 );
		}
	else
		for( int y = y1; y <= y2; ++y  )
		{
			cl1to2 = dc.Interpolate( y1, y, y2, cl1, cl2 );
			cl1to3 = dc.Interpolate( y1, y, y2, cl1, cl3 );
			DrawLine( dc,  edge1to2[y], edge1to3[y], y, cl1to2,  cl1to3 );
		}
}

template <class ScreenPlotter, class DrawValue>
void	DrawTriangle(ScreenPlotter& dc, int x1, int y1, int x2, int y2, int x3, int y3,
					    DrawValue cl1, DrawValue cl2, DrawValue cl3  )
{
	//! сортируем пока не y1 <= y2 <= y3
	while (true)
	{
		if (y1 > y2)
		{
			std::swap(y1, y2);
			std::swap(x1, x2);
			std::swap(cl1, cl2);
		}
		else if (y2 > y3)
		{
			std::swap(y2, y3);
			std::swap(x2, x3);
			std::swap(cl2, cl3);
		}
		else if (y1 > y3)
		{
			std::swap(y1, y3);
			std::swap(x1, x3);
			std::swap(cl1, cl3);
		}
		else
			break;
	}

	if( abs(y1) >= c_nMaxResolution/2  ||
		abs(x1) >= c_nMaxResolution/2  ||
		abs(y2) >= c_nMaxResolution/2  ||
		abs(x2) >= c_nMaxResolution/2  ||
		abs(x3) >= c_nMaxResolution/2  ||
		abs(y3) >= c_nMaxResolution/2   )
		return ; //! error

	if( y3 == y1 )
	{
		DrawLine( dc,  x1, x3, y1, cl1,  cl3 );
		return;
	}

	int  nx = (x3 - x1 )*(y2-y1)/(y3 - y1) + x1;
	DrawValue cln = dc.Interpolate( y1, y2, y3, cl1, cl3 );

	DrawAlignTriangle( dc, x1, y1, x2, y2, nx, cl1, cl2, cln );
	DrawAlignTriangle( dc, x3, y3, x2, y2, nx, cl3, cl2, cln );
}
