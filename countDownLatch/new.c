#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "add.h"

struct timeval start;
struct timeval end;
unsigned long timer;

void integer2string(int num, char* b){
	int i = 0;
	char* temp = malloc(strlen(b));
	for(;;){
		temp[i] = num % 10 + '0';
		i++;
		num = num /10;
		if(num < 10){
			temp[i] = num + '0';
			i++;
			break;
		}
	}
	int j = 0;
	for(j = 0; j < i; j++){
		b[j] = temp[i - j - 1];
	}
	b[j] = '\0';
	free(temp);
}


void main(){
	gettimeofday(&start, NULL);
   // printf("hello world!\n");
	char* p1 =malloc(100); 
	int i;
	i=1;
	integer2string(i,p1);
	char* b = malloc(100);
	char* temp = b;
	printf("new thread\n");
	for(i=2;i<21000001;i++){
		integer2string(i,b);
		temp=add(p1,b);
		memcpy(p1,temp,strlen(temp));
		free(temp);	
		//printf("b = %s\n",b);
		}
	printf("p1=%s\n",p1);
	free(b);
	gettimeofday(&end, NULL);
    timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("timer = %ld us\n", timer);
	free(p1);
}