#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DuLNode{
	struct DuLNode *prior;
	struct DuLNode *next;
	int data;
}*DuLinkList;
/******注意：头指针只能指向所创建链表中的第一个节点的位置，头指针不包含于链表中******/
/******************creat Linklist****************************/
DuLinkList Creat(DuLinkList L){
	DuLinkList p,s;
	int m=0;
	p=L;
	p->next=L;
	p->prior=L;
	printf("-----将文件中的数据读入到链表!------\n");
	FILE *fp=fopen("/home/user/workspace/test/LinkList/input.txt","r");
	if(fp==NULL){
		printf("open error\n");
		return NULL;
	} 
	int x;

	int length=0;
	int counter=0;
	while(!feof(fp)){
		fscanf(fp,"%d",&x);
		if(counter == 0){
			length = x;
			counter++;
			continue;
		}
		counter = counter + 1;

		s=(DuLinkList)malloc(sizeof(struct DuLNode));
		s->data=x;
		s->next=p->next;
		s->prior=p;
		p->next->prior=s;
		p->next=s;
		p=s;
		printf("%d  ",p->data);
		if(counter == length + 1)
			break;
	}
	rewind(fp);
	fclose(fp);	
	printf("\n------length=%d\n",length);

	/*******************将链表的头部和尾部连接起来*****************/
	L->prior=p;
	p->next=L;
	/*********************************************************/
	return L;
}

/*******************get the value*****************************/
DuLinkList Getelem(DuLinkList L,int n){
	DuLinkList p;
	p=L->next;
	int count=0;
	while(p!=L){
		count=count+1;
		p=p->next;
	}
	if(n>count){
		printf("The data to query is not in the right place!\n");
		return 0;
	}else{
		p=L;
		for(int i=0;i<n;i++)
		{
			p=p->next;
		}
		return p;
	}
}
//
DuLinkList bubleSort(DuLinkList L,int n);
DuLinkList mergesort(DuLinkList arr[],int start,int end);
//
void main(){
	int m,n;
	printf("Input the length of LinkList!\n");
	DuLinkList L,p;
	L=(DuLinkList)malloc(sizeof(struct DuLNode));
	L=Creat(L);
	
	printf("print the data in linklist!\n");
	p=L->next;
    while(p!=L){
    	printf("%d	",p->data);
    	p=p->next;
    }
    printf("\n----------显示链表首尾的数据-----------");
    printf("\n------------%d  %d\n",L->prior->data,L->next->data);
    printf("\n Input the location of searching data\n");
    scanf("%d",&n);
	DuLinkList t,t1;
	t=Getelem(L,n); 
	printf("The data is:%d\n",t->data);	
	/********************************************************/

	FILE *fp=fopen("/home/user/workspace/test/LinkList/input.txt","r");
	if(fp==NULL){
		printf("open error\n");
	} 
	printf("--------计算文件中数据长度---------\n");
	int x;
	int length=0;
	int counter = 0;
	while(!feof(fp)){
		fscanf(fp,"%d",&x);//该行不能缺省，否则无法正确计算文件中的数据长度,fscanf函数读取了一个数据后，对指针有一个后移的操作，若缺少本行，指针的位置一直没有改变
		if(counter == 0){
			length = x;
			counter++;
			continue;
		}
		counter = counter + 1;
		
		printf("x=%d	",x);
		if(counter == length + 1)
			break;
	}
	printf("\n--------------------------------------------\n");
    m=length;
	printf("-----m=%d\n",m);	
	fclose(fp);
	/*******************************************************/
	/***********将链表中数据节点的指针地址存入到一个数组中**********/
	/*******************************************************/
	p=L->next;
	DuLinkList* arr=(DuLinkList*)malloc(m*sizeof(DuLinkList));
	int i;
	for(i=0;i<length;i++){
		arr[i]=p;
		p=p->next;
		printf("arr[%d]=%p		",i,arr[i]);
		printf("arr[%d]->data=%d	\n",i,arr[i]->data);
	}
	printf("\n");
	/*******************************************************/
	/********************该处要调用排序函数********************/
	/*******************************************************/
	mergesort(arr,0,m-1);
	for(i=0;i<length;i++){
		printf("arr[%d]->data=%d\n",i,arr[i]->data);
	}
    //p=L->next;
	L->next = arr[0];
	p = arr[0];
	for(i=1;i<length;i++){
		p->next = arr[i];
    	p=arr[i];
    	p->prior = arr[i-1];
    	printf("p=%p	",p);
	}
	p->next = arr[0];
	arr[0]->prior = p;
	
//    	bubleSort(L,m);
	/******************************************************/
	/******************************************************/
	printf("\n");
	t1=L->next;
    while(t1->next != NULL){
    	printf("node data = %d	",t1->data);
    	t1=t1->next;
    	if(t1 == L->next)
    		break;
    }

    printf("\n");
    printf("\n----------显示链表首尾的数据-----------");
    printf("\n---------------%d  %d\n",L->prior->data,L->next->data);
	p=L->next;
	DuLinkList temp_p;
    while(p->next != NULL){
    	temp_p = p->next;
    	free(p);
    	p=temp_p;
    	if(p == L->next){
    		free(p);
    		break;
    	}
    }
	free(L);
	
}


















