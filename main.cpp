#include "Graphics.h"
#include "stolb.h"
//#include "sorts.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <fstream>
using namespace std;

bool isSorted(vector<Stolb>stolbs)
{
	bool res = true;
	for (int i = 0; i < stolbs.size() - 1; i++)
	{
		stolbs[i].VisGreen();
		stolbs[i + 1].VisGreen();
		Sleep(60);
		if(res)
			if (stolbs[i].val > stolbs[i + 1].val)
			{
				res = false;
			}
		stolbs[i].VisSt();
		stolbs[i + 1].VisSt();
	}
	return res;
}

void bubleSort(vector<Stolb>stolbs)
{
	int n = stolbs.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			stolbs[j].VisRed();
			stolbs[j + 1].VisRed();
			Sleep(20);
			if (stolbs[j].val > stolbs[j + 1].val)
			{
				move_swap(stolbs, j, j + 1);
			}
			Sleep(20);
			stolbs[j].VisSt();
			stolbs[j + 1].VisSt();
			Sleep(50);
		}
	}
	for (int i = 0; i < n; i++)
	{
		Sleep(35);
		stolbs[i].VisGreen();
	}
}

void gnomeSort(vector<Stolb>stolbs)
{
	int n = stolbs.size();
	int j = 2;
	for (int i = 1; i < n;)
	{
		stolbs[i].VisRed();
		stolbs[i - 1].VisRed();
		Sleep(20);
		if (stolbs[i - 1].val < stolbs[i].val)
		{
			stolbs[i].VisSt();
			stolbs[i - 1].VisSt();
			i = j;
			j++;
		}
		else
		{
			move_swap(stolbs, i - 1, i);
			stolbs[i].VisSt();
			stolbs[i - 1].VisSt();
			i--;
			if (i == 0)
			{
				i = j;
				j++;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		Sleep(35);
		stolbs[i].VisGreen();
	}
}

void bogoSort(vector<Stolb>stolbs)
{
	int n = stolbs.size();
	while (!isSorted(stolbs))
	{
		for (int i = n - 1; i >= 1; i--)
		{
			int j = rand() % (i + 1);  // j принадлежит [0;i];
			stolbs[i].VisRed();
			stolbs[j].VisRed();
			Sleep(20);
			move_swap(stolbs, i, j);
			stolbs[i].VisSt();
			stolbs[j].VisSt();
			Sleep(10);
		}	
	}
	for (int i = 0; i < n; i++)
	{
		Sleep(35);
		stolbs[i].VisGreen();
	}
}

int main()
{
	srand((unsigned)time(0));
	//SetConsoleTitle((LPCWSTR)"Program");
	system("mode con cols=200 lines=50"); //Установить размер окна в знакоместах
	HANDLE HandleCons = ::GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWnd = GetConsoleWindow(); //Получить ссылку на окно
	Graphics::InitGraphics(hWnd);
	Sleep(50);
	int wid = Graphics::GetWid();
	int heg = Graphics::GetHeg();
	setlocale(LC_ALL, "RUS");
	cout << "Введите размер исходного массива: ";
	int n;
	cin >> n;
	if (n > 100 || n < 1)
	{
		cout << "Ошибка во входных данных, введите n в промежутке [1;200]\n";
		exit(0);
	}
	vector<int>v(n);
	cout << "Выберите опцию:\n";
	cout << "1 - ввод массива с клавиатуры\n";
	cout << "2 - генерация случайного массива\n";
	char optionResult = _getch();
	if (optionResult == '1')
	{
		cout << "Введите n элементов:\n";
		for (int i = 0; i < n; i++)
			cin >> v[i];
	}
	else
	{
		bool doAgain = false;
		do
		{
			for (int i = 0; i < n; i++)
			{
				v[i] = i + 1;
			}
			for (int i = n - 1; i >= 1; i--)
			{
				int j = rand() % (i + 1);  // j принадлежит [0;i]
				swap(v[i], v[j]);
			}
			cout << "Полученный массив:\n";
			for (int i = 0; i < n; i++)
			{
				cout << v[i] << ' ';
			}
			cout << '\n';
			cout << "Перегенерировать массив?\n";
			cout << "1 - Оставить и приступить к выбору сортировки\n";
			cout << "2 - Сгенерировать новый массив\n";
			cout << "0 - Выход из программы\n";
			char ch = _getch();
			switch (ch)
			{
			case '1':
				doAgain = false;
				break;
			case '2':
				system("cls");
				doAgain = true;
				break;
			default:
				exit(0);
				break;
			}
		} while (doAgain);
	}
	vector<Stolb>stolbs(n);
	int x, y;
	x = 0; y = (heg - 100) / n;
	for (int i = 0; i < n; i++)
	{
		stolbs[i].set(x,heg, wid, n, (heg - 100) / n, v[i]);
		x += wid / n;
	}
//	cout << "Выберите сортировку\n";
	system("cls");
	Sleep(100);
	cout << "Исходный массив:\n";
	for (int i = 0; i < n; i++)
	{
		cout << v[i] << ' ';
	}
	cout << '\n';
	draw(stolbs); 
	/* Сортировка пузырьком */
	//bubbleSort(stolbs);
	//bubleSort(stolbs);
	//bogoSort(stolbs);
	gnomeSort(stolbs);
}
