// 读者优先

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/types.h>
# include <pthread.h>
# include <semaphore.h>
# include <string.h>
# include <unistd.h>

sem_t Rmutex,Wmutex;
int readCount;

struct data {
    int id;
    int opTime;
    int lastTime;
};

//读者
void* Reader(void* param) {
    int id = ((struct data*)param)->id;
    int lastTime = ((struct data*)param)->lastTime;
    int opTime = ((struct data*)param)->opTime;

    sleep(opTime);
    printf("Thread %d: waiting to read\n", id);
    sem_wait(&Rmutex);
    readCount++;
    if(readCount == 1) 
        sem_wait(&Wmutex);
    sem_post(&Rmutex);

//执行读操作
    printf("Thread %d: start reading\n", id);
    sleep(lastTime);
    printf("Thread %d: end reading\n", id);

    sem_wait(&Rmutex);
    readCount--;
    if(readCount == 0)
        sem_post(&Wmutex);
    sem_post(&Rmutex);
    pthread_exit(0);
}

//写者
void* Writer(void* param) {
    int id = ((struct data*)param)->id;
    int lastTime = ((struct data*)param)->lastTime;
    int opTime = ((struct data*)param)->opTime;

    sleep(opTime);
    printf("Thread %d: waiting to write\n", id);
    sem_wait(&Wmutex);

//执行写操作
    printf("Thread %d: start writing\n", id);
    sleep(lastTime);
    printf("Thread %d: end writing\n", id);

    sem_post(&Wmutex);
    pthread_exit(0);
}

int main() {
    pthread_t tid; 

    //初始化信号量
    sem_init(&Rmutex, 0, 1);
    sem_init(&Wmutex, 0, 1);
    readCount = 0;

    int id = 0;
    while(scanf("%d", &id) != EOF) {
        char role;         //读者还是写者
        int opTime;     //每一个进程开始前的间隔时间
        int lastTime;   //执行读/写操作的时间

        scanf("%c%d%d", &role, &opTime, &lastTime);
        struct data* d = (struct data*)malloc(sizeof(struct data));

        d->id = id;
        d->opTime = opTime;
        d->lastTime = lastTime;

        if(role == 'R') {
            printf("Create the %d thread: Reader\n", id);
            pthread_create(&tid, NULL, Reader, d);

        }
        else if(role == 'W') {
            printf("Create the %d thread: Writer\n", id);
            pthread_create(&tid, NULL, Writer, d);
        }
    }

    //信号量销毁
    sem_destroy(&Rmutex);
    sem_destroy(&Wmutex);

    return 0;
}

