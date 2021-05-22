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
	Graphics::Set_pen(RGB(0, 191, 255), 3);
	Graphics::Set_brush(RGB(255, 255, 255), 1);
}
