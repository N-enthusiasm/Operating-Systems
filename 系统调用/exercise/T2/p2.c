#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *argv[]) {
	char buffer[13];
	int in,out;
	in=open("test.txt",O_RDONLY);   //读取文件
	out=open("test.txt",O_WRONLY | O_CREAT);  //写入文件
	int rc=fork();
	if(rc<0)
	{
		fprintf(stderr,"fork failed\n");
		exit(1);
	}
	else if(rc==0)
	{
		int rd=read(in,buffer,13); //读取文件的前13个字符到buffer
		if(rd==-1)
		{
			printf("child cannot visit file\n");//读取失败
		}
		else
		{
			printf("child can visit file\n");//读取成功
		}
		write(out,"I am child\n",10);//向文件中写入
	}
	else
	{
		int rd1=read(in,buffer,13);
		if(rd1==-1)
		{
			printf("parent cannot visit file\n");
		}
		else
		{
			printf("parent can visit file\n");
		}
		write(out,"I am parent\n",12);
	}
	return 0;
}
