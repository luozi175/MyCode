#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define WIN 2048    //ʤ������,�ﵽ��ʤ��


int sum;   //�ܷ�
int key;   //����ʶ������ʱҪ��Ҫ��ӡ���Ż���Ϸ���飨��shuiji�����У�


//��������
void Menu();
void Printf(int board[4][4]);   //��ӡ��ʾ
void shuiji(int board[4][4]);   //�������2
void move_d(int board[4][4]);   //����
void move_a(int board[4][4]);   //����
void move_s(int board[4][4]);   //����
void move_w(int board[4][4]);   //����
void game2048(int board[4][4]); //��Ϸ���
int panduan(int board[4][4]);   //�ж���û����
void clear(int x, int y, int w, int h);//����ָ����������(��(x,y)��(x+w,y+h)�ľ���

void gotoXY(int x, int y);// ��������, ������ƶ���ָ������
void SetPos(int y, int x);//���ˢ��