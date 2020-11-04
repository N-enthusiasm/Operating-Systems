#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int x=100;
	int rc=fork();
	if(rc<0){
		printf("failed.\n");
	}else if (rc == 0)
	{
		printf("child x is %d\n",x);
		x=3;
		printf("child x has changed to %d \n",x);
	}else
	{
		x=10;
		printf("father x is %d\n",x);
	}
	exit(1);
	return 0;
}
