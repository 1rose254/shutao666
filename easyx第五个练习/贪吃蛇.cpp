#include<stdio.h>
#include<conio.h>//�������ͷ�ļ�����ʹ��_kbhit()��_getch()��ʵ�ּ���ʵʱ����
#include<easyx.h>//�������ͷ�ļ�����ʹ��easyxͼ�ο�
#include<time.h>//�������ͷ�ļ�����ʹ��time����������
#define NODE_WIDTH 40
//�ߵĽڵ�����
typedef struct {
	int x;
	int y;
}node;
//ö�ٳ������ж��ߵ����������ƶ�
enum direction
{
	eup,
	edown,
	eleft,
	eright
};
//����һ���ͼĻ��
void paintmap()
{
	for (int x = 0; x < 800; x += NODE_WIDTH) {
		line(x, 0, x, 600);
	}
	for (int y = 0; y < 600; y += NODE_WIDTH) {
		line(0, y, 800, y);
	}
}
//������
void paintsnake(node* snake, int n)
{
	int z, s, y, x;
	for (int i = 0; i < n; i++) {
		z = snake[i].x * NODE_WIDTH;
		s = snake[i].y * NODE_WIDTH;
		y = (snake[i].x + 1) * NODE_WIDTH;
		x = (snake[i].y + 1) * NODE_WIDTH;
		solidrectangle(z, s, y, x);
	}
}
//�ߵ��ƶ�
node snakemove(node* snake, int length, int direction) {
	node tail = snake[length - 1];
	for (int i = length - 1 ; i > 0; i--) {
		snake[i] = snake[i - 1];
	}
	node newhead;
	newhead = snake[0];
	if (direction == eup) {
		newhead.y--;
	}
	else if (direction == edown) {
		newhead.y++;
	}
	else if (direction == eleft) {
		newhead.x--;
	}
	else {
		newhead.x++;
	}
	snake[0] = newhead;
	return tail;
}
//����wasd�ƶ���ʵ���ߵ��ƶ�
void changedirection(enum direction* pd) {
	if (_kbhit() != 0) {
		char c = _getch();
		switch (c)
		{
		case 'w':
			if (*pd != edown)
				*pd = eup;
			break;
		case 's':
			if (*pd != eup)
				*pd = edown;
			break;
		case 'a':
			if (*pd != eright)
				*pd = eleft;
			break;
		case 'd':
			if (*pd != eleft)
				*pd = eright;
			break;
		}
	}
}
//����ʳ��
void paintfood(node food) {
	int z, s, y, x;
	z = food.x * NODE_WIDTH;
	s = food.y * NODE_WIDTH;
	y = (food.x + 1) * NODE_WIDTH;
	x = (food.y + 1) * NODE_WIDTH;
	setfillcolor(YELLOW);
	solidrectangle(z, s, y, x);
	setfillcolor(WHITE);
}
//��Ļ�����������ʳ��
node createfood(node* snake, int length) {
	node food;
	while (1) {
		food.x = rand() % (800 / NODE_WIDTH);
		food.y = rand() % (600 / NODE_WIDTH);
		int i;
		for (i = 0; i < length; i++) {
			if (snake[i].x == food.x && snake[i].y == food.y) {
				break;
			}
		}
		if (i < length)
			continue;
		else
			break;
	}
	return food;
}
//�ж���Ϸ�Ƿ����
bool gameover(node* snake, int length) {
	if (snake[0].x < 0 || snake[0].x>800 / NODE_WIDTH)
		return true;
	if (snake[0].y < 0 || snake[0].y>600 / NODE_WIDTH)
		return true;
	for (int i = 1; i < length; i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			return true;
	}
	return false;
}
//��Ϸ������������Ϸ����
void reset(node* snake, int* plength, enum direction* d,int num) {
	snake[0] = node{ 5,7 };
	snake[1] = node{ 4,7 };
	snake[2] = node{ 3,7 };
	snake[3] = node{ 2,7 };
	snake[4] = node{ 1,7 };
	*plength = 5;
	*d = eright;
	num = 0;
}
//������Ϸ�Ѷ�ÿ��������Ѷ�����
int adjustnandu(int num) {
	if (num == 1)
		return 400;
	if (num == 2)
		return 200;
	if (num == 3)
		return 100;
	if (num == 4)
		return 50;
	/*if (num == 5)
		return 100;*/
	return 50;


}
int main()
{
	//����Ļ��
	initgraph(800, 600);
	setbkcolor(BLACK);//RGB(164, 225, 202)
	cleardevice();
	//��Ϸ��ʼʱ�ߵ�λ��
	node snake[100] = { {5,7},{4,7},{3,7},{2,7},{1,7} };
	int length = 5;
	//��Ϸ��ʼʱ�ߵ��ƶ�����
	enum direction d = eright;
	srand(unsigned int(time(NULL)));
	node food = createfood(snake, length);
	int num = 0;
	while (1) {
		cleardevice();
		paintmap();
		paintsnake(snake, length);
				paintfood(food);
				Sleep(num);
				changedirection(&d);
				//��ÿ���ߵ��ƶ����β�ڵ�洢����
				node lasttail = snakemove(snake, length, d);
				if (snake[0].x == food.x && snake[0].y == food.y) {
					if (length < 100) {
						//����߳Ե���ʳ���֮ǰ�洢��β�ڵ�����ߵ�ĩβ
						snake[length] = lasttail;
						length++;
						num = adjustnandu(length / 5);
					}
					//������ʳ��
					food = createfood(snake, length);
				}
				//�����Ϸ���ˣ�������Ϸ����
				if (gameover(snake, length) == true) {
					reset(snake, &length, &d,num);
					food = createfood(snake, length);
				}
			}

	getchar();
	closegraph();
	return 0;
}