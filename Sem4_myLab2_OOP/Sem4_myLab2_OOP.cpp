#pragma once

//***************************************************************************************************
//								Лабораторные работы по ООП, C++										*
//***************************************************************************************************
//																									*
//	Project type: Win32 Console Application															*
//	File name:    Sem4_myLab2_OOP																	*
//	Programmer:	  Krasnov A.D.																	*
//	Вариант:      13 (Лицо)																		*
//	Номер:		  2																					*
//	Created:      05.05.23																			*
//	Last revision:05.11.23																			*	
//  Комментарий:  Построить иерархию потомков класса Figure, построить иерархию						*
//				  дополнительных объектов, реализовать взаимодействие объектов						*
//																									*
//***************************************************************************************************

#include <windows.h>
#include <iostream>
#include <thread>
#include "Classes.h"
//#include "GetCons.cpp"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

HDC hdc;

int main() {
	setlocale(LC_ALL, "ru");
	system("color F0");

	int x0 = 500;
	int y0 = 500;
	int radius = 10;
	bool f1 = true;
	const int n = 3;
	int i = 0;

	HWND hwnd = GetConcolWindow();                      // функция, позволяющая "рисовать"

	if (hwnd != NULL) {

		hdc = GetWindowDC(hwnd);

		if (hdc != 0) {

			Point aPoint(x0, y0, x0, y0);	// точка

			Figure Face(x0, y0, x0 + 100, y0 + 100);	// лицо

			FaceWithEars FaceEars(x0, y0, x0 + 100, y0 + 100);			// лицо с ушами
			FaceWithEarsAndNose FaceEarsNose(x0, y0, x0 + 100, y0 + 100);	// лицо с ушами и носом

			AsianFace Asian(x0, y0, x0 + 300, y0 + 100);		// азиат
			BlackFace Black(x0, y0, x0 + 200, y0 + 100);			// негр

			CRectangle oRectangle(100, 100, 30, 40);	// прямоугольник
			Square oSquare(400, 400, 20);				// квадрат
			Circle oCircle(200, 200, radius);			// круг

			Point* ptrFaces[n + 1] = { &Face, &FaceEars, &Asian, &Black };  // массив указателей на лица
			//Point* ptrFaces[n + 1] = { &NoHeelsBoots };
			Point* ptrGeometry[n] = { &oRectangle, &oSquare, &oCircle };					   // массив указателей на геометрические фигуры
			Point* currentFace = ptrFaces[i];												   // нынешнее лицо
			currentFace->Show();															   // показать нынешнее лицо

			// матрица переходов (ОНА ДЛЯ 3 И 4 ЛАБЫ), строки - это сапоги, столбцы - это геометрические фигуры
			//int transitionMatrix[n + 1][n] = {
			//	{1, 2, 3},
			//	{3, 2, 1},
			//	{1, 3, 2},
			//	{1, 2, 3}
			//};

			//окрашиваем фигуры в цвета
			ptrGeometry[0]->Show();                    // показать прямоугольник
			ptrGeometry[1]->Show();                    // показать квадрат
			ptrGeometry[2]->Show();                    // показать круг
			
			while (!KEY_DOWN(VK_ESCAPE)) {				// начинаем двигать нашу фигуру

				currentFace->Drag(10);					// двигаем лицо
				Sleep(1);

				for (int j = 0; j < 3; j++) {			// проходим по каждой геометрической фигуре
					Point* Object = ptrGeometry[j];		// геометрический объект
					if (ptrGeometry[j]->IsCollision(ptrFaces[i], ptrGeometry[j]) && ptrGeometry[j]->IsVisible()) {	// если лицо столкнулось с фигурой, то

						std::cout << "Произошло столкновение!" << std::endl;		// ВОТ ЭТИ ДВЕ СТРОЧКИ ДЛЯ 2 ЛАБЫ
						return 0;													// ОСТАЛЬНОЕ ВСЕ ТУТ ДЛЯ 3 ЛАБЫ
						
						//ptrGeometry[j]->Hide();			// прячем геометрическую фигуру
						//ptrGeometry[j]->MoveTo(ptrGeometry[j]->GetX() + rand() % 100 - 2, ptrGeometry[j]->GetY() + rand() % 100 - 2, 0, 0);
						//// если фигура вышла за пределы поля, то возвращаем ее обратно
						//if ((ptrGeometry[j]->GetX() + 30 > X_MAX) || (ptrGeometry[j]->GetX() - 30 < X_MIN) || (ptrGeometry[j]->GetY() - 40 > Y_MAX) || (ptrGeometry[j]->GetY() + 40 < Y_MIN)) {
						//	ptrGeometry[j]->MoveTo(100 + rand() % 1000, 100, 0, 0);
						//}

						//ptrGeometry[j]->Show();	// показываем фигуру

						//currentFace->Hide();			// прячем прошлые сапоги
						//Point* NewBoots = ptrFaces[transitionMatrix[i][j]]; // новые сапоги
						//NewBoots->SetX(currentFace->GetX()); // присваиваем новым сапогам координаты старых
						//NewBoots->SetY(currentFace->GetY());
						//NewBoots->SetXright(currentFace->GetXr());
						//NewBoots->SetYright(currentFace->GetYr());
						//i = transitionMatrix[i][j];		// i - индекс следующих сапог
						//currentFace = NewBoots;		// текущие сапоги = новые сапоги
						//currentFace->Show();			// показываем текующие сапоги
					}
				} 
			} 
		}
	}
}
