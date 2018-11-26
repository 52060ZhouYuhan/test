
/***************************************************************
 * 
 ****************针对链表，归并排序之递归排序法***********************
 *  
 * ************************************************************/
#include "DuLNode.h"

/******************将两个有序序列合并为一个有序序列********************/
DuLinkList combine(struct DuLNode* arr[],int start,int m,int end){
	struct DuLNode* aux[20]={0};
	int i,j,k;
	for(i=start,j=m+1,k=0;k<=end-start;k++){
		if(i==m+1){
			aux[k]=arr[j++];
			continue;
		}
		if(j==end+1){
			aux[k]=arr[i++];
			continue;
		}
		if((arr[i]->data)<=(arr[j]->data)){
			aux[k]=arr[i++];
		}else{
			aux[k]=arr[j++];
		}
	}
	i=0;
	printf("\n");
	for(j=start;j<end+1;j++){//		
		arr[j]=aux[i];
		printf("arr[%d]=%p	aux[%d]=%p		\n",j,arr[j],i,aux[i]);
		i++;
	}
}
/************************mergesort*****************************/
DuLinkList mergesort(DuLinkList arr[],int start,int end){
	int i;
	if(start<end){
    i=(start+end)/2;
	mergesort(arr,start,i);
	mergesort(arr,i+1,end);
	combine(arr,start,i,end);
	}
}