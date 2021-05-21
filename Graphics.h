#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <iostream>
using namespace std;

HWND hWnd;		//��������� ������ �� ����
HDC dc;			//��������� ��������� ����������
HPEN hPen;		//����������� ����
HBRUSH hBrush;	//���������� �����
HANDLE HandleCons; //���������� ����
int wid, heg;

void Set_pen(HDC dc, int r, int g, int b, int w)
{
	hPen = CreatePen(PS_INSIDEFRAME, w, RGB(r, g, b));	//������� ����
	SelectObject(dc, hPen); //�������� ���� � �������� �������� ����������
}

void Set_brush(HDC dc, int r, int g, int b)
{
	if (r == -1)
		hBrush = ::CreateSolidBrush(HOLLOW_BRUSH); //������� ������ �����
	else
		hBrush = ::CreateSolidBrush(RGB(r, g, b));	//������� ����� ����� rgb
	::SelectObject(dc, hBrush); //�������� ����� � �������� �������� ����������
}

void Line(HDC dc, int x1, int y1, int x2, int y2)
{
	MoveToEx(dc, x1, y1, NULL);//������ �������
	LineTo(dc, x2, y2);//����� �������
}

//////////////////////////////////////////////////////////////////////////

#define PI 3.14159265359f
#define KVer 8

int dx1;
int dy1;

struct Figure
{
	POINT pt0; //���������� ������ ���������������
	POINT topVer[8] = { 0 }; //� ������� �������� ��������� �������� ��������� ������ ���������������
	POINT transVer[8] = { 0 }; //������ ������������ ��� ��������������� ���������
	int R = 120; //������ ���������������
};

Figure oct8; //�������� ������� oct8 (��� - Figure) 

void CreatFigure()
{
	oct8.pt0.x = 0;
	oct8.pt0.y = 0;

	for (int i = 0; i < KVer; i++)
	{
		//������ ��������� ������ ���������������
		//(���������� �������������� ������ ����).
		//� �������� ������� ��������� 0 - ����� ������� ����
		//���������� ������� ����
		oct8.topVer[i].x = (long)(oct8.R * cos(PI * i / 4.) + 0.5f);
		oct8.topVer[i].y = (long)(oct8.R * sin(PI * i / 4.) + 0.5f);

		oct8.transVer[i].x = oct8.topVer[i].x;
		oct8.transVer[i].y = oct8.topVer[i].y;
	}
}
//������� ������ ��������������� �� ��������
//dx � dy �� ���� x � y ��������������
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

//������� ������ �� alfa ��������
void RotFigure(int alfa)
{
	long x, y;
	float rad = alfa * PI / 180;//������� �������� � �������

//������������ ������� �������� ������ ������
//������ ��������� (������ 0).
//������� ���������� ������������ ��������
//��������� ���������, �������������� ��� ��������
//������ (������� CreatFigure())

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
//������������ ���������������
void VisFigure()
{
	//������ �������������� � ������� ������������
	//������� Polygon(). � �������� ���������� �������
	//��������� �������� ���������� (dc),
	//������ ���� POINT (oct8.transVer), ������
	//������� (KVer).
	//���� ����� ���������� ����� -1 -1 -1, ��
	//�������� ������ �������������
	Set_pen(dc, 255, 0, 0, 3);
	Set_brush(dc, 255, 1, 1);
	Polygon(dc, oct8.transVer, KVer);
	//��������� "����" ��������������� ���
	//������ ��������� �������� ������ ������� 3 �������
	Set_pen(dc, 0, 255, 0, 3); //������� ����
	Line(dc, oct8.transVer[0].x, oct8.transVer[0].y, oct8.transVer[4].x, oct8.transVer[4].y);
	Set_pen(dc, 0, 0, 255, 3); //����� ����
	Line(dc, oct8.transVer[1].x, oct8.transVer[1].y, oct8.transVer[5].x, oct8.transVer[5].y);
	Set_pen(dc, 255, 255, 0, 3); //������ ����
	Line(dc, oct8.transVer[2].x, oct8.transVer[2].y, oct8.transVer[6].x, oct8.transVer[6].y);
	Set_pen(dc, 255, 0, 255, 3); //��������� ����
	Line(dc, oct8.transVer[3].x, oct8.transVer[3].y, oct8.transVer[7].x, oct8.transVer[7].y);
}

void AnimFigure()
{
	int key = 1, gr = 15, dx = 30;
	//��� ������� Esc - 27
	//��� ������� -> - 224
	//���� ��������, ���� �� ������ ������� Esc
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

