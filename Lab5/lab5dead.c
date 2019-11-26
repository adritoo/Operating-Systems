#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>


pthread_mutex_t lock1,lock2,lock3;


void * proc1(){

	printf("Process 1 started\n");				
	pthread_mutex_lock(&lock1);						//Locking lock1
	sleep(1);
	printf("Trying to get ressource 2 \n");
	pthread_mutex_lock(&lock2);						//Getting lock n°2, but it's been already locked by proc2
	printf("Aquired ressource 2 \n");
	pthread_mutex_unlock(&lock2);					//Unlocking lock2
	printf("Trying to get ressource 3 \n");			//Getting lock n°3, but it's been already locked by proc3
	pthread_mutex_lock(&lock3);
	printf("Aquired ressource 3 \n"); 
	pthread_mutex_unlock(&lock3);					//Unlocking lock3
	printf("Job done in process 1 \n");
	pthread_mutex_unlock(&lock1);					//Unlocking lock1
	pthread_exit(NULL);
}

void * proc2(){

	printf("Process 2 started\n");
	pthread_mutex_lock(&lock2);	//On vérouille le lock2 (pout le thread2)
	sleep(1);
	printf("Trying to get ressource 3 \n"); // On essaie de collecter une ressource du thread3.
	pthread_mutex_lock(&lock3); //On vérouille le lock3 mais already locked par thread3.
	printf("Aquired ressource 3 \n");
	pthread_mutex_unlock(&lock3);	//On déverouille le thread3.
	printf("Trying to get ressource 1 \n"); // On essaie de collecter une ressource du thread1.
	pthread_mutex_lock(&lock1); //On vérouille le lock1 mais already locked par thread1.
	printf("Aquired ressource 1 \n");
	pthread_mutex_unlock(&lock1); //On déverouille le thread1.
	printf("Job done in process 2 \n"); //Si le programme est ok, on ne voit jamais cette ligne
	pthread_mutex_unlock(&lock2); //On dévérouille le thread2.
	pthread_exit(NULL);
}

void * proc3(){

	printf("Process 3 started\n");
	pthread_mutex_lock(&lock3);
	sleep(1);
	printf("Trying to get ressource 1 \n");
	pthread_mutex_lock(&lock1);
	printf("Aquired ressource 1 \n");
	pthread_mutex_unlock(&lock1);
	printf("Trying to get ressource 2 \n");
	pthread_mutex_lock(&lock2);
	printf("Aquired ressource 2 \n");
	pthread_mutex_unlock(&lock2);
	printf("Job done in process 3 \n");
	pthread_mutex_unlock(&lock3);
	pthread_exit(NULL);
}

int main(){
	pthread_mutex_init(&lock1,NULL);
	pthread_mutex_init(&lock2,NULL);
	pthread_mutex_init(&lock3,NULL);
	
	pthread_t thread1, thread2, thread3;  //Initialisation des threads
	
	pthread_create(&thread1,NULL,proc1,NULL);
	pthread_create(&thread2,NULL,proc2,NULL);
	pthread_create(&thread3,NULL,proc3,NULL);
	
	pthread_join(thread1,NULL);	
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);	
	
	return 0;	
}
