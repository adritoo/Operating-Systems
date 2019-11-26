#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/resource.h>

#define KEY1 4567
#define KEY2 4568
#define PERMS 0660

clock_t times(struct tms *buf);

int main()
{
	int id1, id2, *ptr1, *ptr2;
	int a=1, b=1, c=4, d=2, e=1, f=1;
	int i;
	struct tms start, end;
	struct rusage rstart, rend;
	// Initialisation du temps
	times(&start);
	getrusage(RUSAGE_SELF, &rstart);
	
	id1 = shmget(KEY1, sizeof(int), IPC_CREAT | PERMS);
	id2 = shmget(KEY2, sizeof(int), IPC_CREAT | PERMS);
	ptr1 = (int *) shmat(id1, NULL, 0);
	ptr2 = (int *) shmat(id2, NULL, 0);

	for(i=0; i<500; i++)
	{
		//1er fils	
		if(fork()==0)
		{
			*ptr1 = (a+b);
			exit(0);
		}
	
		//parent
		else 
		{
			//second fils
			if(fork()==0){
				*ptr2 = (c-d);
				exit(0);
			}
			//parent
			else 
			{
				int var = (e+f);
				wait(NULL);
				int res = var + ((*ptr1)*(*ptr2));
				printf("(a+b)*(c-d)+(e+f) = %d\n", res);
			}
		}
	}
	times(&end); // Temps à la fin du process
	getrusage(RUSAGE_SELF, &rend);
	
	//Affichage du temps
	printf("%lf usec\n", (end.tms_utime+end.tms_stime-start.tms_utime-start.tms_stime)*1000000.0/sysconf(_SC_CLK_TCK));
	
	// Affichage du contexte switch
	printf(" Context switches: %ld\n", rend.ru_nvcsw-rstart.ru_nvcsw+rend.ru_nivcsw-rstart.ru_nivcsw);
	
	// Affichage des input / ouput
	printf("Imput= %ld ; Output = %ld\n", rend.ru_inblock, rend.ru_oublock);
	shmctl(id1, IPC_RMID, NULL);
	shmctl(id2, IPC_RMID, NULL);

	return 0;
}
