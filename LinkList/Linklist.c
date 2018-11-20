#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct DuLNode{
	struct DuLNode *prior;
	struct DuLNode *next;
	int data;
}*DuLinkList;

/******************creat Linklist****************************/
DuLinkList Creat(DuLinkList L){
	DuLinkList p,s;
	int m=0;
	p=L;
	p->next=L;
	p->prior=L;
	printf("-----将文件中的数据读入到链表!------\n")
	FILE *fp=fopen("/home/user/workspace/LinkList/input.txt","r");
	if(fp==NULL){
		printf("open error\n");
		return NULL;
	} 
	int x;
	int length=0;
	while(!feof(fp)){
		fscanf(fp,"%d%*[^0123456789]",&x);
		s=(DuLinkList)malloc(sizeof(struct DuLNode));
		s->data=x;
		s->netx=p->next;
		s->prior=p;
		p->next->prior=s;
		p->next=s;
		p=s;
		length++;
		printf("%d  ",p->data);
	}
	rewind(p);
	printf("length=%d\n",length);
		
//	printf("input the inserted data:  \n");
//	for(int i=0;i<n;i++)
//	{
//		scanf("%d",&m);
//		s=(DuLinkList)malloc(sizeof(struct DuLNode));//s=(DuLinkList)malloc(sizeof(DuLinkList));is error
//		s->data=m;	
//		s->next=p->next;
//		s->prior=p;
//		p->next->prior=s;
//		p->next=s; 
//		p=s;
//	}
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
//
void main(){
	int m,n;
	printf("Input the length of LinkList!\n");
	DuLinkList L,p;
	L=(DuLinkList)malloc(sizeof(struct DuLNode));
	/*************************************************************/
	
	/**************************************************************/
	L=Creat(L);
	
	printf("print the data in linklist!\n");
	p=L->next;
    while(p!=L){
    	printf("%d	",p->data);
    	p=p->next;
    }
    
    printf("\n------------%d  %d\n",L->prior->data,L->next->data);
    printf("\n Input the location of searching data\n");
    scanf("%d",&n);
	DuLinkList t,t1;
	t=Getelem(L,n);
	printf("The data is:%d\n",t->data);	
	
	bubleSort(L,m);
	t1=L->next;
    while(t1!=L){
    	printf("%d	",t1->data);
    	t1=t1->next;
    }
    printf("\n");
    printf("---------------%d  %d\n",L->prior->data,L->next->data);
	p=L->next;
	DuLinkList temp_p;
    while(p!=L){
    	p=p->next;
    	temp_p = p->prior;
    	free(temp_p);
    }
	free(L);
}
/**********************bubleSort******************************/
DuLinkList bubleSort(DuLinkList L,int n){
	int i,j;
	DuLinkList p,t,s;
	s=(DuLinkList)malloc(sizeof(struct DuLNode));
	p=L->next;
	t=p;
	for(j=0;j<n-1;j++){
		for(i=0;i<n-j-1;i++){
			if((p->data)>(p->next->data)){
				s->data=p->data;
				p->data=p->next->data;
				p->next->data=s->data;
			}
			p=p->next;
		}
		p=t;
	}
	free(s);
}



















