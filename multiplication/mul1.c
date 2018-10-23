#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
	char* result=(char*)malloc(length);
	memset(result,0,length);
	char* result_2=(char*)malloc(length);
	memset(result_2,0,length);
	
	char* temp_long=NULL;
	char* temp_short=NULL;


	int max,min,i,j;
	if(a_length>b_length){
		max = a_length;
		min = b_length;
		temp_long = a;
		temp_short = b;
	}else{
		max = b_length;
		min = a_length;
		temp_long = b;
		temp_short = a;
	}

	int cb=0,ww=0;//cb is carry bit
	/***********first***************/
	 int t=0;
    for(j=max-1;j>=0;j--){
    	ww=(temp_short[min-1]-'0')*(temp_long[j]-'0')+cb;
		result[t]=ww%10;
		cb=ww/10;
		t++;
    }
	if(cb!=0){
		result[t]=cb;
	}
	printf("\n t1= %d\n",t);
	for(t=0;t<length;t++)
		printf("result[t]= %d ",result[t]);//above is right;


    /**********************************/
	cb=0;
	for(i=min-2;i>=0;i--){
		t=min-1-i;
		for(j=max-1;j>=0;j--){
			ww=(temp_short[i]-'0')*(temp_long[j]-'0')+cb;
			result_2[t]=ww%10;
			cb=ww/10;
			t++;
		}
		if(cb!=0){
			result_2[t]=cb;
		}
		for(j=0;j<min-1-i;j++)
			result_2[j]=0;
		printf("\n\n");
		for(j=0;j<length;j++)
			printf("result_2[j]= %d ",result_2[j]);//
		printf("\n");

	    cb=0;
		for(j=0;j<length;j++){
			ww=result[j]+result_2[j]+cb;
			result[j]=ww%10;
			cb=ww/10;
		}
		printf("\n");

		if(cb!=0){
			result[j]=cb;
			printf("r[t]=%d \n",result[j]);
		}
		for(j=0;j<length;j++){
			printf("r1= %d ",result[j]);
		}
	}
	t=0;
	printf("\n\n");
	char* mul = (char*)malloc(length);
	memset(mul,'0',length);
for(j=length-1;j>=0;j--){
    if(result[j]==0){
    	continue;
    }
	mul[t]=result[j]+'0';
	printf(" mul= %c ",mul[t]);
	t++;
}
mul[t]='\0';
free(result_2);
free(result);
return mul;
}
