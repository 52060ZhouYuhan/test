#include "DuLNode.h"
/*****************************************************************
   * merge_sort: 非递归实现 --迭代(自底向上)
   * 非递归思想: 将数组中的相邻元素两两配对。用merge函数将他们排序，
   * 构成n/2组长度为2的排序好的子数组段，然后再将他们排序成长度为4的子数组段，
   * 如此继续下去，直至整个数组排好序。
   * 针对链表，采用归并排序的非递归算法（迭代法）
 ****************************************************************/
DuLinkList merge_sort(struct DuLNode* arr[],int length){
	int i,left_min,left_max,right_min,right_max;
	DuLinkList* temp=(DuLinkList*)malloc(length*sizeof(DuLinkList));
	int j;
	 
	for(i=1;i<length;i*=2){
		for(left_min=0;left_min<length-i;left_min=right_max){
			right_min=left_max=left_min+i;
			right_max=right_min+i;
			
			if(right_max>length)
				right_max=length;
			j=0;
			while(left_min<left_max&&right_min<right_max){
				temp[j++]=(arr[left_min]->data)<(arr[right_min]->data)?arr[left_min++]:arr[right_min++];
			}
			while(left_min<left_max){
				arr[--right_min]=arr[--left_max];
			}
			if(j>0)
				arr[--right_min]=temp[--j];
			
		}
	}
	free(temp);
}
/****************************************************************
 * *************以下代码部分是针对一般的数组采用归并排序的非递归算法（迭代法）
 ****************************************************************/
//#include <stdio.h>
//#include <stdlib.h>

//void merge_sort(int arr[],int length){
//	int i,left_min,left_max,right_min,right_max;
//	int* p=(int*)malloc(length*sizeof(int));
//	int j;
//	
//	for(i=1;i<length;i*=2){
//		
//		for(left_min=0;left_min<length-i;left_min=right_max){
//			
//			right_min=left_max=left_min+i;
//			right_max=right_min+i;
//			
//			if(right_max>length){
//				right_max=length;
//			}
//			
//			j=0;
//			while(left_min<left_max&&right_min<right_max){
//				p[j++]=arr[left_min]<arr[right_min]?arr[left_min++]:arr[right_min++];
//				printf("------j=%d\n",j);
//			}
//			
//			
//			while(left_min<left_max){
//				arr[--right_min]=arr[--left_max];
//			}
//			
//			while(j>0){
//				arr[--right_min]=p[--j];
//			}
//			
//			
//		}
//	}
//			free(p);
//}
//	
//	
//	int main(void)
//	{
//	    int a[8] = { 5, 2, 4, 7, 1, 3, 2, 6 };
//	    merge_sort(a, 8);
//	 
//	    // print array
//	    int i;
//	    for (i = 0; i < 8; i++)
//	        printf("%d ", a[i]);
//	    printf("\n");
//
//	    return 0;
//	}


