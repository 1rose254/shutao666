#include<stdio.h>
#include<easyx.h>
int main()
{
	initgraph(800,600);
	setbkcolor(RGB(169, 92, 10));
	cleardevice();
	setfillcolor(RGB(130, 69, 4));
	solidcircle(200, 130, 90);
	solidcircle(600, 130, 90);
	setfillcolor(RGB(255, 178, 50));
	solidcircle(200, 120, 90);
	solidcircle(600, 120, 90);
	setfillcolor(RGB(130, 200, 32));
	HRGN leftear=CreateEllipticRgn(110, 30, 290, 210);
	HRGN rightear=CreateEllipticRgn(510, 30, 690, 210);
	HRGN ear = CreateRectRgn(0, 0, 0,0);
	CombineRgn(ear, leftear, rightear, RGN_OR);
	setcliprgn(ear);
	setfillcolor(RGB(243, 154, 2));
	solidcircle(200, 130, 90);
	solidcircle(600, 130, 90);
	setfillcolor(RGB(255, 178, 50));
	solidcircle(200, 210, 90);
	solidcircle(600, 210, 90);
	DeleteObject(ear);
	DeleteObject(leftear);
	DeleteObject(rightear);
	setcliprgn(NULL);
	setfillcolor(RGB(255, 178, 50));
	solidcircle(400, 300, 250);
	HRGN head = CreateEllipticRgn(150, 50, 650, 550);
	setcliprgn(head);
	setfillcolor(RGB(243, 152, 2));
	solidcircle(400, 320, 250);
	DeleteObject(head);
	setcliprgn(NULL);
	setfillcolor(RGB(51, 34, 8));
	solidcircle(275, 300, 25);
	solidcircle(525, 300, 25);
	setfillcolor(RGB(130, 69, 4));
	solidellipse(310, 385, 490, 485);
	setfillcolor(WHITE);
	solidellipse(310, 380, 490, 480);
	setfillcolor(RGB(51, 34, 8));
	solidcircle(400, 420, 15);
	setlinestyle(PS_SOLID, 5);
	setlinecolor(RGB(51, 34, 8));
	line(400, 420, 370, 450);
	line(400, 420, 430, 450);

	getchar();
	closegraph();
	return 0;
}