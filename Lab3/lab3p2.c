#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>

typedef struct {
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
	int res1, res2, res3;
} threadinf;

clock_t times(struct tms *buf);

/// Les fonctions à executer.
void *calcul1 (void* z){
	threadinf* sub = (threadinf*) z;
	(*sub).res1 = (*sub).a+(*sub).b;
}
void *calcul2 (void* z){
	threadinf* sub = (threadinf*) z;
	(*sub).res2 = (*sub).c-(*sub).d;
}
void *calcul3 (void* z){
	threadinf* sub = (threadinf*) z;
	(*sub).res3 = (*sub).e+(*sub).f;
}

	int main(void){

		pthread_t thread1, thread2, thread3;
		threadinf item;
		item.a = 1;
		item.b = 1;
		item.c = 4;
		item.d = 2;
		item.e = 1;
		item.f = 1;
		item.res1=0;
		item.res2=0;
		item.res3=0;

		struct tms start, end;
		struct rusage rstart, rend;

		times(&start);
		getrusage(RUSAGE_SELF, &rstart);

		for(int i=0;i<500;i++){
			pthread_create(&thread3, NULL, calcul3, (void*) &item);
			pthread_create(&thread2, NULL, calcul2, (void*) &item);
			pthread_create(&thread1, NULL, calcul1, (void*) &item);

			pthread_join(thread3, NULL);
			pthread_join(thread2, NULL);
			pthread_join(thread1, NULL);

			printf("%d", (item.res1*item.res2)+item.res3);
		}

		times(&end);
		getrusage(RUSAGE_SELF, &rend);
	
	//Affichage du temps
	printf("\n %lf usec\n", (end.tms_utime+end.tms_stime-start.tms_utime-start.tms_stime)*1000000.0/sysconf(_SC_CLK_TCK));
	
	// Affichage du contexte switch
	printf(" Context switches: %ld\n", rend.ru_nvcsw-rstart.ru_nvcsw+rend.ru_nivcsw-rstart.ru_nivcsw);
	
	// Affichage des input / ouput
	printf("Imput= %ld ; Output = %ld\n", rend.ru_inblock, rend.ru_oublock);
}


