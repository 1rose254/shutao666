#include<stdio.h>
#include<easyx.h>
int main()
{
	initgraph(800,600);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(RGB(232, 235, 240));
	solidroundrect(100, 50, 700, 450, 20, 20);
	setfillcolor(RGB(71, 78, 94));
	solidrectangle(100, 390, 700, 410);
	solidroundrect(100, 50, 700, 410, 20, 20);
	setfillcolor(RGB(115, 199, 235));
	solidrectangle(120, 70, 680, 390);
	setfillcolor(RGB(232, 235, 240));
	solidcircle(400, 60, 5);
	setfillcolor(RGB(71, 78, 94));
	solidcircle(400, 118, 12);
	setfillcolor(RGB(218, 219, 224));
	solidellipse(275, 515, 525, 545);
	setfillcolor(RGB(232, 235, 240));
	POINT dixin[4] = { {345,450},{455,450},{475,530},{325,530} };
	solidpolygon(dixin, 4);
	setfillcolor(RGB(218, 219, 224));
	POINT yy[4] = { {345,450},{455,450},{460,470},{340,470} };
	solidpolygon(yy, 4);


	getchar();
	closegraph();
	return 0;
}
