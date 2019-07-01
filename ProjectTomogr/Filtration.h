#pragma once
#include <vector>
using namespace std;
class Filtration
{
public:
	Filtration();
	~Filtration();
	void Gabor_Filtr(vector<double> &Image, int Width, int Height, double sigmx, double sigmy, double tetta, double phi);
private:	
	double Gabor(int x, int y, double sigmx, double sigmy, double tetta, double phi);
};

