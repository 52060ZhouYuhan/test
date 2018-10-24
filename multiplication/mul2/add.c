#include "add.h"

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
		printf("temp[i] = %c", temp[i]);
	}

	printf("\n");

	for(j=max-1;j>=0;j--){
		ww=temp_long[j]-'0'+temp[j]-'0'+cb;
		temp[j]=ww%10 + '0';
		cb=ww/10;
		printf("ww = %d , temp[j] = %c , cb = %d ,\n", ww, temp[j],cb);
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

	

