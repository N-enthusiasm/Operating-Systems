//生产者消费者问题
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
sem_t empty,full,s;
int buffer[10]={-1};
int fill=0;
int use=0;
void put(int value){
	buffer[fill]=value;
	fill=(fill+1)%11;
}
int get(){
	int tmp=buffer[use];
	use=(use+1)%11;
	return tmp;
}
void *producer(void *arg){
	printf("producer\n");

	int i=0;
	for(i=0;i<=20;i++){
		//sleep(3);
		sem_wait(&empty);
		sem_wait(&s);
		
		put(i);
		sem_post(&s);
		sem_post(&full);
		printf("producer put:%d\n",i);
	}

	//pthread_exit(0);
}
void *consumer(void *arg){
	printf("consumer\n");
	
	int i=0;
	for(i=0;i<=20;i++){
		//sleep(3);
		sem_wait(&full);
		sem_wait(&s);
		
		int tmp=get();
		
		sem_post(&s);
		sem_post(&empty);
		printf("consumer get:%d\n",tmp);
	}
	//pthread_exit(0);
}
int main(int argv,char * args[]){
	sem_init(&empty,0,10);
	sem_init(&full,0,0);
	sem_init(&s,0,1);
	pthread_t pro,con;
	pthread_create(&pro,NULL,producer,NULL);
	pthread_create(&con,NULL,consumer,NULL);
	pthread_join(con,NULL);
	pthread_join(pro,NULL);
	
	

}
