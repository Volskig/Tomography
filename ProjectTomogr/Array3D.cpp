#include "stdafx.h"
#include "Array3D.h"

inVector::inVector(double p, int k) : Pnt(p), K(k)
{}

int inVector::GetP()
{
	return Pnt;
}
int inVector::GetKk()
{
	return K;
}

Array3D::Array3D(vector<inVector> v_array, int alpha, int stop, int firstk) :  LineArray(v_array), Alpha(alpha), stop(stop), firstk(firstk)
{}

void Array3D::GetVector(vector<inVector> &v_array_out)
{
	v_array_out = LineArray;
}

int Array3D::GetAlpaha()
{
	return Alpha;
}

int Array3D::GetK(int indx)
{
	return LineArray.at(indx).GetKk();
}

Array3D::~Array3D()
{
}


