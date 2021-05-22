#include "Graphics.h"

int main()
{
	srand((unsigned)time(NULL));
	setlocale(LC_CTYPE, "rus");
	::SetConsoleTitle((LPCWSTR)"Graphics");
	::system("mode con cols=200 lines=50");
	hWnd = ::FindWindow(NULL, (LPCWSTR)"Graphics");


	Graphics::InitGraphics(hWnd);


}