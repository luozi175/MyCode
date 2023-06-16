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

#define music_background 0  //音乐功能
#define music_over 1
#define music_score 2
#define music_title 3

//----------------------------以下全局变量是需要在初始化函数初始化的------------------------------------

//选择名字封装
struct name {
	char name[32];    
	bool isSelect;//是否被选 0没有 1有if(isSelect){p1.name=name}
};
name playername[6];

//玩家结构体
struct player {
	int num;      //玩家是几号（ 初始化为0，1，2）
	bool exist;   //玩家是否存在(玩家是否还可继续游戏)（ 初始化为ture）
	int playerPlace;//玩家在哪个建筑上（ 初始化为0）
	int x;
	int y;          //玩家打印坐标
	int money;      //玩家金钱
	char name[32];  //玩家名字（ 初始化为0）
	int colour;     //玩家颜色打印出来的颜色
	int sleep;      //玩家是否休眠大小即回合数（ 初始化为0）
	int sleepcard;  //睡眠卡数量（ 初始化为0）
	int obsCard;    //障碍卡数（ 初始化为0）
};

player playerNum[3];//玩家最多个数3
player *playermid;  //全局指针，一直指向当前移动的玩家

//建筑种类枚举
typedef enum {
	fangzi,//0房子地区
	jianyu,//1监狱地区
	feiji, //2飞机地区
	
}landType;
//建筑物结构体
struct land {                         
	landType type;  //建筑物种类(用枚举封装)
	int cost;       //购买所需花费
	int passcost;   //过路费
	int belong;     //归属与哪个玩家（初始化为-1）
	char name[64];  //建筑名字
	bool isObs;     //为真时表示有障碍
};

land landNum[24];//建筑个数24  playerplace=3  ==  landNum[3]

int playingSum;  //游玩总人数
int sum;         //游戏掷骰子回合
int winSore;     //游戏胜利金钱条件
int endSum;      //结束回合数

//------------------------------以上全局变量是需要在初始化函数初始化的---------------------------------------

int y_line = 20;//全局变量		消息输出行位置	默认值为20，范围20到29
bool isReadFile; //判断是否读档
int tmid;///////////////读档要用的
//建筑数量和大小
int w, h;               //h和w是地区长和宽
int wallWSum, wallHSum ;//wallWSum=宽上建筑数, wallHSum=长上建筑数

const wchar_t musicPath[4][128] = {  //音乐文件的路径
	L"./background.wav",  //0
	L"./over.wav",  //1
	L"./金币音效2.wav",  //2
	L"./title音乐.wav"    //3
};

extern int isMusic = 1;//是否播放音乐 0表示不播放, 1表示播放


//游戏内函数--------------------------------------------------------------------
//游戏开始，结束
int readFile();       //读档
void keepFile();      //存档
void gameContinue();  //进入读档
void gameBeginPer();  //游戏前准备
void gameBagin();     //开始游戏函数
void playerMoveEnd(); //玩家移动终点交互
void isWin01();         //游戏结束判定1
void isWin02();         //游戏结束判定2
//游戏过程
void selectDice();    //选择使用骰子Dice
void selectProp();    //选择使用道具
void selectProp1();   //选择使用道具休眠卡
void selectProp2();   //选择使用道具路障卡
void prntfplayerS();  //玩家选项
char gameBreak();     //选择退出游戏
void playerNumSclect();//选择角色名字
//游戏打印
void printf01();    //打印初始玩家位置
void title();       //打印初始标题页面
void menu1();       //打印菜单显示
void allLand();     //打印所有地区 
void wall(int ,int);//打印地区
void inti();        //初始化数值

//小满
void infDisplayLine();//实现循环打印事件
void playPassCostM();//打印过路扣钱事件
void playerSleepM();//打印睡眠事件
void playerMeetAbsM();//打印玩家碰到障碍事件
void playerCostM();//打印玩家购买事件
void playerMoveEndJai();//打印终点事件
void playerMoveEndfeiji();//打印飞机场事件
void playerMoveTouzi(int x);//打印骰子事件
void printfselectDice();//打印玩家选择道具事件
//小王
void printfAllHouse();    //打印所有房子
void printfPlayer();      //玩家信息打印
void printfPlayerMove();  //玩家位置移动刷新
//小单
void printfsum();//角色数量界面
//小曾
void gameSet();  //进入设置函数
//小滕
void BUILDING(); //初始化
//协助游戏内函数功能实现类函数---------------------------------------------------
void setPrintColor(int color);         //颜色
void clear(int x, int y, int w, int h);//清理指定矩形区域(从(x,y)到(x+w,y+h)的矩形
void gotoXY(int x, int y);             //传入坐标,将光标移动到指定坐标

void color(int x);              //颜色设置
void SetPos(int y, int x);      //标点位置设置
void screen_size(int a, int b); //设置窗口大小

int stopMusic(int choose);      //停止播放指定音乐
int playMusic(int choose);      //播放指定音乐
void HideCursor();              //隐藏光标