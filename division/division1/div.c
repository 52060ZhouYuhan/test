#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sbu1.h"
#include "mul2.h"


#define MAXMINE 100

char* division(char* m,char* n);
void main(){
	char m[MAXMINE];
	char n[MAXMINE];
	
	printf("divisor=  \n");
	scanf("m= %s",m);
	printf("dividend=  \n");
	scanf("n= %s",n);
	
	char* result=division(m,n);
	printf("result= %s\n",result);
}

/*************************************************************************************/
char* division(char* a,char* b){/***********a is divisor,b is dividend****************/
	int a_length=strlen(a);
	int b_length=strlen(b);
	
	
	
	int i;
	int point_location_a,point_location_b;
	for(i=0;i<a_length;i++){
		if(a[i]=='.'){
			point_location_a=i;
		}else{
			point_location_a=a_length;
		}
	}
	for(i=0;i<b_length;i++){
		if(b[i]=='.'){
			point_location_b=i;
		}else{
			point_location_b=b_length;
		}
	}
	int w_a=a_length-point_location_a-1;//the long of numbers behind point
	int w_b=b_length-point_location_b-1;
	int temp_a_length;
	int temp_b_length;
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
	/******************************************************************/
	char* temp_a=(char*)malloc(temp_a_length+1);
	memset(temp_a,'0',temp_a_length);
	temp_a[temp_a_length]='\0';
	char* temp_b=(char*)malloc(temp_b_length+1);
	memset(temp_b,'0',temp_b_length);
	temp_b[temp_b_length]='\0';
	
	/***************a:give number to temp_a****************************/
	int t_a=0;
	for(i=0;i<a_length;i++){
		if(a[i]=='.'){
			continue;
		}
		temp_a[t_a]=a[i];
		t_a++;
	}
	/****************b:give number to temp_b****************************/
	int t_b=0;
	for(i=0;i<b_length;i++){
		if(b[i]=='.'){
			continue;
		}
		temp_b[t_b]=b[i];
		t_b++;
	}
	/*******************************************************************/
	
	int ww_b,ww_a,point_location,index;
	int result_length;
	
	if(temp_a_length>temp_b_length){
		index=0;
		result_length=temp_a_length-temp_b_length+4;//last bit is used for judging rounding
		ww_a=temp_a_length;
		ww_b=temp_a_length-1;
		point_location=temp_a_length-temp_b_length+1;
	}else if(temp_a_length<temp_b_length){
		index=1;
		result_length=temp_b_length-temp_a_length+4;//last bit is used for judging rounding
		ww_a=temp_b_length+1;
		ww_b=temp_b_length;
		point_location=1;
	}else if(temp_a_length==temp_b_length){
		index=2;
		result_length=4;                            //last bit is used for judging rounding
		ww_a=temp_a_length+1;
		ww_b=temp_b_length;
		point_location=1;
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
	/******************start dividing***********************************/
	char* result=(char*)malloc(result_length+1);
	memset(result,'0',result_length);
	result[result_length]='\0';
	
	char* c=NULL;
	char* d=NULL;
	int t=0,j;
	for(t=0;t<result_length-1;t++)
	for(i=1;;i++){
		c=multiplication(dividend,i+'0');
		d=subtraction(divitor,c);
		if(d[0]=='-'){
			result[t]=i-1+'0';
			i=1;
			c=multiplication(dividend,i-1+'0');
			d=subtraction(divitor,c);
			for(j=0;j<ww_a-1;j++){/*********update divitor**************/
				divitor[j]=d[j+1];
			}
			divitor[j]='0';
		}
	}
	printf("result= %s",result);
	
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//	int point_location,index;
//	char* c=NULL;
//	char* temp=NULL;
//	int i;
//	if(a_length>b_length){
//		index=0;//show that a_length>b_length;
//		if(a[0]>b[0]){
//			point_location=a_length-b_length+1;
//		}else if(a[0]<b[0]){
//			point_location=a_length-b_length;
//		}else if(a[0]==b[0]){
//			for(i=0;i<b_length;i++){
//				c[i]=a[i];
//			}
//			temp=subtraction(c,b);
//			if(temp[0]=='-'){
//				point_location=a_length-b_length;
//			}else{
//				point_location=a_length-b_length+1;
//			}
//		}
//	}else if(a_length<b_length){
//		index=1;//show that a_length<b_length;
//		point_location=1;
//	}else if(a_length==b_length){
//		index=2;//show that a_length==b_length;
//		point_location=1;		
//		}
//	}
//	
//	/**********the code above is to determine the position of the decimal point*******/
//	/*********************************************************************************/
//int w,n,u,t=0;
//	if(index==0){//a_length>b_length;
//		
//	}else if(index==1){//a_length<b_length;
//		
//	}else if(index==2){//a_length==b_length;
//		
//	}

	
//}


