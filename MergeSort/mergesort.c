#include <stdio.h>
#include <stdlib.h>


#define MAX_length 10
  
void print(int arr[], int length){
	for(int i =0;i< length ; i++){
		printf("%d,",arr[i]);
	}
	printf("\n");
}
/******************将两个有序序列合并为一个有序序列********************/
void combine(int arr[],int start,int m,int end){
	int aux[MAX_length]={0};//int aux[]={0};this writing-method does not belong to C,but C++ 
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
		if(arr[i]<=arr[j]){
			aux[k]=arr[i++];
		}else{
			aux[k]=arr[j++];
		}
	}
	
	
	print(aux,10);//
	i = 0;
	for(j=start;j<end+1;j++){//
		arr[j]=aux[i];
		i++;
	}
}


/***************************************************************/
/***************************归并排序******************************/
/***************************************************************/
void mergesort(int arr[],int start,int end){
	int i;
	printf("start = %d, end = %d\n",start , end);
	if(start<end){//{}
		i=(start+end)/2;
		mergesort(arr,start,i);
		mergesort(arr,i+1,end);
		printf("before , start = %d, i=%d,end = %d\n", start, i , end);
		combine(arr,start,i,end);
		print(arr,10);
	}
}
/***************************************************************/
#define LENG 10
void main(){
	int arr[MAX_length]={12,11,3,2,5,13,9,4,7,15};
	mergesort(arr,0,MAX_length-1);
	int i;
	for(i=0;i<MAX_length;i++)
		printf("arr[%d]=%d  ",i,arr[i]);
}


