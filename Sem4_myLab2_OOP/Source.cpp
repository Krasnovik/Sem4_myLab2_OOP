#pragma once

#include<windows.h>
#include"Classes.h" //объявление классов
#include<thread>
#include<iostream>

extern HDC hdc;
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
auto LINE = [](HDC hdc, int x1, int y1, int x2, int y2)	// функция отрисовки прямой
{
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
};

/****************************************************
*													*
*				Методы класса Location				*
*													*
*****************************************************/

// Конструктор
Location::Location(int aX, int aY)
{
	X = aX;
	Y = aY;
}

// Деструктор
Location::~Location(void)
{

};

// Получить координату Х
int Location::GetX(void)
{
	return X;
}

// Получить координату Y
int Location::GetY(void)
{
	return Y;
}

// Установить координату X
void Location::SetX(int aX)
{
	X = aX;
}

// Установить координату Y
void Location::SetY(int aY)
{
	Y = aY;
}


/****************************************************
*													*
*				Методы класса Point					*
*													*
*****************************************************/


// Конструктор
Point::Point(int InitX, int InitY, int aXright, int aYright) : Location(InitX, InitY)
{
	xRight = aXright;
	yRight = aYright;
	Visible = false;
}

// Деструктор
Point::~Point(void)
{

}

// Показать точку
void Point::Show(void)
{
	Visible = true;

	SetPixel(hdc, X, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}

// Спрятать точку
void Point::Hide(void)
{
	Visible = false;

	SetPixel(hdc, X, Y, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 255));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 255));
}

// Узнать, видно ли точку
bool Point::IsVisible(void)
{
	return Visible;
}

// Передвинуть точку
void Point::MoveTo(int newX, int newY, int newXright, int newYright)
{
	Hide();
	X = newX;
	Y = newY;
	xRight = newXright;
	yRight = newYright;
	Show();
}

// Узнать длину
int Point::GetLength() {
	return Length;
}

// Узнать ширину
int Point::GetWidth() {
	return Width;
}

// "тянуть" Фигуру
void Point::Drag(int step)
{
	int X, Y, xRight, yRight;				// координаты Фигуры

	X = GetX();								// узнаем начальное значение координаты Х Фигуры
	Y = GetY();								// узнаем начальное значение координаты Y Фигуры
	xRight = GetXr();						// устанавливаем начальное значение координаты Х правого нижнего угла Фигуры
	yRight = GetYr();						// устанавливаем начальное значение координаты Y правого нижнего угла Фигуры

	if (KEY_DOWN(VK_LEFT))					//стрелка влево (кнопка 37)
	{
		X -= step;							// изменяем координату Х на размер шага
		xRight -= step;						// изменяем координату Х правого нижнего угла на размер шага
		MoveTo(X, Y, xRight, yRight);		// передвигаем Фигуру
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	if (KEY_DOWN(VK_RIGHT))					// стрелка вправо (кнопка 39)
	{
		X += step;							// изменяем координату Х на размер шага
		xRight += step;						// изменяем координату Х правого нижнего угла на размер шага
		MoveTo(X, Y, xRight, yRight);		// передвигаем Фигуру
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	if (KEY_DOWN(VK_DOWN))					// стрелка вниз (кнопка 40)
	{	
		Y += step;							// изменяем координату Y на размер шага
		yRight += step;						// изменяем координату Y правого нижнего угла на размер шага
		MoveTo(X, Y, xRight, yRight);		// передвигаем Фигуру
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	if (KEY_DOWN(VK_UP))					//стрелка вверх (кнопка 38)
	{
		Y -= step;							// изменяем координату Y на размер шага
		yRight -= step;						// изменяем координату Y правого нижнего угла на размер шага
		MoveTo(X, Y, xRight, yRight);		// передвигаем Фигуру
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}
}

void Point::SetColor(int R, int G, int B) {

}

bool Point::IsCollision(class Point* Boots, class Point* oRectangle) {
	int xRight = (*Boots).GetXr();		// координата Х правого угла сапогов
	int yRight = (*Boots).GetYr();		// координата У правого угла сапогов

	// Проверка на столкновение верхней стороны сапогов с геометрической фигурой
	if ((*oRectangle).GetX() <= (*Boots).GetX() + 250 && (*oRectangle).GetY() + (*oRectangle).GetWidth() >= (*Boots).GetY()
		&& (*oRectangle).GetY() <= (*Boots).GetYr() && (*oRectangle).GetX() + (*oRectangle).GetLength() >= (*Boots).GetX()) {
		//std::cout << "Произошло столкновение!1" << std::endl;
		return 1;
	}
	// Проверка на столкновение нижней стороны сапогов с геометрической фигурой
	else if ((*oRectangle).GetX() <= xRight + 250 && (*oRectangle).GetX() + (*oRectangle).GetLength() >= (*Boots).GetX()
		&& (*oRectangle).GetY() <= yRight + 20 && (*oRectangle).GetY() + (*oRectangle).GetWidth() >= (*Boots).GetY()) {
		//std::cout << "Произошло столкновение!2" << std::endl;
		return 1;
	}
	// Проверка на столкновение правой стороны сапогов с геометрической фигурой
	else if (((*oRectangle).GetX() <= xRight + 250 && (*oRectangle).GetX() + (*oRectangle).GetLength() >= (*Boots).GetX() && (*oRectangle).GetY() <= yRight
		&& (*oRectangle).GetY() + (*oRectangle).GetWidth() >= yRight) ||
		((*oRectangle).GetX() <= xRight + 200 && (*oRectangle).GetX() + (*oRectangle).GetLength() >= (*Boots).GetX() && (*oRectangle).GetY() <= yRight
			&& (*oRectangle).GetY() + (*oRectangle).GetWidth() + 100 >= yRight)) {
		//std::cout << "Призошло столкновение!3" << std::endl;
		return 1;
	}
	// Проверка на столкновение левой стороны сапогов с геометрической фигурой
	else if ((*oRectangle).GetX() + (*oRectangle).GetLength() >= (*Boots).GetX() && (*oRectangle).GetX() <= (*Boots).GetXr() && (*oRectangle).GetY() <= yRight
		&& (*oRectangle).GetY() + (*oRectangle).GetWidth() >= (*Boots).GetY()) {
		//std::cout << "Произошло столкновение!4" << std::endl;
		return 1;
	}
	// Иначе столкновения не произошло
	else
	{
		return 0;	
	}
}

// Получить координату X правого нижнего угла Фигуры
int Point::GetXr()
{
	return xRight;
}

// Получить координату Y правого нижнего угла Фигуры
int Point::GetYr()
{
	return yRight;
}

// Установить координату X правого нижнего угла Фигуры
void Point::SetXright(int aXr)
{
	xRight = aXr;
}

// Установить координату Y правого нижнего угла Фигуры
void Point::SetYright(int aYr)
{
	yRight = aYr;
}

/****************************************************
*													*
*				Методы класса Figure				*
*													*
*****************************************************/

// Конструктор
Figure::Figure(int aX, int aY, int aXright, int aYright) : Point(aX, aY, aXright, aYright)
{
	
}

// Деструктор
Figure::~Figure(void)
{

};

// Показать Фигуру
void Figure::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(128, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(128, 0, 0));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	// Первый ботинок
	Rectangle(hdc, X, Y, xRight, yRight);									// тело сапога левого
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// каблук сапога левого
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// нос сапога левого

	// Второй ботинок
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// тело сапога правого
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// каблук сапога правого
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// нос сапога правого


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// Cпрятать Фигуру
void Figure::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	// Первый ботинок
	Rectangle(hdc, X, Y, xRight, yRight);									// тело сапога левого
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// каблук сапога левого
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// нос сапога левого

	// Второй ботинок
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// тело сапога правого
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// каблук сапога правого
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// нос сапога правого


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*			Методы класса ColoredBoots				*
*													*
*****************************************************/

// Конструктор
ColoredBoots::ColoredBoots(int aX, int aY, int xRight, int yRight) : Figure(aX, aY, xRight, yRight)
{

}

bool ColoredBoots::IsVisible() {
	return Visible;
}

// Деструктор
ColoredBoots::~ColoredBoots(void)
{

};

// Показать сапоги
void ColoredBoots::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 128));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 128));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	// Первый ботинок
	Rectangle(hdc, X, Y, xRight, yRight);
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);

	// Второй ботинок
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// Cпрятать сапоги
void ColoredBoots::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	// Первый ботинок
	Rectangle(hdc, X, Y, xRight, yRight);									// тело сапога левого
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// каблук сапога левого
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// нос сапога левого

	// Второй ботинок
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// тело сапога правого
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// каблук сапога правого
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// нос сапога правого


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*			Методы класса TornColoredBoots			*
*													*
*****************************************************/

// Конструктор
TornColoredBoots::TornColoredBoots(int aX, int aY, int xRight, int yRight) : ColoredBoots(aX, aY, xRight, yRight)
{

}

bool TornColoredBoots::IsVisible() {
	return Visible;
}

// Деструктор
TornColoredBoots::~TornColoredBoots(void)
{

};

// Показать сапоги
void TornColoredBoots::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 128, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 128, 0));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	// Первый ботинок	
	Rectangle(hdc, X, Y, xRight, yRight);									// тело сапога левого
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// каблук сапога левого
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// нос сапога левого

	// Второй ботинок
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// тело сапога правого
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// каблку сапога правого
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// нос сапога правого


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// Cпрятать сапоги
void TornColoredBoots::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	// Первый ботинок
	Rectangle(hdc, X, Y, xRight, yRight);									// тело сапога левого
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// каблук сапога левого
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// нос сапога левого

	// Второй ботинок
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// тело сапога правого
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// каблук сапога правого
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// нос сапога правого


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*			Методы класса BootsWithoutHeels			*
*													*
*****************************************************/

// Конструктор
BootsWithoutHeels::BootsWithoutHeels(int aX, int aY, int xRight, int yRight) : Figure(aX, aY, xRight, yRight)
{

}

bool BootsWithoutHeels::IsVisible() {
	return Visible;
}

// Деструктор
BootsWithoutHeels::~BootsWithoutHeels(void)
{

};

// Показать сапоги
void BootsWithoutHeels::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(64, 64, 64));
	HBRUSH Brush = CreateSolidBrush(RGB(64, 64, 64));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	// Первый ботинок
	Rectangle(hdc, X, Y, xRight, yRight);									// тело левого сапога
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// каблук левого сапога
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 20, yRight - 20);	// нос левого сапога

	// Второй ботинок
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// тело правого сапога
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// каблук правого сапога
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 180, yRight - 20);	// нос правого сапога


	DeleteObject(Pen);
	DeleteObject(Brush);
}

// Cпрятать сапоги
void BootsWithoutHeels::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	// Первый ботинок
	Rectangle(hdc, X, Y, xRight, yRight);									// тело левого сапога
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// каблук левого сапога
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 20, yRight - 20);	// нос левого сапога

	// Второй ботинок
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// тело правого сапога
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// каблук правого сапога
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 180, yRight - 20);	// нос правого сапога


	DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*			Методы класса BootsWithStrip			*
*													*
*****************************************************/

// Конструктор
BootsWithStrip::BootsWithStrip(int aX, int aY, int xRight, int yRight) : Figure(aX, aY, xRight, yRight)
{

}

bool BootsWithStrip::IsVisible() {
	return Visible;
}

// Деструктор
BootsWithStrip::~BootsWithStrip(void)
{

};

// Показать сапоги
void BootsWithStrip::Show(void)
{
	Visible = true;

	//HPEN Pen = CreatePen(PS_SOLID, 2, RGB(66, 29, 5));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	//SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	// Первый ботинок
	Rectangle(hdc, X, Y, xRight, yRight);									// тело левого сапога
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// каблук левого сапога
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// нос левого сапога

	// Второй ботинок
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// тело правого сапога
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// каблук правого сапога
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// нос правого


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// Cпрятать сапоги
void BootsWithStrip::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(66, 29, 5));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	// Первый ботинок
	Rectangle(hdc, X, Y, xRight, yRight);									// тело левого сапога
	Rectangle(hdc, xRight - 50, yRight - 30, xRight + 50, yRight + 20);		// каблук левого сапога
	Rectangle(hdc, xRight - 100, yRight + 20, xRight - 60, yRight - 20);	// нос левого сапога

	// Второй ботинок
	Rectangle(hdc, X + 200, Y, xRight + 200, yRight);						// тело правого сапога
	Rectangle(hdc, xRight + 150, yRight - 30, xRight + 250, yRight + 20);	// каблук правого сапога
	Rectangle(hdc, xRight + 100, yRight + 20, xRight + 140, yRight - 20);	// нос правого сапога


	DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*				Методы класса Rectangle				*
*													*
*****************************************************/

// Конструктор
CRectangle::CRectangle(int aX, int aY, int aLength, int aWidth) : Point(aX, aY, xRight, yRight)
{
	Length = aLength;
	Width = aWidth;
}

// Деструктор
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

// Показать Прямоугольник
void CRectangle::Show(void)
{
	Visible = true;

	//HPEN Pen = CreatePen(PS_SOLID, 2, RGB(66, 29, 5));
	HBRUSH Brush = CreateSolidBrush(RGB(252, 15, 192));
	//SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	Rectangle(hdc, X, Y, X + Length, Y + Width);


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// Cпрятать Прямоугольник
void CRectangle::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	Rectangle(hdc, X, Y, X + Length, Y + Width);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

/****************************************************
*													*
*				Методы класса Square				*
*													*
*****************************************************/

// Конструктор
Square::Square(int aX, int aY, int aLength) : Point(aX, aY, xRight, yRight)
{
	Length = aLength;
	Width = Length;
}

// Деструктор
Square::~Square(void)
{

};

bool Square::IsVisible() {
	return Visible;
}

// Показать Прямоугольник
void Square::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 128, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 128, 0));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	Rectangle(hdc, X, Y, X + Length, Y + Width);


	//DeleteObject(Pen);
	DeleteObject(Brush);
}

// Cпрятать Прямоугольник
void Square::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	Rectangle(hdc, X, Y, X + Length, Y + Width);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

// Получить длину квадрата
int Square::GetLength() {
	return Length;
}

// Получить ширину квадрата
int Square::GetWidth() {
	return Width;
}

/****************************************************
*													*
*				Методы класса Circle				*
*													*
*****************************************************/

// Получить диаметр круга
int Circle::GetLength() {
	return Length;
}

// Получить диаметр круга
int Circle::GetWidth() {
	return Width;
}

// Конструктор
Circle::Circle(int aX, int aY, int aRadius) : Point(aX, aY, xRight, yRight)
{
	radius = aRadius;
	Length = radius * 2;
	Width = radius * 2;
}

// Деструктор
Circle::~Circle(void)
{

};

bool Circle::IsVisible() {
	return Visible;
}

// Показать Прямоугольник
void Circle::Show(void)
{
	Visible = true;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(66, 29, 5));
	HBRUSH Brush = CreateSolidBrush(RGB(66, 29, 5));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	Ellipse(hdc, X, Y, X + radius*2, Y + radius*2);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

// Cпрятать Прямоугольник
void Circle::Hide(void)
{
	Visible = false;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen); // сделаем перо активным
	SelectObject(hdc, Brush);

	Ellipse(hdc, X, Y, X + radius * 2, Y + radius * 2);

	DeleteObject(Pen);
	DeleteObject(Brush);
}
