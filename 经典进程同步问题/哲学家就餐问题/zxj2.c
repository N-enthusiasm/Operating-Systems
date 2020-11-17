//哲学家进餐问题方法二
#include<pthread.h>
#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#define N 5//5个哲学家

//定义信号量以及数组
sem_t chopsticks[N],mutex;
int think[N]={0,1,2,3,4};

//同时拿起左右筷子时才允许进餐
void *func2(void* arg){
	int i= *(int *)arg;
	int left=i;
	int right = (i+1)%N;
	printf("t %d is thinking.\n",i);
	sleep(5);
	printf("t %d is hungry.\n",i);	
	
	sem_wait(&mutex);

	sem_wait(&chopsticks[left]);
	printf("%d gets the  NO.%d ,only one,don't eat.\n",i,left);
	sem_wait(&chopsticks[right]);
	printf("%d gets the NO.%d ,has two,can eat.\n",i,right);
	
	sem_post(&mutex);
		
	sleep(6);

	sem_post(&chopsticks[right]);
	printf("%d puts the NO.%d\n",i,right);
	sem_post(&chopsticks[left]);
	printf("%d puts the NO.%d\n",i,left);
	
}

void main(){
	pthread_t PHD[N];
	int m;
	for(m=0;m<N;m++){
		sem_init(&chopsticks[m],0,1);
	}
	sem_init(&mutex,0,1);

	int j;
	for(j=0;j<N;j++){
		pthread_create(&PHD[j],NULL,(void*)func2,&think[j]);
	}

	int k;
	for(k=0;k<N;k++){
		pthread_join(PHD[k],NULL);
	}

	for(m=0;m<N;m++){
		sem_destroy(&chopsticks[m]);
	}
	sem_destroy(&mutex);
}
