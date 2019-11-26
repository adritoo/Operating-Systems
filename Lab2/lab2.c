#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#define KEY1 4567
#define KEY2 4568
#define PERMS 0660

int main()
{
	int id1, id2, *ptr1, *ptr2;
	int a=1, b=1, c=4, d=2, e=1, f=1;
	
	id1 = shmget(KEY1, sizeof(int), IPC_CREAT | PERMS);
	id2 = shmget(KEY2, sizeof(int), IPC_CREAT | PERMS);
	ptr1 = (int *) shmat(id1, NULL, 0);
	ptr2 = (int *) shmat(id2, NULL, 0);

	//1er fils	
	if(fork()==0)
	{
		*ptr1 = (a+b);
		exit(0);
	}
	
	//parent
	else 
	{
		int res = (c-d);
		wait(NULL);
		res = res * (*ptr1);
		//2e fils
		if(fork()==0)
		{
			*ptr2 = (e+f);
			exit(0);	
		} 
		//parent
		else 
		{
			wait(NULL);			
			res = res + (*ptr2);
			printf("(a+b)*(c-d)+(e+f) = %d\n", res);

			shmctl(id1, IPC_RMID, NULL);
			shmctl(id2, IPC_RMID, NULL);
			return 0;
		}
	}

}
