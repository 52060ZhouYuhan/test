#include "tool.h"

char* add(char* a,char* b){
	int a_length=strlen(a);
	int b_length=strlen(b);
	
	/************determine the length of a and b,then filling short*******************/
	int max,min,ww,cb=0;
	int j,i,v;
	char* temp_long = NULL;// index which long
	char* temp_short = NULL;

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

	char* temp = (char*)malloc(max);
	memset(temp,'0',max);

	int offet = max - min;
	for(i=max-1;i>max-min-1;i--){
		temp[i] = temp_short[i-offet];
		//printf("temp[i] = %c", temp[i]);
	}

	//printf("\n");

	for(j=max-1;j>=0;j--){
		ww=temp_long[j]-'0'+temp[j]-'0'+cb;
		temp[j]=ww%10 + '0';
		cb=ww/10;
		//printf("ww = %d , temp[j] = %c , cb = %d ,\n", ww, temp[j],cb);
	}
	int result_length = max;
	if(cb==1){
		result_length = result_length + 1;
	}

	char* result = (char*)malloc(result_length + 1); // 1 : '\0'
	result[result_length] = '\0';
	int temp_index = max -1;
	for(i = result_length - 1; i >=0 ; i--){
		result[i] = temp[temp_index];
		if(temp_index < 0){
			result[0] = cb + '0';
		}
		temp_index = temp_index - 1;
	}

	free(temp);

	return result;
}

char* multiplication(char* a,char* b){
	int a_length = strlen(a);
	int b_length = strlen(b);
	int length = a_length + b_length;
	char* result = (char*)malloc(length+1);
	memset(result,'0',length);
	result[length] = '\0';
	char* result_2 = (char*)malloc(length+1);
	memset(result_2,'0',length);
	result_2[length] = '\0';
	
	int i,j,t;
	int count=0,cb=0,ww=0;
	
	for(i=a_length-1;i>=0;i--){
		t =length-count-1;  
      memset(result_2,'0',length);
      cb=0;
		for(j=b_length-1;j>=0;j--){
			ww=(a[i]-'0')*(b[j]-'0')+cb;
			result_2[t]=ww%10+'0';
			cb=ww/10;
			t--;
		}
		if(cb!=0){
			result_2[t]=cb+'0';
		}
		char* temp_result=add(result,result_2);
		memcpy(result,temp_result,length);
		free(temp_result);
		count=count+1;
	}
	
	    int sign = 0;
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
			//printf(" mul= %c ",mul[t]);
			t++;
		}
		mul[t]='\0';
		free(result_2);
		free(result);
		return mul;	
}

char* subtraction(char* subtractor,char* minuend){
	int subtractor_length = strlen(subtractor);
	int minuend_length = strlen(minuend);
	char* temp_long=NULL;
	char* temp_short=NULL;
	char* temp = NULL;
	
	int i;
	// -------------------------------
	int max,min,swap = 0;
	int sign = 0;
	if(subtractor_length>minuend_length){
		max=subtractor_length;
		swap = 0;
	}else if(subtractor_length<minuend_length){
		max=minuend_length;
		swap = 1;
		sign = 1;
	}else{
		max=subtractor_length;
		swap = 2;
	}

	temp_long=(char*)malloc(max + 1);//long
	memset(temp_long,'0',max);
	memcpy(temp_long + max - subtractor_length,subtractor,subtractor_length);
	temp_long[max]='\0';
	
	temp_short=(char*)malloc(max + 1);//short
	memset(temp_short,'0',max);
	memcpy(temp_short + max - minuend_length , minuend , minuend_length);
	temp_short[max]='\0';


	char* result=(char*)malloc(max+2);//result
	memset(result,'0',max+1);
	result[max+1]='\0';
	
	//printf("temp_long = %s , temp_short = %s \n", temp_long, temp_short);

	if(swap == 1){
		temp = temp_long;
		temp_long = temp_short;
		temp_short = temp;
	}
	else if(swap == 2){
		for( i = 0; i < max; i++){
			if(temp_long[i] > temp_short[i]){
				break;
			}else if(temp_long[i] < temp_short[i]){
				temp = temp_long;
				temp_long = temp_short;
				temp_short = temp;
				sign = 1;
				break;
			}
		}
	}	

	//printf("----- temp_long = %s , temp_short = %s \n", temp_long, temp_short);

	
	int cb=0;
	for(i=max-1;i>=0;i--){
		if(temp_long[i]>temp_short[i]){
			result[i+1]=temp_long[i]+'0'-temp_short[i]-cb;
			cb=0;
		}else if(temp_long[i]<temp_short[i]){
			result[i+1]=temp_long[i]+'0'+10-temp_short[i]-cb;
			cb=1;
		}else if(temp_long[i]==temp_short[i]){
			if(cb==0){
				result[i+1]='0';
				cb=0;
			}else{
				result[i+1]=temp_long[i]+'0'+10-temp_short[i]-cb;
				cb=1;
			}
		}
	}

	//printf("result= %s\n",result);

	if(sign == 1){
		result[0] = '-';
		int length = strlen(result);
		int index = 0;
		int firstZero = 0;
		int idx = 1;
		for(index = 1 ; index < length + 1;index++){
			if(result[index] == '0' && firstZero == 0)
				continue;
			else{
				result[idx] = result[index];
				idx = idx + 1;
				firstZero = 1;
			}
		}
	}
	else{
		int length = strlen(result);
		int index = 0;
		int k;
		for(k = 0 ; k < length; k++){
			if(result[k] != '0')
				break;
		}
		if(k == length){
			result[0] = '0';
			result[1] = '\0';
		}else{
			int firstZero = 0;
			int idx = 0;
			for(index = 0 ; index < length + 1; index++){
				if(result[index] == '0' && firstZero == 0)
					continue;
				else{
					result[idx] = result[index];
					idx = idx + 1;
					firstZero = 1;				
				}
			}
		}
	}
	
	

	return result;
}
	

