//在子进程中调用wait()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char*argv[])
{
	int count=0;
	pid_t pc;
	pc=fork();
	if(pc<0)//进程未创建成功
	{
		fprintf(stderr,"fork failed\n");
		exit(1);
	}
	else if(pc==0)//如果当前进程是子进程
	{
		wait(NULL);//子进程调用wait阻塞自己
		printf("This is child process with pid of %d\n",getpid());
	}
	else //如果当前进程是父进程
	{
		printf("This is parent process with pid of %d ,my child is %d\n",getpid(),pc);
		int i=0;
		for(i=0;i<10;i++)
		{
			count++;
			printf("count= %d\n",count);
		}
	}
	return 0;
}

