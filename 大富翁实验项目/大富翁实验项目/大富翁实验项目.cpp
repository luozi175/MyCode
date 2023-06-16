// 大富翁实验项目.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include"my.h"

//此处是拿来测试代码的函数
void text() {
	HideCursor();//隐藏光标美化界面
	BUILDING();  //初始化
	title();     //标题
	menu1();     //正式游戏开始菜单
}
//初始化函数简单初始化一些全局变量
void inti() {
	int i;
	sum = 0;
	playingSum = 3;
	srand(time(NULL));
	w = 17, h = 6;               //h和w是长和宽
	wallWSum = 8, wallHSum = 6;  //wallHSum和wallWSum是长和宽上的墙壁个数
	screen_size(w*wallWSum+2,h*wallHSum+2);//屏幕大小
	isReadFile=0;                //判断是否读档
	//初始化角色
	playerNum[0] = { 0,1,0,2,4,20000,"",2,0,0,0 };   
	playerNum[1] = { 1,1,0,6,4,20000,"",3,0 ,0,0};
	playerNum[2] = { 2,1,0,10,4,20000,"",4,0 ,0,0};
	text();
}
int main()
{
	inti();
}
void BUILDING()
{
	;
	int citycost[24] = { 200,300,400,450,500,560,600,0,650,700,740,810,0,860,900,100,0,1050,1200,1290,1340,0,1400,1420 };
    int citypasscost[24] = { 300,450,500,520,570,600,650,0,680,780,800,890,0,1000,1200,1340,0,1440,1520,1590,1690,0,1770,1800 };
	char cityname[24][24] = { "曼谷","台北", "珀斯","基辅","苏州","华沙","雅典","监狱",
		                      "深圳","香港","大阪","柏林",
							  "飞机场","悉尼","迪拜","费城","监狱","伦敦","东京","巴黎",
							  "上海","飞机场","北京","纽约"};
	int i;
	for (i = 0; i < 24; i++)
	{
		landNum[i].type = fangzi;
		landNum[i].belong = -1;
		landNum[i].cost = citycost[i];
		landNum[i].passcost = citypasscost[i];
		strcpy_s(landNum[i].name, &cityname[i][0]);
	}
	landNum[7].type = jianyu;
	landNum[12].type = feiji;
	landNum[16].type = jianyu;
	landNum[21].type = feiji;
	 winSore = 50000;  //游戏胜利金钱条件
	 endSum = 30;      //结束回合数
}
//打印所有墙壁
void allLand() {
	SetPos(0,0);
	clear(0, 0, w * wallWSum, h * wallHSum);
	int i=0, j=0,a=1;
	for (i = 0, a = 1;a <= wallWSum;a++) {
		wall(i, j);
		j = j + w;
	}
	for (i = h,j=0, a = 2;a < wallHSum;a++) {
		wall(i, j);
		i = i + h;
	}
	for (i = h, j = w*(wallWSum-1), a = 1;a < wallHSum;a++) {
		wall(i, j);
		i = i + h;
	}
	for (i = h*(wallHSum-1),j=0, a = 1;a <= wallWSum;a++) {
		wall(i, j);
		j = j + w;
	}
	SetPos((h * wallHSum)/2-1, w);
	for (i = 1;i < w * (wallWSum - 2);i++)putchar('-');
}
//打印墙壁
void wall(int x,int  y) {
	int i;

	SetPos(x, y);
	for (i = 1;i <= w;i++)putchar('%');
	for (i = 1;i <= h-2;i++) {
		SetPos(i + x, y );
		putchar('%');
		SetPos(i + x, y + w-1);
		putchar('%');
	}
	SetPos(h+x-1, y);
	for (i = 1;i <= w;i++)putchar('%');
}
void setPrintColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//菜单显示
void menu1() {
	clear(0, 0, w * wallWSum, h * wallHSum);
	int userChoose = 0;
	while (1) {
		gotoXY((w * wallWSum) / 2 - 14, (h * wallHSum) / 2 - 15);
		printf("大     富     翁");

		if (userChoose == 0) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 12);
		printf("开始游戏");
		if (userChoose == 0) setPrintColor(0x0f);

		if (userChoose == 1) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 9);
		printf("继续游戏");
		if (userChoose == 1) setPrintColor(0x0f);

		if (userChoose == 2) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 6);
		printf("游戏设置"); 
		if (userChoose == 2) setPrintColor(0x0f);

		if (userChoose == 3) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 3);
		printf("退出游戏");
		if (userChoose == 3) setPrintColor(0x0f);


		char input = _getch();
		switch (input) {
		case 'w':
			userChoose -= 1;
			if (userChoose == -1) userChoose = 3;
			break;
		case 's':
			userChoose = (userChoose + 1) % 4;
			break;
		case '\r':
			clear(0, 0, w * wallWSum, h * wallHSum);
			switch (userChoose) {
			case 0:
				gameBeginPer();
				exit(0);
				break;
			case 1:
				isReadFile = 1;
				gameContinue();
				exit(0);
				break;
			case 2:
				gameSet();
				exit(0);
				break;
			case 3:
				
				exit(0);
				break;
			}
			clear(0, 0, w * wallWSum, h * wallHSum);
			break;
		}
	}
}

//读档
void gameContinue() {
	gameBagin();
		
}


//选择角色
void  playerNumSclect(){
	clear(0, 0, w * wallWSum, h * wallHSum);
	strcpy_s(playername[0].name, "小曾");
	strcpy_s(playername[1].name, "小单");
	strcpy_s(playername[2].name, "小满");
	strcpy_s(playername[3].name, "小滕");
	strcpy_s(playername[4].name, "小王");
	strcpy_s(playername[5].name, "小罗");
	int i,j=0;
	for (i = 0;i < 6;i++) {
		playername[i].isSelect = 0;
	}
	int userChoose = 0;
	while (1) {
		if (j == playingSum) {
			return;
		}
		gotoXY((w * wallWSum) / 2 - 12, (h * wallHSum) / 2 - 15);
		printf("名称选择                      ");

		if (userChoose == 0) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 12);
		printf("小曾");
		if (userChoose == 0) setPrintColor(0x0f);

		if (userChoose == 1) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 9);
		printf("小单");
		if (userChoose == 1) setPrintColor(0x0f);

		if (userChoose == 2) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 6);
		printf("小满");
		if (userChoose == 2) setPrintColor(0x0f);

		if (userChoose == 3) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 3);
		printf("小滕");
		if (userChoose == 3) setPrintColor(0x0f);

		if (userChoose == 4) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 );
		printf("小王");
		if (userChoose == 4) setPrintColor(0x0f);

		if (userChoose == 5) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 + 3);
		printf("小罗");
		if (userChoose == 5) setPrintColor(0x0f);
		char input = _getch();
		switch (input) {
		case 'w':
			userChoose -= 1;
			if (userChoose == -1) userChoose = 6;
			break;
		case 's':
			userChoose = (userChoose + 1) % 6;
			break;
		case '\r':
			switch (userChoose) {
			case 0:
				gotoXY((w * wallWSum) / 2 - 15, (h * wallHSum) / 2 - 12);
				if (playername[0].isSelect != 1)
				{
					strcpy_s(playerNum[j].name, playername[0].name);
					color(playerNum[j].colour);
					printf("p%d", j+1);
					j++;
					setPrintColor(0x0f);
					playername[0].isSelect = 1;
				}
				break;
			case 1:
				gotoXY((w * wallWSum) / 2 - 15, (h * wallHSum) / 2 - 9);
				if (playername[1].isSelect != 1)
				{
					strcpy_s(playerNum[j].name, playername[1].name);
					color(playerNum[j].colour);
					printf("p%d", j+1);
					j++;
					setPrintColor(0x0f);
					playername[0].isSelect = 1;
				}
				
				break;
			case 2:
				gotoXY((w * wallWSum) / 2 - 15, (h * wallHSum) / 2 -6);
				if (playername[2].isSelect != 1)
				{
					strcpy_s(playerNum[j].name, playername[2].name);//strcpy_s(playerNum[j].name, playername[2].name);
					color(playerNum[j].colour);
					printf("p%d", j+1);
					j++;
					setPrintColor(0x0f);
					playername[0].isSelect = 1;
				}
				break;
			case 3:
				gotoXY((w * wallWSum) / 2 - 15, (h * wallHSum) / 2 - 3);
				if (playername[3].isSelect != 1)
				{
					strcpy_s(playerNum[j].name, playername[3].name);
					color(playerNum[j].colour);
					printf("p%d", j+1);
					j++;
					setPrintColor(0x0f);
					playername[0].isSelect = 1;
				}
				break;
			case 4:
				gotoXY((w * wallWSum) / 2 - 15, (h * wallHSum) / 2 );
				if (playername[4].isSelect != 1)
				{
					strcpy_s(playerNum[j].name, playername[4].name);
					color(playerNum[j].colour);
					printf("p%d", j+1);
					j++;
					setPrintColor(0x0f);
					playername[0].isSelect = 1;
				}
				break;
			case 5:
				gotoXY((w * wallWSum) / 2 - 15, (h * wallHSum) / 2 + 3 );
				if (playername[5].isSelect != 1)
				{
					strcpy_s(playerNum[j].name, playername[5].name);
					color(playerNum[j].colour);
					printf("p%d", j+1);
					j++;
					setPrintColor(0x0f);
					playername[0].isSelect = 1;
				}
				break;
			}
			//clear(0, 0, w * wallWSum, h * wallHSum);
			break;
		}
	}
}

//选择使用道具休眠卡
void selectProp1()
{
	int x1;
	if (playermid->sleepcard) {
		while(1) {
			x1 = rand() % playingSum;
			if (x1 != playermid->num) {
				playerNum[x1].sleep++;
				playermid->sleepcard--;
				infDisplayLine();
				setPrintColor(playermid->colour);
				printf("[%s]休眠了[%c]！", playermid->name,playerNum[x1].name);
				setPrintColor(0);
				return;
			}
		}
	}
	else {
		infDisplayLine();
		setPrintColor(playermid->colour);
		printf("[%s]没有休眠卡！", playermid->name);
		setPrintColor(0);
	}
}
//选择使用道具路障卡
void selectProp2()
{
	
	if (playermid->obsCard) {
		landNum[playermid->playerPlace].isObs = true;
		playermid->obsCard--;
		infDisplayLine();
		setPrintColor(playermid->colour);
		printf("[%s]设置了路障！", playermid->name);
		setPrintColor(0);
		return;
	}
	else {
		infDisplayLine();
		setPrintColor(playermid->colour);
		printf("[%s]没有障碍卡！", playermid->name);
		setPrintColor(0);
		return;
	}
}
//选择使用道具
void selectProp() {
	char input;
	color(playermid->colour);
	clear((wallWSum / 2 + 1) * w + 1, h + 1, 2 * w, 2 * h - 1);//选项区清除
	SetPos(h, (wallWSum / 2 + 1) * w);
	printf("1.休眠卡");
	SetPos(h + 1, (wallWSum / 2 + 1) * w);
	printf("2.路障卡");
	SetPos(h + 2, (wallWSum / 2 + 1) * w);
	printf("3.返回");
	while (1) {
		input = _getch();
		switch (input) {
		case '1':   selectProp1();break;
		case '2':   selectProp2();break;
		case '3': return ;
		default: break;
		}
	}
}

//玩家移动终点交互
void playerMoveEnd() {
	
	//破产判断
	if (playermid->money<=0) {
			infDisplayLine();
			setPrintColor(playermid->colour);
			printf("[%s]破产了！！！！！", playermid->name);
			setPrintColor(0);
			playermid->exist = false;
			return;
		}
	//房子判断
	if (landNum[playermid->playerPlace].type==fangzi&& landNum[playermid->playerPlace].belong==-1) {
		char input;
		color(playermid->colour);
		clear((wallWSum / 2 + 1) * w + 1, h + 1, 2 * w, 2 * h - 1);//选项区清除
		SetPos(h, (wallWSum / 2 + 1) * w);
		printf("1.购买");
		SetPos(h + 1, (wallWSum / 2 + 1) * w);
		printf("2.跳过");
		while (1) {
			input = _getch();
			switch (input) {
			case '1':
				landNum[playermid->playerPlace].belong = playermid->num;
				playermid->money -=  landNum[playermid->playerPlace].cost;
				printfAllHouse();
				      playerCostM();
					  
				      return;
			case '2': return;
			default: break;
			}
		}
	}
	else
		if (landNum[playermid->playerPlace].type == jianyu)
		{
			playerMoveEndJai();
			playermid->sleep++;
			return;
		}
		else
			if (landNum[playermid->playerPlace].type == feiji) {
				playerMoveEndfeiji();
				selectDice();
				return;
			}


				
}
void infDisplayLine() {
	if (y_line >= 20 && y_line <= 29) {
		clear(19, y_line, 90, 1);//信息块清除内容，最后的参数w可选
		gotoXY(19, y_line);
		y_line++;
	}
	else {
		y_line = 20;
		clear(19, y_line, 40, 10);//w=9清理消息区域，w=2清理要打印行区域及下一行区域
		gotoXY(19, y_line);
		y_line++;
	}
}


//选择使用骰子
void selectDice() {
	int x1, x2,summove;
	x1 = rand()%6+1;
	x2 = rand()%6+1;
	summove = x1 + x2;

	//打印骰子事件
	printfselectDice();
	playerMoveTouzi(summove);

	//玩家移动
	while (summove) {
		
		printfPlayerMove();//玩家名字移动一次
		 if (landNum[playermid->playerPlace].belong != playermid->num && landNum[playermid->playerPlace].belong !=-1)
		 {
			 playerNum[landNum[playermid->playerPlace].belong].money += landNum[playermid->playerPlace].passcost;
			 playermid->money -= landNum[playermid->playerPlace].passcost;
			 playPassCostM();//玩家移动中的扣钱打印
		 }
		 if (landNum[playermid->playerPlace].isObs) { playerMeetAbsM(); return; }
		summove--;
	}
	//终点事件
	playerMoveEnd();
}
//玩家选项
void prntfplayerS() {
	
	color(playermid->colour); //玩家颜色
	clear((wallWSum / 2 + 1) * w+1, h+1, 2 * w, 2 * h-1);//选项区清除
	SetPos(h, (wallWSum / 2 + 1) * w);
	printf("1.掷骰子");
	SetPos(h + 1, (wallWSum / 2 + 1) * w);
	printf("2.使用道具");
	SetPos(h + 2, (wallWSum / 2 + 1) * w);
	printf("q.退出游戏");
	
}
//选择退出游戏
char  gameBreak(){
	char input;
	color(playermid->colour);//当前玩家颜色
	clear((wallWSum / 2 + 1) * w + 1, h + 1, 2 * w, 2 * h - 1);//选项区清除
	SetPos(h, (wallWSum / 2+1)*w);
	printf("确定要退出游戏吗");
	SetPos(h+1, (wallWSum / 2+1) * w);
	printf("1.退出");
	SetPos(h + 2, (wallWSum / 2+1) * w);
	printf("2.取消");
	while (1) {
		input = _getch();
		switch (input) {
		case '1':return 'q';
		case '2':return '3';
		default: break;
		}
	}
}
//游戏开始前准备
void gameBeginPer()
{
	printfsum();//选择角色数量
	playerNumSclect();//选择角色名字
	gameBagin();
}

//打印初始玩家位置
void printf01() {
	int i;
	for (i=0;i < playingSum;i++) {
		setPrintColor(playerNum[i].colour);
		gotoXY(playerNum[i].x, playerNum[i].y);
		printf("%s", playerNum[i].name);
		setPrintColor(0x0f);
	}
}


//正式开始游戏
void gameBagin() {
	int i = 0;

	//如果读档则i变为上次游戏玩家序号
	if (isReadFile)
	 i=readFile();

	//音乐开启
	stopMusic(3);
	playMusic(0);

	//开始基本游戏界面打印
	allLand();       //地区墙壁打印
	printfPlayer();  //玩家状态打印
	printfAllHouse();//建筑打印
	printf01();      //打印初始玩家位置

	char input;

	//玩家轮流进行游戏选择
	for (;i < playingSum;i++) {
		playermid = &playerNum[i];
		
		//打印当前游戏玩家名字
		color(playermid->colour);//当前玩家颜色                                  
		SetPos(h, (wallWSum / 2 + 1) * w - 6);
		printf("%s:", playermid->name);

		//回合打印
		color(7);
		SetPos(h*3, (wallWSum / 2 + 1) * w - 3);
		printf("回合%d/%d", sum / 3+1, endSum);

		//如果休眠或破产则跳过回合
		if (playerNum[i].sleep) { playerNum[i].sleep--;if (i == playingSum - 1)i = -1; playerSleepM(); continue; }
		if (!playerNum[i].exist) { if (i == playingSum - 1)i = -1;continue; }

		//当前玩家开始游戏选择
		while (1) {
			prntfplayerS();
			input = _getch();
			switch (input) {
			case '1':selectDice(); break;
			case '2':selectProp(); break;
			case 'q':input=gameBreak();break;
			}
			if (input == '1' ||input == 'q')break;
		}
		printfPlayer();//玩家选择结束后更新玩家状态

		//判断是否退出游戏
		if (i == playingSum-1 )i = -1;
		if (input == 'q')break;

		sum++;//增加游戏回合

		//游戏结束判定
		//游戏胜利金钱条件判断
		if (playermid->money >= winSore) { 
			stopMusic(0);
			playMusic(1); 
			isWin02();
			break; 
		} 
		//结束回合数判断
		if (endSum * 3 == sum) { 
			stopMusic(0);
			playMusic(1);
			isWin01(); 
			break; 
		}           
	}
	if (input == 'q') {
		keepFile();//退出时存档
		return;
	}
}
//存档
void keepFile() {
	FILE* p1 = fopen("land.txt", "w");
	int i;
	if (!p1){
		printf("%s", strerror(errno));
		return;
	}
	for (i = 0;i < 24;i++) {
		fwrite(&landNum[i], sizeof(struct land), 1, p1);
	}
	fclose(p1);
	p1 = NULL;

	FILE* p2 = fopen("player.txt", "w");
	if (!p2) {
		printf("%s", strerror(errno));
		return;
	}
	for (i = 0;i < playingSum;i++) {
		fwrite(&playerNum[i], sizeof(struct player), 1, p2);
	}
	fclose(p2);
	p2 = NULL;
	FILE* p3 = fopen("gamemessage.txt", "w");
	if (!p3) {
		printf("%s", strerror(errno));
		return;
	}
	tmid= playermid->num;
	fscanf(p3, "%d%d%d", &tmid, &playingSum, &sum);
	fclose(p3);
	p3 = NULL;
}
//读档
int readFile() {

	FILE* p1 = fopen("land.txt", "r");
	int i;
	if (!p1) {
		printf("%s", strerror(errno));
	}
	for (i = 0;i < 24;i++) {
		fread(&landNum[i], sizeof(struct land), 1, p1);
	}
	fclose(p1);
	p1 = NULL;

	FILE* p2 = fopen("player.txt", "r");
	if (!p2) {
		printf("%s", strerror(errno));
	}
	for (i = 0;i < playingSum;i++) {
		fread(&playerNum[i], sizeof(struct player), 1, p2);
	}
	fclose(p2);
	p2 = NULL;

	FILE* p3 = fopen("gamemessage.txt", "r");
	if (!p3) {
		printf("%s", strerror(errno));
	}
	fprintf(p3, "%d%d%d", &tmid, &playingSum, &sum);
	fclose(p3);
	p3 = NULL;
	return tmid;
}
void isWin02() {
	clear(0, 0, w * wallWSum, h * wallHSum);
	color(playermid->colour);
	SetPos((h * wallHSum) / 2, (w * wallWSum) / 2 - 8);
	printf("[%s]s胜利了！！！！！！", playermid->name);
	Sleep(3000);
	system("pause");
}
//游戏结束
void isWin01() {
	int a[3] = { playerNum[0].money ,playerNum[1].money ,playerNum[2].money },i,j,t;
	
	for (i = 0;i < playingSum - 1;i++)//n个数的数列总共扫描n-1次
	{
		for (j = 0;j < playingSum - i - 1;j++)//每一趟扫描到a[n-i-2]与a[n-i-1]比较为止结束
		{
			if (a[j] > a[j + 1])//后一位数比前一位数小的话，就交换两个数的位置（升序）
			{
				t = a[j + 1];
				a[j + 1] = a[j];
				a[j] = t;
			}
		}
	}
	for (i = 0;i < playingSum - 1;i++) {
		if (playerNum[i].money == a[2]) {
			clear(0, 0, w * wallWSum, h * wallHSum);
			color(playermid->colour);
			SetPos((h * wallHSum) / 2, (w * wallWSum) / 2 - 8);
			printf("[%s]胜利了！！！！！！", playerNum[i].name);
		}
	}
	Sleep(3000);
	system("pause");
}

//清理指定矩形区域(从(x,y)到(x+w,y+h)的矩形
void clear(int x, int y, int w, int h)
{
	for (int i = 0; i < h; i++) {
		gotoXY(x, y + i);
		for (int j = 0;j < w;j++) putchar(' ');
	}
}
// 传入坐标, 将光标移动到指定坐标
void gotoXY(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


//初始页面
void title()
{
	
	waveOutSetVolume(0, 0x0000FFFF);
	//waveOutSetVolume(0, 0xFFFFFFFF);
	//playMusic(0);
	playMusic(3);
	int j=1;
	while(!_kbhit()){
	color(j);
	int i;
	for (i = 4; i <= 14; i++)
	{
		SetPos(i, 25);
		switch (i)
		{
		case 4:
			printf("*           *     * * * *     *          *     * * * *     * * * * *   *           *         *");
			break;
		case 5:
			printf("* *       * *    *       *    * *        *    *       *    *        *  *            *       * ");
			break;
		case 6:
			printf("*  *     *  *   *         *   *  *       *   *         *   *        *  *             *     *  ");
			break;
		case 7:
			printf("*   *   *   *  *           *  *  *       *  *           *  *        *  *              *   *   ");
			break;
		case 8:
			printf("*   *   *   *  *           *  *   *      *  *           *  *        *  *               * *    ");
			break;
		case 9:
			printf("*    * *    *  *           *  *     *    *  *           *  * * * * *   *                *     ");
			break;
		case 10:
			printf("*     *     *  *           *  *     *    *  *           *  *           *                *     ");
			break;
		case 11:
			printf("*     *     *  *           *  *       *  *  *           *  *           *                *     ");
			break;
		case 12:
			printf("*           *   *         *   *       *  *   *         *   *           *                *     ");
			break;
		case 13:
			printf("*           *    *       *    *        * *    *       *    *           *                *     ");
			break;
		case 14:
			printf("*           *     * * * *     *          *     * * * *     *           * * * * * *      *     ");
			break;
		}
		SetPos((h * wallHSum) / 2, (w * wallWSum) / 2 -5);
		printf("按任意键继续");	
	}
	
	j++;
	Sleep(500);
	if (j == 16)j = 1;
	}
	_getch();
	
	
	color(15);

}
//颜色设置
void color(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
//标点刷新
void SetPos(int y, int x)
{
	COORD point = { x, y };
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
}

void screen_size(int a, int b)  // 屏幕大小（a列b行）
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = { a, b };
    SetConsoleScreenBufferSize(hOut, size);
    SMALL_RECT rc = { 1,1, a - 2, b - 2 };
    SetConsoleWindowInfo(hOut, 1, &rc);
}

// 播放指定音乐
int playMusic(int choose) {
	if (!isMusic) return 0;
	wchar_t cmd[MAX_PATH + 10];
	if (choose >= 0 && choose <= 3) {
		if (choose == music_title) {
			// 如果是背景音乐  则循环播放
			wsprintf(cmd, L"open %s alias title_bgm type mpegvideo", musicPath[choose]);
			mciSendString(cmd, 0, NULL, NULL);
			mciSendString(L"play title_bgm repeat", NULL, 0, NULL);
		}
		else if (choose == music_background) {
			// 如果是背景音乐  则循环播放
			wsprintf(cmd, L"open %s alias background_bgm type mpegvideo", musicPath[choose]);
			mciSendString(cmd, 0, NULL, NULL);
			mciSendString(L"play background_bgm repeat", NULL, 0, NULL);
		}
		else {
			// 否则 只播放一次
			wsprintf(cmd, L"play %s ", musicPath[choose]);
			mciSendString(cmd, 0, NULL, NULL);
		}
		return 1;
	}

	return 0;
};

// 停止播放指定音乐
int stopMusic(int choose) {
	wchar_t cmd[MAX_PATH + 10];
	if (choose == music_background || choose == music_title) {

	}
	if (choose == music_title) {
		return mciSendString(L"stop title_bgm", NULL, 0, NULL);
	}
	else if (choose == music_background) {
		return mciSendString(L"stop background_bgm", NULL, 0, NULL);
	}
	wsprintf(cmd, L"stop %s", musicPath[choose]);
	return mciSendString(cmd, NULL, 0, NULL);
}
void playPassCostM() {
	//打印环节
	infDisplayLine();
	setPrintColor(playermid->colour);
	printf("[%s]交了 %d 元过路费", playermid->name, landNum[playermid->playerPlace].passcost);
	setPrintColor(0);
	waveOutSetVolume(0, 0x000FFFFF);
	playMusic(2);
	waveOutSetVolume(0, 0x0000FFFF);
}
void playerSleepM() {
	if (playermid->sleep) {
		infDisplayLine();
		setPrintColor(playermid->colour);
		printf("[%s]休眠跳过回合", playermid->name);
		setPrintColor(0);
	}
}
void playerMeetAbsM() {
	infDisplayLine();
	setPrintColor(playermid->colour);
	printf("[%s]被暂停", playermid->name);
	setPrintColor(0);
}
void playerCostM() {
	infDisplayLine();
	setPrintColor(playermid->colour);
	printf("[%s]花费 %d 元购买了 %s", playermid->name,
		landNum[playermid->playerPlace].cost,
		landNum[playermid->playerPlace].name);
	setPrintColor(0);
	waveOutSetVolume(0, 0x000FFFFF);
	playMusic(2);
	waveOutSetVolume(0, 0x0000FFFF);
}
void playerMoveEndJai() {
	infDisplayLine();
	setPrintColor(playermid->colour);
	printf("[%s]进监狱暂停一回合", playermid->name);
	setPrintColor(0);
}
void playerMoveEndfeiji() {
	infDisplayLine();
	setPrintColor(playermid->colour);
	printf("[%s]飞机场随机前进", playermid->name);
	setPrintColor(0);
}

void playerMoveTouzi(int x) {
	infDisplayLine();
	setPrintColor(playermid->colour);
	printf("[%s]前进%d格", playermid->name,x);
	setPrintColor(0);

}
void printfselectDice() {
	infDisplayLine();
	setPrintColor(playermid->colour);
	printf("[%s]选择前进", playermid->name);
	setPrintColor(0);
}
void printfPlayer()
{

	int width = 19;// 角色信息宽度
	int height = 7;// 角色栏高度
	// 打印p1角色栏
	setPrintColor(playerNum[0].colour);
	gotoXY(width, height);
	//setPrintColor(playerNum[0].colour);
	printf("-------------------\n");
	for (int i = 0; i <= 10; i++)
	{
		gotoXY(width, i + height);
		printf("|\n");
	}
	for (int j = 0; j <= 10; j++)
	{
		gotoXY(2 * width, j + height);
		printf("|\n");
	}
	gotoXY(width, 10 + height);
	printf("-------------------\n");
	setPrintColor(0x0f);
	// 打印结束

	// 打印p2角色栏
	setPrintColor(playerNum[1].colour);
	gotoXY(2 * width, height);
	printf("-------------------\n");
	for (int i = 0; i <= 10; i++)
	{
		gotoXY(2 * width, i + height);
		printf("|\n");
	}
	for (int j = 0; j <= 10; j++)
	{
		gotoXY(3 * width, j + height);
		printf("|\n");
	}
	gotoXY(2 * width, 10 + height);
	printf("-------------------\n");
	setPrintColor(0x0f);
	// 打印结束

	// 打印p3角色栏
	if (playingSum == 3) {
		setPrintColor(playerNum[2].colour);
		gotoXY(3 * width, height);
		printf("-------------------\n");
		for (int i = 0; i <= 10; i++)
		{
			gotoXY(3 * width, i + height);
			printf("|\n");
		}
		for (int j = 0; j <= 10; j++)
		{
			gotoXY(4 * width, j + height);
			printf("|\n");
		}
		gotoXY(3 * width, 10 + height);
		printf("-------------------\n");
		setPrintColor(0x0f);
	}
	// 打印结束

	// 打印角色状态
	for (int i = 0; i < playingSum ; i++)
	{
		setPrintColor(playerNum[i].colour);
		gotoXY(i * width + 21, height + 2);
		printf("%s", playerNum[i].name);
		gotoXY(i * width + 21, height + 3);
		printf("当前资金：%d\n", playerNum[i].money);
		gotoXY(i * width + 21, height + 4);
		printf("当前休眠卡：%d\n", playerNum[i].sleepcard);
		gotoXY(i * width + 21, height + 5);
		printf("当前路障卡：%d\n", playerNum[i].obsCard);
	}
	
}
void printfAllHouse()
{


	int n = 0;//2-8建筑接收颜色值
	int h = 0;// 9-12建筑接收颜色
	int b = 0;// 13-20建筑接收颜色
	int o = 0;// 21-23建筑接收颜色
	// 打印2-8的建筑
	for (int i = 0; i < 8; i++)
	{
		switch (landNum[i].belong) {
		case 0:
			n = playerNum[0].colour;
			break;
		case 1:
			n = playerNum[1].colour;
			break;
		case 2:
			n = playerNum[2].colour;
			break;
		case -1:
			n = 7;
			break;
		}
		setPrintColor(n);
		gotoXY(3 + i * 17, 2);
		printf("%s\n", landNum[i].name);
		if (landNum[i].type == fangzi) {
			gotoXY(3 + i * 17, 3);
			printf("金额：%d\n", landNum[i].cost);
			setPrintColor(0x0f);
		}
		if(landNum[i].type == jianyu) {
			gotoXY(3 + i * 17, 3);
			printf("暂停一回合");
			setPrintColor(0x0f);
		}
		if (landNum[i].type == feiji) {
			gotoXY(3 + i * 17, 3);
			printf("随机前进");
			setPrintColor(0x0f);
		}
	}
	// 打印8-12的建筑
	for (int i = 0; i < 4; i++)
	{
		switch (landNum[i + 8].belong) {
		case 0:
			h = playerNum[0].colour;
			break;
		case 1:
			h = playerNum[1].colour;
			break;
		case 2:
			h = playerNum[2].colour;
			break;
		case -1:
			h = 7;
			break;
		}
		setPrintColor(h);
		gotoXY(122, 8 + 6 * i);
		printf("%s", landNum[i + 8].name);
		if (landNum[i + 8].type == fangzi) {
			gotoXY(122, 9 + 6 * i);
			printf("金额：%d", landNum[i + 8].cost);
			setPrintColor(0x0f);
		}
		if (landNum[i + 8].type == jianyu) {
			gotoXY(122, 9 + 6 * i);
			printf("暂停一回合");
			setPrintColor(0x0f);
		}
	    if (landNum[i + 8].type == feiji) {
			gotoXY(122, 9 + 6 * i);
			printf("随机前进");
			setPrintColor(0x0f);
		}

	}
	//打印12-20的建筑
	for (int i = 0; i < 8; i++)
	{
		switch (landNum[i + 12].belong) {
		case 0:
			b = playerNum[0].colour;
			break;
		case 1:
			b = playerNum[1].colour;
			break;
		case 2:
			b = playerNum[2].colour;
			break;
		case -1:
			b = 7;
			break;
		}
		setPrintColor(b);
		gotoXY(122 - 17 * i, 32);
		printf("%s", landNum[i + 12].name);
		if (landNum[i + 12].type == fangzi) {
			gotoXY(122 - 17 * i, 33);
			printf("金额：%d", landNum[i + 12].cost);
			setPrintColor(0x0f);
		}
		if (landNum[i + 12].type == jianyu) {
			gotoXY(122 - 17 * i, 33);
			printf("暂停一回合");
			setPrintColor(0x0f);
		}
		if (landNum[i + 12].type == feiji) {
			gotoXY(122 - 17 * i, 33);
			printf("随机前进");
			setPrintColor(0x0f);
		}
	}
	// 21-24

	for (int i = 0; i < 4; i++)
	{
		switch (landNum[i + 20].belong) {
		case 0:
			o = playerNum[0].colour;
			break;
		case 1:
			o = playerNum[1].colour;
			break;
		case 2:
			o = playerNum[2].colour;
			break;
		case -1:
			o = 7;
			break;
		}
		setPrintColor(o);
		gotoXY(3, 26 - i * 6);
		printf("%s", landNum[i + 20].name);
		if (landNum[i + 20].type == fangzi) {
			gotoXY(3, 27 - i * 6);
			printf("金额：%d", landNum[i + 20].cost);
			setPrintColor(0x0f);
		}
	    if (landNum[i + 20].type == jianyu) {
			gotoXY(3, 27 - i * 6);
			printf("暂停一回合");
			setPrintColor(0x0f);
		}
		if (landNum[i + 20].type == feiji) {
			gotoXY(3, 27 - i * 6);
			printf("随机前进");
			setPrintColor(0x0f);
		}
	}

	//Sleep(200);
	for (int i = 0; i < 8; i++)
	{
		switch (landNum[i].belong) {
		case 0:
			n = playerNum[0].colour;
			break;
		case 1:
			n = playerNum[1].colour;
			break;
		case 2:
			n = playerNum[2].colour;
			break;
		case -1:
			n = 7;
			break;
		}
		setPrintColor(n);
		gotoXY(3 + i * 17, 2);
		printf("%s\n", landNum[i].name);
		if (landNum[i ].type == fangzi) {
			gotoXY(3 + i * 17, 3);
			printf("金额：%d\n", landNum[i].cost);
			setPrintColor(0x0f);
		}
	    if (landNum[i].type == jianyu) {
			gotoXY(3 + i * 17, 3);
			printf("暂停一回合");
			setPrintColor(0x0f);
		}
		if (landNum[i].type == feiji) {
			gotoXY(3 + i * 17, 3);
			printf("随机前进");
			setPrintColor(0x0f);
		}
	}
	// 打印8-12的建筑
	for (int i = 0; i < 4; i++)
	{
		switch (landNum[i + 8].belong) {
		case 0:
			h = playerNum[0].colour;
			break;
		case 1:
			h = playerNum[1].colour;
			break;
		case 2:
			h = playerNum[2].colour;
			break;
		case -1:
			h = 7;
			break;
		}
		setPrintColor(h);
		gotoXY(122, 8 + 6 * i);
		printf("%s", landNum[i + 8].name);
		if (landNum[i + 8].type == fangzi) {
			gotoXY(122, 9 + 6 * i);
			printf("金额：%d", landNum[i + 8].cost);
			setPrintColor(0x0f);
		}
		if (landNum[i + 8].type == jianyu) {
			gotoXY(122, 9 + 6 * i);
			printf("暂停一回合");
			setPrintColor(0x0f);
		}
		if (landNum[i + 8].type == feiji) {
			gotoXY(122, 9 + 6 * i);
			printf("随机前进");
			setPrintColor(0x0f);
		}
	}
	//打印12-20的建筑
	for (int i = 0; i < 8; i++)
	{
		switch (landNum[i + 12].belong) {
		case 0:
			b = playerNum[0].colour;
			break;
		case 1:
			b = playerNum[1].colour;
			break;
		case 2:
			b = playerNum[2].colour;
			break;
		case -1:
			b = 7;
			break;
		}
		setPrintColor(b);
		gotoXY(122 - 17 * i, 32);
		printf("%s", landNum[i + 12].name);
		if (landNum[i + 12].type == fangzi) {
			gotoXY(122 - 17 * i, 33);
			printf("金额：%d", landNum[i + 12].cost);
			setPrintColor(0x0f);
		}
		if (landNum[i].type == jianyu) {
			gotoXY(122 - 17 * i, 33);
			printf("暂停一回合");
			setPrintColor(0x0f);
		}
		if (landNum[i].type == feiji) {
			gotoXY(122 - 17 * i, 33);
			printf("随机前进");
			setPrintColor(0x0f);
		}
	}
	// 21-24

	for (int i = 0; i < 4; i++)
	{
		switch (landNum[i + 20].belong) {
		case 0:
			o = playerNum[0].colour;
			break;
		case 1:
			o = playerNum[1].colour;
			break;
		case 2:
			o = playerNum[2].colour;
			break;
		case -1:
			o = 7;
			break;
		}
		setPrintColor(o);
		gotoXY(3, 26 - i * 6);
		printf("%s", landNum[i + 20].name);
		if (landNum[i + 20].type == fangzi) {
			gotoXY(3, 27 - i * 6);
			printf("金额：%d", landNum[i + 20].cost);
			setPrintColor(0x0f);
		}
		if (landNum[i].type == jianyu) {
			gotoXY(3, 27 - i * 6);
			printf("暂停一回合");
			setPrintColor(0x0f);
		}
		if (landNum[i].type == feiji) {
			gotoXY(3, 27 - i * 6);
			printf("随机前进");
			setPrintColor(0x0f);
		}
	}


}
//角色数量界面
void printfsum() {
	clear(0, 0, w * wallWSum, h * wallWSum);
	int userchoose = 0;
	while (1) {
		gotoXY((w * wallWSum) / 2 - 12, (h * wallHSum) / 2 - 15);
		printf("游 戏 模 式 选 择");

		if (userchoose == 0) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 12);
		printf("双 人 模 式");
		if (userchoose == 0) setPrintColor(0x0f);

		if (userchoose == 1) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 9);
		printf("三 人 模 式");
		if (userchoose == 1) setPrintColor(0x0f);

		char input = _getch();
		switch (input) {
		case 'w':
			userchoose -= 1;
			if (userchoose == -1) userchoose = 1;
			break;
		case 's':
			userchoose = (userchoose + 1) % 2;
			break;
		case '\r':
			//clear(0, 0, w * wallWSum, h * wallHSum);
			switch (userchoose) {
			case 0:
				playingSum = 2;
				return;
				break;
			case 1:
				playingSum = 3;
				return;
				break;

			}
			clear(0, 0, w * wallWSum, h * wallHSum);
			break;
		}
	}
}

void gameSet()
{
	clear(0, 0, w * wallWSum, h * wallHSum);
	int userChoose = 0;
	char s[6] = "on";
	if (isMusic) {
		strcpy_s(s, "on");
	}
	else {
		strcpy_s(s, "off");
	}
	while (1) {
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 15);
		printf("游   戏   设   置");

		if (userChoose == 0) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 12);
		printf("胜利金钱：%d", winSore);
		if (userChoose == 0) setPrintColor(0x0f);

		if (userChoose == 1) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 9);
		printf("结束回合：%d", endSum);
		if (userChoose == 1) setPrintColor(0x0f);

		if (userChoose == 2) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 6);
		printf("声音：%s", s);

		if (userChoose == 2) setPrintColor(0x0f);

		if (userChoose == 3) setPrintColor(0x6f);
		gotoXY((w * wallWSum) / 2 - 10, (h * wallHSum) / 2 - 3);
		printf("返回主界面");
		if (userChoose == 3) setPrintColor(0x0f);


		char input = _getch();
		switch (input) {
		case 'w':
			userChoose -= 1;
			if (userChoose == -1) userChoose = 3;
			break;
		case 's':
			userChoose = (userChoose + 1) % 4;
			break;
		case '\r':
			//clear(0, 0, w * wallWSum, h * wallHSum);
			switch (userChoose) {
			case 0:
				gotoXY((w * wallWSum) / 2 , (h * wallHSum) / 2 - 12);
				scanf_s("%d", &winSore);
				break;
			case 1:
				gotoXY((w * wallWSum) / 2 , (h * wallHSum) / 2 - 9);
				scanf_s("%d", &endSum);

				break;
			case 2:
					if (isMusic)
					{
						s[0] = 'o';
						s[1] = 'f';
						s[2] = 'f';
						s[3] = '\0';
						isMusic = 0;
						waveOutSetVolume(0, 0x00000000);
					}
					else {
						s[0] = 'o';
						s[1] = 'n';
						s[2] = '\0';
						isMusic = 1;
						waveOutSetVolume(0, 0x0000FFFF);
					}
				break;
			case 3:

				menu1();
				break;
			}
			clear(0, 0, w * wallWSum, h * wallHSum);
			break;
		}
	}
}
void printfPlayerMove()
{
	// 清理玩家原来位置
	clear(playermid->x, playermid->y, 4, 1);
	
    //根据玩家位置移动并打印
	if (playermid->playerPlace >= 0 && playermid->playerPlace < 7) {
		playermid->x += w;
		
		setPrintColor(playermid->colour);
		gotoXY(playermid->x, playermid->y);
		printf("%s", playermid->name);
		setPrintColor(0x0f);
	}
	if (playermid->playerPlace >= 7 && playermid->playerPlace < 12) {
		playermid->y += h;
		setPrintColor(playermid->colour);
		gotoXY(playermid->x, playermid->y);
		printf("%s", playermid->name);
		setPrintColor(0x0f);
	}
	if (playermid->playerPlace >= 12 && playermid->playerPlace < 19) {
		playermid->x += -w;
		setPrintColor(playermid->colour);
		gotoXY(playermid->x, playermid->y);
		printf("%s", playermid->name);
		setPrintColor(0x0f);
	}
	if (playermid->playerPlace >= 19 && playermid->playerPlace < 24) {
		playermid->y += -h;
		setPrintColor(playermid->colour);
		gotoXY(playermid->x, playermid->y);
		printf("%s", playermid->name);
		setPrintColor(0x0f);
		
	}
    //玩家位置增加
	Sleep(500);
	playermid->playerPlace++;
	//实现循环打印
	if (playermid->playerPlace == 24) {
		int x1;
		playermid->playerPlace = 0;
		infDisplayLine();
		setPrintColor(playermid->colour);
		printf("[%s]回到开始增加金钱1000", playermid->name);
		waveOutSetVolume(0, 0x000FFFFF);
		playMusic(2);
		waveOutSetVolume(0, 0x0000FFFF);
		playermid->money += 1000;
		x1 = rand();
		if (x1 % 2) {
			infDisplayLine();
			setPrintColor(playermid->colour);
			playermid->sleepcard++;
			printf("[%s]获得休眠卡", playermid->name);
		}
		else {
			infDisplayLine();
			setPrintColor(playermid->colour);
			playermid->obsCard++;
			printf("[%s]获得路障卡", playermid->name);
		}
		setPrintColor(0);
	}
	return;
}
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}
