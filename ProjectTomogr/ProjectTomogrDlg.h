
// ProjectTomogrDlg.h: файл заголовка
//

#pragma once
#include<vector>

// Диалоговое окно CProjectTomogrDlg
class CProjectTomogrDlg : public CDialogEx
{
// Создание
public:
	CProjectTomogrDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECTTOMOGR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;
	int width = 0;
	int height = 0;

	CDC *Window1;
	CWnd *Wind1;
	CRect Win1;

	CDC *Window2;
	CWnd *Wind2;
	CRect Win2;

	CDC *Window3;
	CWnd *Wind3;
	CRect Win3;
	int N = 512;

	double teta = 0;

	int shag_pi = 50; // count of step on PI (PI / shag_pi)
	int length_line = 300;// length of line (circle around object)
	int length_step = 1; // step on line
	int s_count = length_line / length_step; //count of massiv for s
	int N_for_Int = 512; 
	int N_for_Int2 = 512; // for Interpolation
	float** imr = nullptr;
	int **image1 = nullptr;//picture	
	int **image2 = nullptr;//picture	
	int **imageex2 = nullptr;//picture		
	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void MainF();
	void WhiteLine(double angle, double s, int** matr, int W, int H);
	void WhiteLine2(double angle, double s, int** matr, int W, int H);
	void MxM(float** matr1, int** matr2, int W, int H);
	double SumMatr(int** matr, int W, int H);
	void Normal_MAtr(float** matr, int width, int height);
	void Normal_MAtr(int** matr, int width, int height);
	void Normal_MAtr(std::vector<double> v_in, int width, int height);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();	
	BOOL flag_picture = false;
	afx_msg void OnBnClickedOk();
	int LRAY;
	int STEPPI;
	float WMAX;
	BOOL one;
	BOOL two;
	BOOL fl4;
	BOOL fl5;
};
