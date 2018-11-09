#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_LENGTH 16
 
typedef struct store{
	int buffer[BUFFER_LENGTH];
	int readpos;
	int writepos;
	pthread_mutex_t mutex;
	pthread_cond_t notfull;
	pthread_cond_t notempty;
	
}store;

void init(store* b){
	memset(b->buffer,0,BUFFER_LENGTH);//---------modify(memcpy(b->buffer,0,BUFFER_LENGTH);)
	b->readpos=0;
	b->writepos=0;
    pthread_mutex_init(&(b->mutex),NULL);
	pthread_cond_init(&(b->notfull),NULL);
	pthread_cond_init(&(b->notempty),NULL);
}
/**********************write operation**************************/
void put(store* b,int data){
	//printf("write operation!\n");
	pthread_mutex_lock(&(b->mutex));
	if((b->writepos+1)%BUFFER_LENGTH==b->readpos){
		pthread_cond_wait(&(b->notfull),&(b->mutex));
		printf("the store is full,producers need to wait!\n");
	}
	
	b->buffer[b->writepos]=data;
	printf("buffer[%d]=%d\n",b->writepos,b->buffer[b->writepos]);
	b->writepos++;
	if(b->writepos>=BUFFER_LENGTH){
		b->writepos=0;
	}
	pthread_cond_signal(&(b->notempty));
	pthread_mutex_unlock(&(b->mutex));
}
/************************read operation*************************/
int get(store* b){
	//printf("read operation!\n");
	pthread_mutex_lock(&(b->mutex));
	if(b->readpos==b->writepos){
		pthread_cond_wait(&(b->notempty),&(b->mutex));
		printf("the store is empty,consumers need to wait!\n");
	}
	
	int data=b->buffer[b->readpos];
	printf("readpos-----buffer[%d]=%d\n",b->readpos,b->buffer[b->readpos]);
	b->readpos++;
	if(b->readpos>=BUFFER_LENGTH){
		b->readpos=0;
	}
	pthread_cond_signal(&(b->notfull));
	pthread_mutex_unlock(&(b->mutex));
	return data;//------------add this line;
}
/************************************************/
#define OVER (-1)		//定义结束标志
store buffer;	        //定义全局变量//-----------modify(store* buffer;)
/************************************************/
void* producer(void* data){
	int n=0;
	for(;n<48;n++){
		put(&buffer,n);
	}
	put(&buffer,OVER);
	pthread_exit(NULL);
}
/**********************************************/
pthread_mutex_t lock;
pthread_cond_t exit1;
int exit_temp = 0;//----------add this line;
void* consumer(void* data){
	while(1){
		int d=get(&buffer);
		
		if(d==OVER){
			printf("enter d == OVER\n");
			pthread_mutex_lock(&lock);
			exit_temp = 1;
			pthread_cond_signal(&exit1);
			pthread_mutex_unlock(&lock);
			break;
		}
	}
	pthread_exit(NULL);
}
/************************************************/
void main(){
	init(&buffer);
	pthread_t t_producer;
	pthread_t t_consumer;
	pthread_create(&t_producer,NULL,producer,NULL);
	pthread_create(&t_consumer,NULL,consumer,NULL);
	
	/***************the following section is very important**************************/
	pthread_mutex_lock(&lock);
	while(exit_temp == 0){
		pthread_cond_wait(&exit1,&lock);
	}
	pthread_mutex_unlock(&lock);
	
	/********************************************************************************/
	printf("exit!\n");
}






