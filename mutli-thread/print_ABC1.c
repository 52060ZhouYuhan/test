#include <stdio.h>
#include <pthread.h>
/******************************************************************************/
/************implement sequential output of multiple threads*******************/
/*编写一个程序，开启3个线程，这3个线程的ID分别为A、B、C，每个线程将自己的ID在屏幕上打印10遍，
 * 要求输出结果必须按ABC的顺序显示；如：ABCABC….依次递推*******************************/
/******************************************************************************/
pthread_mutex_t mutex;
pthread_cond_t counter_nonzero;
int sign=0;
int counter=3;

pthread_mutex_t mutex1;
pthread_cond_t counter_nonzero1;
/*********************************************/
void counterWait(){
	pthread_mutex_lock(&mutex1);  
	while(counter > 0){
		pthread_cond_wait(&counter_nonzero1,&mutex1);
	}
	pthread_mutex_unlock(&mutex1);
}

void counterDown( ){
	pthread_mutex_lock(&mutex1);
	counter--;
	if(counter == 0){
		pthread_cond_signal(&counter_nonzero1);  //used to wake up the lock>>> pthread_cond_wait(&counter_nonzero1,&mutex1);
	}
	pthread_mutex_unlock(&mutex1);
}
/*********************************************/
void* fun(void* p){

	int* id=(int*)p;
	
	int i;
	for(i=0;i<10;i++){

    	pthread_mutex_lock(&mutex);
		while(sign!=*id)
			pthread_cond_wait(&counter_nonzero,&mutex);
		printf(" %c\n",'A'+*id);
		sign=(sign+1)%3;
		pthread_cond_broadcast(&counter_nonzero);
		pthread_mutex_unlock(&mutex);
		
	}
	counterDown( );
}
void main(){
	pthread_t ta;
	pthread_t tb;
	pthread_t tc;
	int p1=0;
	int p2=1;
	int p3=2;
	pthread_create(&ta,NULL,fun,(void*)(&p1));
	pthread_create(&tb,NULL,fun,(void*)(&p2));
	pthread_create(&tc,NULL,fun,(void*)(&p3));
	
	
	counterWait();

}





