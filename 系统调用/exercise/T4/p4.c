#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
int main(){
	int rc = fork();
	if(rc<0)
	{
		printf("failed. \n ");
		exit(1);
	}else if(rc==0){
		printf("child. \n");
		//execl、execlp、execle的参数个数是可变的，参数以一个空指针结束
		execl("/bin/ls","ls","-l",NULL);
		execle("/bin/ls","ls","-l",NULL,NULL);
		execlp("/bin/ls","ls","-l",NULL);
		exit(1);
	}else{
		printf("father\n");
		//execv\execvp和execvpe的第二个参数是一个字符串数组，新程序在启动时会把在argv数组中给定的
		//参数传递到main
		char *v[] = {"ls","-l",NULL};
		execve("/bin/ls",v,NULL);
		execv("/bin/ls",v);
		execvp("/bin/ls",v);
		exit(1);
	}
	return 0;
}
