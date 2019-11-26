#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#define KEY 4500
#define PERMS 8600
sem_t mutex;

void *inc(void* i){
	
	sem_wait(&mutex); // Prologue
	printf("INCREMENTATION DEBUT | i: %d\n", *(int*)i);
	int reg;
	reg = *(int*)i;
	sleep(1);
	reg++;
	*(int*)i= reg;
	printf("INCREMENTATION FIN | i: %d\n", *(int*)i);
	sem_post(&mutex); // Epilogue 
	return NULL;
}

void *dec(void* i){
	
	sem_wait(&mutex);
	printf("DECREMENTATION DEBUT | i: %d\n", *(int*)i);
	int reg;
	reg = *(int*)i;
	sleep(1);
	reg--;
	*(int*)i= reg;
	printf("DECREMENTATION FIN | i: %d\n", *(int*)i);
	sem_post(&mutex);
	return NULL;
}

void *mult(void* i){
	
	sem_wait(&mutex);
	printf("MULTIPLICATION DEBUT | i: %d\n", *(int*)i);
	int reg;
	reg = *(int*)i;
	sleep(1);
	reg*=2;
	*(int*)i= reg;
	printf("MULTIPLICATION FIN | i: %d\n", *(int*)i);
	sem_post(&mutex);
	return NULL;
}


int main(){

	
	sem_init(&mutex, 0,1);
	pthread_t thread1, thread2, thread3;
	int i = 10;

	pthread_create(&thread2, NULL, dec, &i);
	pthread_create(&thread1, NULL, inc, &i);
	pthread_create(&thread3, NULL, mult, &i);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	
	sem_destroy(&mutex);

	return 0;
}
