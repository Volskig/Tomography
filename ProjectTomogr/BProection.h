#pragma once
class BProection
{
public:
	BProection(/*int **bmatr,*/ int shag_PI, int s_count);
	
	void GetXYimage(float **matrXY, int nX, int nY, float wMax, float **bmatr);
	~BProection();
private:
	//float **bmatr;
	int shag_PI;
	int s_count;

	float GetI(int x, int y, int teta, float tta, float wMax, float **bmatr);
	double AddFiltr(float s, float wMax);
};

