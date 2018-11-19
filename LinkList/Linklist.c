#include <stdio.h>
//#include <stlib.h>
#include <string.h>
#include <malloc.h>

typedef struct DuLNode{
	int data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode,*DuLinkList;

/******************creat Linklist****************************/
DuLinkList Creat(DuLinkList L,int n){
	DuLinkList p,s;
	int m=0;
	p=L;
	p->next=L;
	p->prior=L;
	printf("input the inserted data:  \n");
	for(int i=0;i<n;i++)
	{
	scanf("%d",&m);
	s=(DuLinkList)malloc(sizeof(DuLNode));
	s->data=m;	
	s->next=p->next;
	s->prior=p;
	p->next->prior=s;
	p->next=s; 
	p=s;
	}
	return L;
}

/*******************get the value*******************************/
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
	L=(DuLinkList)malloc(sizeof(DuLNode));
	scanf("%d",&m);
	L=Creat(L,m);
	
	printf("print the data in linklist!\n");
	p=L->next;
    while(p!=L){
    	printf("%d	",p->data);
    	p=p->next;
    }
	
    printf("\n Input the location of searching data\n");
    scanf("%d",&n);
	DuLinkList t,t1;
	t=Getelem(L,n);
	printf("The data is:%d\n",t->data);	
	
	bubleSort(L,n);
	t1=L->next;
    while(t1!=L){
    	printf("%d	",t1->data);
    	t1=t1->next;
    }
    printf("\n");
	//printf("The data is:%d",t1->data);
}

/**********************bubleSort******************************/
DuLinkList bubleSort(DuLinkList L,int n){
	int i,j;
	DuLinkList p,t,s;
	//s=L->next;
	p=L->next;
	t=p->next;
	for(j=0;j<n-1;j++){
		for(i=0;i<n-j-1;i++){
			if(p->data>t->data){
				s->data=p->data;
				p->data=t->data;
				t->data=s->data;
			}
			p=p->next;
			t=t->next;
		}
	}
}


















