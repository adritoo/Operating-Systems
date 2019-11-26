#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#define KEY 4500
#define PERMS 8600
sem_t mutex1;
sem_t mutex2;
sem_t mutex3;

void *prg1(void* i){
	
	sem_wait(&mutex1); // Prologue
	printf("1\n");
	execl("/usr/bin/gnome-terminal","--new window",NULL);
	
	sem_post(&mutex2); // Epilogue 
}

void *prg2(void* i){
	
	sem_wait(&mutex2);
	printf("2\n");
 	execl("/usr/bin/firefox","--new window","www.eurosport.com",NULL);
	sem_post(&mutex3);
	
}

void *prg3(void* i){
	
	sem_wait(&mutex3);
	printf("3\n");
//	execl("/u/userid/bin/newShell", "newShell", NULL);
	//sem_post(&mutex);
	
}


int main(){

	
	sem_init(&mutex1, 0,1);
	sem_init(&mutex2, 0,0);
	sem_init(&mutex3, 0,0);

	pthread_t thread1, thread2, thread3;
	int i = 10;

	pthread_create(&thread1, NULL, prg1, &i);
	pthread_create(&thread2, NULL, prg2, &i);
	pthread_create(&thread3, NULL, prg3, &i);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	
	sem_destroy(&mutex1);
	sem_destroy(&mutex2);
	sem_destroy(&mutex3);

	return 0;
}
