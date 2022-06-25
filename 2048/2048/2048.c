// 2048.c : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#define _CRT_SECURE_NO_WARNINGS
#include"2048.h"
//游戏实现
Game()
{
	key = 1;
	int board[4][4]={0,0,0,0,//定义初始状态
		             0,0,0,0,
	                 0,0,0,0,
	                 0,0,0,0};
	game2048(board);//进入游戏
}
	
//游戏入口
text()
{
	int input = 1;
	Menu();
	//do
	//{
		scanf_s("%d", &input);
		getchar();//读取缓冲
		switch (input)
		{
			case 1:Game();break;
			case 0:break;
			case 2:break;
			default:printf("开始输入错误");break;
		}
	//} while (input);
}
int main()
{
	text();
	return 0;
}