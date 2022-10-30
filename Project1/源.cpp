#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#pragma comment(lib,"Winmm.lib")

#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'
#define stop 'p'

void welcome();               //��ʼ����
void Finish();                //��������
void creatgraph();            //Χǽ��ӡ
void gotoxy(int x, int y);    //�����ת����ΪX 0,1,2..
void gotoprint(int x, int y); //��ת��ӡ
void gotodelete(int x, int y);//��תɾ��
void creatfood();             //ʳ�����
int ClickControl();           //��ȡ�����ź�
int Judge();                  //��Ϸ�����ж�
void MovingBody();            //�ߵ��ƶ� 
void Eating();                //�߳Ե�������Ĳ������쳤��
void ChangeBody(int a, int b); //�ߵ�����任,��һ������ǰһ��STRUCT,a,bΪhead֮ǰ���� 
int paimin(int score);         //���β��������в����е�����

/*ȫ�ֱ��� + Ԥ����*/
typedef struct Snakes
{
	int x;
	int y;
	struct Snakes* next;
}snake;

snake* head, * tail;

struct Food
{
	int x;
	int y;
}food;
char name[200];
int score = 0;
char click = 1;
int speed;
int choice;
char direct;
char move = 2;
int n;

/************************************************************/

int main()
{
	system("color 0F");
	PlaySound(TEXT("1.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	welcome();
	creatgraph();
	creatfood();
	if (ClickControl() == 0)
		return 0;
	return 0;
}

/**********************************************************/
void welcome()
{
	int a;
	gotoxy(25, 8);
	printf("/**********************************************/");
	gotoxy(25, 20);
	printf("/**********************************************/");
	gotoxy(40, 10);
	printf("��ӭ����̰������Ϸ");
	gotoxy(25, 12);
	printf("���ߣ����д�       ��ϵ��ʽ��shangdazhao@gmail.com");
	gotoxy(25, 14);
	printf("����Ӣ�����뷨�в�����W,A,S,D�����Ʒ���P����ͣ����������������ʼ");
	gotoxy(25, 16);
	printf("ע�⣺�߲��ܷ����ƶ���ֻ��ͨ��ת��ı䷽��");
	gotoxy(25, 18);
	printf("��ѡ����Ϸ�Ѷȣ�A.��  B.��ͨ   C����       ����ѡ���ǣ�");
	scanf_s("%c", &choice);
	while (choice != 'A' && choice != 'B' && choice != 'C')
	{
		system("cls");
		gotoxy(40, 12);
		printf("�����������������\n");
		gotoxy(25, 14);
		printf("��ѡ����Ϸ�Ѷȣ�A.��  B.��ͨ   C����       ����ѡ���ǣ�");
		scanf_s("%c", &choice);
	}
	system("cls");
}
/**********************************************************/
void creatgraph()
{
	int i;
	for (i = 0; i < 58; i += 2)//��ӡ���±߿�
	{
		gotoprint(i, 0);
		gotoprint(i, 26);
	}
	for (i = 1; i < 26; i++)
	{
		gotoprint(0, i);
		gotoprint(56, i);
	}
	gotoxy(63, 10);
	printf("������");
	gotoxy(63, 15);
	printf("�����ڵķ�����:%d", score);
	head = (snake*)malloc(sizeof(snake));
	head->x = 16;
	head->y = 15;
	//gotoprint(head->x, head->y);
	tail = (snake*)malloc(sizeof(snake));
	snake* p = (snake*)malloc(sizeof(snake));
	snake* q = (snake*)malloc(sizeof(snake));
	p->x = 16;
	p->y = 16;
	q->x = 16;
	q->y = 17;
	head->next = p;
	p->next = q;
	q->next = tail;
	//gotoprint(p->x, p->y);
	//gotoprint(q->x, q->y);
	tail->next = NULL;
	tail->x = 4;
	tail->y = 2;
}
/**********************************************************/
void creatfood()
{
	srand((int)time(NULL));
lable:
	food.y = rand() % (25 - 1 + 1) + 1;
	food.x = rand() % (54 - 2 + 1) + 2;
	if (food.x % 2 != 0)
	{
		food.x = food.x + 1;
	}
	snake* judge = head;
	while (1)  //�����ų������ظ�
	{
		if (judge->next == NULL) break;
		if (food.x == judge->x && food.y == judge->y)
		{
			goto lable;
		}
		judge = judge->next;
	}
	gotoxy(food.x, food.y);
	printf("��");
}
/**********************************************************/
int ClickControl()
{
	while (1)
	{
		if (_kbhit())
			click = _getch();
		if (click == 'a' && move == 'd')
			click = move;
		else if (click == 'd' && move == 'a')
			click = move;
		else if (click == 'w' && move == 's')
			click = move;
		else if (click == 's' && move == 'w')
			click = move;
		else
		{
			if (Judge() == 0)
				return 0;
			move = click;
		}
		MovingBody();
		Eating();
	}
	return 1;
}
/**********************************************************/
int Judge()
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		Finish();
		return 0;
	}
	snake* p = head->next;
	while (1)
	{
		if (p->next == NULL)
			break;
		if (head->x == p->x && head->y == p->y)
		{
			Finish();
			return 0;
		}
		p = p->next;
	}
	return 1;
}
/**********************************************************/
void gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
/**********************************************************/
void gotoprint(int x, int y)
{
	gotoxy(x, y);
	printf("��");
}
/**********************************************************/
void gotodelete(int x, int y)
{
	gotoxy(x, y);
	printf("  ");
}
/**********************************************************/

void MovingBody()
{

	int count = 0;
	int a = head->x, b = head->y;
	snake* p = head;
	//ͨ������պ��ӡʵ�ֶ���Ч��
	while (1)
	{
		if (p->next == NULL)
			break;
		gotodelete(p->x, p->y);
		count++;
		p = p->next;
	}
	switch (click)
	{
	case up:
		head->y -= 1;
		ChangeBody(a, b);
		break;
	case down:
		head->y += 1;
		ChangeBody(a, b);
		break;
	case left:
		head->x -= 2;
		ChangeBody(a, b);
		break;
	case right:
		head->x += 2;
		ChangeBody(a, b);
		break;
	case stop:
		_getch();
		break;
	}
	p = head;
	while (1)
	{
		if (p->next == NULL)
			break;
		gotoprint(p->x, p->y);
		p = p->next;
	}
	p = head;
	gotoxy(0, 28);
	if (count <= 5)
	{
		if (choice == 'A')
			speed = 200;
		else if (choice == 'B')
			speed = 150;
		else
			speed = 100;
	}
	else if (count > 5 && count <= 15)
	{
		if (choice == 'A')
			speed = 150;
		else if (choice == 'B')
			speed = 125;
		else
			speed = 100;
	}

	else if (count > 15 && count <= 25)
	{
		if (choice == 'A')
			speed = 75;
		else if (choice == 'B')
			speed = 50;
		else
			speed = 25;
	}
	else
		speed = 10;
	Sleep(speed);

}
/**********************************************************/
void Eating()
{
	if (head->x == food.x && head->y == food.y)
	{
		creatfood();
		snake* _new = (snake*)malloc(sizeof(snake));
		snake* p;
		p = head;
		while (1)
		{
			if (p->next->next == NULL) break;
			p = p->next;
		}
		p->next = _new;
		_new->next = tail;
		score += 10;
		gotoxy(77, 15);
		printf("%d", score);
	}
}
/**********************************************************/
void ChangeBody(int a, int b)
{
	snake* p = head->next;
	int mid1, mid2, _mid1, _mid2;
	mid1 = p->x;
	mid2 = p->y;
	while (1)
	{
		if (p->next->next == NULL)
			break;
		_mid1 = p->next->x;
		_mid2 = p->next->y;
		p->next->x = mid1;
		p->next->y = mid2;
		mid1 = _mid1;
		mid2 = _mid2;
		p = p->next;
	}
	p = head->next;
	//if (p->next!= NULL)
	{
		p->x = a;
		p->y = b;
	}
}
/**********************************************************/

void Finish()
{
	PlaySound(TEXT("2.wav"), 0, SND_FILENAME | SND_ASYNC);
	system("cls");
	gotoxy(35, 10);
	printf("/**********************************************/");
	gotoxy(35, 20);
	printf("/**********************************************/");
	gotoxy(55, 12);
	printf("��Ϸ����!");
	gotoxy(35, 14);
	printf("��ĵ÷���%d,������%d", score, paimin(score));
	gotoxy(35, 16);
	printf("������Ŷ������Ŭ��");
	gotoxy(35, 18);
	printf("�����ʲô��������⣬�뷢�ʼ��� shangdazhao@gmail.com");
	gotoxy(0, 27);
	system("pause");
}
/*********************************************************/
int paimin(int score)
{
	FILE* fp, * ft;
	int a[100];
	int i, j = 1, k = 1, num, m;
	if ((fp = fopen("rank.txt", "r")) == NULL)
	{
		printf("cann't open file");
		exit(0);
	}
	if ((ft = fopen("linshi.txt", "w")) == NULL)
	{
		printf("cann't open file");
		exit(0);
	}
	fscanf_s(fp, "%d", &num);
	for (i = 1; i < num + 1; i++)
	{
		fscanf_s(fp, "%d", &k);
		a[i] = k;
		if (score < k)
			j++;
	}
	a[0] = num + 1;
	a[num + 1] = score;
	for (i = 0; i < num + 2; i++)
	{
		fprintf(ft, "%d\n", a[i]);
	}
	fclose(fp);
	fclose(ft);
	remove("rank.txt");
	rename("linshi.txt", "rank.txt");
	return j;
}