#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define WIN 2048    //胜利数字,达到后胜利


int sum;   //总分
int key;   //用来识别当满格时要不要打印，优化游戏体验（在shuiji函数中）


//函数声明
void Menu();
void Printf(int board[4][4]);   //打印显示
void shuiji(int board[4][4]);   //随机出现2
void move_d(int board[4][4]);   //右移
void move_a(int board[4][4]);   //左移
void move_s(int board[4][4]);   //下移
void move_w(int board[4][4]);   //上移
void game2048(int board[4][4]); //游戏入口
int panduan(int board[4][4]);   //判断有没有输
void clear(int x, int y, int w, int h);//清理指定矩形区域(从(x,y)到(x+w,y+h)的矩形

void gotoXY(int x, int y);// 传入坐标, 将光标移动到指定坐标
void SetPos(int y, int x);//标点刷新