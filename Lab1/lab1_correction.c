#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/times.h>


int main(void) {
  // (a+b) * (c-d) / (e+f)
  double a=2, b=3, c=4, d=5, e=6, f=7;
  int shmid;
  double *res;
  int i;
  struct tms time_buf;
  

  // create the varaibles to share results; using 4 slots to make things clear but can do with just 3
  shmid = shmget(IPC_PRIVATE, 4 * sizeof(double), IPC_CREAT|0660);
  res = shmat(shmid, NULL, 0);  
  

  for (i = 0; i < 20000; i++) {
    // do it a 1000 times

    // parent = process 1, child = process 2, child = process 3
    if (fork() == 0) {
      // child 1s
      res[1] = c - d;
      exit(0);
    }
    
    // parent
    if (fork() == 0) {
    // child 2
      res[2] = e + f;
      exit(0);
    }

    // parent again...
    res[0] = a + b;
  
    // wait for children
    wait(NULL);
    wait(NULL);
    res[3] = res[0] * res[1] / res[2];

  }

  times(&time_buf);
  printf("user time = %ld\nsys time = %ld\n", time_buf.tms_utime + time_buf.tms_cutime, time_buf.tms_stime + time_buf.tms_cstime);

  printf("Result = %lf\n", res[3]);
}
