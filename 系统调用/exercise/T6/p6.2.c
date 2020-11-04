//在子进程中调用wait()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork failed\n");
		exit(1);
	}
	if(pid==0)
	{
		printf("child is running wit the pid :%d\n",getpid());
		sleep(10);
		printf("child is running\n");
		exit(10);
	}
	if(pid>0)
	{
		int status=0;
		pid_t ret=0;
		do
		{
			ret=waitpid(-1,&status,WNOHANG);//非阻塞式等待
			if(ret==0)
				printf("child is running\n");
			sleep(1);
		}while(ret==0); //ret!=0时，子进程结束
		if(WIFEXITED(status)&&(ret==pid))//如果子进程正常结束并且清理掉对应的子进程
		{
			printf("wait child success");
		}
		else
		{	
			printf("wait child failed");
			exit(1);
		}	
	}
	
	return 0;
}

