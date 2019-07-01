#pragma once
class Draw
{
public:
	Draw();
	void DrawImage(CDC* Window, CRect Win, int W, int H, int** image);
	void Draw::DrawRandColor(CDC* Window, CRect Win, int W, int H, int** image);
	~Draw();
};

