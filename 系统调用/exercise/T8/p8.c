//编写一个程序，创建两个子进程，并使用pipe()系统调用，将一个子进程的
//标准输出连接到另一个子进程的标准输入
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <limits.h>
#define BUFSZ PIPE_BUF

void err_quit(char *msg)
{
	perror(msg);
	exit(1);
}
int main()
{
	int fd[2];//fd[0]用于读，fd[1]用于写
	pid_t pid;
	char buf[BUFSZ];//数据缓冲区
	int len=0;

	if(pipe(fd)<0) //创建管道失败
		err_quit("pipe failed");

	if((pid=fork())<0)//创建第一个子进程失败
        	err_quit("fork failed");

	else if(pid==0)//创建第一个子进程成功
	{//在第一个子进程中
		close(fd[0]);//关闭不用的文件描述符
		write(fd[1],"hello,this is pipe\n",20);//把相应的数据写入文件描述符中
		exit(0);
	}
 
	if((pid=fork())<0)//创建第二个子进程失败
       	 	err_quit("fork failed");

	else if(pid>0)
	{//在父进程中
		close(fd[0]);//关闭不用的文件描述符
		close(fd[1]);
		exit(0);
	}
	else
	{//在第二个子进程中
		close(fd[1]);
		len=read(fd[0],buf,BUFSZ);//读取消息
		write(STDOUT_FILENO,buf,len);//将数据写入数据缓冲区并输出到屏幕
		exit(0);
	}
	return 0;
}
