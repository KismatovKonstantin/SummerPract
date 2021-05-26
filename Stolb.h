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
	int n, a; // ���������� ������� � ���������� ��������
	HPEN Pen = CreatePen(PS_INSIDEFRAME, 3, RGB(0, 191, 255));
	HPEN PenBlack = CreatePen(PS_INSIDEFRAME, 3, RGB(12, 12, 12));
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH BrushGreen = CreateSolidBrush(RGB(0, 255, 127));
	HBRUSH BrushRed = CreateSolidBrush(RGB(255, 105, 180));
	HBRUSH BrushBlack = CreateSolidBrush(RGB(12, 12, 12));
	HDC dc = GetDC(GetConsoleWindow());
public:
	int val;
	int right;


	void set(int, int, int, int, int, int);
	void VisSt();
	void VisBlack();
	void VisRed();
	void VisGreen();
	void make_equal(Stolb);
};

void Stolb::VisSt() // ������� ������� � ����� �����
{

	/*Graphics t;
	t.InitGraphics(GetConsoleWindow());
	t.Set_pen(RGB(0, 191, 255), 3);
	t.Set_brush(RGB(255, 255, 255), 1);
	Rectangle(t.dc, x, h - 0, x + w / n, right);
	t.~Graphics();*/
	SelectObject(dc, Pen);
	SelectObject(dc, BrushWhite);
	Rectangle(dc, x, h - 0, x + w / n, right);
}

void Stolb::VisGreen() // ������� ������� � ������� �����
{
	/*Graphics::Set_pen(RGB(0, 191, 255), 3);
	Graphics::Set_brush(RGB(0, 255, 127), 1);
	Rectangle(Graphics::dc, x, h - 0, x + w / n, right);*/
	Graphics t;
	/*t.InitGraphics(GetConsoleWindow());
	t.Set_pen(RGB(0, 191, 255), 3);
	t.Set_brush(RGB(0, 255, 127), 1);
	Rectangle(t.dc, x, h - 0, x + w / n, right);
	t.~Graphics();*/
	SelectObject(dc, Pen);
	SelectObject(dc, BrushGreen);
	Rectangle(dc, x, h - 0, x + w / n, right);
}

void Stolb::VisRed() // ������� ������� � ��������� �����
{
	/*Graphics::Set_pen(RGB(0, 191, 255), 3);
	Graphics::Set_brush(RGB(255, 105, 180), 1);
	Rectangle(Graphics::dc, x, h - 0, x + w / n, right);*/
	/*Graphics t;
	t.InitGraphics(GetConsoleWindow());
	t.Set_pen(RGB(0, 191, 255), 3);
	t.Set_brush(RGB(255, 105, 180), 1);
	Rectangle(t.dc, x, h - 0, x + w / n, right);
	t.~Graphics();*/
	SelectObject(dc, Pen);
	SelectObject(dc, BrushRed);
	Rectangle(dc, x, h - 0, x + w / n, right);
}

void Stolb::VisBlack() // ��������� ������ ���������
{
	/*Graphics::Set_pen(RGB(12, 12, 12), 3);
	Graphics::Set_brush(RGB(12, 12, 12), 1);
	Rectangle(Graphics::dc, x, h - 0, x + w / n, right);*/
	Graphics t;
	/*t.InitGraphics(GetConsoleWindow());
	t.Set_pen(RGB(12, 12, 12), 3);
	t.Set_brush(RGB(12, 12, 12), 1);
	Rectangle(t.dc, x, h - 0, x + w / n, right);
	t.~Graphics();*/
	SelectObject(dc, PenBlack);
	SelectObject(dc, BrushBlack);
	Rectangle(dc, x, h - 0, x + w / n, right);
}

void Stolb::set(int _x, int _h, int _w, int _n, int _a, int _val)
{
	x = _x;
	h = _h;
	w = _w;
	val = _val;
	n = _n;
	a = _a;
	val = _val;
	right = h - a * val;
} // �������������


void draw(vector<Stolb>v) //���������� ��� ������ ����������� ������.
{
	for (int i = 0; i < v.size(); i++)
		v[i].VisSt();
}

void move_swap(vector<Stolb>& v, int i, int j) // ������� �������� swap'a ���� ���������
{
	if (i == j)
		return;
	Sleep(5);
	int speed = v.size() * 2;
	if (v.size() * 2 < 25)
		speed = 25;
	int start = v[i].right;
	int end = v[j].right;
	int k, k1 = 0;
	k = start > end ? -1 : 1;
	ofstream fout("debug.txt", ios::app);
	fout << start << ' ' << end << '\n'; // start > end;
	while (1)
	{
		k1++;
		Sleep(25); // �������� ��� ���������
		v[i].VisBlack();
		v[j].VisBlack();

		v[i].right += k * speed; // 2n - �������� �� ���������
		v[j].right += -k * speed; // 2n - �������� �� ���������
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

void Stolb::make_equal(Stolb II)
{
	VisBlack();
	Sleep(10);
	int step = n * 2;
	int k = right > II.right ? -1 : 1;
	if (right == II.right)
	{
		VisSt();
		return;
	}
	if (abs(right - II.right) < step)
	{
		right = II.right;
		Sleep(30);
		VisSt();
		Sleep(30);
		return;
	}
	right += k * step;
	VisRed();
	Sleep(30);
}