#include <stdio.h>
#include <stdlib.h>//其中包含system函数
#include <conio.h>//定义了通过控制台进行 数据输入 和数据输出的函数，如getch函数。
#include <string.h>//定义字符数组
#include <math.h>
#include<Windows.h>
typedef struct student														//学生结构信息
{
	int po;
	char name[20];
	int age;
	char sex[5];
	char tel[13];
}student;
typedef struct Node															//学生链表结点 
{
	struct student student;
	struct Node* next;
}Node;
typedef struct userNode														//用户结构体 
{
	char userName[20];
	char userPassword[20]; 
	struct userNode	* next;
}userNode;
typedef struct userList														 //用户List 
{
	userNode users[16];
	int size;
}userList;
void readUserFile(userList* list)
{
	FILE *fp=fopen("用户信息.txt","r");						/*开文件*/
	printf("正在读取用户信息......\n");
	Sleep(300); 
	char Name[20];
	char Password[20];
	if(!fp) {
		printf("错误：打开用户信息文件失败，可能不存在！\n生成新用户信息文件...\n"); 
		fopen("用户信息.txt","w+");								
	}
	while(fscanf(fp,"%s\t%s\t",&Name,&Password)!=EOF)		/*读文件,把文件中的学生数据全部读入链表结点，以便增删查排改*/
	{
		//printf("正在读取用户信息\n");
		//printf("%s,%s,%d\n",Name,Password,list->size);
		strcpy(list->users[list->size].userName,Name);
		//printf("正在读取用户信息1...11...\n");
		strcpy(list->users[list->size++].userPassword,Password);
		//printf("%d",list->size);														
	}
	fclose(fp);																						/*关闭文件*/ 
	printf("读取用户信息完毕！\n");
	Sleep(1000);
	return ;
}
void writeUserToFile(userList* userList)
{
	FILE* fp = fopen("用户信息.txt", "w");
	if (fp == NULL)
	{
		printf("ERRPR:用户文件写入\n");
		system("pause");
		return;
	}
	for (int i = 0;i < userList->size;i++)
	{
		fprintf(fp, "%s\t%s\t\n", userList->users[i].userName, userList->users[i].userPassword);
	}
	printf("用户写入完毕！\n");
	fclose(fp);	
	return;
}
void addUser(userList* userList)
{
	system("cls");
	char name[30];
	char password[30];
	printf("-----------------新增用户-------------------\n");
	printf("请输入新用户名：\n");
	scanf("%s", name);
	fflush(stdin);
	printf("请为新用户设置密码(6-30位）：\n");
	scanf("%s", password);
	fflush(stdin);
	while (strlen(password) < 6 || strlen(password) > 30)
	{
		printf("密码长度不得低于6位，高于30位,请重新输入！\n");
		scanf("%s", password);
		fflush(stdin);
	}
	//printf("\n%d\n",userList->size);
	strcpy(userList->users[userList->size].userName, name);
	strcpy(userList->users[userList->size++].userPassword, password);
	//printf("\n%d\n",userList->size);
	printf("添加用户成功！\n");
	char * fileName = strcat(name,".txt");
	FILE *fp=fopen(fileName,"w");       
	fclose(fp);
	printf("%s",name) ;
	system("pause");
	return;
}
void alterUser(userList* list)
{
	if (list->size == 0)
	{
		printf("错误：没有管理员用户！\n");
		system("pause");
		return;
	}
	int i;
	for ( i = 0;i < list->size;i++)
	{
		printf("%d.%s\n", i + 1, list->users[i].userName);
	}
	printf("请选择您要更改的用户！\n");
	int choice = -1;
	scanf("%d", &choice);
	while (choice <= 0 || choice > list->size)
	{
		printf("您输入的编号超出正常范围，请重新输入！\n");
		scanf("%d", &choice);
	}
	printf("请输入原密码！\n");
	char word[20];
	scanf("%s", word);
	fflush(stdin);
	if (strcmp(word, list->users[choice - 1].userPassword) == 0)
	{
		char newword1[20];
		char newword2[20];
		printf("请输入新密码:\n");
		scanf("%s", newword1);
		fflush(stdin);
		while (strlen(newword1) < 6 || strlen(newword1) > 30)
		{
			printf("密码长度不得低于6位或高于30位，请重新输入！\n");
			scanf("%s", newword1);
		}
		printf("请再次确认新密码:\n");
		scanf("%s", newword2);
		if (strcmp(newword1, newword2) == 0)
		{
			strcpy(list->users[choice - 1].userPassword, newword1);
			printf("密码修改完成！\n");
			return;
		}
	}
	else
	{
		printf("密码错误！禁止修改！\n");
		return;
	}
}

void deleteUser(userList* list)
{
	system("cls");
	printf("-----------------删除用户-------------------\n");
	if (list->size == 0)
	{
		printf("ERROR:没有管理员用户！\n");
		system("pause");
		return;
	}
	int i;
	for ( i = 0;i < list->size;i++)
	{
		printf("%d.%s\n", i + 1, list->users[i].userName);
	}
	printf("请选择您要删除的用户！\n");
	int choice = -1;
	scanf("%d", &choice);
	while (choice <= 0 || choice > list->size)
	{
		printf("您输入的编号超出正常范围，请重新输入！\n");
		fflush(stdin);
		scanf("%d", &choice);
	}
	char word[30];
	printf("请输入改用户的原密码：\n");
	scanf("%s", word);
	if (strcmp(word, list->users[choice - 1].userPassword) == 0)
	{
		int i;
		for ( i = choice;i < list->size;i++)
		{
			list->users[i - 1] = list->users[i];
		}
		list->size--;
		printf("删除完成！\n");
	}
	else
	{
		printf("密码错误,禁止删除！\n");
	}
	return;
}
char* Login(userList* userList)
{
	system("cls");
	printf("-----------------登录-------------------\n");
	if (userList->size == 0)
	{
		printf("用户为空！请先注册用户！\n");
		system("pause");
		addUser(userList);
		return NULL;
	}
	char name[20];
	char word[20];
	int flag = 0;
	printf("请输入用户名：\n");
	scanf("%s", name);
	int i = 0, j = 0;
	for (i = 0;i < userList->size;i++)
	{
		if (strcmp(name, userList->users[i].userName) == 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		printf("用户名不存在，程序将退出！\n");
		exit(0);
	}
	printf("请输入登录密码:\n");
	scanf("%s", word);
	fflush(stdin); 
	for (j = 0;j < 4;j++)
	{
		if (strcmp(userList->users[i].userPassword, word) == 0)				//i是上面依照用户名获取的下标 
		{
			printf("登录成功！\n");
			Sleep(1000);
			return userList->users[i].userName;
		}
		if(j!=4) printf("密码错误！您还有%d次输入机会！\n", 4 - j);
		scanf("%s", word);
	}
	printf("3次输入密码错误，程序将退出！\n");
	exit(0);
}
struct Node* createList()													//创建链表头结点 
{
	struct Node* head= (struct Node*)malloc(sizeof(struct Node));
	head->next=NULL;
	return head;
}
struct Node* createNode(struct student data)								//创建结点 
{
	struct Node* nNode= (struct Node*)malloc(sizeof(struct Node));
	nNode->student= data;
	nNode->next= NULL;
	return nNode;
} 

void insertNodebyhead(struct Node*headNode,struct student data)				/*头插结点 不用遍历 */ 
{
	struct Node*newNode = createNode(data);
	newNode->next = headNode->next;
	headNode-> next= newNode;
}
void printUser(userList* list)
{
	system("cls");
	if (list->size == 0)
	{
		printf("用户数为0！\n");
		system("pause");
		return;
	}
	int i;
	for ( i = 0;i < list->size;i++)
	{
		printf("%d\t%s\n", i + 1, list->users[i].userName);
	}
	return;
}
void printList (struct Node* L)												/*输出链表中全部学生信息*/ 
{
	struct Node*p=L->next;
	if(p == NULL)
	{
		printf("还没有录入学生信息，请先输入学生信息\n");
		return ;
	}
	printf("-----------------查询到全体学生信息如下-------------------\n");
	printf("序号\t姓名\t年龄\t性别\t电话\n");
	while (p)
	{
		printf("%d\t%s\t%d\t%s\t%s\n",p->student.po,p->student.name,p->student.age,p->student.sex,p->student.tel);
		p = p->next;
	}
	printf("\n");
}
void showmenu0(){															/*打印主菜单*/
	system ("cls");
	printf("-----------------------【学生信息管理系统】-----------------------");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 0.退出 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 1.登录 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 2.注册 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
	printf("\n 请按键选择，回车确定\n");
	printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}
void showmenu1(){															/*打印主菜单*/
	system ("cls");
	printf("-----------------------【学生信息管理系统】-----------------------");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 0.退出 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 1.查看全部学生信息 *-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 2.录入学生信息 *-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 3.删除学生信息（按姓名） *-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 4.排序学生信息(按学号) *-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 5.查询学生信息（按学号） *-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 6.更改学生信息 *-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 7.管理用户信息 *-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
	printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n 请按键选择，回车确定\n");
	printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

void swapnodestr(struct Node*m,struct Node*n){
	struct student tempdata=m->student;
	m->student=n->student;
	n->student=tempdata;
}

void stolsort(struct Node*head){
	struct Node*p=head,*q;
	for(p=head->next;p;p=p->next){
		for(q=p->next;q;q=q->next){
			if(q->student.po<p->student.po){
				swapnodestr(q,p);
			}
		}
	}
}
void stolsort1(struct Node*head){
	struct Node*p=head,*q;
	for(p=head->next;p;p=p->next){
		for(q=p->next;q;q=q->next){
			if(q->student.po>p->student.po){
				swapnodestr(q,p);
			}
		}
	}
}
void deNode(struct Node* L,char*name){										/*找到学生姓名后删除结点*/ 
	struct Node*p1=L;	
	struct Node*p2=L->next;
	if(p2==NULL){
		printf("输入学生姓名后才能完成删除\n");
		return ;
	}
	while(strcmp(p2->student.name,name)){
		p1=p2;
		p2=p2->next;
		if(!p2){
			printf("未找到指定位置无法删除！\n");
			return ; 
		}
	}
	//找到
	 p1->next=p2->next;
	 free(p2); 
}

struct Node* searchdatabyname(struct Node* L,char *name){							/*按姓名,查找学生所在结点*/ 
	struct Node*p=L->next;
	if(!p){
		return NULL;													/*找不到在返回空外界打印错误*/
	}
	while(strcmp(p->student.name,name)){
		p=p->next;
		if(!p){
			return NULL;														/*外部打印错误信息*/
		}
	}
	return p;																/*找不到在返回空界打印错误*/ 
}

struct Node* searchdatabynumber(struct Node* L,int targetnumber){						/*按学号,查找学生所在结点*/ 
	struct Node*p=L->next;
	if(!p){
		return NULL;													/*找不到在返回空界打印错误*/ 
	}
	while(targetnumber!=p->student.po){
		p=p->next;
		if(!p){
			return NULL;												/*外部打印错误信息*/
		} 
	}
	return p;															/*找不到在返回空界打印错误*/ 
}

void readInfor(struct Node*head,const char* filename){			/*读文件函数*/
	FILE *fp=fopen(filename,"r");						/*开文件*/
	printf("正在读取文件......\n");
	Sleep(300); 
	struct student temp;
	if(!fp) {
		printf("错误：打开文件%s失败，可能不存在！\n生成新文件...\n",filename); 
		fopen(filename,"w+");								
	}
	while(fscanf(fp,"%d\t%s\t%d\t%s\t%s",&temp.po,temp.name,&temp.age,temp.sex,temp.tel)!=EOF)		/*读文件,把文件中的学生数据全部读入链表结点，以便增删查排改*/
	{
		insertNodebyhead(head,temp);																/*头插所以重新打开出来序号是从大到小的*/ 
	}
	fclose(fp);																						/*关闭文件*/ 
}

void writeintofile(struct Node*head,const char* filename) {								/*往文件中写学生信息*/
	FILE *fp=fopen(filename,"w");															/*开文件,"w"如果文件存在，那么清空文件内容,"a"为追加*/	
	struct Node*p=head->next;
	if (fp == NULL)											//打开文件出错时，fopen() 将返回一个空指针
	{
		printf("ERRPR:学生文件写入\n");
		system("pause");
		return;
	}
	while(p){
		fprintf(fp,"%d\t%s\t%d\t%s\t%s\n",p->student.po,p->student.name,p->student.age,p->student.sex,p->student.tel);										/*文件中存入信息*/
		p=p->next;
	} 
	printf("学生写入完毕！\n");
	fclose(fp);																		/*关闭文件*/ 
} 

char* keydown0(userList* list){
	int choice = -1,temp1=-1;
	fflush(stdin);
	scanf("%d",&choice);
	fflush(stdin);
	struct userNode* tNode; 
	char userName [20],userPassword[20];	
	int userNumber = 0;		
	char *userNm;
	switch(choice){
		case 0:
			printf("退出\n");
			exit(1);
		case 1:
			userNm = Login(*&list);
			printf("\n欢迎%s登录学生管理系统！\n",userNm);
			return userNm;
		case 2:
			addUser(*&list);
			writeUserToFile(*&list);
			userNm = Login(*&list);
			return userNm;
		default:
			printf("ERROR0:选择错误\n");
			exit(0);
			break; 
	}
	
}

void keydown1(struct Node* list,const char *filename,userList* userList){
	int choice = -1;
	fflush(stdin);
	scanf("%d",&choice);
	fflush(stdin);										/*以防下面switch出错*/
	struct student temp; 													/*结点里边的暂时学生，用于录入学生信息 */ 
	struct Node *tp=NULL;													/*临时结点，用于删除信息时删除结点*/ 
	int temp1=-1;
	//const char *filename = strcat(userNm,".txt");
	switch (choice)
	{
		case 0:
			printf("正常退出\n");
			exit(0);
			break;
		case 1:
			printf("------------------【查看全部学生信息】------------------\n");			/*打印信息 */ 
			printList(list);
			break;
		case 2:
			printf("--------------------【录入学生信息】--------------------\n");			/*把学生信息存入新结点，再插入 */ 
			printf("请输入学生学号，姓名，年龄，性别，电话\n");
			fflush(stdin);
			while(scanf("%d%s%d%s%s",&temp.po,temp.name,&temp.age,temp.sex,temp.tel)!=5){
				fflush(stdin);																/*以免影响下一次输入*/
				printf("您输入的数据不正确，请在下方重新输入正确信息！\n");
				continue; 
			} 
			fflush(stdin);
			insertNodebyhead(list,temp); 
			writeintofile(list,filename);							/*将以上进行数据的改动保存入文件中*/ 
			break;
		case 3:																			//不能在case下定义变量 
			printf("--------------------【删除学生信息】--------------------\n");
			printf("请输入删除的学生姓名\n"); 
			scanf("%s",temp.name);
			fflush(stdin);
			tp=searchdatabyname(list,temp.name);
			if(tp){
				printf("学号\t姓名\t年龄\t性别\t电话\n");
				printf("%d\t%s\t%d\t%s\t%s\n",tp->student.po,tp->student.name,tp->student.age,tp->student.sex,tp->student.tel);
			}
			else{
				printf("没有名叫%s的学生\n",temp.name); 
			}
			deNode(list,temp.name);
			writeintofile(list,filename) ;							/*将以上进行数据的改动保存入文件中*/ 
			break;
		case 4:{
			printf("--------------------【排序学生信息】--------------------\n");
			printf("1.输入1按学号从小到大排序\n2.输入2按学号从大到小排序\n");
			int choice = -1;
			fflush(stdin);
			scanf("%d",&choice);
			switch (choice)
			{
				case 1:
				{
					stolsort(list); 
			        printf("------------按学号从小到大排好的学生信息如---------------\n");
		        	printList(list); 
		        	break; 
				}
				case 2:
				{
					stolsort1(list);
			        printf("------------按学号从大到小排好的学生信息如---------------\n");
		        	printList(list);
		        	break;
				}
				default:
				{
					printf("输入错误！\n");
					break;
				}
			}	 
			writeintofile(list,filename) ;							/*将以上进行数据的改动保存入文件中*/ 
			break;	 
		}
		case 5:{
			printf("---------------【查询学生信息（按学号）】----------------\n");
			printf("请输入要查询的学生学号\n");
			temp1=-1;
			scanf("%d",&temp1);
			tp=searchdatabynumber(list,temp1);
			if(tp){
				printf("学号\t姓名\t年龄\t性别\t电话\n");
				printf("%d\t%s\t%d\t%s\t%s\n",tp->student.po,tp->student.name,tp->student.age,tp->student.sex,tp->student.tel);
			}
			else{
				printf("按学号查找不到此学生！\n"); 
			}
			break;
		}
		case 6:{
			printf("--------------------【更改学生信息】--------------------\n");
			printf("请输入要更改的学生学号\n");
			scanf("%d",&temp1);
			tp=searchdatabynumber(list,temp1);								//先找到 
			if(tp){
				printf("请输入数字确定要更改的数据\n");
				printf("\n\n 1.更改学生学号\n\n");
				printf("\n\n 2.更改学生姓名\n\n");
				printf("\n\n 3.更改学生年龄\n\n");
				printf("\n\n 4.更改学生性别\n\n");
				printf("\n\n 5.更改学生电话\n\n");
				printf("\n\n 请按键选择，回车确定\n");
			}
			else {
				printf("不存在学号为%d的学生\n",temp1);
				break; 
			}
			int choice = -1,temp1=-1;
			fflush(stdin);
			scanf("%d",&choice);
			fflush(stdin);
			int temppo=-1,tempage=-1; 
			char tempname [20],tempsex[5],temptel[13];					/*没有等于*/
			switch(choice){
				case 1:
					printf("请输入新的学号\n");
					scanf("%d",&temppo);
					tp->student.po=temppo;
					printf("学号修改已完成！"); 
					break;
				case 2:
					printf("请输入新的姓名\n");
					scanf("%s",tempname);
					strcpy(tp->student.name,tempname);
					printf("姓名修改已完成！"); 
					break;
				case 3:
					printf("请输入新的年龄\n");
					scanf("%d",&tempage);
					tp->student.age=tempage;
					printf("年龄修改已完成！"); 
					break;
				case 4:
					printf("请输入新的性别\n");
					scanf("%s",&tempsex);
					strcpy(tp->student.sex,tempsex);
					printf("性别修改已完成！"); 
					break;
				case 5:
					printf("请输入新的电话\n");
					scanf("%s",&temptel);
					strcpy(tp->student.tel,temptel);
					printf("电话修改已完成！"); 
					break;
				default:
					printf("选择错误\n");
					system("pause"); 
					break; 
			}
			writeintofile(list,filename) ;							/*将以上进行数据的改动保存入文件中*/ 
			break;
		}
		case 7:{
			system("cls");
			printf("--------------------【管理用户信息】--------------------\n");
			printf("1.添加用户\n2.修改用户密码\n3.删除用户\n4.查看所有用户\n");
			fflush(stdin);
			printf("请选择：\n");
			int choice = -1;
			scanf("%d",&choice);
			fflush(stdin);
			switch (choice)
			{
				case 1:
				{
					addUser(userList);
					writeUserToFile(userList); 
					break;
				}
				case 2:
				{
					alterUser(userList);
					writeUserToFile(userList);
					break;
				}
				case 3:
				{
					deleteUser(userList);
					writeUserToFile(userList);
					break;
				}
				case 4:
				{
					printUser(userList);
					break;
				}
				default:
				{
					printf("输入错误！\n");
					break;
				}
			}	 
		}
		break; 
		default:{
			printf("选择错误\n");
			break;
		}
	}
}

int main(){
	system("color 7C");
	const char *userFile = "用户信息.txt";
	char *filename = "xx.txt";
	char *userNm = "x";
	userList List;
	List.size = 0;
	readUserFile(&List);
	showmenu0();
	userNm = keydown0(&List); 
	system("pause");									
	system("cls");	
	
	//printf("1111111,,,,%s",userNm);
	struct Node*list= createList();
	filename = strcat(userNm,".txt");
	readInfor(list,filename); 								/*先把文件中的学生数据全部读入链表结点，以便增删查排改*/
	//printf("333");
	while(1){	
		showmenu1();											/*展示界面*/ 
		keydown1(list,filename,&List);											/*接收输入值*/ 	
		system("pause");									
		system("cls");								 
	}
	return 0;
}

