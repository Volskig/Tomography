#include "stdafx.h"
#include "Draw.h"


Draw::Draw()
{
}
void Draw::DrawImage(CDC* Window, CRect Win, int W, int H, int** image)
{
	CBitmap bd;
	bd.CreateCompatibleBitmap(Window, Win.Width(), Win.Height());
	CDC *BDC = new CDC();	BDC->CreateCompatibleDC(Window);
	BDC->SelectObject(&bd);
	for (int i = 0; i < W; ++i)
	{
		for (int j = 0; j < H; ++j)
		{
			BDC->SetPixel(i,j, RGB(image[i][j], image[i][j], image[i][j]));
		}
	}
	Window->BitBlt(0, 0, Win.Width(), Win.Height(), BDC, 0, 0, SRCCOPY);
	delete BDC;
}
void Draw::DrawRandColor(CDC* Window, CRect Win, int W, int H, int** image)
{
	CBitmap bd;
	bd.CreateCompatibleBitmap(Window, Win.Width(), Win.Height());
	CDC *BDC = new CDC();	BDC->CreateCompatibleDC(Window);
	BDC->SelectObject(&bd);
	for (int i = 0; i < W; ++i)
	{
		for (int j = 0; j < H; ++j)
		{			

			if (image[i][j] > 20)
				BDC->SetPixel(i, j, RGB(0, 0, 100));

			if (image[i][j] > 40)
				BDC->SetPixel(i, j, RGB(0, 150, 0));

			if (image[i][j] > 60)
				BDC->SetPixel(i, j, RGB(150, 0, 0));	

			if (image[i][j] > 70)
				BDC->SetPixel(i, j, RGB(0, 100, 12));

			if (image[i][j] > 80)
				BDC->SetPixel(i, j, RGB(0, 150, 200));	

			if (image[i][j] > 90)
				BDC->SetPixel(i, j, RGB(17, 0, 0));

			if (image[i][j] > 100)
				BDC->SetPixel(i, j, RGB(0, 200, 0));			

			if (image[i][j] > 110)
				BDC->SetPixel(i, j, RGB(2550, 90, 90));

			if (image[i][j] > 120)
				BDC->SetPixel(i, j, RGB(200, 0, 0));

			if (image[i][j] > 130)
				BDC->SetPixel(i, j, RGB(55, 255, 0));

			if (image[i][j] > 140)
				BDC->SetPixel(i, j, RGB(0, 255, 255));

			if (image[i][j] > 160)
				BDC->SetPixel(i, j, RGB(255, 255, 0));

			if (image[i][j] > 170)
				BDC->SetPixel(i, j, RGB(21, 88, 14));

			if (image[i][j] > 180)
				BDC->SetPixel(i, j, RGB(100, 0, 255));

			if (image[i][j] > 190)
				BDC->SetPixel(i, j, RGB(48, 78, 20/*image[i][j]*/));

			if (image[i][j] > 200)
				BDC->SetPixel(i, j, RGB(50, 255, 50/*image[i][j]*/));

			if (image[i][j] > 210)
				BDC->SetPixel(i, j, RGB(50, 50/*image[i][j]*/, 50/*image[i][j]*/));

			if(image[i][j] > 220)
				BDC->SetPixel(i, j, RGB(255, 50/*image[i][j]*/, 50/*image[i][j]*/));

			if (image[i][j] > 230)
				BDC->SetPixel(i, j, RGB(250, 250/*image[i][j]*/, 250/*image[i][j]*/));

			if (image[i][j] > 240)
				BDC->SetPixel(i, j, RGB(0, 0/*image[i][j]*/, 0/*image[i][j]*/));

			if (image[i][j] > 250)
				BDC->SetPixel(i, j, RGB(230, 230/*image[i][j]*/, 230/*image[i][j]*/));

		
		}
	}
	Window->BitBlt(0, 0, Win.Width(), Win.Height(), BDC, 0, 0, SRCCOPY);
	delete BDC;
}
Draw::~Draw()
{
}
