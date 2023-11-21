#pragma once
#define X_MAX 1000
#define X_MIN 0
#define Y_MAX 500
#define Y_MIN 0

HWND GetConcolWindow();

// Базовый класс
class Location {                                    // инициализация
protected:

    int X;                                          // координата X
    int Y;                                          // координата Y

public:

    Location(int aX, int aY);                       // конструктор базового класса
    virtual~Location();                             // деструктор базового класса
    int GetX();                                     // получить координату X
    int GetY();                                     // получить координату Y
    void SetX(int aX);
    void SetY(int aY);
};

// Класс Точка (наследуется от базового класса) 
class Point : public Location {                     // инициализация
protected:

    bool Visible;                                   // показатель видимости Точки
    int Length;
    int Width;
    int xRight;
    int yRight;

public:
    int GetLength();
    int GetWidth();
    int GetXr();
    int GetYr();

    Point(int aX, int aY, int xRight, int yRight);                          // консуктор класса Точка
    virtual~Point();                                // деструктор класса Точка
    bool IsVisible();                               // узнать, видно ли Точку
    void MoveTo(int newX, int newY, 
        int newXright, int newYright);              // передвинуть Точку
    void Drag(int Step);                            // тянуть Точку
    virtual void Show();                            // показать Точку
    virtual void Hide();                            // спрятать Точку
    void SetXright(int aXr);
    void SetYright(int aYr);

    void SetColor(int R, int G, int B);

    virtual bool IsCollision(class Point *Boots, class Point *oRectangle);
};

// Класс Фигура (наследуется от класса Точка)
class Figure : public Point {                       // инициализация
protected:

public:

    Figure(int xLeft, int yLeft,                    // конструктор класса Фигура
        int xRight, int yRight);            
    virtual~Figure();                               // деструктор класса Фигура

    bool IsVisible();                               // узнать, видно ли Фигуру
    virtual void Show();                                    // показать Фигуру
    virtual void Hide();                                    // спрятать Фигуру
};

// Класс Цветные сапоги (наследуется от класса Фигура)
class ColoredBoots : public Figure {                // инициализация
protected:


public:
    ColoredBoots(int aX, int aY,                    // конструктор класса Цветные сапоги
        int xRight, int yRight);
    virtual~ColoredBoots();                         // деструктор класса Цветные сапоги

    bool IsVisible();                               // узнать, видно ли Цветные сапоги                  
    virtual void Show();                                    // показать
    virtual void Hide();                                    // спрятать
};

// Класс Порванные цветные сапоги (наследуется от класса Цветные сапоги)
class TornColoredBoots : public ColoredBoots {      // инициализация
protected:

public:
    TornColoredBoots(int aX, int aY,                // конструктор
        int xRight, int yRight);
    virtual~TornColoredBoots();                     // деструктор

    bool IsVisible();                               // показатель видимости
    virtual void Show();                                    // показать
    virtual void Hide();                                    // спрятать
};


// Класс Сапоги без каблука (наследуется от класса Фигура)
class BootsWithoutHeels : public Figure {
protected:

public:
    BootsWithoutHeels(int aX, int aY,               // конструктор
        int xRight, int yRight);
    virtual~BootsWithoutHeels();                    // деструктор

    bool IsVisible();                               // показатель видимости
    virtual void Show();                                    // показать
    virtual void Hide();                                    // спрятать
};

// Класс Сапоги с полоской (наследуется от класса Фигура)
class BootsWithStrip : public Figure {
protected:

public:
    BootsWithStrip(int aX, int aY,                  // конструктор
        int xRight, int yRight);
    virtual~BootsWithStrip();                       // деструктор

    bool IsVisible();                               // показатель видимости
    virtual void Show();                                    // показать
    virtual void Hide();                                    // спрятать
};

/****************************************************
*													*
*			   Дополнительные объекты			    *
*													*
*****************************************************/

// Класс Прямоугольник (наследуется от класса Точка)
class CRectangle : public Point {                    // инициализация
protected:

public:
    int GetLength();
    int GetWidth();

    CRectangle(int aX, int aY,                       // конструктор класса Прямоугольник
        int Length, int Width);
    virtual~CRectangle();                            // деструктор класса Прямоугольник

    bool IsVisible();                               // показатель видимости
    virtual void Show();                                    // показать
    virtual void Hide();                                    // спрятать
};

// Класс Квадрат
class Square : public Point {                    // инициализация
protected:

public:
    int GetLength();
    int GetWidth();

    Square(int aX, int aY, int Length);                         // конструктор класса Квадрат
    virtual~Square();                               // деструктор класса Квадрат
        
    bool IsVisible();                               // показатель видимости
    virtual void Show();                                    // показать
    virtual void Hide();                                    // спрятать
};

// Класс Круг
class Circle : public Point {                    // инициализация
protected:

    int radius;                                     // радиус Круга

public:
    int GetLength();
    int GetWidth();

    Circle(int aX, int aY, int radius);             // конструктор класса Круг
    virtual~Circle();                               // деструктор класса Круг

    bool IsVisible();                               // показатель видимости
    virtual void Show();                                    // показать
    virtual void Hide();                                    // спрятать
};
