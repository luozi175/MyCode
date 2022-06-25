#define _CRT_SECURE_NO_WARNINGS
#include"2048.h"
void Menu()
{
	printf("˵����\n����1��ʼ��Ϸ\n'w'��������'s'��������'a'��������'d'��������(���ִ�Сд)\nʤ���������ִܷﵽ2048\n");
	printf("*******************************\n");
	printf("***          2048           ***\n");
	printf("*** 1.��ʼ           0.�˳� ***\n");
	printf("*******************************\n");
}
//��ӡ
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
				printf("%2d |", board[i][j]);//ע��������%2d�����ִ�ʱ��ӡ����ѿ�
			}
			printf("\n");
		}
		printf("-----------------");
		printf("  �ܷ�=%d\n", sum);
	}
}

//���ˢ��
void SetPos(int y, int x)
{
	COORD point = { x, y };
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
}

//����ָ����������(��(x,y)��(x+w,y+h)�ľ���
void clear(int x, int y, int w, int h)
{
	for (int i = 0; i < h; i++) {
		gotoXY(x, y + i);
		for (int j = 0;j < w;j++) putchar(' ');
	}
}
// ��������, ������ƶ���ָ������
void gotoXY(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//�����2��4
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

	//�ж��Ƿ��п�λ����key��ֵ
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
//����
void move_w(int board[4][4])
{
	int i, j,m,n;
	//�ƶ�
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
				n++;//����Ҫ��n++���˳�ѭ��
			}
			else
			{
				j++;
			}
		}
	}
	//�ϲ�
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
	//�ƶ�
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
//����
void move_a(int board[4][4])

{
	int i, j, m, n;
	//�ƶ�
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
				n++;//����Ҫ��n++���˳�ѭ��
			}
			else
			{
				j++;
			}
		}
	}
	//�ϲ�
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
	//�ƶ�
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
				n++;//����Ҫ��n++���˳�ѭ��
			}
			else
			{
				j++;
			}
		}
	}
}
//����
void move_s(int board[4][4])
{
	int i, j, m, n;
	//�ƶ�
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
				n++;//����Ҫ��n++���˳�ѭ��
			}
			else
			{
				j--;
			}
		}
	}
	//�ϲ�
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
	//�ƶ�
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
				n++;//����Ҫ��n++���˳�ѭ��
			}
			else
			{
				j--;
			}
		}
	}
}
//����
void move_d(int board[4][4])
{
	int i, j, m, n;
	//�ƶ�
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
				n++;//����Ҫ��n++���˳�ѭ��
			}
			else
			{
				j--;
			}
		}
	}
	//�ϲ�
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
	//�ƶ�
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
				n++;//����Ҫ��n++���˳�ѭ��
			}
			else
			{
				j--;
			}
		}
	}
}
//��Ϸ���
void game2048(int board[4][4])
{
	int win = 1;//�����Ӯ
	char input;
	printf("������Ϸ\n");
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
		input=getch();  //��ȡ����
		switch (input)  //�ж��ƶ�
		{
		case 'w':move_w(board);shuiji(board);win=panduan(board);Printf(board);break;//������жϣ����������2������ѭ��
		case 's':move_s(board);shuiji(board);win=panduan(board);Printf(board);break;
		case 'a':move_a(board);shuiji(board);win = panduan(board);Printf(board);break;
		case 'd':move_d(board);shuiji(board);win = panduan(board);Printf(board);break;
		default:printf("��Ϸ�������\n");break;
	    }
	}
	if (win == 0)
	{
		printf("��Ϸ������");
	}
	else
	{
		printf("ʤ������");
	}
	getchar();//��ֹ�˳���Ϸ����
}
//�ж�
int panduan(int board[4][4])
{
	int i,j;
	sum = 0;
	//�����ܷ�
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			sum = board[i][j] + sum;
		}
	}
	if (sum >= WIN)
	{
		return 2;//����ֵ�ж��Ƿ�ʤ��
	}
	//�ж��Ƿ��п�λ
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (board[i][j]==0)
			{
				return 1;//����ֵ�ж��Ƿ������Ϸ
			}
			
		}
	}
	//�жϺ����Ƿ�����ͬ��
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 3;j++)
		{
			if (board[i][j] == board[i][j+1])
			{
				return 1;//����ֵ�ж��Ƿ������Ϸ
			}

		}
	}
	//�ж��������Ƿ�����ͬ��
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 3;j++)
		{
			if (board[j][i] == board[j+1][i])
			{
				return 1;//����ֵ�ж��Ƿ������Ϸ
			}

		}
	}
	return 0;
}
void jiafen()
{

}