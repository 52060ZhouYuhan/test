//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//#define MAXMINE 100
//
//char* subtraction(char* m,char* n);
//void main(){
//	char m[MAXMINE];
//	char n[MAXMINE];
//	 
//	printf("subtractor =  \n");
//	scanf("%s",m);
//	printf("minuend =  \n");
//	scanf("%s",n); 
//	
//	char* result=subtraction(m,n);
//	printf("\n sub= %s\n",result);
//	free(result);
// }
//
///*********************************************/
//char* subtraction(char* subtractor,char* minuend){
//	int subtractor_length = strlen(subtractor);
//	int minuend_length = strlen(minuend);
//	char* temp_long=NULL;
//	char* temp_short=NULL;
//	
//	
//	int max,min,index;
//	if(subtractor_length>=minuend_length){
//		temp_long=subtractor;
//		temp_short=minuend;
//		max = subtractor_length;
//		min = minuend_length;
//		index = 0;
//	}else{
//		temp_long=minuend;
//		temp_short=subtractor;
//		max = minuend_length;
//		min = subtractor_length;
//		index = 1;
//		printf("the result is negative: -");
//	}
//	char* result = (char*)malloc(max+2);
//	memset(result,'0',max+1);
//	result[max+1]='\0';
//	
//	
//	int i,j,ww,cb=0;
//	j=min-1;
//	/****************************************/
//	for(i=max-1;i>=max-min;i--){        //
//		if(temp_long[i]<temp_short[j]){
//			cb=1;
//			ww=(temp_long[i]-'0')-(temp_short[j]-'0')+cb*10;
//			result[i+1]=ww%10+'0';
//			if(temp_long[i-1]-cb<'0'){///
//				temp_long[i-1] = 9+'0';
//				cb=1;
//			}else{
//				temp_long[i-1] = temp_long[i-1]-cb;
//				cb=0;
//			}
//		}else{
//			cb=0;
//			ww=(temp_long[i]-'0')-(temp_short[j]-'0')+cb*10;
//			result[i+1]=ww%10+'0';
//		}
//		j--;
//	}
//	if(j == i){
//		if(cb == 1){
//			result[0]=45;
//		}else{
//			result[0]='0';
//		}
//	}else{
//		int k=i;
//		for(;k>=0;k--){
//			result[k]=temp_long[k];
//		}
//	}
//return result;
//}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXMINE 100

char* subtraction(char* m,char* n);
void main(){
	char m[MAXMINE];
	char n[MAXMINE];
	 
	printf("subtractor =  \n");
	scanf("%s",m);
	printf("minuend =  \n");
	scanf("%s",n); 
	
	char* result_3=subtraction(m,n);
	printf("\n sub= %s\n",result_3);
	free(result_3);
 }

/*********************************************/
char* subtraction(char* subtractor,char* minuend){
	int subtractor_length = strlen(subtractor);
	int minuend_length = strlen(minuend);
	char* temp_long=NULL;
	char* temp_short=NULL;
	char* temp=NULL;
	
	/******************pretreatment*********************/
	int max,min,index,index_1;
	if(subtractor_length>minuend_length){
		max=subtractor_length;
		min=minuend_length;
		temp_long=subtractor;
		temp_short=minuend;	
		index=0;
		index_1=0;
		printf("the result is positive: +\n");
	}else if(subtractor_length<minuend_length){
		max=minuend_length;
		min=subtractor_length;
		temp_long=minuend;	
		temp_short=subtractor;
		index=1;
		index_1=1;
		printf("the result is negative: -\n");
	}else if(subtractor_length=minuend_length){
		max=subtractor_length;
		min=minuend_length;
		temp_long=subtractor;
		temp_short=minuend;	
		index=2;
	}
	char* result_1=(char*)malloc(max);//long
	memset(result_1,'0',max);
	result_1[max]='\0';
	char* result_2=(char*)malloc(max);//short
	memset(result_2,'0',max);
	result_2[max]='\0';
	char* result_3=(char*)malloc(max+2);//result
	memset(result_3,'0',max+1);
	result_3[max+1]='\0';
	printf("result_3= %s\n",result_3);
	
	
	int i;
	if(index==2){
		for(i=0;i<max;i++){
			if(temp_long[i]>=temp_short[i]){
				result_1[i]=temp_long[i];
				result_2[i]=temp_short[i];
				index_1=0;
			}else{
				result_1[i]=temp_short[i];
				result_2[i]=temp_long[i];
				index_1=1;
			}
		}	
	}else{
		for(i=0;i<max;i++){
			result_1[i]=temp_long[i];
			result_2[i+max-min]=temp_short[i];
		}
	}
	printf("result_1= %s\n",result_1);
	printf("result_2= %s\n",result_2);

	
	/******************subtraction**************************/
	int cb=0,ww;
	for(i=max-1;i>=0;i--){
		if(result_1[i]>result_2[i]){
			result_3[i+1]=result_1[i]+'0'-result_2[i]-cb;
			cb=0;
		}else if(result_1[i]<result_2[i]){
			result_3[i+1]=result_1[i]+'0'+10-result_2[i]-cb;
			cb=1;
		}else if(result_1[i]==result_2[i]){
			if(cb==0){
				result_3[i+1]=result_1[i]+'0'-result_2[i]-cb;
				cb=0;
			}else{
				result_3[i+1]=result_1[i]+'0'+10-result_2[i]-cb;
				cb=1;
			}
		}
		printf("result_3= %c",result_3[i+1]);
	}
	if(index_1==1){
		result_3[0]='-';
		printf("the result is negative: - ");
	}
	else if(index_1==0){
		printf("the result is positive: + ");
	}
	free(result_1);
	free(result_2);
	return result_3;
}




