#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <iostream>
using namespace std;

HWND hWnd;		//Получение ссылки на окно
HDC dc;			//Получение контекста устройства
HPEN hPen;		//Декскриптор пера
HBRUSH hBrush;	//Дескриптор кисти
HANDLE HandleCons; //Дескриптор окна
int wid, heg;

void Set_pen(HDC dc, int r, int g, int b, int w)
{
	hPen = CreatePen(PS_INSIDEFRAME, w, RGB(r, g, b));	//Создать перо
	SelectObject(dc, hPen); //Выбирает перо в заданный контекст устройства
}

void Set_brush(HDC dc, int r, int g, int b)
{
	if (r == -1)
		hBrush = ::CreateSolidBrush(HOLLOW_BRUSH); //Создать пустую кисть
	else
		hBrush = ::CreateSolidBrush(RGB(r, g, b));	//Создать кисть цвета rgb
	::SelectObject(dc, hBrush); //Выбирает кисть в заданный контекст устройства
}

void Line(HDC dc, int x1, int y1, int x2, int y2)
{
	MoveToEx(dc, x1, y1, NULL);//начало отрезка
	LineTo(dc, x2, y2);//конец отрезка
}

//////////////////////////////////////////////////////////////////////////

#define PI 3.14159265359f
#define KVer 8

int dx1;
int dy1;

struct Figure
{
	POINT pt0; //Координаты центра восьмиугольника
	POINT topVer[8] = { 0 }; //В массиве хранятся начальные значения координат вершин восьмиугольника
	POINT transVer[8] = { 0 }; //Массив используется для преобразованных координат
	int R = 120; //Радиус восьмиугольника
};

Figure oct8; //Создание объекта oct8 (тип - Figure) 

void CreatFigure()
{
	oct8.pt0.x = 0;
	oct8.pt0.y = 0;

	for (int i = 0; i < KVer; i++)
	{
		//Расчет координат вершин восьмиугольника
		//(координаты рассчитываются вокруг нуля).
		//В экранной системе координат 0 - левый верхний угол
		//клиентской области окна
		oct8.topVer[i].x = (long)(oct8.R * cos(PI * i / 4.) + 0.5f);
		oct8.topVer[i].y = (long)(oct8.R * sin(PI * i / 4.) + 0.5f);

		oct8.transVer[i].x = oct8.topVer[i].x;
		oct8.transVer[i].y = oct8.topVer[i].y;
	}
}
//Функция сдвига восьмиугольника на величину
//dx и dy по осям x и y соответственно
void MoveFigure(int dx, int dy)
{
	oct8.pt0.x += dx;
	oct8.pt0.y += dy;
	for (int i = 0; i < KVer; i++)
	{
		oct8.transVer[i].x += dx;
		oct8.transVer[i].y += dy;
	}
}

//Поворот фигуры на alfa градусов
void RotFigure(int alfa)
{
	long x, y;
	float rad = alfa * PI / 180;//Перевод градусов в радианы

//Используются формулы поворота фигуры вокруг
//начала координат (вокруг 0).
//Поэтому необходимо использовать значения
//начальных координат, сформированных при создании
//фигуры (функция CreatFigure())

	oct8.pt0.x = 0;
	oct8.pt0.y = 0;
	for (int i = 0; i < KVer; i++)
	{
		x = oct8.topVer[i].x;
		y = oct8.topVer[i].y;
		oct8.transVer[i].x = (long)((x * cos(rad) - y * sin(rad)) + 0.5f);
		oct8.transVer[i].y = (long)((x * sin(rad) + y * cos(rad)) + 0.5f);
	}
}
//Визуализация восьмиугольника
void VisFigure()
{
	//Рисуем восьмиугольник с помощью библиотечной
	//функции Polygon(). В качестве параметров функция
	//принимает контекст устройства (dc),
	//массив типа POINT (oct8.transVer), размер
	//массива (KVer).
	//Если кисть использует цвета -1 -1 -1, то
	//рисуется пустой многоугольник
	Set_pen(dc, 255, 0, 0, 3);
	Set_brush(dc, 255, 1, 1);
	Polygon(dc, oct8.transVer, KVer);
	//Рисование "спиц" восьмиугольника при
	//помощи различных цветовых перьев шириной 3 пиксела
	Set_pen(dc, 0, 255, 0, 3); //Зеленый цвет
	Line(dc, oct8.transVer[0].x, oct8.transVer[0].y, oct8.transVer[4].x, oct8.transVer[4].y);
	Set_pen(dc, 0, 0, 255, 3); //Синий цвет
	Line(dc, oct8.transVer[1].x, oct8.transVer[1].y, oct8.transVer[5].x, oct8.transVer[5].y);
	Set_pen(dc, 255, 255, 0, 3); //Желтый цвет
	Line(dc, oct8.transVer[2].x, oct8.transVer[2].y, oct8.transVer[6].x, oct8.transVer[6].y);
	Set_pen(dc, 255, 0, 255, 3); //Сиреневый цвет
	Line(dc, oct8.transVer[3].x, oct8.transVer[3].y, oct8.transVer[7].x, oct8.transVer[7].y);
}

void AnimFigure()
{
	int key = 1, gr = 15, dx = 30;
	//Код клавиши Esc - 27
	//Код клавиши -> - 224
	//Цикл работает, пока не нажата клавиша Esc
	while (key != 27)
	{
		key = _getch();
		if (key == 224)
		{

			RotFigure(gr);
			MoveFigure(dx1, dy1);
			MoveFigure(dx, 0);

			VisFigure();
			dx += 30;
			gr += 30;
		}
	}
}

