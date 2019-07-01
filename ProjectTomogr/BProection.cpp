#include "stdafx.h"
#include "BProection.h"

#define PI 3.1415926535897932384626433832795

BProection::BProection(int s_count, int shag_PI) : shag_PI(shag_PI), s_count(s_count)
{
	//this->bmatr = new float*[s_count];
	//for (int i = 0; i < s_count; ++i)
	//{
	//	this->bmatr[i] = new float[shag_PI];
	//}
	//for (int i = 0; i < s_count; ++i)
	//{
	//	for (int j = 0; j < shag_PI; ++j)
	//	{
	//		this->bmatr[i][j] = bmatr[i][j];
	//	}
	//}
}
void BProection::GetXYimage(float ** matrXY, int nX, int nY, float wMax, float **bmatr)
{
	int tsh = 0;
	for (float teta = 0; teta < PI; teta += PI / shag_PI)
	{
		for (int i = 0; i < nX; ++i)
		{
			for (int j = 0; j < nY; j += 8)
			{
				matrXY[nX - 1 - i][j] += GetI(i - nX / 2, j - nY / 2, tsh, teta, wMax, bmatr);	
				matrXY[nX - 1 - i][j + 1] += GetI(i - nX / 2, j + 1 - nY / 2, tsh, teta, wMax, bmatr);
				matrXY[nX - 1 - i][j + 2] += GetI(i - nX / 2, j + 2 - nY / 2, tsh, teta, wMax, bmatr);
				matrXY[nX - 1 - i][j + 3] += GetI(i - nX / 2, j + 3 - nY / 2, tsh, teta, wMax, bmatr);
				matrXY[nX - 1 - i][j + 4] += GetI(i - nX / 2, j + 4 - nY / 2, tsh, teta, wMax, bmatr);
				matrXY[nX - 1 - i][j + 5] += GetI(i - nX / 2, j + 5 - nY / 2, tsh, teta, wMax, bmatr);
				matrXY[nX - 1 - i][j + 6] += GetI(i - nX / 2, j + 6 - nY / 2, tsh, teta, wMax, bmatr);
				matrXY[nX - 1 - i][j + 7] += GetI(i - nX / 2, j + 7 - nY / 2, tsh, teta, wMax, bmatr);				
			}			
		}
		tsh++;
	}

}
float BProection::GetI(int x, int y, int teta, float tta, float wMax, float **bmatr)
{
	float minS = 1000;
	float ns = 0;

	for (int j = -s_count / 2; j < s_count / 2; ++j)
	{
		ns += bmatr[j + s_count / 2][teta] * AddFiltr(x * cos(tta) + y * sin(tta) - j, wMax);
	}

	//for (int j = -s_count / 2; j < s_count / 2; ++j)
	//{
	//	if (fabs(x * cos(tta) + y * sin(tta) - j) < minS)
	//	{
	//		ns = j;
	//		minS = fabs(x * cos(tta) + y * sin(tta) - j);
	//	}
	//}

	return ns; 
}
double BProection::AddFiltr(float s, float wMax)
{
	return 	4 * (wMax * wMax) * (cos(PI*s*wMax) * cos(PI*s*wMax)) / (PI * PI - 4 * PI * PI * s * s * wMax * wMax);
	//wMax / PI / s * sin(2 * PI*wMax*s) + 1 / 2 / PI / PI / s / s * (cos(2 * PI*wMax*s) - 1);
}
BProection::~BProection()
{
	/*for (int i = 0; i < s_count; ++i)
	{
		delete[] bmatr[i];
	}
	delete[] bmatr;*/
}
