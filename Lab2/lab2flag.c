#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define KEY1 4567
#define KEY2 4568
#define KEY3 4569
#define PERMS 0660 

int main()
{
	int id1, id2, id3, *ptr1, *ptr2, *flag;
	int a=3, b=2, c=6, d=4, e=1, f=1;
	
	id1 = shmget(KEY1, sizeof(int), IPC_CREAT | PERMS);
	id2 = shmget(KEY2, sizeof(int), IPC_CREAT | PERMS);
	id3 = shmget(KEY3, sizeof(int), IPC_CREAT | PERMS);
	ptr1 = (int *) shmat(id1, NULL, 0);
	ptr2 = (int *) shmat(id2, NULL, 0);
	flag = (int *) shmat(id3, NULL, 0);

	//1er fils	
	if(fork()==0)
	{
		*ptr1 = (a+b);
		*flag = 1;
		exit(0);
	}
	
	//parent
	else 
	{
		int res = (c-d);
		while(*flag != 1){}
		res = res * (*ptr1);
		//2e fils
		if(fork()==0)
		{
			*ptr2 = (e+f);
			*flag = 2;
			exit(0);	
		} 
		//parent
		else 
		{
			while(*flag != 2){}			
			res = res + (*ptr2);
			printf("(a+b)*(c-d)+(e+f) = %d\n", res);
			shmctl(id1, IPC_RMID, NULL);
			shmctl(id2, IPC_RMID, NULL);
			return 0;
		}
	}

}
