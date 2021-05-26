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
		if (res)
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
			stolbs[i].VisSt(); //расчёска
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

void brushSort(vector<Stolb>stolbs)
{
	double factor = 1.2473309;
	int step = stolbs.size() - 1;
	while (step >= 1)
	{
		for (int i = 0; i + step < stolbs.size(); i++)
		{
			stolbs[i].VisRed();
			stolbs[i + step].VisRed();
			Sleep(20);
			if (stolbs[i].val > stolbs[i + step].val)
			{
				move_swap(stolbs, i, i + step);
			}
			stolbs[i].VisSt();
			stolbs[i + step].VisSt();
			Sleep(11);
		}
		step /= factor;
	}
	for (int i = 0; i < stolbs.size(); i++)
	{
		Sleep(35);
		stolbs[i].VisGreen();
	}
}

void shakeSort(vector<Stolb>stolbs)
{
	int left = 0;
	int right = stolbs.size() - 1;
	while (left <= right)
	{
		for (int i = right; i > left; i--)
		{
			stolbs[i - 1].VisRed();
			stolbs[i].VisRed();
			Sleep(20);
			if (stolbs[i - 1].val > stolbs[i].val)
			{
				move_swap(stolbs, i - 1, i);
			}
			stolbs[i - 1].VisSt();
			stolbs[i].VisSt();
			Sleep(5);
		}
		left++;
		for (int i = left; i < right; i++)
		{
			stolbs[i].VisRed();
			stolbs[i + 1].VisRed();
			Sleep(20);
			if (stolbs[i].val > stolbs[i + 1].val)
			{
				move_swap(stolbs, i, i + 1);
			}
			stolbs[i].VisSt();
			stolbs[i + 1].VisSt();
			Sleep(5);
		}
		right--;
	}
	for (int i = 0; i < stolbs.size(); i++)
	{
		Sleep(35);
		stolbs[i].VisGreen();
	}
}

void selectionSort(vector<Stolb>stolbs)
{
	for (int i = 0; i < stolbs.size() - 1; i++)
	{
		int mn = i;
		stolbs[mn].VisRed();
		for (int j = i + 1; j < stolbs.size(); j++)
		{
			int t = mn;
			stolbs[j].VisRed();

			Sleep(20);
			if (stolbs[j].val < stolbs[mn].val)
			{
				mn = j;
			}
			stolbs[j].VisSt();

			Sleep(5);
		}
		stolbs[mn].VisSt();
		if (mn != i)
		{
			move_swap(stolbs, i, mn);
			stolbs[i].VisSt();
			stolbs[mn].VisSt();
		}
	}
	for (int i = 0; i < stolbs.size(); i++)
	{
		Sleep(35);
		stolbs[i].VisGreen();
	}
}

void mergeRec(vector<Stolb>& stolbs, int start, int end)
{
	ofstream fout("test.txt", ios::app);
	int n = end - start + 1;
	if (n == 1)
		return;
	if (n == 2)
	{
		stolbs[start].VisRed();
		stolbs[end].VisRed();
		Sleep(20);
		if (stolbs[start].val > stolbs[end].val)
			move_swap(stolbs, start, end);
		stolbs[start].VisSt();
		stolbs[end].VisSt();
		Sleep(5);
		fout << stolbs[start].val << ' ' << stolbs[end].val << endl;
		return;
	}
	if (n == 3)
	{
		stolbs[start].VisRed();
		stolbs[start + 1].VisRed();
		Sleep(20);
		if (stolbs[start].val > stolbs[start + 1].val)
			move_swap(stolbs, start, start + 1);
		stolbs[start].VisSt();
		stolbs[start + 1].VisSt();
		Sleep(5);

		stolbs[start + 1].VisRed();
		stolbs[end].VisRed();
		Sleep(20);
		if (stolbs[start + 1].val > stolbs[end].val)
			move_swap(stolbs, start + 1, end);
		stolbs[start + 1].VisSt();
		stolbs[end].VisSt();
		Sleep(5);

		stolbs[start].VisRed();
		stolbs[start + 1].VisRed();
		Sleep(20);
		if (stolbs[start].val > stolbs[start + 1].val)
			move_swap(stolbs, start, start + 1);
		stolbs[start].VisSt();
		stolbs[start + 1].VisSt();
		Sleep(5);

		fout << stolbs[start].val << ' ' << stolbs[start + 1].val << ' ' << stolbs[end].val << endl;
		return;
	}
	mergeRec(stolbs, start, (start + end) / 2);
	mergeRec(stolbs, (start + end) / 2 + 1, end);
	vector<Stolb> sorted;
	int i = start, j = (start + end) / 2 + 1;
	while (i <= (start + end) / 2 && j <= end)
	{
		if (stolbs[i].val < stolbs[j].val)
		{
			sorted.push_back(stolbs[i]);
			i++;
		}
		else
		{
			if (stolbs[i].val > stolbs[j].val)
			{
				sorted.push_back(stolbs[j]);
				j++;
			}
		}
	}
	while (i <= (start + end) / 2)
	{
		sorted.push_back(stolbs[i]);
		i++;
	}
	while (j <= end)
	{
		sorted.push_back(stolbs[j]);
		j++;
	}

	for (i = 0; i < n; i++)
	{
		while (stolbs[i + start].right != sorted[i].right)
			stolbs[i + start].make_equal(sorted[i]);
		stolbs[i + start].VisSt();
	}


	for (int i = 0; i < sorted.size(); i++)
	{
		stolbs[i + start].val = sorted[i].val;
		stolbs[i + start].right = sorted[i].right;
		Sleep(10);
		stolbs[i + start].VisSt();
		Sleep(10);
	}

	for (i = start; i <= end; i++)
		fout << stolbs[i].val << ' ';
	fout << endl;
}

void mergeSort(vector<Stolb>stolbs)
{
	mergeRec(stolbs, 0, stolbs.size() - 1);
	for (int i = 0; i < stolbs.size(); i++)
	{
		stolbs[i].VisGreen();
		Sleep(35);
	}
}

int main()
{
	srand((unsigned)time(0));
	//SetConsoleTitle((LPCWSTR)"Program");
	system("mode con cols=150 lines=35"); //Установить размер окна в знакоместах
	HANDLE HandleCons = ::GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWnd = GetConsoleWindow(); //Получить ссылку на окно
	Graphics::InitGraphics(hWnd);
	Sleep(50);
	int wid = 1600; //Graphics::GetWid();
	int heg = 835; //Graphics::GetHeg();
	setlocale(LC_ALL, "RUS");
	cout << "Введите размер исходного массива (от 5 до 100): ";
	int n;
	cin >> n;
	while(n > 100 || n < 5)
	{
		cout << "Ошибка во входных данных, введите n в промежутке [5;100]\n";
		cin >> n;
	}
	vector<int>v(n);
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
	vector<Stolb>stolbs(n);
	int x, y;
	x = 0; y = (heg - 100) / n;
	for (int i = 0; i < n; i++)
	{
		stolbs[i].set(x, heg, wid, n, y, v[i]);
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
	brushSort(stolbs);
	//selectionSort(stolbs);
	//mergeSort(stolbs);
	//while (stolbs[0].right != stolbs[1].right)
	//	make_equal(stolbs[0], stolbs[1]);
	_getch();
}