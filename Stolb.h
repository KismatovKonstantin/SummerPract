#include "Graphics.h"
#include <vector>

class Stolb
{
private:
	int x;
	int h, w;
	int val;
	int n, a; // количество столбов и коэфициент перевода
	COLORREF color = RGB(255, 255, 255);
public:
	void set(int,int,int,int,int,int);
	void VisSt();
};

void Stolb::VisSt()
{
	Graphics::Set_pen(RGB(0, 191, 255), 3);
	Graphics::Set_brush(RGB(255, 255, 255), 1);
	Rectangle(Graphics::dc, x, h - 0, x + w / n, h - a * val);
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
}

void draw(vector<Stolb>v)
{
	for (int i = 0; i < v.size(); i++)
		v[i].VisSt();
}

