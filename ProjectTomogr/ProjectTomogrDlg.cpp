
// ProjectTomogrDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "ProjectTomogr.h"
#include "ProjectTomogrDlg.h"
#include "afxdialogex.h"
#include "Draw.h"
#include"math.h"
#include "BiInterpolation.h"
#include "BProection.h"
//#include "Array3D.h"
#include "MultiplyMetod.h"
//#include "Filtration.h"
//#include "K_Means.h"
#include <thread>
#include <mutex>


#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/nonfree/features2d.hpp"

using namespace cv;
#define PI 3.1415

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CProjectTomogrDlg



CProjectTomogrDlg::CProjectTomogrDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECTTOMOGR_DIALOG, pParent)
	, flag_picture(FALSE)
	, LRAY(5)
	, STEPPI(10)
	, WMAX(15)
	, one(FALSE)
	, two(FALSE)
	, fl4(FALSE)
	, fl5(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectTomogrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, flag_picture);
	DDX_Text(pDX, IDC_EDIT2, LRAY);
	DDX_Text(pDX, IDC_EDIT1, STEPPI);
	DDX_Text(pDX, IDC_EDIT3, WMAX);
	DDX_Check(pDX, IDC_CHECK2, one);
	DDX_Check(pDX, IDC_CHECK3, two);
	DDX_Check(pDX, IDC_CHECK4, fl4);
	DDX_Check(pDX, IDC_CHECK5, fl5);
}

BEGIN_MESSAGE_MAP(CProjectTomogrDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CProjectTomogrDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CProjectTomogrDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CProjectTomogrDlg

BOOL CProjectTomogrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	Wind1 = GetDlgItem(IDC_WINDOW1);
	Window1 = Wind1->GetDC();
	Wind1->GetClientRect(&Win1);

	Wind2 = GetDlgItem(IDC_WINDOW2);
	Window2 = Wind2->GetDC();
	Wind2->GetClientRect(&Win2);

	Wind3 = GetDlgItem(IDC_WINDOW3);
	Window3 = Wind3->GetDC();
	Wind3->GetClientRect(&Win3);

	shag_pi = STEPPI;
	length_line = LRAY;

	imr = new float*[N_for_Int];
	for (int i = 0; i < N_for_Int; ++i)
	{
		imr[i] = new float[N_for_Int]();
	}

	image1 = new int*[N_for_Int2];
	for (int i = 0; i < N_for_Int2; ++i)
	{
		image1[i] = new int[N_for_Int2]();
	}

	image2 = new int*[N_for_Int2];
	for (int i = 0; i < N_for_Int2; ++i)
	{
		image2[i] = new int[N_for_Int2]();
	}

	imageex2 = new int*[N_for_Int2];
	for (int i = 0; i < N_for_Int2; ++i)
	{
		imageex2[i] = new int[N_for_Int2]();
	}

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CProjectTomogrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		Draw obDraw;
		obDraw.DrawImage(Window3, Win3, N_for_Int2, N_for_Int2, image1);
		obDraw.DrawImage(Window2, Win2, N_for_Int2, N_for_Int2, image2);
		//obDraw.DrawRandColor(Window2, Win2, N_for_Int2, N_for_Int2, image2);
		obDraw.DrawImage(Window1, Win1, N_for_Int2, N_for_Int2, imageex2);
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CProjectTomogrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CProjectTomogrDlg::MainF()
{
	flag_picture = false;
	UpdateData(false);
	CBitmap cbm;	BITMAP bm;
	CFileDialog fd(TRUE, NULL, NULL, OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY |
		OFN_LONGNAMES | OFN_PATHMUSTEXIST, _T("Image Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL, 0, TRUE);
	if (fd.DoModal() != IDOK)
	{
		MessageBox(L"NO TOUCH. EXIT?", L"Bad eye", MB_OK);
		exit(0);
	};
	CString pathBMP = fd.GetPathName();
	cbm.Attach(LoadImage(0, pathBMP, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	cbm.GetObject(sizeof(BITMAP), &bm);

	width = bm.bmWidth;
	height = bm.bmHeight;

	CDC *BDC = new CDC();	BDC->CreateCompatibleDC(Window1);
	BDC->SelectObject(&cbm);

	float **image = new float*[width];//picture
	for (int i = 0; i < width; ++i)
	{
		image[i] = new float[height]();
	}
	N_for_Int = width;
	COLORREF color;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			color = BDC->GetPixel(i, j);
			image[i][j] = (int)(0.299f * GetRValue(color) + 0.587f * GetGValue(color) + 0.114f * GetBValue(color));
			if (image[i][j] > 255) image[i][j] = 255;
			if (image[i][j] < 0) image[i][j] = 0;
		}
	}
	if (one)
	{
		two = false;
		teta = -PI / 4;

		int **onematr = new int*[width];//matr
		for (int i = 0; i < width; ++i)
		{
			onematr[i] = new int[height]();
		}
		int **badmatr = new int*[shag_pi + 150];//matr for teta s
		for (int i = 0; i < shag_pi + 150; ++i)
		{
			badmatr[i] = new int[s_count]();
		}

		int tsh = 0;
		for (teta = 0; teta < PI - 0.01; teta += PI / shag_pi)
		{
			for (int s = 0; s < s_count; s += length_step)
			{
				WhiteLine(teta, s, onematr, width, height);
				MxM(image, onematr, width, height);
				badmatr[tsh][s] = SumMatr(onematr, width, height);
			}
			tsh++;
		}
		BiInterpolation oBI;
		oBI.Interpolation(image, width, height, image1, N_for_Int2);

		/*-------------------------------------------------------------------------------====================*/
		for (int i = 0; i < width; ++i)
		{
			delete[] onematr[i];
		}
		delete[] onematr;
		/*-------------------------------------------------------------------------------====================*/



		float **bmatr = new float*[s_count + 150];//matr for teta s
		for (int i = 0; i < s_count + 150; ++i)
		{
			bmatr[i] = new float[shag_pi + 150]();
		}

		for (int i = 0; i < shag_pi; ++i)
		{
			for (int j = 0; j < s_count; ++j)
			{
				bmatr[j][i] = badmatr[i][j];
			}
		}

		for (int i = 0; i < shag_pi + 150; ++i)
		{
			delete[] badmatr[i];
		}
		delete[] badmatr;

		BProection *pBpr = new BProection(s_count, shag_pi);

		pBpr->GetXYimage(imr, N_for_Int, N_for_Int, WMAX, bmatr);

		double max = 0;
		for (int i = 0; i < s_count; ++i)
		{
			for (int j = 0; j < shag_pi; ++j)
			{
				if (bmatr[i][j] > max)
					max = bmatr[i][j];
			}
		}
		for (int i = 0; i < s_count; ++i)
		{
			for (int j = 0; j < shag_pi; ++j)
			{
				bmatr[i][j] = (int)(bmatr[i][j] * (255 / max));
				if (bmatr[i][j] < 0)
					bmatr[i][j] = 0;
			}
		}

		oBI.Interpolation(bmatr, s_count, shag_pi, image2, N_for_Int2);

		for (int i = 0; i < s_count + 150; ++i)
		{
			delete[] bmatr[i];
		}
		delete[] bmatr;

		max = 0;
		for (int i = 0; i < N_for_Int; ++i)
		{
			for (int j = 0; j < N_for_Int; ++j)
			{
				if (imr[i][j] > max)
					max = imr[i][j];
			}
		}
		for (int i = 0; i < N_for_Int; ++i)
		{
			for (int j = 0; j < N_for_Int; ++j)
			{
				imr[i][j] = (int)(imr[i][j] * (255 / max));
			}
		}
		oBI.Interpolation(imr, N_for_Int, N_for_Int, imageex2, N_for_Int2);

	}
	//===========================================================================================================
	if (two)
	{
		one = false;

		int **onematr = new int*[width];//matr
		for (int i = 0; i < width; ++i)
		{
			onematr[i] = new int[height]();
		}
		float **onematr2 = new float*[width];//matr
		for (int i = 0; i < width; ++i)
		{
			onematr2[i] = new float[height]();
		}


		vector<Array3D> v_Big;

		vector<inVector> XxY;

		int stop = 0;
		int kf = 10000000000000000;
		int tsh = 0;
		for (teta = 0; teta < PI - 0.01; teta += PI / shag_pi)
		{
			for (int s = 0; s < s_count; s += length_step)
			{
				//WhiteLine2(teta, s - s_count / 2, onematr, width, height);				
				WhiteLine(teta, s, onematr, width, height);
				for (int i = 0; i < width; ++i)
				{
					for (int j = 0; j < height; ++j)
					{
						inVector objLine(onematr[i][j], i * height + j);
						if (onematr[i][j] != 0)
						{
							++stop;
							if (kf > i * height + j)
								kf = i * height + j;
						}
						XxY.push_back(objLine);
					}
				}
				if (stop == 0)
				{
					Array3D obj3D(XxY, tsh * s_count + s, 0, kf);
					v_Big.push_back(obj3D);
				}
				else
				{
					Array3D obj3D(XxY, tsh * s_count + s, stop, kf);
					v_Big.push_back(obj3D);
				}
				XxY.clear();
			}
			tsh++;
			stop = 0;
			kf = 10000000000000000;
		}

		vector<inVector> v_BadMatr;

		tsh = 0;
		for (teta = 0; teta < PI - 0.01; teta += PI / shag_pi)
		{
			for (int s = 0; s < s_count; s += length_step)
			{
				WhiteLine(teta, s, onematr, width, height);
				MxM(image, onematr, width, height);
				inVector objL(SumMatr(onematr, width, height), tsh * s_count + s);
				v_BadMatr.push_back(objL);
			}
			tsh++;
		}

		MultiplyMetod *p = new MultiplyMetod();

		p->Start(v_Big, v_BadMatr, XxY, width, height);

		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				onematr2[i][j] = XxY[i * height + j].GetP();
			}
		}

		BiInterpolation oBI;
		oBI.Interpolation(onematr2, width, height, image2, N_for_Int2);
		oBI.Interpolation(image, width, height, image1, N_for_Int2);

		for (int i = 0; i < width; ++i)
		{
			delete[] onematr[i];
		}
		delete[] onematr;
		for (int i = 0; i < width; ++i)
		{
			delete[] onematr2[i];
		}
		delete[] onematr2;

	}
	//===========================================================================================================

	if (fl4)
	{
		vector<double> Image(width* height, 0);

		//K_Means metod;

		BiInterpolation oBI;

		oBI.Interpolation(image, width, height, image1, N_for_Int2);
			

		//metod.Start(pathBMP, Image, LRAY, STEPPI, WMAX);

		float **onematr2 = new float*[width];//matr
		for (int i = 0; i < width; ++i)
		{
			onematr2[i] = new float[height]();
		}

		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				onematr2[x][y] = Image[height * x + y] * 255;
			}
		}

		oBI.Interpolation(onematr2, width, height, image2, N_for_Int2);

		for (int i = 0; i < width; ++i)
		{
			delete[] onematr2[i];
		}
		delete[] onematr2;		
		
	}
	//=============================================================================================================
	if (fl5)
	{
		Mat Img;		
		char st[_MAX_PATH];		

		for (int i = 0; i < pathBMP.GetLength() + 1; ++i)
		{
			st[i] = pathBMP[i];
		}


		CFileDialog fdS(TRUE, NULL, NULL, OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY |
			OFN_LONGNAMES | OFN_PATHMUSTEXIST, _T("Image Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL, 0, TRUE);
		if (fdS.DoModal() != IDOK)
		{
			MessageBox(L"NO TOUCH. EXIT?", L"Bad eye", MB_OK);
			exit(0);
		};
		CString pathBMPS = fdS.GetPathName();

		char st2[_MAX_PATH];

		for (int i = 0; i < pathBMPS.GetLength() + 1; ++i)
		{
			st2[i] = pathBMPS[i];
		}

		Img = imread(st, 1);

		imshow("Object", Img);

		Mat Img2;
	
		Img2 = imread(st2, 1);

		//imshow("window2", Img2);
		//1=========================================================================
		int minHessian = 400;

		SiftFeatureDetector detector(minHessian);

		std::vector<KeyPoint> keypoints_object, keypoints_scene;

		detector.detect(Img, keypoints_object);
		detector.detect(Img2, keypoints_scene);
	
		//2=========================================================================

		SiftDescriptorExtractor extractor;

		Mat descriptors_object, descriptors_scene;

		extractor.compute(Img, keypoints_object, descriptors_object);
		extractor.compute(Img2, keypoints_scene, descriptors_scene);

		//3=========================================================================
		
		FlannBasedMatcher matcher;
		vector< DMatch > matches;
		matcher.match(descriptors_object, descriptors_scene, matches);

		double max_dist = 0; double min_dist = 50;

		//-- Вычисление минимального расстояния среди всех дескрипторов
				   // в пространстве признаков
		for (int i = 0; i < descriptors_object.rows; i++)
		{
			double dist = matches[i].distance;
			if (dist < min_dist) min_dist = dist;
			//if (dist > max_dist) max_dist = dist;
		}

		//-- Отобрать только хорошие матчи, расстояние меньше чем 3 * min_dist
		vector< DMatch > good_matches;

		for (int i = 0; i < descriptors_object.rows; i++)
		{
			if (matches[i].distance < 3 * min_dist)
			{
				good_matches.push_back(matches[i]);
			}
		}

		Mat img_matches;

		//-- Нарисовать хорошие матчи
		drawMatches(Img, keypoints_object, Img2, keypoints_scene,
			good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
			vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

		imshow("Good matches", img_matches);
		//4==========================================================================================
		vector<Point2f> objs;
		vector<Point2f> scene;

		for (int i = 0; i < good_matches.size(); i++)
		{
			objs.push_back(keypoints_object[good_matches[i].queryIdx].pt);
			scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
		}

		Mat H = findHomography(objs, scene, CV_RANSAC);
		//5==========================================================================================
		std::vector<Point2f> obj_corners(4);
		obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(Img.cols, 0);
		obj_corners[2] = cvPoint(Img.cols, Img.rows); obj_corners[3] = cvPoint(0, Img.rows);
		std::vector<Point2f> scene_corners(4);

		//-- Отобразить углы целевого объекта, используя найденное преобразование, на сцену
		perspectiveTransform(obj_corners, scene_corners, H);

		//-- Соеденить отображенные углы
		line(Img2, scene_corners[0], scene_corners[1], Scalar(0, 0, 255), 6);
		line(Img2, scene_corners[1], scene_corners[2], Scalar(0, 0, 255), 6);
		line(Img2, scene_corners[2], scene_corners[3], Scalar(0, 0, 255), 6);
		line(Img2, scene_corners[3], scene_corners[0], Scalar(0, 0, 255), 6);

		//-- Show detected matches
		imshow("Scene", Img2);
	}
	//=============================================================================================================
	for (int i = 0; i < width; ++i)
	{
		delete[] image[i];
	}
	delete[] image;
	delete BDC;
	/*-------------------------------------------------------------------------------====================*/
	flag_picture = true;
	UpdateData(false);
	OnPaint();
}
void CProjectTomogrDlg::WhiteLine(double angle, double s, int** matr, int W, int H)
{
	for (int i = 0; i < W; ++i)
	{
		for (int j = 0; j < H; ++j)
		{
			double k = tan(angle - PI / 2);
			if (angle == 0)
			{
				if (j == /*H + */-s)
					matr[i][j] = 1;
				else matr[i][j] = 0;
			}
			else
			{
				if (j == (int)(-k * i + k * (W / 2.0 - ((s - s_count / 2) * cos(teta))) + H / 2.0 - (-(s - s_count / 2) * sin(teta))))
					matr[i][j] = 1;
				else matr[i][j] = 0;
			}
		}
	}
}
void CProjectTomogrDlg::WhiteLine2(double angle, double s, int** matr, int W, int H)
{
	for (int i = 0; i < W; ++i)
	{
		for (int j = 0; j < H; ++j)
		{
			double k = tan(angle);
			if (angle == PI / 2)
			{
				if (i == W / 2.0)
					matr[i][j] = 1;
				else matr[i][j] = 0;
			}
			else
			{
				if (j == -(int)(k * (i - W / 2.0) + s - H / 2.0))
					matr[i][j] = 1;
				else matr[i][j] = 0;
			}
		}
	}
}
void CProjectTomogrDlg::MxM(float ** matr1, int ** matr2, int W, int H)
{
	for (int i = 0; i < W; ++i)
	{
		for (int j = 0; j < H; ++j)
		{
			matr2[i][j] = matr1[i][j] * matr2[i][j];
		}
	}
}
double CProjectTomogrDlg::SumMatr(int ** matr, int W, int H)
{
	int Summa = 0;
	for (int i = 0; i < W; ++i)
	{
		for (int j = 0; j < H; ++j)
		{
			Summa += matr[i][j];
		}
	}
	return Summa;
}
void CProjectTomogrDlg::Normal_MAtr(float ** matr, int width, int height)
{
	double max = 0;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (matr[i][j] > max)
				max = matr[i][j];
		}
	}
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (matr[i][j] < 1 && matr[i][j] > 0)
			{
				int a = 0;
			}
			matr[i][j] = (int)(matr[i][j] * /*(double)*/(255 / max));
			if (matr[i][j] < 1 && matr[i][j] > 0)
			{
				int a = 0;
			}
		}
	}
}
void CProjectTomogrDlg::Normal_MAtr(vector<double> v_in, int width, int height)
{
	double max = 0;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (v_in[j + height * i] > max)
				max = v_in[j + height * i];
		}
	}
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			v_in[j + height * i] = /*(int)*/(v_in[j + height * i] * (double)(255 / max));
		}
	}
}
void CProjectTomogrDlg::Normal_MAtr(int ** matr, int width, int height)
{
	double max = 0;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (matr[i][j] > max)
				max = matr[i][j];
		}
	}
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			matr[i][j] = (int)(matr[i][j] * (255 / max));
		}
	}
}
void CProjectTomogrDlg::OnBnClickedButton1()
{
	UpdateData(true);
	shag_pi = STEPPI;
	s_count = LRAY;
	MainF();
}
void CProjectTomogrDlg::OnBnClickedOk()
{
	for (int i = 0; i < N_for_Int2; ++i)
	{
		delete[] imageex2[i];
	}
	delete[] imageex2;
	for (int i = 0; i < N_for_Int2; ++i)
	{
		delete[] image2[i];
	}
	delete[] image2;
	for (int i = 0; i < N_for_Int2; ++i)
	{
		delete[] image1[i];
	}
	delete[] image1;
	CDialogEx::OnOK();
}
