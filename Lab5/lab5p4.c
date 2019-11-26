#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>
sem_t pmutex; 


int storeInTable(int* sharedTable, int x){
	int cpt=0;
	for(int i=0; i<3; i++){
		if((sharedTable[i]==0)&&(cpt==0)){
			sharedTable[i] = x;	          	
			cpt=cpt+1;
			return i;
		}
	}
	return 0;
}

void *calc1(void *table){
	int* sharedTable = (int*) table;
	int a=1;
	int b=2;
	storeInTable(sharedTable, a + b);
	printf("Calcul 1: DONE\n");
	sem_post(&pmutex);  
	pthread_exit(NULL);

}

void *calc2(void *table){
	int* sharedTable = (int*) table;
	int c=4;
	int d=3;
	storeInTable(sharedTable, c - d);
	printf("Calcul 2: DONE\n");
	sem_post(&pmutex);
	pthread_exit(NULL);
}

void *calc3(void *table){
	int* sharedTable = (int*) table;
	int e=5;
	int f=6;
	int val = storeInTable(sharedTable, e + f);
	printf("Calcul 3: DONE\n");
	sem_post(&pmutex);
	pthread_exit(NULL);
}

void *res4(void *table){
	int* sharedTable = (int*) table;

	while(sharedTable[1]==0){  
		sem_wait(&pmutex); 
	}
	printf("Calcul de 2 & 3: OK\n");


	int result;
	result = sharedTable[0] * sharedTable[1];
	printf("Résultalt (c-d)*(e+f):  %d\n", result);


	printf("Attente de Calcul 1 ...\n");
	sem_wait(&pmutex);

	
	result = result * sharedTable[2]; // Résultat de la partie 2 & 3 * P1
	printf("Résultat (a+b)*(c-d)*(e+f): %d\n",result);
	pthread_exit(NULL);
}

int main(){

	sem_close(&pmutex); 
	int* table[3] = {0,0,0};

 	pthread_t thread1, thread2, thread3, thread4;
	
	// initialisation of the semaphore
	sem_init(&pmutex, 0, 0);

    	/* Create independent threads each of which will execute function */
	// Interestingly enough, whatever the order, the code outputs the same results.

	pthread_create( &thread1, NULL, calc1, (void*) table);
	pthread_create( &thread3, NULL, calc3, (void*) table);
	
	pthread_create( &thread2, NULL, calc2, (void*) table);
	pthread_create( &thread4, NULL,	res4, (void*) table);
	
	
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	pthread_join( thread3, NULL);
	pthread_join( thread4, NULL);
	
	///printf("%d\n", table[0]);
	return 0;
}
