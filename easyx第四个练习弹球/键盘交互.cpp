#include<stdio.h>
#include<easyx.h>
#include<conio.h>
int main()
{
	initgraph(800, 600);
	setorigin(400, 300);
	setaspectratio(1, -1);
	setbkcolor(RGB(164, 225, 202));
	cleardevice();
	setfillcolor(WHITE);
	int x = -400, y = 0;
	int dx = 5, dy = 0;
	solidcircle(x, y, 50);
	while (1) {
		cleardevice();
		solidcircle(x, y, 50);
		x += dx;
		y += dy;
		Sleep(40);
		if(_kbhit()!=0){
		char c = _getch();
			switch (c) {
			case 'w':
				dx = 0;
				dy = 5;
				break;
			case 's':
				dx = 0;
				dy = -5;
				break;
			case 'a':
				dx = -5;
				dy = 0;
				break;
			case 'd':
				dx = 5;
				dy = 0;
				break;
			}
		}
	}
	getchar();
	closegraph();
	return 0;
}