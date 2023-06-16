#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define scanf scanf_s
#define LEN sizeof(LNode)

int seat;
typedef struct LNode   //通讯录结点
{
	int number; //学号
	char name[20];    //姓名
	double telenum; //电话
	struct LNode* next;
}LNode, * LinkList;
void printList(LinkList L)
{    // 打印头结点地址为L的通讯录
	LinkList p = L;////
	int n = 1;
	printf("\n          ---------------------------------------\n");
	printf("               学号       姓名     电话号码\n");
	printf("          ----------------------------------------\n");
	if (L == NULL || L->next == NULL)
		printf("该通讯录中没有元素\n");
	else
		while (p->next != NULL)
		{
			printf("          %2d   %-9d", n, p->next->number);
			printf("    %-5s  %.0f\n", p->next->name, p->next->telenum);
			p = p->next;
			n++;
		}
	printf("          ----------------------------------------\n");
	return;
}
LinkList prior(LinkList L, LinkList p)
{  // 查找位于当前地址元素的前一元素的地址
	LinkList p_prior = L;
	if (L->next == NULL)
		return(L);
	while (p_prior->next != p)
	{
		p_prior = p_prior->next;
	}
	return (p_prior);
}
void insertYouXu(LinkList L, LinkList Elem)
{              //插入一个元素，使原有序表仍为有序
	LinkList p = L->next;
	while (p != NULL && Elem->number >= p->number)
	{
		if (p->number == Elem->number)
		{
			printf("重复输入！！\n"); return;
		}
		p = p->next;
	}         //确定Elem插入的位置
	if (p == NULL)
	{
		p = prior(L, p); Elem->next = NULL; p->next = Elem;
	}
	else       //若为空表，插到头结点之后
	{
		p = prior(L, p); Elem->next = p->next; p->next = Elem;
	}
}
LinkList creatIncreLink()
{//创建一个存放通讯录成员的非递减有序表，返回头结点地址
	int num = 1, number;
	double telenum;
	char name[20], temp;
	LinkList L, p;
	L = (LinkList)malloc(LEN);    //头结点
	L->next = NULL;
	printf("请输入学生学号、姓名和电话号码，建立通讯录，以'-1'为输入结束标志\n");
	printf("请输入学号 %d：", num);
	scanf("%d", &number);
	printf("请输入姓名 %d: ", num);
	temp = getchar(); gets(name);
	printf("请输入电话号码 %d：", num);
	scanf("%lf", &telenum);
	while (number >= 0)
	{
		p = (LinkList)malloc(LEN); //新结点
		p->number = number;
		p->telenum = telenum;
		strcpy(p->name, name);
		insertYouXu(L, p);       //有序的插入新结点
		num++;
		printf("请输入学号 %d：", num);
		scanf("%d", &number);
		printf("请输入姓名 %d: ", num);
		temp = getchar();  gets(name);
		printf("请输入电话号码 %d：", num);
		scanf("%lf", &telenum);
	}
	return(L);
}
void deleteElem(LinkList L, int i)
{ //从通讯录中删除第i个元素
	LinkList p = L, q;//////
	int j = 0;
	while (p->next && j < i - 1)
	{
		p = p->next; j++;
	}
	if (!(p->next)) //判断i是否合法，i既不能大于元素的个数，也不能小于等于0
	{
		printf("第%d个元素删除失败\n", i);
		return;
	}
	q = p->next;
	p->next = q->next;
	free(q);  //释放删除的结点 
}
int searchNum(LinkList L, int n)
{    // 按学号查找通讯者
	int flag = 0;
	LinkList p = L->next;
	seat = 1;
	if (L->next == NULL) printf("该链表中没有元素,查找失败\n");
	else
	{
		while (p != NULL)
		{
			if (p->number <= n)
				if (p->number == n)
				{
					flag = 1;
					printf("要查找的是第%d位通讯者：\n", seat);
					printf("                        学号: %d   姓名: %s   电话号码.:%.0f\n", p->number, p->name, p->telenum);
				}
			p = p->next; seat++;//!!!!
		}
	}
	return flag;
}

int searchName(LinkList L, char n[])
{    // 按姓名查找通讯者
	int flag = 0;
	LinkList p = L->next;
	seat = 1;
	if (L->next == NULL || L == NULL)
		printf("该通讯录中没有元素,查找失败\n");
	else
	{
		while (p != NULL)
		{
			if (!strcmp(p->name, n))
			{
				flag = 1;
				printf("要查找的是第%d位通讯者：\n", seat);
				printf("                        Number: %d   Name: %s   TeleNo.:%.0f\n", p->number, p->name, p->telenum);
			}
			p = p->next; seat++;//!!!!!
		}
	}
	return flag;
}
int delNum(LinkList L, int n)
{    // 按学号删除通讯者
	int flag = 0;
	LinkList p = L->next;
	seat = 1;
	if (L->next == NULL)
		printf("该链表中没有元素,删除失败\n");
	else
	{
		while (p != NULL)
		{
			if (p->number <= n)
			{
				if (p->number == n)
				{
					flag = 1;
					printf("%d ", p->number);
					p = p->next;
					deleteElem(L, seat);

				}
			}
			else { p = p->next; seat++; }
		}
		printf("被删除\n");
	}
	return flag;
}
int delName(LinkList L, char n[])
{    // 按姓名删除通讯者	
	int flag = 0;
	LinkList p = L->next;
	seat = 1;
	if (L->next == NULL)
		printf("该链表中没有元素,查找失败\n");
	else
	{
		while (p != NULL)
		{
			if (!strcmp(p->name, n))
			{
				flag = 1;
				printf("%s ", p->name);
				p = p->next;
				deleteElem(L, seat);
			}
			else { p = p->next; seat++; }
		}
		if (flag)printf("被删除\n");
	}
	return flag;
}
void main()
{
	LinkList L = NULL, p;
	int flag = 0, menu;
	char temp;
	system("color 1f");
	printf("\n           ***************** ^@^欢迎使用通讯录系统***********\n");
	printf("           *               1 通讯录的建立                   *\n");
	printf("           *               2 插入通讯记录                   *\n");
	printf("           *               3 查询通讯记录                   *\n");
	printf("           *               4 删除通讯记录                   *\n");
	printf("           *               5 显示通讯录信息                 *\n");
	printf("           *               0 退出管理系统                   *\n");
	printf("           **************** ^@^欢迎使用通讯录系统************\n");
	printf("请选择0-5：");
	scanf("%d", &menu);
	while (menu != 0)
	{
		switch (menu)
		{
		case 1:
		{
			L = creatIncreLink();
			printf("建立通讯录：");
			printList(L);
			flag = 1;
			break;
		}
		case 2:
		{
			if (flag == 1)
			{
				int number, telenum;
				char name[20];
				printf("请输入通讯者的学号和姓名：\n");
				printf("请输入学号: ");
				scanf("%d", &number);
				printf("请输入姓名: ");
				temp = getchar(); gets(name);
				printf("请输入电话号码: ");
				scanf("%d", &telenum);
				p = (LinkList)malloc(LEN); //新结点
				p->number = number;
				strcpy(p->name, name);
				p->telenum = telenum;
				insertYouXu(L, p);       //有序的插入新结点
				printf("插入后：");
				printList(L);
			}//endif
			else printf("\nERROR: 通讯录还没有建立，请先建立通讯录\n");
			break;
		}//endcase2
		case 3:
		{
			int way, n;
			char na[20], temp;
			int s;
			if (L != NULL)
			{
				if (flag)
				{
					printf("选择查找方式：\n");
					printf("               1.按学号   2.按姓名\n");
					scanf("%d", &way);
					if (way == 1)
					{
						printf("\n请输入学号:");
						scanf("%d", &n);
						s = searchNum(L, n);
						if (s == 0) printf("无此通讯者，查找失败！\n");
					}
					else if (way == 2)
					{
						printf("\n请输入姓名:");
						temp = getchar(); gets(na);
						s = searchName(L, na);
						if (s == 0) printf("无此通讯者，查找失败！\n");
					}
					else printf("通讯录中无记录！\n");
				}
				break;
			}
			else printf("通讯录中无记录！\n"); break;
		}//endcase3
		case 4:
		{
			int way;
			char temp; ////
			printf("选择删除方式：1.按序号  2. 按学号  3.按姓名 \n");
			scanf("%d", &way);
			if (way == 1)
			{
				int n;
				printf("请输入通讯录序号: ");
				scanf("%d", &n);
				printf("删除后：\n");
				deleteElem(L, n);
				printList(L);
			}
			else if (way == 2)
			{
				int n, f;
				printf("请输入学号: ");
				scanf("%d", &n);
				f = delNum(L, n);
				if (f != 0)
				{
					printf("删除后：\n");
					printList(L);
				}
				else printf("无该学号，删除失败!\n");
			}
			else if (way == 3)
			{
				char na[20], temp;
				int f;
				printf("\n请输入姓名:");
				temp = getchar();  gets(na);
				f = delName(L, na);
				if (f != 0)
				{
					printf("删除后：\n");
					printList(L);
				}
				else printf("无该学号，删除失败!\n");
			}
			else printf("ERROR!!\n");
			break;
		}//endcase4
		case 5:
		{
			printf("当前通讯录内容如下：\n");
			printList(L);
			break;
		}
		case 0: exit(0);
		default:  printf("\n没有此功能，重新输入\n");
		}//endswitch
		printf("选择功能：");
		scanf("%d", &menu);
	}//endwhile
}//end
