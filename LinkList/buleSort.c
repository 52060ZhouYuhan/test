#include <stdio.h>
#include <stdlib.h>



typedef struct DuLNode{
	struct DuLNode *prior;
	struct DuLNode *next;
	int data;
}*DuLinkList;


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
