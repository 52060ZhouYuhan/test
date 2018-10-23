#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

char* add(char* m,char* n);

void main(){
//	int s;
//	printf("the length of addition");
//	scanf("s= %d\n",s);
	
	char m[10000];
	char n[10000];

//	unsigned int a = 1<<31;
//	unsigned int b = 1<<31;
//	printf("a = %u , b = %u , a + b = %u \n", a , b , a + b);

//	while(1){
		printf("first number: m=");
		scanf("%s",m);
		printf("second number:n=");
		scanf("%s",n);
		

		char* result = add(m,n);
		printf("\n result= %s \n",add(m,n));
		free(result);
//	}
	


}

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

	

