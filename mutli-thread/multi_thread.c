#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "add.h"

struct timeval start;
struct timeval end;
struct timeval start1;
struct timeval end1;
struct timeval start2;
struct timeval end2;
struct timeval start3;
struct timeval end3;
unsigned long timer,timer1,timer2,timer3;



pthread_mutex_t counter_lock;
pthread_cond_t counter_nonzero;
int counter = 3;//the value of counter equels to the number of  sub-threads; 
void counterDown(char* input);

char* first = NULL;
char* second = NULL;
char* third = NULL;

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


/*********************************/
void* add1(void* p){
	
			//printf("enter add1\n");
	gettimeofday(&start1, NULL);
	char* p1 = (char*)p; 
	memcpy(p1,"1",2);
	char* b = malloc(100);
	int i;
	char* temp = b;
	//printf("new thread\n");
	for(i=2;i<7000001;i++){
		integer2string(i,b);
		temp=add(p1,b);
		memcpy(p1,temp,strlen(temp));
		free(temp);	
		//printf("b = %s\n",b);
		}
		
//	printf("p1=%s\n",p1);
	free(b);
	counterDown(p1);
	gettimeofday(&end1, NULL);
    timer1 = 1000000 * (end1.tv_sec - start1.tv_sec) + end1.tv_usec - start1.tv_usec;
    printf("----------timer1 = %ld us\n", timer1);
}
///*********************************/
void* add2(void* p ){
	gettimeofday(&start2, NULL);
	char* p2=(char*)p;
	int num=7000001;
	integer2string(num,p2);
	char* b=malloc(100);
	char* temp=b;
	int i;
	for(i=7000002;i<14000001;i++){
		integer2string(i,b);
		temp=add(p2,b);
		memcpy(p2,temp,strlen(temp));
		//printf("b=%s\n",b);
		free(temp);
	}
//	printf("p2=%s\n",p2);
	free(b);
	counterDown(p2);
	gettimeofday(&end2, NULL);
    timer2 = 1000000 * (end2.tv_sec - start2.tv_sec) + end2.tv_usec - start2.tv_usec;
    printf("-----------timer2 = %ld us\n", timer2);
}
///*********************************/
void* add3(void* p){
	gettimeofday(&start3, NULL);
	char* p3=(char*)p;
	int num=14000001;
	integer2string(num,p3);
	char* b=malloc(100);
	char* temp=b;
	int i;
	for(i=14000002;i<21000001;i++){
		integer2string(i,b);
		temp=add(p3,b);
		memcpy(p3,temp,strlen(temp));
		free(temp);
	}
//	printf("p3=%s\n",p3);
	free(b);
	counterDown(p3);
	gettimeofday(&end3, NULL);
    timer3= 1000000 * (end3.tv_sec - start3.tv_sec) + end3.tv_usec - start3.tv_usec;
    printf("----------timer3 = %ld us\n", timer3);
}

/*********************************************************************/

void counterWait(){
	pthread_mutex_lock(&counter_lock);  
	while(counter > 0){//
		
		pthread_cond_wait(&counter_nonzero,&counter_lock);
		
	}
	pthread_mutex_unlock(&counter_lock);
}

void counterDown(char * input){
	pthread_mutex_lock(&counter_lock);
	counter--;
	if(first == NULL)
		first = input;
	else if(second==NULL)
		second = input;
	else
		third = input;
	if(counter == 0){
		pthread_cond_signal(&counter_nonzero);  //used to wake up the lock;
	}
	pthread_mutex_unlock(&counter_lock);
}
/************************************************************************/

void main(){
//    printf("hello world!\n");
  
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	char* p1 = malloc(100);
	char* p2 = malloc(100);
	char* p3 = malloc(100);
//	printf("start\n");
	pthread_create(&t1,NULL,add1,(void*)p1);
	pthread_create(&t2,NULL,add2,(void*)p2);
	pthread_create(&t3,NULL,add3,(void*)p3);
	
    gettimeofday(&start, NULL);
	counterWait();//wait for the three sub-threads end;
	
//	printf("main()\n");
//	printf("---------first=%s\n",first);
//	printf("---------second=%s\n",second);
//	printf("---------third=%s\n",third);
	char* p;
	p = add(p1,p2);
	p = add(p,p3);
	printf("----p = %s\n",p);
	
	free(p);
	gettimeofday(&end, NULL);
    timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("timer = %ld us\n", timer);
}











