#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{
	printf("hello world (pid:%d)\n",(int)getpid());
	int rc=fork();
	if(rc<0)
	{
		fprintf(stderr,"fork failed\n");
		exit(1);
	}
	else if(rc==0)
	{
		printf("I am child (pid:%d)\n",(int)getpid());
		char *myargs[3];
		myargs[0]=strdup("wc"); //“wc”字符计数程序
		myargs[1]=strdup("exec.c");
		myargs[2]=NULL;
		execvp(myargs[0],myargs); //执行成功后就返回，接着调用父进程
		printf("this shouldn't print out");
	}
	else
	{
		int wc=wait(NULL); //成功，返回子进程的进程ID，否则返回-1
		printf("I am parent of %d (wc:%d),my pid is %d\n",rc,wc,(int)getpid());
	}
	return 0;
}
