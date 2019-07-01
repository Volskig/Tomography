#pragma once
#include "Array3D.h"
class MultiplyMetod
{
public:
	MultiplyMetod();
	~MultiplyMetod();
public:

	void Start(vector<Array3D> v_Big, vector<inVector> v_BadMatr, vector<inVector> &v_Back, int width, int height);

private:

	inline double GetSum(vector<Array3D> v_Big, vector<inVector> v_Back, int maxk, int alpha);
	inline double GetExit(vector<Array3D> v_Big, vector<inVector> v_Back, vector<inVector> v_BadMatr, int maxa,  int maxk);
};

