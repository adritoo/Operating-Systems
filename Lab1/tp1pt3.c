#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

	int i = 5;
	if(fork()==0){
		execl("/usr/bin/firefox","--new window","www.eurosport.com",NULL);
		i++;
		printf("I'm the child pid: %d\n, i: %d", getpid(), i);
	}else{
	printf("I'm the parent pid: %d", getpid());
	}
	sleep(3);
	return 0;
}
