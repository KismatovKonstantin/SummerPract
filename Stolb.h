#include "Graphics.h"

class Stolb
{
private:
	int x0, y0;
	int h, w;
	int val;
	COLORREF color = RGB(255, 255, 255);

public:
	Stolb();
	void VisSt();

};

void Stolb::VisSt()
{
	Graphics::Set_brush(color, 1);
	Graphics::Set_pen(color, 1);
}