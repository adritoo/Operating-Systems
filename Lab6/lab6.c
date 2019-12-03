#include <stdio.h>
#include <stdlib.h>
#ifndef __MMU__H__
#define __MMU__H__
#define SIZE 65536



typedef short byte_t;
typedef int address_t;


typedef struct {
 byte_t mem[SIZE];
 byte_t log[SIZE]; /// holes list
} mem_t;

/// dynamically allocates a mem_t structure and initializes its content
mem_t *initMem();
/// allocates space in bytes (byte_t) using First-Fit, Best-Fit or Worst-Fit
address_t myAlloc(mem_t *mp, int sz);
/// release memory that has already been allocated previously
void myFree(mem_t *mp, address_t p, int sz);
/// assign a value to a byte
void myWrite(mem_t *mp, address_t p, byte_t val);
/// read memory from a byte
byte_t myRead(mem_t *mp, address_t p);
#endif
 
mem_t *initMem(){
    mem_t *new_mem = malloc(sizeof(mem_t));
    for (int i=0;i<SIZE;i++){
        new_mem->mem[i]=0;
        new_mem->log[i]=0;
    }
    return new_mem;
}

address_t myAlloc1stFit(mem_t *mp, int sz){

    int holes;          ///Nombre de trous consecutif
    address_t adr=0;      ///Curseur dans l'index de la memoire logique
    int i;

    do {
        holes=0;
        if (!mp->log[adr]){         ///Vérifie si la place est libre
            for(i=adr;i<adr+sz;i++){
                if(!mp->log[i]){
                    holes++;        ///Vérifie si il y a de la place apres
                }else{
                    adr=i;          ///Mise en mémoire de la derniere adresse utilisée
                }
            }
        }
        adr++;
    }while(holes!=sz);

    for(i=adr-1;i<adr+sz-1;i++){    ///Ecriture dans la memoire logique l'indisponibilité
        mp->log[i]=1;
    }
    return adr-1;
}

address_t myAllocBest(mem_t *mp, int sz){
    int holes;                  ///Nombre de trous consecutif
    address_t adr=0;             ///Curseur dans la mémoire logique
    address_t cpt_last_hole = SIZE;
    address_t best_fit;
    int i;

    for (adr=0;adr<SIZE;adr++){
        if(mp->log[adr]==0){
            holes++;            ///Espace disponible
        }else{
            if(holes>sz && holes<cpt_last_hole){
                cpt_last_hole=holes;
                best_fit=adr-holes;
            }
            holes=0;
        }
        if(adr=SIZE-1){
            if(holes>sz && holes<cpt_last_hole){
                cpt_last_hole=holes;
                best_fit=adr-cpt_last_hole;
            }
            else if(holes==SIZE) {
                best_fit=SIZE-holes;
            }
            else if(cpt_last_hole=SIZE)
                printf("Plus de place disponible");
        }
    }




}

void myFree(mem_t *mp, address_t p, int sz){
    address_t i;
    for(i=p;i<p+sz;i++){
        mp->log[i]=0;
    }
    printf("Memoire de taille %d liberee en position %d\n",sz,p);
}

void myWrite(mem_t *mp, address_t p, byte_t val){
    if (mp->log[p]){
        mp->mem[p]=val;
    }
}

byte_t myRead(mem_t *mp, address_t p){
    if (mp->log[p]){
        return mp->mem[p];
    }
    else {
        printf("Impossible de lire le byte n°%d\n",p);
    }
}



int main() {
 mem_t *mem = initMem();
 address_t adr1 = myAlloc1stFit(mem, 5);
 printf("Utilisation de l'algo First Fit \nAdress: %d\t Size : 5\n",adr1);

 address_t adr2 = myAlloc1stFit(mem, 10);
 printf("Utilisation de l'algo First Fit \nAdress: %d\t Size : 10\n",adr2);

 address_t adr3 = myAlloc1stFit(mem, 100);
 printf("Utilisation de l'algo Best Fit \nAdress: %d\t Size : 100\n",adr3);

 myFree(mem, adr2, 10);
 myFree(mem, adr1, 5);

 myWrite(mem, adr3, 543); /// write on the 1st byte
 myWrite(mem, adr3+9, 34); /// write on the 10th byte
 byte_t val1 = myRead(mem, adr3);
 byte_t val2 = myRead(mem, adr3+9);

 printf("Valeur de val1 : %d \t val2 : %d",val1,val2);

}
