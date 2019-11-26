//Adrien BOURGET & Valentin MONIER

#ifndef __MMU__H__
#define __MMU__H__
#define SIZE 65536
typedef short byte_t;
typedef int address_t;

typedef struct hole {
  address_t adr;
  int sz;
  struct hole *next;
  struct hole *prev;
}hole_t;

typedef struct {
  byte_t mem[SIZE];
  hole_t root; // holes list
}mem_t;

// dynamically allocates a mem_t structure and initializes its content
mem_t *initMem(){

}

// allocates space in bytes (byte_t) using First-Fit, Best-Fit or Worst-Fitaddress_t
int myAlloc(mem_t *mp, int sz){
  
}

// release memory that has already been allocated previously
void myFree(mem_t *mp, address_t p, int sz){
  printf("BITE\n");
} // assign a value to a byte
void myWrite(mem_t *mp, address_t p, byte_t val){


} // read memory from a byte
byte_t myRead(mem_t *mp, address_t p);

#endif

int main(){

  mem_t *men = initMem();
  address_t adr1 = myAlloc(mem, 5);
  address_t adr2 = myAlloc(mem, 10);
  address_t adr3 = myAlloc(mem, 100);

  myFree(mem, adr2, 10);
  myFree(mem, adr1, 5);

  myWrite(mem, adr3, 543); // Write on the 1byte
  myWrite(mem, adr3+9, 34); // Write on the 10th byte

  byte_t val1 = myRead(mem, adr3);
  byte_t val2 = myRead(mem, adr3+9);
}
