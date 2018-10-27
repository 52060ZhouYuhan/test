#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sbu1.h"
#include "mul2.h"
#include "add.h"

#define MAXMINE 100

char* division(char* m,char* n);
void main(){
	char m[MAXMINE];
	char n[MAXMINE];
	
	printf("divisor=");
	scanf("m=%s",m);
	printf("dividend=");
	scanf("n=%s",n);
	
	char* result=division(m,n);
	printf("result= %s\n",result);
	free(result);
}

/*************************************************************************************/
char* division(char* a,char* b){/***********a is divisor,b is dividend****************/
	int a_length=strlen(a);
	int b_length=strlen(b);
	/*******************************************************************/
	/************************pretreatment*******************************/
	/*******************************************************************/
	int i,k_a,k_b;//k_a and k_b are used to determind  the result of w_a and w_b
	int a_dot,b_dot;
	int index_dot_a=0,index_dot_b=0;
	for(i=0;i<a_length;i++){
		if(index_dot_a==0){
			if(a[i]!='.'){
				a_dot=a_length;
				printf("divitor is a integer\n")
				k_a=0;//show that a is an integer
			}
		}else{
			index_dot_a=1;
			a_dot=i;
			k_a=1;//show that a is a decimals
			break;	
		}
	}
	for(i=0;i<b_length;i++){
		if(index_dot_b==0){
			if(b[i]!='.'){
				b_dot=b_length;
				printf("dividend is a integer\n");
				k_b=0;//show that b is an integer
			}
		}else{
			index_dot_b=1;
			a_dot=i;
			k_b=1;//show that b is a decimals
			break;
		}
	}
	int w_a,w_b;//the length of numbers behind dot
	if(k_a==0){
		w_a=a_length-a_dot;
	}else{
		w_a=a_length-a_dot-1;
	}
	if(k_b==0){
		w_b=b_length-b_dot;
	}else{ 
		w_b=b_length-b_dot-1;		
	}
	
	/*****************only getting rid of the dot in numbers***********************/
	int temp_a_length;
	int temp_b_length;
	if(k_a==0&&k_b==0){//a and b are integers
			temp_a_length=a_length;
			temp_b_length=b_length-1;// right
	}else if(k_a==1&&k_b==1){//a and b are decimals
		if(w_a>w_b){
			temp_a_length=a_length-1;
			temp_b_length=b_length-1+w_a-w_b;
		}else if(w_a<w_b){
			temp_a_length=a_length-1+w_b-w_a;
			temp_b_length=b_length-1;
		}else if(w_a==w_b){
			temp_a_length=a_length-1;
			temp_b_length=b_length-1;
		}
	}else if(k_a==0&&k_b==1){//a is an integer,b is a decimals
			temp_a_length=a_length+w_b;
			temp_b_length=b_length-1;	
	}else if(k_a==1&&k_b==0){//a is a decimals,b is an integer
			temp_a_length=a_length-1;
			temp_b_length=a_length-2;
	}
	printf("\n temp_a_length=%d\n temp_b_length=%d",temp_a_length,temp_b_length);
	
	
	
	
	/*******************************************************************/
	char* temp_a=(char*)malloc(temp_a_length+1);
	memset(temp_a,'0',temp_a_length);
	temp_a[temp_a_length]='\0';
	char* temp_b=(char*)malloc(temp_b_length+1);
	memset(temp_b,'0',temp_b_length);
	temp_b[temp_b_length]='\0';
	
	/***************a:give number to temp_a*****************************/
	int t_a=0;
	for(i=0;i<a_length;i++){
		if(a[i]=='.'){
			continue;
		}
		temp_a[t_a]=a[i];
		t_a++;
	}
	/************get rid of the zero in front of temp_a*****************/
	int sign=0;
	int index=0;
	for(i=0;i<temp_a_length+1;i++){
		if(sign==0){
			if(temp_a[i]==0){
				continue;
			}
		}else{
			temp_a[index]=temp_a[i];
			index++;
			sign=1;
		}
	}
	printf("index_a = temp_a_length%d\n",index);
	temp_a_length=index;//update temp_a_length,attention:the last is \0
	/****************b:give number to temp_b****************************/
	int t_b=0;
	for(i=0;i<b_length;i++){
		if(b[i]=='.'){
			continue;
		}
		temp_b[t_b]=b[i];
		t_b++;
	}
	/*************get rid of the zero in front of temp_b****************/
	sign=0;
	index=0;
	for(i=0;i<temp_b_length+1;i++){
		if(sign==0){
			if(temp_b[i]==0){
				continue;
			}
		}else{
			temp_b[index]=temp_b[i];
			index++;
			sign=1;
		}
	}
	printf("index_b = temp_b_length%d\n",index);
	temp_b_length=index;//update temp_b_length,attention:the last is \0
	
	
	/*******************************************************************/
	
	int ww_b,ww_a;//ww_a - ww_b ==1 
	int result_length,result_dot;//result_dot show the quotient's dot location
	
	if(temp_a_length>temp_b_length){
		index=0;
		result_length=temp_a_length-temp_b_length+4;//last bit is used for judging rounding
		ww_a=temp_a_length;
		ww_b=temp_a_length-1;
		result_dot=temp_a_length-temp_b_length+1;
	}else if(temp_a_length<temp_b_length){
		index=1;
		result_length=temp_b_length-temp_a_length+4;//last bit is used for judging rounding
		ww_a=temp_b_length+1;
		ww_b=temp_b_length;
		result_dot=1;
	}else if(temp_a_length==temp_b_length){
		index=2;
		result_length=4;                            //last bit is used for judging rounding
		ww_a=temp_a_length+1;
		ww_b=temp_b_length;
		result_dot=1;
	}
	char* divitor=(char*)malloc(ww_a+1);
	memset(divitor,'0',ww_a);
	divitor[ww_a]='\0';
	char* dividend=(char*)malloc(ww_b+1);
	memset(dividend,'0',ww_b);
	dividend[ww_b]='\0';
	
	for(i=0;i<temp_a_length;i++){
		divitor[i]=temp_a[i];
	}
	for(i=0;i<temp_b_length;i++){
		dividend[i]=temp_a[i];
	}
	/********************above is pretreatment**************************/
	/*******************************************************************/
	/******************start dividing***********************************/
	char* result=(char*)malloc(result_length+1);
	memset(result,'0',result_length);
	result[result_length]='\0';
	
	char* c;
	char* d;
	char* ii;
	int t=0,j;
	for(t=0;t<result_length-1;t++)
	for(i=1;;i++){
		ii[i]=i+'0';
		c=multiplication(dividend,ii[i]);
		d=subtraction(divitor,c);
		if(d[0]=='-'){
			ii[i]=ii[i]-1;
			result[t]=ii[i];
			i=1;
			c=multiplication(dividend,ii[i]);
			d=subtraction(divitor,c);
			for(j=0;j<ww_a-1;j++){/*********update divitor**************/
				divitor[j]=d[j+1];
			}
			divitor[j]='0';
		}
	}
	printf("result= %s",result);
	free(temp_a);
	free(temp_b);
	free(divitor);
	free(dividend);
}	
