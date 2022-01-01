#include <stdio.h>
#include <stdlib.h>//���а���system����
#include <conio.h>//������ͨ������̨���� �������� ����������ĺ�������getch������
#include <string.h>//�����ַ�����
#include <math.h>
#include<Windows.h>
typedef struct student														//ѧ���ṹ��Ϣ
{
	int po;
	char name[20];
	int age;
	char sex[5];
	char tel[13];
}student;
typedef struct Node															//ѧ�������� 
{
	struct student student;
	struct Node* next;
}Node;
typedef struct userNode														//�û��ṹ�� 
{
	char userName[20];
	char userPassword[20]; 
	struct userNode	* next;
}userNode;
typedef struct userList														 //�û�List 
{
	userNode users[16];
	int size;
}userList;
void readUserFile(userList* list)
{
	FILE *fp=fopen("�û���Ϣ.txt","r");						/*���ļ�*/
	printf("���ڶ�ȡ�û���Ϣ......\n");
	Sleep(300); 
	char Name[20];
	char Password[20];
	if(!fp) {
		printf("���󣺴��û���Ϣ�ļ�ʧ�ܣ����ܲ����ڣ�\n�������û���Ϣ�ļ�...\n"); 
		fopen("�û���Ϣ.txt","w+");								
	}
	while(fscanf(fp,"%s\t%s\t",&Name,&Password)!=EOF)		/*���ļ�,���ļ��е�ѧ������ȫ�����������㣬�Ա���ɾ���Ÿ�*/
	{
		//printf("���ڶ�ȡ�û���Ϣ\n");
		//printf("%s,%s,%d\n",Name,Password,list->size);
		strcpy(list->users[list->size].userName,Name);
		//printf("���ڶ�ȡ�û���Ϣ1...11...\n");
		strcpy(list->users[list->size++].userPassword,Password);
		//printf("%d",list->size);														
	}
	fclose(fp);																						/*�ر��ļ�*/ 
	printf("��ȡ�û���Ϣ��ϣ�\n");
	Sleep(1000);
	return ;
}
void writeUserToFile(userList* userList)
{
	FILE* fp = fopen("�û���Ϣ.txt", "w");
	if (fp == NULL)
	{
		printf("ERRPR:�û��ļ�д��\n");
		system("pause");
		return;
	}
	for (int i = 0;i < userList->size;i++)
	{
		fprintf(fp, "%s\t%s\t\n", userList->users[i].userName, userList->users[i].userPassword);
	}
	printf("�û�д����ϣ�\n");
	fclose(fp);	
	return;
}
void addUser(userList* userList)
{
	system("cls");
	char name[30];
	char password[30];
	printf("-----------------�����û�-------------------\n");
	printf("���������û�����\n");
	scanf("%s", name);
	fflush(stdin);
	printf("��Ϊ���û���������(6-30λ����\n");
	scanf("%s", password);
	fflush(stdin);
	while (strlen(password) < 6 || strlen(password) > 30)
	{
		printf("���볤�Ȳ��õ���6λ������30λ,���������룡\n");
		scanf("%s", password);
		fflush(stdin);
	}
	//printf("\n%d\n",userList->size);
	strcpy(userList->users[userList->size].userName, name);
	strcpy(userList->users[userList->size++].userPassword, password);
	//printf("\n%d\n",userList->size);
	printf("����û��ɹ���\n");
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
		printf("����û�й���Ա�û���\n");
		system("pause");
		return;
	}
	int i;
	for ( i = 0;i < list->size;i++)
	{
		printf("%d.%s\n", i + 1, list->users[i].userName);
	}
	printf("��ѡ����Ҫ���ĵ��û���\n");
	int choice = -1;
	scanf("%d", &choice);
	while (choice <= 0 || choice > list->size)
	{
		printf("������ı�ų���������Χ�����������룡\n");
		scanf("%d", &choice);
	}
	printf("������ԭ���룡\n");
	char word[20];
	scanf("%s", word);
	fflush(stdin);
	if (strcmp(word, list->users[choice - 1].userPassword) == 0)
	{
		char newword1[20];
		char newword2[20];
		printf("������������:\n");
		scanf("%s", newword1);
		fflush(stdin);
		while (strlen(newword1) < 6 || strlen(newword1) > 30)
		{
			printf("���볤�Ȳ��õ���6λ�����30λ�����������룡\n");
			scanf("%s", newword1);
		}
		printf("���ٴ�ȷ��������:\n");
		scanf("%s", newword2);
		if (strcmp(newword1, newword2) == 0)
		{
			strcpy(list->users[choice - 1].userPassword, newword1);
			printf("�����޸���ɣ�\n");
			return;
		}
	}
	else
	{
		printf("������󣡽�ֹ�޸ģ�\n");
		return;
	}
}

void deleteUser(userList* list)
{
	system("cls");
	printf("-----------------ɾ���û�-------------------\n");
	if (list->size == 0)
	{
		printf("ERROR:û�й���Ա�û���\n");
		system("pause");
		return;
	}
	int i;
	for ( i = 0;i < list->size;i++)
	{
		printf("%d.%s\n", i + 1, list->users[i].userName);
	}
	printf("��ѡ����Ҫɾ�����û���\n");
	int choice = -1;
	scanf("%d", &choice);
	while (choice <= 0 || choice > list->size)
	{
		printf("������ı�ų���������Χ�����������룡\n");
		fflush(stdin);
		scanf("%d", &choice);
	}
	char word[30];
	printf("��������û���ԭ���룺\n");
	scanf("%s", word);
	if (strcmp(word, list->users[choice - 1].userPassword) == 0)
	{
		int i;
		for ( i = choice;i < list->size;i++)
		{
			list->users[i - 1] = list->users[i];
		}
		list->size--;
		printf("ɾ����ɣ�\n");
	}
	else
	{
		printf("�������,��ֹɾ����\n");
	}
	return;
}
char* Login(userList* userList)
{
	system("cls");
	printf("-----------------��¼-------------------\n");
	if (userList->size == 0)
	{
		printf("�û�Ϊ�գ�����ע���û���\n");
		system("pause");
		addUser(userList);
		return NULL;
	}
	char name[20];
	char word[20];
	int flag = 0;
	printf("�������û�����\n");
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
		printf("�û��������ڣ������˳���\n");
		exit(0);
	}
	printf("�������¼����:\n");
	scanf("%s", word);
	fflush(stdin); 
	for (j = 0;j < 4;j++)
	{
		if (strcmp(userList->users[i].userPassword, word) == 0)				//i�����������û�����ȡ���±� 
		{
			printf("��¼�ɹ���\n");
			Sleep(1000);
			return userList->users[i].userName;
		}
		if(j!=4) printf("�������������%d��������ᣡ\n", 4 - j);
		scanf("%s", word);
	}
	printf("3������������󣬳����˳���\n");
	exit(0);
}
struct Node* createList()													//��������ͷ��� 
{
	struct Node* head= (struct Node*)malloc(sizeof(struct Node));
	head->next=NULL;
	return head;
}
struct Node* createNode(struct student data)								//������� 
{
	struct Node* nNode= (struct Node*)malloc(sizeof(struct Node));
	nNode->student= data;
	nNode->next= NULL;
	return nNode;
} 

void insertNodebyhead(struct Node*headNode,struct student data)				/*ͷ���� ���ñ��� */ 
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
		printf("�û���Ϊ0��\n");
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
void printList (struct Node* L)												/*���������ȫ��ѧ����Ϣ*/ 
{
	struct Node*p=L->next;
	if(p == NULL)
	{
		printf("��û��¼��ѧ����Ϣ����������ѧ����Ϣ\n");
		return ;
	}
	printf("-----------------��ѯ��ȫ��ѧ����Ϣ����-------------------\n");
	printf("���\t����\t����\t�Ա�\t�绰\n");
	while (p)
	{
		printf("%d\t%s\t%d\t%s\t%s\n",p->student.po,p->student.name,p->student.age,p->student.sex,p->student.tel);
		p = p->next;
	}
	printf("\n");
}
void showmenu0(){															/*��ӡ���˵�*/
	system ("cls");
	printf("-----------------------��ѧ����Ϣ����ϵͳ��-----------------------");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 0.�˳� *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 1.��¼ *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 2.ע�� *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
	printf("\n �밴��ѡ�񣬻س�ȷ��\n");
	printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}
void showmenu1(){															/*��ӡ���˵�*/
	system ("cls");
	printf("-----------------------��ѧ����Ϣ����ϵͳ��-----------------------");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 0.�˳� *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 1.�鿴ȫ��ѧ����Ϣ *-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 2.¼��ѧ����Ϣ *-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 3.ɾ��ѧ����Ϣ���������� *-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 4.����ѧ����Ϣ(��ѧ��) *-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 5.��ѯѧ����Ϣ����ѧ�ţ� *-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 6.����ѧ����Ϣ *-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-* 7.�����û���Ϣ *-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
	printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\n �밴��ѡ�񣬻س�ȷ��\n");
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
void deNode(struct Node* L,char*name){										/*�ҵ�ѧ��������ɾ�����*/ 
	struct Node*p1=L;	
	struct Node*p2=L->next;
	if(p2==NULL){
		printf("����ѧ��������������ɾ��\n");
		return ;
	}
	while(strcmp(p2->student.name,name)){
		p1=p2;
		p2=p2->next;
		if(!p2){
			printf("δ�ҵ�ָ��λ���޷�ɾ����\n");
			return ; 
		}
	}
	//�ҵ�
	 p1->next=p2->next;
	 free(p2); 
}

struct Node* searchdatabyname(struct Node* L,char *name){							/*������,����ѧ�����ڽ��*/ 
	struct Node*p=L->next;
	if(!p){
		return NULL;													/*�Ҳ����ڷ��ؿ�����ӡ����*/
	}
	while(strcmp(p->student.name,name)){
		p=p->next;
		if(!p){
			return NULL;														/*�ⲿ��ӡ������Ϣ*/
		}
	}
	return p;																/*�Ҳ����ڷ��ؿս��ӡ����*/ 
}

struct Node* searchdatabynumber(struct Node* L,int targetnumber){						/*��ѧ��,����ѧ�����ڽ��*/ 
	struct Node*p=L->next;
	if(!p){
		return NULL;													/*�Ҳ����ڷ��ؿս��ӡ����*/ 
	}
	while(targetnumber!=p->student.po){
		p=p->next;
		if(!p){
			return NULL;												/*�ⲿ��ӡ������Ϣ*/
		} 
	}
	return p;															/*�Ҳ����ڷ��ؿս��ӡ����*/ 
}

void readInfor(struct Node*head,const char* filename){			/*���ļ�����*/
	FILE *fp=fopen(filename,"r");						/*���ļ�*/
	printf("���ڶ�ȡ�ļ�......\n");
	Sleep(300); 
	struct student temp;
	if(!fp) {
		printf("���󣺴��ļ�%sʧ�ܣ����ܲ����ڣ�\n�������ļ�...\n",filename); 
		fopen(filename,"w+");								
	}
	while(fscanf(fp,"%d\t%s\t%d\t%s\t%s",&temp.po,temp.name,&temp.age,temp.sex,temp.tel)!=EOF)		/*���ļ�,���ļ��е�ѧ������ȫ�����������㣬�Ա���ɾ���Ÿ�*/
	{
		insertNodebyhead(head,temp);																/*ͷ���������´򿪳�������ǴӴ�С��*/ 
	}
	fclose(fp);																						/*�ر��ļ�*/ 
}

void writeintofile(struct Node*head,const char* filename) {								/*���ļ���дѧ����Ϣ*/
	FILE *fp=fopen(filename,"w");															/*���ļ�,"w"����ļ����ڣ���ô����ļ�����,"a"Ϊ׷��*/	
	struct Node*p=head->next;
	if (fp == NULL)											//���ļ�����ʱ��fopen() ������һ����ָ��
	{
		printf("ERRPR:ѧ���ļ�д��\n");
		system("pause");
		return;
	}
	while(p){
		fprintf(fp,"%d\t%s\t%d\t%s\t%s\n",p->student.po,p->student.name,p->student.age,p->student.sex,p->student.tel);										/*�ļ��д�����Ϣ*/
		p=p->next;
	} 
	printf("ѧ��д����ϣ�\n");
	fclose(fp);																		/*�ر��ļ�*/ 
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
			printf("�˳�\n");
			exit(1);
		case 1:
			userNm = Login(*&list);
			printf("\n��ӭ%s��¼ѧ������ϵͳ��\n",userNm);
			return userNm;
		case 2:
			addUser(*&list);
			writeUserToFile(*&list);
			userNm = Login(*&list);
			return userNm;
		default:
			printf("ERROR0:ѡ�����\n");
			exit(0);
			break; 
	}
	
}

void keydown1(struct Node* list,const char *filename,userList* userList){
	int choice = -1;
	fflush(stdin);
	scanf("%d",&choice);
	fflush(stdin);										/*�Է�����switch����*/
	struct student temp; 													/*�����ߵ���ʱѧ��������¼��ѧ����Ϣ */ 
	struct Node *tp=NULL;													/*��ʱ��㣬����ɾ����Ϣʱɾ�����*/ 
	int temp1=-1;
	//const char *filename = strcat(userNm,".txt");
	switch (choice)
	{
		case 0:
			printf("�����˳�\n");
			exit(0);
			break;
		case 1:
			printf("------------------���鿴ȫ��ѧ����Ϣ��------------------\n");			/*��ӡ��Ϣ */ 
			printList(list);
			break;
		case 2:
			printf("--------------------��¼��ѧ����Ϣ��--------------------\n");			/*��ѧ����Ϣ�����½�㣬�ٲ��� */ 
			printf("������ѧ��ѧ�ţ����������䣬�Ա𣬵绰\n");
			fflush(stdin);
			while(scanf("%d%s%d%s%s",&temp.po,temp.name,&temp.age,temp.sex,temp.tel)!=5){
				fflush(stdin);																/*����Ӱ����һ������*/
				printf("����������ݲ���ȷ�������·�����������ȷ��Ϣ��\n");
				continue; 
			} 
			fflush(stdin);
			insertNodebyhead(list,temp); 
			writeintofile(list,filename);							/*�����Ͻ������ݵĸĶ��������ļ���*/ 
			break;
		case 3:																			//������case�¶������ 
			printf("--------------------��ɾ��ѧ����Ϣ��--------------------\n");
			printf("������ɾ����ѧ������\n"); 
			scanf("%s",temp.name);
			fflush(stdin);
			tp=searchdatabyname(list,temp.name);
			if(tp){
				printf("ѧ��\t����\t����\t�Ա�\t�绰\n");
				printf("%d\t%s\t%d\t%s\t%s\n",tp->student.po,tp->student.name,tp->student.age,tp->student.sex,tp->student.tel);
			}
			else{
				printf("û������%s��ѧ��\n",temp.name); 
			}
			deNode(list,temp.name);
			writeintofile(list,filename) ;							/*�����Ͻ������ݵĸĶ��������ļ���*/ 
			break;
		case 4:{
			printf("--------------------������ѧ����Ϣ��--------------------\n");
			printf("1.����1��ѧ�Ŵ�С��������\n2.����2��ѧ�ŴӴ�С����\n");
			int choice = -1;
			fflush(stdin);
			scanf("%d",&choice);
			switch (choice)
			{
				case 1:
				{
					stolsort(list); 
			        printf("------------��ѧ�Ŵ�С�����źõ�ѧ����Ϣ��---------------\n");
		        	printList(list); 
		        	break; 
				}
				case 2:
				{
					stolsort1(list);
			        printf("------------��ѧ�ŴӴ�С�źõ�ѧ����Ϣ��---------------\n");
		        	printList(list);
		        	break;
				}
				default:
				{
					printf("�������\n");
					break;
				}
			}	 
			writeintofile(list,filename) ;							/*�����Ͻ������ݵĸĶ��������ļ���*/ 
			break;	 
		}
		case 5:{
			printf("---------------����ѯѧ����Ϣ����ѧ�ţ���----------------\n");
			printf("������Ҫ��ѯ��ѧ��ѧ��\n");
			temp1=-1;
			scanf("%d",&temp1);
			tp=searchdatabynumber(list,temp1);
			if(tp){
				printf("ѧ��\t����\t����\t�Ա�\t�绰\n");
				printf("%d\t%s\t%d\t%s\t%s\n",tp->student.po,tp->student.name,tp->student.age,tp->student.sex,tp->student.tel);
			}
			else{
				printf("��ѧ�Ų��Ҳ�����ѧ����\n"); 
			}
			break;
		}
		case 6:{
			printf("--------------------������ѧ����Ϣ��--------------------\n");
			printf("������Ҫ���ĵ�ѧ��ѧ��\n");
			scanf("%d",&temp1);
			tp=searchdatabynumber(list,temp1);								//���ҵ� 
			if(tp){
				printf("����������ȷ��Ҫ���ĵ�����\n");
				printf("\n\n 1.����ѧ��ѧ��\n\n");
				printf("\n\n 2.����ѧ������\n\n");
				printf("\n\n 3.����ѧ������\n\n");
				printf("\n\n 4.����ѧ���Ա�\n\n");
				printf("\n\n 5.����ѧ���绰\n\n");
				printf("\n\n �밴��ѡ�񣬻س�ȷ��\n");
			}
			else {
				printf("������ѧ��Ϊ%d��ѧ��\n",temp1);
				break; 
			}
			int choice = -1,temp1=-1;
			fflush(stdin);
			scanf("%d",&choice);
			fflush(stdin);
			int temppo=-1,tempage=-1; 
			char tempname [20],tempsex[5],temptel[13];					/*û�е���*/
			switch(choice){
				case 1:
					printf("�������µ�ѧ��\n");
					scanf("%d",&temppo);
					tp->student.po=temppo;
					printf("ѧ���޸�����ɣ�"); 
					break;
				case 2:
					printf("�������µ�����\n");
					scanf("%s",tempname);
					strcpy(tp->student.name,tempname);
					printf("�����޸�����ɣ�"); 
					break;
				case 3:
					printf("�������µ�����\n");
					scanf("%d",&tempage);
					tp->student.age=tempage;
					printf("�����޸�����ɣ�"); 
					break;
				case 4:
					printf("�������µ��Ա�\n");
					scanf("%s",&tempsex);
					strcpy(tp->student.sex,tempsex);
					printf("�Ա��޸�����ɣ�"); 
					break;
				case 5:
					printf("�������µĵ绰\n");
					scanf("%s",&temptel);
					strcpy(tp->student.tel,temptel);
					printf("�绰�޸�����ɣ�"); 
					break;
				default:
					printf("ѡ�����\n");
					system("pause"); 
					break; 
			}
			writeintofile(list,filename) ;							/*�����Ͻ������ݵĸĶ��������ļ���*/ 
			break;
		}
		case 7:{
			system("cls");
			printf("--------------------�������û���Ϣ��--------------------\n");
			printf("1.����û�\n2.�޸��û�����\n3.ɾ���û�\n4.�鿴�����û�\n");
			fflush(stdin);
			printf("��ѡ��\n");
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
					printf("�������\n");
					break;
				}
			}	 
		}
		break; 
		default:{
			printf("ѡ�����\n");
			break;
		}
	}
}

int main(){
	system("color 7C");
	const char *userFile = "�û���Ϣ.txt";
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
	readInfor(list,filename); 								/*�Ȱ��ļ��е�ѧ������ȫ�����������㣬�Ա���ɾ���Ÿ�*/
	//printf("333");
	while(1){	
		showmenu1();											/*չʾ����*/ 
		keydown1(list,filename,&List);											/*��������ֵ*/ 	
		system("pause");									
		system("cls");								 
	}
	return 0;
}

