#include "DuLNode.h"

/**********************bubleSort******************************/
DuLinkList bubleSort(DuLinkList L,int n){
	int i,j; 
	DuLinkList p,t,s,temp;
	s=(DuLinkList)malloc(sizeof(struct DuLNode));
	p=L->next;
	t=p;
   /**********************************************************/
   /********次数为5×(5-1)/2，而改进后当进行到某一轮序列已经为正序排列时，
    直接跳出，而无需再进行多余的操作********************************/	
   /**********************************************************/
	int counter=0;
	for(j=0;j<n-1;j++){
		int judge=0;
		for(i=0;i<n-j-1;i++){
			if((p->data)>(p->next->data)){
				s->data=p->data;
				p->data=p->next->data;
				p->next->data=s->data;
				judge=1;
				counter++;
			}
			p=p->next; 
		}
		if(judge==0)
			break;
		p=t;
		}
		printf("counter=%d\n",counter);
	free(s);
}
