#define _CRT_SECURE_NO_WARNINGS
#include"2048.h"
void Menu()
{
	printf("说明：\n输入1开始游戏\n'w'控制上移's'控制下移'a'控制左移'd'控制右移(区分大小写)\n胜利条件：总分达到2048\n");
	printf("*******************************\n");
	printf("***          2048           ***\n");
	printf("*** 1.开始           0.退出 ***\n");
	printf("*******************************\n");
}
//打印
void Printf(int board[4][4])
{
	int  i, j;
	
	SetPos(0, 0);
	if (key == 1)
	{
		for (i = 0;i < 4;i++)
		{
			printf("-----------------\n|");
			for (j = 0;j < 4;j++)
			{
				printf("%2d |", board[i][j]);//注意这里是%2d当数字大时打印会变难看
			}
			printf("\n");
		}
		printf("-----------------");
		printf("  总分=%d\n", sum);
	}
}

//标点刷新
void SetPos(int y, int x)
{
	COORD point = { x, y };
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
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

//随机附2，4
void fuzhi(int board[4][4]) {
	int x, y, flag = 1,s;
	srand(time(NULL));
	do
	{
		x = rand() % 4;
		y = rand() % 4;
		s = rand() % 4+1;
		if (board[x][y] == 0&&(s==2||s==4))
		{
			board[x][y] = s;
			flag = 0;
		}
	} while (flag == 1);
}
void shuiji(int board[4][4])
{
	int i, j,flag = 0;

	//判断是否有空位并对key赋值
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (board[i][j] == 0)
			{
				flag = 1;
				key = 1;
			}

		}
	}
	if (flag == 0)
	{
		key = 0;
	}
	else
	{
		fuzhi(board);
	}
}
//上移
void move_w(int board[4][4])
{
	int i, j,m,n;
	//移动
	for (i = 0;i < 4;i++)
	{
		j = 0, n = 0;
		while (n < 3 && j < 3)
		{
			if (board[j][i] == 0)
			{
				for (m = j;m < 3;m++)
				{
					board[m][i] = board[m + 1][i];
				}
				board[3][i] = 0;
				n++;//必须要有n++来退出循环
			}
			else
			{
				j++;
			}
		}
	}
	//合并
	for (i = 0;i < 4;i++)
	{
		for (m = 0;m < 3;m++)
		{
			if (board[m][i] == board[m + 1][i] && board[m][i] != 0)
			{
				board[m][i] = board[m + 1][i] * 2;
				board[m + 1][i] = 0;
			}
		}
	}
	//移动
	for (i = 0;i < 4;i++)
	{
		j = 0, n = 0;
		while (n < 3 && j < 3)
		{
			if (board[j][i] == 0)
			{
				for (m = j;m < 3;m++)
				{
					
					board[m][i] = board[m + 1][i];
				}
				board[3][i] = 0;
				n++;
			}
			else
			{
				j++;
			}
		}
	}
}
//左移
void move_a(int board[4][4])

{
	int i, j, m, n;
	//移动
	for (i = 0;i < 4;i++)
	{
		j = 0, n = 0;
		while (n < 3 && j < 3)
		{
			if (board[i][j] == 0)
			{
				for (m = j;m < 3;m++)
				{
					board[i][m] = board[i ][m+1];
				}
				board[i][3] = 0;
				n++;//必须要有n++来退出循环
			}
			else
			{
				j++;
			}
		}
	}
	//合并
	for (i = 0;i < 4;i++)
	{
		for (m = 0;m < 3;m++)
		{
			if (board[i][m] == board[i][m+1] && board[i][m] != 0)
			{
				board[i][m] = board[i][m+1] * 2;
				board[i][m+1] = 0;
			}
		}
	}
	//移动
	for (i = 0;i < 4;i++)
	{
		j = 0, n = 0;
		while (n < 3 && j < 3)
		{
			if (board[i][j] == 0)
			{
				for (m = j;m < 3;m++)
				{
					board[i][m] = board[i][m + 1];
				}
				board[i][3] = 0;
				n++;//必须要有n++来退出循环
			}
			else
			{
				j++;
			}
		}
	}
}
//下移
void move_s(int board[4][4])
{
	int i, j, m, n;
	//移动
	for (i = 0;i < 4;i++)
	{
		j = 3, n = 0;
		while (n < 3 && j >0)
		{
			if (board[j][i] == 0)
			{
				for (m = j;m > 0;m--)
				{
					board[m][i] = board[m -1][i];
				}
				board[0][i] = 0;
				n++;//必须要有n++来退出循环
			}
			else
			{
				j--;
			}
		}
	}
	//合并
	for (i = 3;i >=0;i--)
	{
		for (m = 3;m > 0;m--)
		{
			if (board[m][i] == board[m -1][i] && board[m][i] != 0)
			{
			    board[m][i] = board[m -1][i] * 2;
				board[m - 1][i] = 0;
			}
		}
	}
	//移动
	for (i = 0;i < 4;i++)
	{
		j = 3, n = 0;
		while (n < 3 && j >0)
		{
			if (board[j][i] == 0)
			{
				for (m = j;m > 0;m--)
				{
					board[m][i] = board[m - 1][i];
				}
				board[0][i] = 0;
				n++;//必须要有n++来退出循环
			}
			else
			{
				j--;
			}
		}
	}
}
//右移
void move_d(int board[4][4])
{
	int i, j, m, n;
	//移动
	for (i = 0;i < 4;i++)
	{
		j = 3, n = 0;
		while (n < 3 && j >0)
		{
			if (board[i][j] == 0)
			{
				for (m = j;m >0;m--)
				{
					board[i][m] = board[i][m -1];
				}
				board[i][0] = 0;
				n++;//必须要有n++来退出循环
			}
			else
			{
				j--;
			}
		}
	}
	//合并
	for (i = 0;i < 4;i++)
	{
		for (m = 3;m >0;m--)
		{
			if (board[i][m] == board[i][m -1] && board[i][m] != 0)
			{
				board[i][m] = board[i][m - 1] * 2;
				board[i][m -1] = 0;
			}
		}
	}
	//移动
	for (i = 0;i < 4;i++)
	{
		j = 3, n = 0;
		while (n < 3 && j >0)
		{
			if (board[i][j] == 0)
			{
				for (m = j;m > 0;m--)
				{
					board[i][m] = board[i][m - 1];
				}
				board[i][0] = 0;
				n++;//必须要有n++来退出循环
			}
			else
			{
				j--;
			}
		}
	}
}
//游戏入口
void game2048(int board[4][4])
{
	int win = 1;//标记输赢
	char input;
	printf("进入游戏\n");
	SetPos(0, 0);
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");

	shuiji(board);
	Printf(board);
	win = panduan(board);//
	while (win)
	{
		if(win==2)
		{
			break;
		}
		input=getch();  //读取输入
		switch (input)  //判断移动
		{
		case 'w':move_w(board);shuiji(board);win=panduan(board);Printf(board);break;//最后做判断，否则随机附2会无限循环
		case 's':move_s(board);shuiji(board);win=panduan(board);Printf(board);break;
		case 'a':move_a(board);shuiji(board);win = panduan(board);Printf(board);break;
		case 'd':move_d(board);shuiji(board);win = panduan(board);Printf(board);break;
		default:printf("游戏输入错误\n");break;
	    }
	}
	if (win == 0)
	{
		printf("游戏结束！");
	}
	else
	{
		printf("胜利！！");
	}
	getchar();//防止退出游戏界面
}
//判断
int panduan(int board[4][4])
{
	int i,j;
	sum = 0;
	//计算总分
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			sum = board[i][j] + sum;
		}
	}
	if (sum >= WIN)
	{
		return 2;//返回值判断是否胜利
	}
	//判断是否有空位
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (board[i][j]==0)
			{
				return 1;//返回值判断是否继续游戏
			}
			
		}
	}
	//判断横向是否有相同数
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 3;j++)
		{
			if (board[i][j] == board[i][j+1])
			{
				return 1;//返回值判断是否继续游戏
			}

		}
	}
	//判断竖向向是否有相同数
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 3;j++)
		{
			if (board[j][i] == board[j+1][i])
			{
				return 1;//返回值判断是否继续游戏
			}

		}
	}
	return 0;
}
void jiafen()
{

}