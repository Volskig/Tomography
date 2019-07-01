#pragma once
#include <vector>
using namespace std;

class inVector
{
public:
	inVector(double p, int k);
	int GetKk();
	int GetP();
private:
	double Pnt;
	int K;
};

class Array3D
{
public:
	Array3D(vector<inVector> v_array, int alpha, int stop, int firstk);

	void GetVector(vector<inVector> &v_array_out);
	int GetAlpaha();
	int GetK(int indx);
	int stop;
	int firstk;
	~Array3D();
private:
	vector<inVector> LineArray;
	int Alpha;
};

