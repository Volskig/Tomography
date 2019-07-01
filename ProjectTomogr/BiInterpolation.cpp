#include "stdafx.h"
#include "BiInterpolation.h"

#include <vector>
BiInterpolation::BiInterpolation()
{
}
void BiInterpolation::Interpolation(float ** image, int W, int H, int ** imagexit, int N)
{
	int **buf = new int*[N + 1]();
	for (int i = 0; i < N + 1; ++i)
	{
		buf[i] = new int[N]();
	}

	double x_r = (W-1) / (double)(N);
	double y_r = (H-1) / (double)(N);
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			int x = (int)(x_r * j);
			int y = (int)(y_r * i);
			double dx = (x_r * j) - x;
			double dy = (y_r * i) - y;

			double A = image[x][y];
			double B = image[x + 1][y];
			double C = image[x][y + 1];
			double D = image[x + 1][y + 1];

			buf[j][i] = (int)(A + (B - A) * dx + (C - A) * dy + (D + A - B - C) * dx * dy);
		}
	}	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			imagexit[i][j] = buf[i][j];
			if (imagexit[i][j] > 255) imagexit[i][j] = 255;
			if (imagexit[i][j] < 0) imagexit[i][j] = 0;
		}
	}
	for (int i = 0; i < N; ++i)
	{
		delete[] buf[i];
	}
	delete[] buf;
	buf = nullptr;
}
BiInterpolation::~BiInterpolation()
{
}
