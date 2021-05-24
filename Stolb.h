#include "Graphics.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <fstream>
class Stolb
{
private:
	int x;
	int h, w;
	int n, a; // количество столбов и коэфициент перевода
public:
	int val;
	int right;
	void set(int,int,int,int,int,int);
	void addRight(int);
	void VisSt();
	void VisBlack();
	void VisRed();
	void VisGreen();
	int getRight();
};

void Stolb::VisSt() // Голубая обводка с белым фоном
{
	Graphics t;
	t.InitGraphics(GetConsoleWindow());
	t.Set_pen(RGB(0, 191, 255), 3);
	t.Set_brush(RGB(255, 255, 255), 1);
	Rectangle(t.dc, x, h - 0, x + w / n, right);
	t.~Graphics();
}

void Stolb::VisGreen() // Голубая обводка с зеленым фоном
{
	/*Graphics::Set_pen(RGB(0, 191, 255), 3);
	Graphics::Set_brush(RGB(0, 255, 127), 1);
	Rectangle(Graphics::dc, x, h - 0, x + w / n, right);*/
	Graphics t;
	t.InitGraphics(GetConsoleWindow());
	t.Set_pen(RGB(0, 191, 255), 3);
	t.Set_brush(RGB(0, 255, 127), 1);
	Rectangle(t.dc, x, h - 0, x + w / n, right);
	t.~Graphics();
}

void Stolb::VisRed() // Голубая обводка с малиновым фоном
{
	/*Graphics::Set_pen(RGB(0, 191, 255), 3);
	Graphics::Set_brush(RGB(255, 105, 180), 1);
	Rectangle(Graphics::dc, x, h - 0, x + w / n, right);*/
	Graphics t;
	t.InitGraphics(GetConsoleWindow());
	t.Set_pen(RGB(0, 191, 255), 3);
	t.Set_brush(RGB(255, 105, 180), 1);
	Rectangle(t.dc, x, h - 0, x + w / n, right);
	t.~Graphics();
}

void Stolb::VisBlack() // Закрасить черным квадратом
{
	/*Graphics::Set_pen(RGB(12, 12, 12), 3);
	Graphics::Set_brush(RGB(12, 12, 12), 1);
	Rectangle(Graphics::dc, x, h - 0, x + w / n, right);*/
	Graphics t;
	t.InitGraphics(GetConsoleWindow());
	t.Set_pen(RGB(12, 12, 12), 3);
	t.Set_brush(RGB(12, 12, 12), 1);
	Rectangle(t.dc, x, h - 0, x + w / n, right);
	t.~Graphics();
}

void Stolb::addRight(int a)
{
	right += a;
}

void Stolb::set(int _x,int _h,int _w,int _n,int _a,int _val)
{
	x = _x;
	h = _h;
	w = _w;
	val = _val;
	n = _n;
	a = _a;
	val = _val;
	right = h - a * val;
} // инициализатор

int Stolb::getRight()
{
	return right;
}


void draw(vector<Stolb>v) //Нарисовать все столбы стандартным цветом.
{
	for (int i = 0; i < v.size(); i++)
		v[i].VisSt();
}

void move_swap(vector<Stolb>&v, int i, int j) // Функция анимации swap'a двух элементов
{
	Sleep(5);
	int speed = v.size() * 2;
	int start = v[i].getRight();
	int end = v[j].getRight();
	int k,k1 = 0;
	k = start > end ? -1 : 1;
	ofstream fout("debug.txt",ios::app);
	fout << start << ' ' << end << '\n'; // start > end;
	while (1)
	{   
		k1++;
		Sleep(25); // Задержка для обработки
		v[i].VisBlack();
		v[j].VisBlack();
		
		v[i].right +=  k * speed; // 2n - скорость по умолчанию
		v[j].right += -k * speed; // 2n - скорость по умолчанию
		if (v[i].right > end && start < end || v[i].right < end && start > end)
		{
			v[i].right = end;
			v[j].right = start;
			v[i].VisRed();
			v[j].VisRed();
			break;
		}
		if (v[j].right < start && start < end || v[j].right > start && start > end)
		{
			v[i].right = end;
			v[j].right = start;
			v[i].VisRed();
			v[j].VisRed();
			break;
		}
		v[i].VisRed();
		v[j].VisRed();
	}
	v[i].right = end;
	v[j].right = start;
	swap(v[i].val, v[j].val);
	fout << v[i].right << ' ' << v[j].right << '\n'; // start > end;
	return;
}

