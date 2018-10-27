#include  "sbu1.h" 

#define MAXMINE 100

void main(){
	char m[MAXMINE];
	char n[MAXMINE];
	 
	printf("subtractor =  ");
	scanf("%s",m);
	printf("\n");
	printf("minuend =  ");
	scanf("%s",n); 
	
	char* result_3=subtraction(m,n);
	printf("\nsub= %s\n",result_3);
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
		index_1=0;//show that the result is positive: + ;
	}else if(subtractor_length<minuend_length){
		max=minuend_length;
		min=subtractor_length;
		temp_long=minuend;	
		temp_short=subtractor;
		index=1;
		index_1=1;//show that the result is negative: - ;
		printf("the result is negative: -\n");
	}else if(subtractor_length==minuend_length){
		max=subtractor_length;
		min=minuend_length;
		temp_long=subtractor;
		temp_short=minuend;	
		index=2;
	}
	char* result_1=(char*)malloc(max+1);//long
	memset(result_1,'0',max);
	result_1[max]='\0';
	char* result_2=(char*)malloc(max+1);//short
	memset(result_2,'0',max);
	result_2[max]='\0';
	char* result_3=(char*)malloc(max+2);//result
	memset(result_3,'0',max+1);
	result_3[max+1]='\0';
	
	
	int i,tt=0,ww1;
	if(index==2){
		for(i=0;i<max;i++){
			if(temp_long[i]<temp_short[i]){
				tt++;
			}
			if(tt==0){
				index_1=0;
			}else{
				index_1=1;
			}
		}
		/*************************/
		for(i=0;i<max;i++){
			if(temp_long[i]>temp_short[i]){
				ww1=0;//show that temp_long>temp_short
				continue;
			}else if(temp_long[i]<temp_short[i]){
				ww1=1;//show that temp_long<temp_short
				break;
			} 
		}
			if(temp_long[i]==temp_short[i]){
				ww1=2;
			}			
		/*************************/
		if(ww1==1){//exchenge
			for(i=0;i<max;i++){
				result_1[i]=temp_short[i];
				result_2[i]=temp_long[i];
			}
		}else if(ww1==0||ww1==2)// no exchenge
			for(i=0;i<max;i++){
				result_1[i]=temp_long[i];
				result_2[i]=temp_short[i];
			}
		}else if(ww1==2){
			printf("the result=0");
		}
		printf("index_1= %d\nresult_1= %s\nresult_2= %s\n",index_1,result_1,result_2);
	/******************subtraction**************************/
	/*******************************************************/
	for(i=0;i<max;i++){
		if(subtractor_length>minuend_length){
			result_1[i]=temp_long[i];
			result_2[max-min+i]=temp_short[i];
		}else if(subtractor_length<minuend_length){//result is a negative number
			result_1[i]=temp_long[i];
			result_2[max-min+i]=temp_short[i];
		}
	}		
	/******************************************************/	
	/******************************************************/	
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
	}
	printf("\n");
	int result_3_length=strlen(result_3);
	if(index_1==1){
		result_3[0]='-';
		int sign=0;
		int sign_1=1;
		int ii;
		for(ii=1;ii<result_3_length+1;ii++){
			if(sign== 0&&result_3[ii] =='0'){
				continue;
			}else{
				result_3[sign_1]=result_3[ii];
				sign=1;
				sign_1++;
			}
		}		
		printf("the result is negative: - ");
	}
	else if(index_1==0){
		int sign=0;
	    int sign_1=0;
		int ii;
		if(ww1!=2){
		for(ii=0;ii<result_3_length+1;ii++){
			if(sign==0&&result_3[ii]=='0'){
				continue;
			}else{
				result_3[sign_1]=result_3[ii];
				sign=1;
				sign_1++;
			}
		}
		}else if(ww1==2){
			for(ii=result_3_length-1;ii<result_3_length+1;ii++){
				result_3[sign_1]=result_3[ii];
				sign_1++;
			}
		}
	}
	free(result_1);
	free(result_2);
	return result_3;
}




