#pragma once
#define X_MAX 1000
#define X_MIN 0
#define Y_MAX 500
#define Y_MIN 0

HWND GetConcolWindow();

// ������� �����
class Location {                                    // �������������
protected:

    int X;                                          // ���������� X
    int Y;                                          // ���������� Y

public:

    Location(int aX, int aY);                       // ����������� �������� ������
    virtual~Location();                             // ���������� �������� ������
    int GetX();                                     // �������� ���������� X
    int GetY();                                     // �������� ���������� Y
    void SetX(int aX);
    void SetY(int aY);
};

// ����� ����� (����������� �� �������� ������) 
class Point : public Location {                     // �������������
protected:

    bool Visible;                                   // ���������� ��������� �����
    int Length;
    int Width;
    int xRight;
    int yRight;

public:
    int GetLength();
    int GetWidth();
    int GetXr();
    int GetYr();

    Point(int aX, int aY, int xRight, int yRight);                          // ��������� ������ �����
    virtual~Point();                                // ���������� ������ �����
    bool IsVisible();                               // ������, ����� �� �����
    void MoveTo(int newX, int newY, 
        int newXright, int newYright);              // ����������� �����
    void Drag(int Step);                            // ������ �����
    virtual void Show();                            // �������� �����
    virtual void Hide();                            // �������� �����
    void SetXright(int aXr);
    void SetYright(int aYr);

    void SetColor(int R, int G, int B);

    virtual bool IsCollision(class Point *Boots, class Point *oRectangle);
};

// ����� ������ (����������� �� ������ �����)
class Figure : public Point {                       // �������������
protected:

public:

    Figure(int xLeft, int yLeft,                    // ����������� ������ ������
        int xRight, int yRight);            
    virtual~Figure();                               // ���������� ������ ������

    bool IsVisible();                               // ������, ����� �� ������
    virtual void Show();                                    // �������� ������
    virtual void Hide();                                    // �������� ������
};

// ����� ���� � ����� (����������� �� ������ ������)
class FaceWithEars : public Figure {                // �������������
protected:


public:
    FaceWithEars(int aX, int aY,                    // ����������� ������ ���� � �����
        int xRight, int yRight);
    virtual~FaceWithEars();                         // ���������� ������ ���� � �����

    bool IsVisible();                               // ������, ����� �� ���� � �����                  
    virtual void Show();                                    // ��������
    virtual void Hide();                                    // ��������
};

// ����� ���� � ����� � ����� (����������� �� ������ ���� � �����)
class FaceWithEarsAndNose : public FaceWithEars {      // �������������
protected:

public:
    FaceWithEarsAndNose(int aX, int aY,                // �����������
        int xRight, int yRight);
    virtual~FaceWithEarsAndNose();                     // ����������

    bool IsVisible();                               // ���������� ���������
    virtual void Show();                                    // ��������
    virtual void Hide();                                    // ��������
};


// ����� ����� (����������� �� ������ ������)
class AsianFace : public Figure {
protected:

public:
    AsianFace(int aX, int aY,               // �����������
        int xRight, int yRight);
    virtual~AsianFace();                    // ����������

    bool IsVisible();                               // ���������� ���������
    virtual void Show();                                    // ��������
    virtual void Hide();                                    // ��������
};

// ����� ���� (����������� �� ������ ������)
class BlackFace : public Figure {
protected:

public:
    BlackFace(int aX, int aY,                  // �����������
        int xRight, int yRight);
    virtual~BlackFace();                       // ����������

    bool IsVisible();                               // ���������� ���������
    virtual void Show();                                    // ��������
    virtual void Hide();                                    // ��������
};

/****************************************************
*													*
*			   �������������� �������			    *
*													*
*****************************************************/

// ����� ������������� (����������� �� ������ �����)
class CRectangle : public Point {                    // �������������
protected:

public:
    int GetLength();
    int GetWidth();

    CRectangle(int aX, int aY,                       // ����������� ������ �������������
        int Length, int Width);
    virtual~CRectangle();                            // ���������� ������ �������������

    bool IsVisible();                               // ���������� ���������
    virtual void Show();                                    // ��������
    virtual void Hide();                                    // ��������
};

// ����� �������
class Square : public Point {                    // �������������
protected:

public:
    int GetLength();
    int GetWidth();

    Square(int aX, int aY, int Length);                         // ����������� ������ �������
    virtual~Square();                               // ���������� ������ �������
        
    bool IsVisible();                               // ���������� ���������
    virtual void Show();                                    // ��������
    virtual void Hide();                                    // ��������
};

// ����� ����
class Circle : public Point {                    // �������������
protected:

    int radius;                                     // ������ �����

public:
    int GetLength();
    int GetWidth();

    Circle(int aX, int aY, int radius);             // ����������� ������ ����
    virtual~Circle();                               // ���������� ������ ����

    bool IsVisible();                               // ���������� ���������
    virtual void Show();                                    // ��������
    virtual void Hide();                                    // ��������
};
