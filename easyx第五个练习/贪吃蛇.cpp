#include<stdio.h>
#include<conio.h>//引用这个头文件可以使用_kbhit()和_getch()来实现键盘实时交互
#include<easyx.h>//引用这个头文件可以使用easyx图形库
#include<time.h>//引用这个头文件可以使用time函数来生成
#define NODE_WIDTH 40
//蛇的节点坐标
typedef struct {
	int x;
	int y;
}node;
//枚举常量来判断蛇的上下左右移动
enum direction
{
	eup,
	edown,
	eleft,
	eright
};
//绘制一块地图幕布
void paintmap()
{
	for (int x = 0; x < 800; x += NODE_WIDTH) {
		line(x, 0, x, 600);
	}
	for (int y = 0; y < 600; y += NODE_WIDTH) {
		line(0, y, 800, y);
	}
}
//绘制蛇
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
//蛇的移动
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
//键盘wasd移动来实现蛇的移动
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
//绘制食物
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
//在幕布上随机生成食物
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
//判断游戏是否结束
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
//游戏结束，重置游戏数据
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
//调整游戏难度每吃五个就难度提升
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
	//设置幕布
	initgraph(800, 600);
	setbkcolor(BLACK);//RGB(164, 225, 202)
	cleardevice();
	//游戏开始时蛇的位置
	node snake[100] = { {5,7},{4,7},{3,7},{2,7},{1,7} };
	int length = 5;
	//游戏开始时蛇的移动方向
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
				//讲每次蛇的移动后的尾节点存储下来
				node lasttail = snakemove(snake, length, d);
				if (snake[0].x == food.x && snake[0].y == food.y) {
					if (length < 100) {
						//如果蛇吃到了食物，把之前存储的尾节点加在蛇的末尾
						snake[length] = lasttail;
						length++;
						num = adjustnandu(length / 5);
					}
					//再生成食物
					food = createfood(snake, length);
				}
				//如果游戏输了，重置游戏数据
				if (gameover(snake, length) == true) {
					reset(snake, &length, &d,num);
					food = createfood(snake, length);
				}
			}

	getchar();
	closegraph();
	return 0;
}