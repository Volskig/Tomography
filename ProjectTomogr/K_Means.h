#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace cv;

class N_Spa
{
public:	
	int X;
	int Y;
	std::vector<double> N_br;	
	int Cluster1;
private:	
};
class Bank
{
public:
	std::vector<double> bank;
private:
};
class Cluster
{
public:
	std::vector<double> Center;
	std::vector<double> OldCenter;
	std::vector <double> Clust;
	std::vector <double> XY;	
private:
};
class K_Means
{
public:
	K_Means();
	void Start(CString name, std::vector<double> &oimage, int K_count, int Clusters, int stop);
	~K_Means();
private:
	std::vector<Bank> Get_Bank(int K);
	Mat GetKernel(std::vector<double> bank); //	kernel size0	theta1	psi2	lmbd3	sigma4	
	void Metod(std::vector<N_Spa> b_vec, int K, int Ncluster, std::vector<double> &return_v, int N, int M, int stop);
	double Rasst(std::vector<double> center, std::vector<double> koord);
	std::vector<double> NewCenter(int K, std::vector<double> cluster);
	
};

