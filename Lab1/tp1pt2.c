#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

	 int pid;
	 pid=fork();
	 sleep(1);
	 pid = fork();
	
	if(pid == 0){
		pid = fork();
			if(pid==0){
				printf("I'm the grandchild id: %d\n", getpid());
				printf("Parent id: %d\n\n", getppid());
			}
			else{
			printf("I'm the child id: %d\n", getpid());
			printf("Parent id: %d \n\n", getppid());
			}
		}else{
			printf("I'm the parent id: %d | Parent id : %d \n\n", getpid(), getppid());
		}
	return 0;
}
