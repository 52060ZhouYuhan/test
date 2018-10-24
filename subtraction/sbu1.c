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
	
	char* result=subtraction(m,n);
	printf("\n sub= %s\n",result);
	free(result);
 }

/*********************************************/
char* subtraction(char* subtractor,char* minuend){
	int subtractor_length = strlen(subtractor);
	int minuend_length = strlen(minuend);
	char* temp_long=NULL;
	char* temp_short=NULL;
	
	
	int max,min,index;
	if(subtractor_length>=minuend_length){
		temp_long=subtractor;
		temp_short=minuend;
		max = subtractor_length;
		min = minuend_length;
		index = 0;
	}else{
		temp_long=minuend;
		temp_short=subtractor;
		max = minuend_length;
		min = subtractor_length;
		index = 1;
		printf("the result is negative: -");
	}
	char* result = (char*)malloc(max+2);
	memset(result,'0',max+1);
	result[max+1]='\0';
	
	
	int i,j,ww,cb=0;
	j=min-1;
	/****************************************/
	for(i=max-1;i>=max-min;i--){        //
		if(temp_long[i]<temp_short[j]){
			cb=1;
			ww=(temp_long[i]-'0')-(temp_short[j]-'0')+cb*10;
			result[i+1]=ww%10+'0';
			if(temp_long[i-1]-cb<'0'){///
				temp_long[i-1] = 9+'0';
				cb=1;
			}else{
				temp_long[i-1] = temp_long[i-1]-cb;
				cb=0;
			}
		}else{
			cb=0;
			ww=(temp_long[i]-'0')-(temp_short[j]-'0')+cb*10;
			result[i+1]=ww%10+'0';
		}
		j--;
	}
	if(j == i){
		if(cb == 1){
			result[0]=45;
		}else{
			result[0]='0';
		}
	}else{
		int k=i;
		for(;k>=0;k--){
			result[k]=temp_long[k];
		}
	}
return result;
}


