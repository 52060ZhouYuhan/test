#include <stdio.h>



#define MAX_length 10
  
/******************将两个有序序列合并为一个有序序列********************/
void combine(int arr[],int start,int m,int end){
	int aux[]={0};
	int i,j,k;
	for(i=start,j=m+1,k=0;k<=end-start;k++){
		if(i==m+1){
			aux[k]=arr[j++];
			continue;
		}
		if(j=end){
			aux[k]=arr[i++];
		    continue;
		}
		if(arr[i]<=arr[j]){
			aux[k]=arr[i++];
		}else{
			aux[k]=arr[j++];
		}
	}
	
	for(i=0,j=start;j<end;i++,j++){
		arr[j]=aux[i];
	}
}
/***************************************************************/
/***************************归并排序******************************/
/***************************************************************/
void mergesort(int arr[],int start,int end){
	int i;
	if(start<end)
		i=(start+end)/2;
	mergesort(arr,start,i);
	mergesort(arr,i+1,end);
	combine(arr,start,i,end);
}
/***************************************************************/
void main(){
	int arr[MAX_length]={12,11,3,2,5,13,9,4,7,15};
	mergesort(arr,0,MAX_length-1);
	int i;
	for(i=0;i<MAX_length;i++)
		printf("arr[%d]=%d  ",i,arr[i]);
}


