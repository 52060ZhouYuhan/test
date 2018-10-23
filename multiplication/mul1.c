#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "add.h"
#define MAXMINE 100

char* multiplication(char* m,char* n );
void main(){
	char m[MAXMINE];
	char n[MAXMINE];
	
	printf("first number:m=  \n");
	scanf("%s",m);
	printf("second number:n=  \n");
	scanf("%s",n);
	
	char* mul=multiplication(m,n);
	printf("mul=  %s\n",mul);
	free(mul);
}

char* multiplication(char* a,char* b){
	int a_length=strlen(a);
	int b_length=strlen(b);
	int length=a_length+b_length;
	char* result=(char*)malloc(length + 1);
	memset(result,'0',length);
	result[length] = '\0';
	char* result_2=(char*)malloc(length + 1);
	memset(result_2,'0',length);
	result_2[length] = '\0';
	
	char* temp_long=a;
	char* temp_short=b;

	
	int i,j;
	int cb=0,ww=0;
	int t=length -1;
	int count = 0;
	for(i = b_length - 1; i >= 0; i--){ //
		t = length - 1 - count;
		memset(result_2,'0',length);
		cb = 0; 
		for(j = a_length - 1; j >= 0; j--){
			ww=(a[j]-'0')*(b[i]-'0')+cb;
			result_2[t]=ww%10;
			cb=ww/10;
			result_2[t] = result_2[t] + '0';
			t--;
		}
		if(cb!=0){
			result_2[t]=cb + '0';
		}
		char* temp_result = add(result_2,result);
		memcpy(result,temp_result,strlen(temp_result));
		free(temp_result);
		count = count + 1;
	}

	printf("------ result = %s\n", result);

    /**********************************/
	t=0;
	int result_length = strlen(result);
	char* mul = (char*)malloc(result_length+1);
	memset(mul,'0',result_length);
	int sig = 0;
	for(j=0;j<result_length;j++){
		if(sig == 0){
			if(result[j]=='0'){
				continue;
			}
			else
				sig = 1;
		}
		mul[t]=result[j];
		printf(" mul= %c ",mul[t]);
		t++;
	}
	mul[t]='\0';
	free(result_2);
	free(result);
	return mul;
}
