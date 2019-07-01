#include "stdafx.h"
#include "Filtration.h"


Filtration::Filtration()
{
}


Filtration::~Filtration()
{
}

void Filtration::Gabor_Filtr(vector<double> &Image, int Width, int Height, double sigmx, double sigmy, double tetta, double phi)
{
	int lg = 16;
	vector<double> v_Out(Width * Height, 0);
	for (int x = lg / 2; x < Width - lg / 2; ++x)
	{
		for (int y = lg / 2; y < Height - lg / 2; ++y)
		{
			for (int i = 0; i < lg; ++i)
			{
				for (int j = 0; j < lg; ++j)
				{
					v_Out[Width * x + y] += Image[Width * (i + x - lg / 2) + (j + y - lg / 2)] * Gabor(i - lg / 2, j - lg / 2, sigmx, sigmy, tetta, phi) / Width / Height;
				}				
			}
		}
	}
	Image = v_Out;
}

double Filtration::Gabor(int x, int y, double sigmx, double sigmy, double tetta, double phi)
{
	double xf = x * cos(phi) + y * sin(phi);
	double yf = -x * sin(phi) + y * cos(phi);
	/*double s1 = (-((xf * xf / sigmx / sigmx) + (0.5 * 0.5 * yf * yf / sigmy / sigmy)) / 2);
	double s2 = cos(2 * 3.1415 * tetta * xf);

	double a = exp((-((xf * xf / sigmx / sigmx) + (0.5 * 0.5 * yf * yf / sigmy / sigmy)) / 2) * cos(2 * 3.1415 * tetta * xf));*/
	return exp((-((xf * xf / sigmx / sigmx) + (0.5 * 0.5 * yf * yf / sigmy / sigmy)) / 2) * cos(2 * 3.1415 * tetta * xf));
}
