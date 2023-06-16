#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
#include<errno.h>
#include <windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<conio.h>
#include<time.h>

#define music_background 0  //���ֹ���
#define music_over 1
#define music_score 2
#define music_title 3

//----------------------------����ȫ�ֱ�������Ҫ�ڳ�ʼ��������ʼ����------------------------------------

//ѡ�����ַ�װ
struct name {
	char name[32];    
	bool isSelect;//�Ƿ�ѡ 0û�� 1��if(isSelect){p1.name=name}
};
name playername[6];

//��ҽṹ��
struct player {
	int num;      //����Ǽ��ţ� ��ʼ��Ϊ0��1��2��
	bool exist;   //����Ƿ����(����Ƿ񻹿ɼ�����Ϸ)�� ��ʼ��Ϊture��
	int playerPlace;//������ĸ������ϣ� ��ʼ��Ϊ0��
	int x;
	int y;          //��Ҵ�ӡ����
	int money;      //��ҽ�Ǯ
	char name[32];  //������֣� ��ʼ��Ϊ0��
	int colour;     //�����ɫ��ӡ��������ɫ
	int sleep;      //����Ƿ����ߴ�С���غ����� ��ʼ��Ϊ0��
	int sleepcard;  //˯�߿������� ��ʼ��Ϊ0��
	int obsCard;    //�ϰ������� ��ʼ��Ϊ0��
};

player playerNum[3];//���������3
player *playermid;  //ȫ��ָ�룬һֱָ��ǰ�ƶ������

//��������ö��
typedef enum {
	fangzi,//0���ӵ���
	jianyu,//1��������
	feiji, //2�ɻ�����
	
}landType;
//������ṹ��
struct land {                         
	landType type;  //����������(��ö�ٷ�װ)
	int cost;       //�������軨��
	int passcost;   //��·��
	int belong;     //�������ĸ���ң���ʼ��Ϊ-1��
	char name[64];  //��������
	bool isObs;     //Ϊ��ʱ��ʾ���ϰ�
};

land landNum[24];//��������24  playerplace=3  ==  landNum[3]

int playingSum;  //����������
int sum;         //��Ϸ�����ӻغ�
int winSore;     //��Ϸʤ����Ǯ����
int endSum;      //�����غ���

//------------------------------����ȫ�ֱ�������Ҫ�ڳ�ʼ��������ʼ����---------------------------------------

int y_line = 20;//ȫ�ֱ���		��Ϣ�����λ��	Ĭ��ֵΪ20����Χ20��29
bool isReadFile; //�ж��Ƿ����
int tmid;///////////////����Ҫ�õ�
//���������ʹ�С
int w, h;               //h��w�ǵ������Ϳ�
int wallWSum, wallHSum ;//wallWSum=���Ͻ�����, wallHSum=���Ͻ�����

const wchar_t musicPath[4][128] = {  //�����ļ���·��
	L"./background.wav",  //0
	L"./over.wav",  //1
	L"./�����Ч2.wav",  //2
	L"./title����.wav"    //3
};

extern int isMusic = 1;//�Ƿ񲥷����� 0��ʾ������, 1��ʾ����


//��Ϸ�ں���--------------------------------------------------------------------
//��Ϸ��ʼ������
int readFile();       //����
void keepFile();      //�浵
void gameContinue();  //�������
void gameBeginPer();  //��Ϸǰ׼��
void gameBagin();     //��ʼ��Ϸ����
void playerMoveEnd(); //����ƶ��յ㽻��
void isWin01();         //��Ϸ�����ж�1
void isWin02();         //��Ϸ�����ж�2
//��Ϸ����
void selectDice();    //ѡ��ʹ������Dice
void selectProp();    //ѡ��ʹ�õ���
void selectProp1();   //ѡ��ʹ�õ������߿�
void selectProp2();   //ѡ��ʹ�õ���·�Ͽ�
void prntfplayerS();  //���ѡ��
char gameBreak();     //ѡ���˳���Ϸ
void playerNumSclect();//ѡ���ɫ����
//��Ϸ��ӡ
void printf01();    //��ӡ��ʼ���λ��
void title();       //��ӡ��ʼ����ҳ��
void menu1();       //��ӡ�˵���ʾ
void allLand();     //��ӡ���е��� 
void wall(int ,int);//��ӡ����
void inti();        //��ʼ����ֵ

//С��
void infDisplayLine();//ʵ��ѭ����ӡ�¼�
void playPassCostM();//��ӡ��·��Ǯ�¼�
void playerSleepM();//��ӡ˯���¼�
void playerMeetAbsM();//��ӡ��������ϰ��¼�
void playerCostM();//��ӡ��ҹ����¼�
void playerMoveEndJai();//��ӡ�յ��¼�
void playerMoveEndfeiji();//��ӡ�ɻ����¼�
void playerMoveTouzi(int x);//��ӡ�����¼�
void printfselectDice();//��ӡ���ѡ������¼�
//С��
void printfAllHouse();    //��ӡ���з���
void printfPlayer();      //�����Ϣ��ӡ
void printfPlayerMove();  //���λ���ƶ�ˢ��
//С��
void printfsum();//��ɫ��������
//С��
void gameSet();  //�������ú���
//С��
void BUILDING(); //��ʼ��
//Э����Ϸ�ں�������ʵ���ຯ��---------------------------------------------------
void setPrintColor(int color);         //��ɫ
void clear(int x, int y, int w, int h);//����ָ����������(��(x,y)��(x+w,y+h)�ľ���
void gotoXY(int x, int y);             //��������,������ƶ���ָ������

void color(int x);              //��ɫ����
void SetPos(int y, int x);      //���λ������
void screen_size(int a, int b); //���ô��ڴ�С

int stopMusic(int choose);      //ֹͣ����ָ������
int playMusic(int choose);      //����ָ������
void HideCursor();              //���ع��