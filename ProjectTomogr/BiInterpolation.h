#pragma once
class BiInterpolation
{
public:
	BiInterpolation();
	void Interpolation(float** image, int w, int h, int ** imagexit, int N);
	~BiInterpolation();
};

