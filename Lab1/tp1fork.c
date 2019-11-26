#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
	
int main(){

	
	
	pid_t pid;	
	pid=fork();
	fork();

	if (pid == 0)
	{
		printf("I'm the child ");
		printf("%d\n", getpid());
		
	}else{
		printf("I'm the parent ");
		printf("%d\n", getpid());
	}
	return 0;
		
}

