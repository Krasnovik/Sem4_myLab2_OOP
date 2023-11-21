#pragma once

#include<windows.h>
#include"Classes.h" //���������� �������
#include<thread>
#include<iostream>

extern HDC hdc;
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
auto LINE = [](HDC hdc, int x1, int y1, int x2, int y2)	// ������� ��������� ������
{
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
};

/****************************************************
*													*
*				������ ������ Location				*
*													*
*****************************************************/

// �����������
Location::Location(int aX, int aY)
{
	X = aX;
	Y = aY;
}

// ����������
Location::~Location(void)
{

};

// �������� ���������� �
int Location::GetX(void)
{
	return X;
}

// �������� ���������� Y
int Location::GetY(void)
{
	return Y;
}

// ���������� ���������� X
void Location::SetX(int aX)
{
	X = aX;
}

// ���������� ���������� Y
void Location::SetY(int aY)
{
	Y = aY;
}


/****************************************************
*													*
*				������ ������ Point					*
*													*
*****************************************************/


// �����������
Point::Point(int InitX, int InitY, int aXright, int aYright) : Location(InitX, InitY)
{
	xRight = aXright;
	yRight = aYright;
	Visible = false;
}

// ����������
Point::~Point(void)
{

}

// �������� �����
void Point::Show(void)
{
	Visible = true;

	SetPixel(hdc, X, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}

// �������� �����
void Point::Hide(void)
{
	Visible = false;

	SetPixel(hdc, X, Y, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 255));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 255));
}

// ������, ����� �� �����
bool Point::IsVisible(void)
{
	return Visible;
}

// ����������� �����
void Point::MoveTo(int newX, int newY, int newXright, int newYright)
{
	Hide();
	X = newX;
	Y = newY;
	xRight = newXright;
	yRight = newYright;
	Show();
}

// ������ �����
int Point::GetLength() {
	return Length;
}

// ������ ������
int Point::GetWidth() {
	return Width;
}

// "������" ������
void Point::Drag(int step)
{
	int X, Y, xRight, yRight;				// ���������� ������

	X = GetX();								// ������ ��������� �������� ���������� � ������
	Y = GetY();								// ������ ��������� �������� ���������� Y ������
	xRight = GetXr();						// ������������� ��������� �������� ���������� � ������� ������� ���� ������
	yRight = GetYr();						// ������������� ��������� �������� ���������� Y ������� ������� ���� ������

	if (KEY_DOWN(VK_LEFT))					//������� ����� (������ 37)
	{
		X -= step;							// �������� ���������� � �� ������ ����
		xRight -= step;						// �������� ���������� � ������� ������� ���� �� ������ ����
		MoveTo(X, Y, xRight, yRight);		// ����������� ������
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	if (KEY_DOWN(VK_RIGHT))					// ������� ������ (������ 39)
	{
		X += step;							// �������� ���������� � �� ������ ����
		xRight += step;						// �������� ���������� � ������� ������� ���� �� ������ ����
		MoveTo(X, Y, xRight, yRight);		// ����������� ������
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	if (KEY_DOWN(VK_DOWN))					// ������� ���� (������ 40)
	{	
		Y += step;							// �������� ���������� Y �� ������ ����
		yRight += step;						// �������� ���������� Y ������� ������� ���� �� ������ ����
		MoveTo(X, Y, xRight, yRight);		// ����������� ������
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	if (KEY_DOWN(VK_UP))					//������� ����� (������ 38)
	{
		Y -= step;							// �������� ���������� Y �� ������ ����
		yRight -= step;						// �������� ���������� Y ������� ������� ���� �� ������ ����
		MoveTo(X, Y, xRight, yRight);		// ����������� ������
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}
}

void Point::SetColor(int R, int G, int B) {

}

bool Point::IsCollision(class Point* Boots, class Point* oRectangle) {
	int xRight = (*Boots).GetXr();		// ���������� � ������� ���� �������
	int yRight = (*Boots).GetYr();		// ���������� � ������� ���� �������

	// �������� �� ������������ ������� ������� ������� � �������������� �������
	if ((*oRectangle).GetX() <= (*Boots).GetX() + 250 && (*oRectangle).GetY() + (*oRectangle).GetWidth() >= (*Boots).GetY()
		&& (*oRectangle).GetY() <= (*Boots).GetYr() && (*oRectangle).GetX() + (*oRectangle).GetLength() >= (*Boots).GetX()) {
		//std::cout << "��������� ������������!1" << std::endl;
		return 1;
	}
	// �������� �� ������������ ������ ������� ������� � �������������� �������
	else if ((*oRectangle).GetX() <= xRight + 250 && (*oRectangle).GetX() + (*oRectangle).GetLength() >= (*Boots).GetX()
		&& (*oRectangle).GetY() <= yRight + 20 && (*oRectangle).GetY() + (*oRectangle).GetWidth() >= (*Boots).GetY()) {
		//std::cout << "��������� ������������!2" << std::endl;
		return 1;
	}
	// �������� �� ������������ ������ ������� ������� � �������������� �������
	else if (((*oRectangle).GetX() <= xRight + 250 && (*oRectangle).GetX() + (*oRectangle).GetLength() >= (*Boots).GetX() && (*oRectangle).GetY() <= yRight
		&& (*oRectangle).GetY() + (*oRectangle).GetWidth() >= yRight) ||
		((*oRectangle).GetX() <= xRight + 200 && (*oRectangle).GetX() + (*oRectangle).GetLength() >= (*Boots).GetX() && (*oRectangle).GetY() <= yRight
			&& (*oRectangle).GetY() + (*oRectangle).GetWidth() + 100 >= yRight)) {
		//std::cout << "�������� ������������!3" << std::endl;
		return 1;
	}
	// �������� �� ������������ ����� ������� ������� � �������������� �������
	else if ((*oRectangle).GetX() + (*oRectangle).GetLength() >= (*Boots).GetX() && (*oRectangle).GetX() <= (*Boots).GetXr() && (*oRectangle).GetY() <= yRight
		&& (*oRectangle).GetY() + (*oRectangle).GetWidth() >= (*Boots).GetY()) {
		//std::cout << "��������� ������������!4" << std::endl;
		return 1;
	}
	// ����� ������������ �� ���������
	else
	{
		return 0;	
	}
}

// �������� ���������� X ������� ������� ���� ������
int Point::GetXr()
{
	return xRight;
}

// �������� ���������� Y ������� ������� ���� ������
int Point::GetYr()
{
	return yRight;
}

// ���������� ���������� X ������� ������� ���� ������
void Point::SetXright(int aXr)
{
	xRight = aXr;
}

// ���������� ���������� Y ������� ������� ���� ������
void Point::SetYright(int aYr)
{
	yRight = aYr;
}

/****************************************************
*													*
*				������ ������ Figure				*
*													*
*****************************************************/

// �����������
Figure::Figure(int aX, int aY, int aXright, int aYright) : Point(aX, aY, aXright, aYright)
{
	
}

// ����������
Figure::~Figure(void)
{

};

// �������� ������
void Figure::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(128, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(128, 0, 0));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	// ������ �������
	Rectangle(hdc, X, Y, xRight, yRight);									// ���� ������ ������
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// ������ ������ ������
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// ��� ������ ������

	// ������ �������
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// ���� ������ �������
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// ������ ������ �������
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// ��� ������ �������


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// C������� ������
void Figure::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	// ������ �������
	Rectangle(hdc, X, Y, xRight, yRight);									// ���� ������ ������
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// ������ ������ ������
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// ��� ������ ������

	// ������ �������
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// ���� ������ �������
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// ������ ������ �������
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// ��� ������ �������


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*			������ ������ ColoredBoots				*
*													*
*****************************************************/

// �����������
ColoredBoots::ColoredBoots(int aX, int aY, int xRight, int yRight) : Figure(aX, aY, xRight, yRight)
{

}

bool ColoredBoots::IsVisible() {
	return Visible;
}

// ����������
ColoredBoots::~ColoredBoots(void)
{

};

// �������� ������
void ColoredBoots::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 128));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 128));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	// ������ �������
	Rectangle(hdc, X, Y, xRight, yRight);
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);

	// ������ �������
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// C������� ������
void ColoredBoots::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	// ������ �������
	Rectangle(hdc, X, Y, xRight, yRight);									// ���� ������ ������
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// ������ ������ ������
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// ��� ������ ������

	// ������ �������
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// ���� ������ �������
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// ������ ������ �������
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// ��� ������ �������


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*			������ ������ TornColoredBoots			*
*													*
*****************************************************/

// �����������
TornColoredBoots::TornColoredBoots(int aX, int aY, int xRight, int yRight) : ColoredBoots(aX, aY, xRight, yRight)
{

}

bool TornColoredBoots::IsVisible() {
	return Visible;
}

// ����������
TornColoredBoots::~TornColoredBoots(void)
{

};

// �������� ������
void TornColoredBoots::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 128, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 128, 0));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	// ������ �������	
	Rectangle(hdc, X, Y, xRight, yRight);									// ���� ������ ������
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// ������ ������ ������
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// ��� ������ ������

	// ������ �������
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// ���� ������ �������
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// ������ ������ �������
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// ��� ������ �������


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// C������� ������
void TornColoredBoots::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	// ������ �������
	Rectangle(hdc, X, Y, xRight, yRight);									// ���� ������ ������
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// ������ ������ ������
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// ��� ������ ������

	// ������ �������
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// ���� ������ �������
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// ������ ������ �������
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// ��� ������ �������


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*			������ ������ BootsWithoutHeels			*
*													*
*****************************************************/

// �����������
BootsWithoutHeels::BootsWithoutHeels(int aX, int aY, int xRight, int yRight) : Figure(aX, aY, xRight, yRight)
{

}

bool BootsWithoutHeels::IsVisible() {
	return Visible;
}

// ����������
BootsWithoutHeels::~BootsWithoutHeels(void)
{

};

// �������� ������
void BootsWithoutHeels::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(64, 64, 64));
	HBRUSH Brush = CreateSolidBrush(RGB(64, 64, 64));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	// ������ �������
	Rectangle(hdc, X, Y, xRight, yRight);									// ���� ������ ������
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// ������ ������ ������
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 20, yRight - 20);	// ��� ������ ������

	// ������ �������
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// ���� ������� ������
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// ������ ������� ������
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 180, yRight - 20);	// ��� ������� ������


	DeleteObject(Pen);
	DeleteObject(Brush);
}

// C������� ������
void BootsWithoutHeels::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	// ������ �������
	Rectangle(hdc, X, Y, xRight, yRight);									// ���� ������ ������
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// ������ ������ ������
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 20, yRight - 20);	// ��� ������ ������

	// ������ �������
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// ���� ������� ������
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// ������ ������� ������
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 180, yRight - 20);	// ��� ������� ������


	DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*			������ ������ BootsWithStrip			*
*													*
*****************************************************/

// �����������
BootsWithStrip::BootsWithStrip(int aX, int aY, int xRight, int yRight) : Figure(aX, aY, xRight, yRight)
{

}

bool BootsWithStrip::IsVisible() {
	return Visible;
}

// ����������
BootsWithStrip::~BootsWithStrip(void)
{

};

// �������� ������
void BootsWithStrip::Show(void)
{
	Visible = true;

	//HPEN Pen = CreatePen(PS_SOLID, 2, RGB(66, 29, 5));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	//SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	// ������ �������
	Rectangle(hdc, X, Y, xRight, yRight);									// ���� ������ ������
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// ������ ������ ������
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// ��� ������ ������

	// ������ �������
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// ���� ������� ������
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// ������ ������� ������
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// ��� �������


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// C������� ������
void BootsWithStrip::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(66, 29, 5));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	// ������ �������
	Rectangle(hdc, X, Y, xRight, yRight);									// ���� ������ ������
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// ������ ������ ������
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// ��� ������ ������

	// ������ �������
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// ���� ������� ������
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// ������ ������� ������
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// ��� ������� ������


	DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*				������ ������ Rectangle				*
*													*
*****************************************************/

// �����������
CRectangle::CRectangle(int aX, int aY, int aLength, int aWidth) : Point(aX, aY, xRight, yRight)
{
	Length = aLength;
	Width = aWidth;
}

// ����������
CRectangle::~CRectangle(void)
{

};

int CRectangle::GetLength() {
	return Length;
}

int CRectangle::GetWidth() {
	return Width;
}

bool CRectangle::IsVisible() {
	return Visible;
}

// �������� �������������
void CRectangle::Show(void)
{
	Visible = true;

	//HPEN Pen = CreatePen(PS_SOLID, 2, RGB(66, 29, 5));
	HBRUSH Brush = CreateSolidBrush(RGB(252, 15, 192));
	//SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	Rectangle(hdc, X, Y, X + Length, Y + Width);


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// C������� �������������
void CRectangle::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	Rectangle(hdc, X, Y, X + Length, Y + Width);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*				������ ������ Square				*
*													*
*****************************************************/

// �����������
Square::Square(int aX, int aY, int aLength) : Point(aX, aY, xRight, yRight)
{
	Length = aLength;
	Width = Length;
}

// ����������
Square::~Square(void)
{

};

bool Square::IsVisible() {
	return Visible;
}

// �������� �������������
void Square::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 128, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 128, 0));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	Rectangle(hdc, X, Y, X + Length, Y + Width);


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// C������� �������������
void Square::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	Rectangle(hdc, X, Y, X + Length, Y + Width);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

// �������� ����� ��������
int Square::GetLength() {
	return Length;
}

// �������� ������ ��������
int Square::GetWidth() {
	return Width;
}

/****************************************************
*													*
*				������ ������ Circle				*
*													*
*****************************************************/

// �������� ������� �����
int Circle::GetLength() {
	return Length;
}

// �������� ������� �����
int Circle::GetWidth() {
	return Width;
}

// �����������
Circle::Circle(int aX, int aY, int aRadius) : Point(aX, aY, xRight, yRight)
{
	radius = aRadius;
	Length = radius * 2;
	Width = radius * 2;
}

// ����������
Circle::~Circle(void)
{

};

bool Circle::IsVisible() {
	return Visible;
}

// �������� �������������
void Circle::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(66, 29, 5));
	HBRUSH Brush = CreateSolidBrush(RGB(66, 29, 5));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	Ellipse(hdc, X, Y, X + radius*2, Y + radius*2);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

// C������� �������������
void Circle::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // ������� ���� ��������
	SelectObject(hdc, Brush);

	Ellipse(hdc, X, Y, X + radius * 2, Y + radius * 2);

	DeleteObject(Pen);
	DeleteObject(Brush);
}
