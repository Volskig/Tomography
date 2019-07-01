#include "stdafx.h"
#include "MultiplyMetod.h"


MultiplyMetod::MultiplyMetod()
{}

void MultiplyMetod::Start(vector<Array3D> v_Big, vector<inVector> v_BadMatr, vector<inVector> &v_Back, int width, int height)
{
	vector<inVector> v_Work;

	//float eps = 400;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			inVector objLine(255, i * height + j);
			v_Back.push_back(objLine);
		}
	}
	int sch = 0;
	do
	{
		for (int alpha = 0; alpha < v_BadMatr.size(); ++alpha)
		{
			if (v_Big[alpha].stop == 0)
			{
			}
			else {
				v_Big[alpha].GetVector(v_Work);
				for (int k = v_Big[alpha].firstk; k < v_Back.size(); ++k)
				{
					if (v_Work[k].GetP() == 0)
					{
					}
					else
					{
						inVector objW(v_Back[k].GetP() * v_BadMatr[alpha].GetP() / GetSum(v_Big, v_Back, v_Back.size(), alpha), k);
						v_Back[k] = objW;
						--v_Big[alpha].stop;
					}
					if (v_Big[alpha].stop == 0)
						break;
				}
			}
		}
		for (int k = 0; k < v_Back.size(); ++k)
		{
			if (v_Back[k].GetP() < 0)
			{
				inVector objW(0, k);
				v_Back[k] = objW;
			}
			if (v_Back[k].GetP() > 255)
			{
				inVector objW(255, k);
				v_Back[k] = objW;
			}
		}
		sch++;
	} while (/*!(GetExit(v_Big, v_Back, v_BadMatr, v_BadMatr.size(), v_Back.size()) <= eps) */sch != 3);
}

inline double MultiplyMetod::GetSum(vector<Array3D> v_Big, vector<inVector> v_Back, int maxk, int alpha)
{
	double sum = 0;
	vector<inVector> v_Work;
	v_Big[alpha].GetVector(v_Work);
	for (int i = 0; i < maxk; ++i)
	{
		sum += v_Back[i].GetP() * v_Work[i].GetP();
	}
	return sum;
}

inline double MultiplyMetod::GetExit(vector<Array3D> v_Big, vector<inVector> v_Back, vector<inVector> v_BadMatr, int maxa, int maxk)
{
	double sum = 0;
	vector<inVector> v_Work;

	for (int i = 0; i < maxa; ++i)
	{
		v_Big[i].GetVector(v_Work);

		sum += fabs(v_BadMatr[i].GetP() - GetSum(v_Big, v_Back, maxk, i));

	}
	return sum;
}

MultiplyMetod::~MultiplyMetod()
{
}
