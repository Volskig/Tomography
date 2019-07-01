#include "stdafx.h"
#include "K_Means.h"


K_Means::K_Means()
{
}

void K_Means::Start(CString name, std::vector<double> &oimage, int K_count, int Clusters, int stop)
{
	Mat Img;
	char st[_MAX_PATH];

	for (int i = 0; i < name.GetLength() + 1; ++i)
	{
		st[i] = name[i];
	}

	Img = imread(st, 0);

	/*imshow("windo2w", Img);*/


	std::vector <N_Spa> b_vec(Img.rows * Img.cols);

	std::vector<Bank> bank = Get_Bank(K_count);


	for (int i = 0; i < K_count; ++i)
	{
		Mat kernel = GetKernel(bank[i].bank);
		Mat src_f;
		Mat dest;
		Img.convertTo(src_f, CV_32F, 1.0 / 255, 0);
		filter2D(src_f, dest, CV_32F, kernel);
		for (int x = 0; x < Img.rows; ++x)
		{
			for (int y = 0; y < Img.cols; ++y)
			{
				b_vec[Img.cols * x + y].N_br.push_back(dest.at<float>(x, y));
				b_vec[Img.cols * x + y].X = x;
				b_vec[Img.cols * x + y].Y = y;
			}
		}
	}
	std::vector<double> return_v(Img.rows * Img.cols, 0);

	Metod(b_vec, K_count, Clusters, return_v, Img.rows, Img.cols, stop);

	oimage = return_v;

	/*Mat m(Img.rows, Img.cols, CV_32F);*/
	//for (int x = 0; x < Img.rows; ++x)
	//{
	//	for (int y = 0; y < Img.cols; ++y)
	//	{
	//		m.at<float>(x, y) = return_v[x + Img.rows * y];
	//	}
	//}

	//imshow("window", m);

	//Mat src;
	//imageCV.convertTo(src_f, CV_8UC3, 255.0);
	//Img.convertTo(src, CV_32F, 1.0 / 255, 0);
	//imshow("window", Img);

}

K_Means::~K_Means()
{
}

std::vector<Bank> K_Means::Get_Bank(int K)
{
	std::vector<Bank> Bank1;
	for (int i = 0; i < K; ++i)
	{
		std::vector<double> Odyn(5, 0);
		Odyn[0] = 13; // ks
		Odyn[1] = 0 + 180 / (K - 1) * i; // theta
		Odyn[2] = rand() % 100; // psi		
		Odyn[3] = rand() % 60; //lmbd
		Odyn[4] = rand() % 4 + 1;; //sigm

		//Odyn[0] = 17; // ks
		//Odyn[1] = 0; // theta
		//Odyn[2] = 78; // psi		
		//Odyn[3] = 37; //lmbd
		//Odyn[4] = 4; //sigm


		//Odyn[0] = 17; // ks
		//Odyn[1] = 144; // theta
		//Odyn[2] = 20; // psi		
		//Odyn[3] = 100; //lmbd
		//Odyn[4] = 3; //sigm
		Bank obj;
		obj.bank = Odyn;

		Bank1.push_back(obj);
	}
	return Bank1;
}

Mat K_Means::GetKernel(std::vector<double> bank)
{
	int hks = (bank[0] - 1) / 2;
	double theta = bank[1] * CV_PI / 180;
	double psi = bank[2] * CV_PI / 180;
	double del = 2.0 / (bank[0] - 1);
	double lmbd = 0.5 + bank[3] / 100.0;;
	double sigma = bank[4] / bank[0];
	double x_theta;
	double y_theta;
	cv::Mat kernel(bank[0], bank[0], CV_32F);
	for (int y = -hks; y <= hks; y++)
	{
		for (int x = -hks; x <= hks; x++)
		{
			x_theta = x * del*cos(theta) + y * del*sin(theta);
			y_theta = -x * del*sin(theta) + y * del*cos(theta);
			kernel.at<float>(hks + y, hks + x) = (float)exp(-0.5*(pow(x_theta, 2) + pow(y_theta, 2)) / pow(sigma, 2))* cos(2 * CV_PI*x_theta / lmbd + psi);
		}
	}
	return kernel;
}

void K_Means::Metod(std::vector<N_Spa> b_vec, int K, int Ncluster, std::vector<double> &return_v, int M, int N, int stop)
{
	std::vector<Cluster> Centers(Ncluster);
	for (int j = 0; j < Ncluster; ++j)
	{
		for (int i = 0; i < K; ++i)
		{
			Centers[j].Center.push_back(255 / (Ncluster) * (j + 1) * 1 / 255.0);
		}
	}
	std::vector<bool> fl(Ncluster, false);

	int sch1 = 0, sch2 = 0;

	do {
		//**----------------------------------------------------------------------------------------------
		for (int j = 0; j < Ncluster; ++j)
		{
			Centers[j].Clust.clear();
			Centers[j].XY.clear();
		}
		for (int x = 0; x < b_vec.size(); ++x)
		{
			double r1 = 1000000, r2 = 1000000;
			int jj = 0;
			for (int j = 0; j < Ncluster; ++j)
			{
				r1 = Rasst(Centers[j].Center, b_vec[x].N_br);
				if (r1 < r2)
				{
					r2 = r1;
					jj = j;
				}
			}
			Centers[jj].XY.push_back(b_vec[x].X);
			Centers[jj].XY.push_back(b_vec[x].Y);
			for (int i = 0; i < K; ++i)
			{
				Centers[jj].Clust.push_back(b_vec[x].N_br[i]);
			}
		}

		//**----------------------------------------------------------------------------------------------


		for (int j = 0; j < Ncluster; ++j)
		{
			Centers[j].OldCenter = Centers[j].Center;
			Centers[j].Center = NewCenter(K, Centers[j].Clust);
		}

		for (int j = 0; j < Ncluster; ++j)
		{
			if (Centers[j].OldCenter == Centers[j].Center)
			{
				fl[j] = true;
			}
		}

		sch2 = 0;
		for (int j = 0; j < Ncluster; ++j)
		{
			if (fl[j] == true)
				++sch2;
		}
		sch1++;
	} while (sch1 != stop);

	for (int j = 0; j < Ncluster; ++j)
	{
		if (Centers[j].XY.size() != 0)
		{
			for (int i = 0; i < Centers[j].XY.size() - 1; i += 2)
			{
				return_v[Centers[j].XY[i] + M * Centers[j].XY[i + 1]] = 255 / (Ncluster) * (j + 1) * 1 / 255.0;
			}
		}
	}	
}

double K_Means::Rasst(std::vector<double> center, std::vector<double> koord)
{
	double sum = 0;
	for (int i = 0; i < center.size(); ++i)
	{
		sum += (center[i] - koord[i]) * (center[i] - koord[i]);
	}
	sum = sqrt(sum);
	return sum;
}

std::vector<double> K_Means::NewCenter(int K, std::vector<double> cluster)
{
	std::vector<double> newcenter;

	for (int i = 0; i < K; ++i)
	{
		double sum = 0; double sch = 0;
		for (int j = 0; j < cluster.size(); j += K)
		{
			sum += cluster[j + i];
			++sch;
		}
		sum /= sch;
		newcenter.push_back(sum);
	}
	return newcenter;
}


