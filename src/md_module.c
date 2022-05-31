#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
//
#include "../include/md_module.h"
 
#define PRIMO    1
#define N_PRIMO  0

#define troca(x, y){\
    __typeof(x) temp = (x);\
    (x) = (y);\
    (y) = (temp);\
}

int mdc_euclides(unsigned int x, unsigned int y){
    if(x < y)
        troca(x, y);
    
    if((x % y) == 0)
        return y;
        
    return mdc_euclides(y, (x % y));
}
 
unsigned int isprime(unsigned long int num){
    unsigned long int raizq;
 
    if(num < 3){
        if(num < 2)
            return N_PRIMO;
        return PRIMO; 
    }
 
    if((num % 2) == 0)
        return N_PRIMO;
 
    raizq = sqrt(num);
 
    for(int c = 3; c <= raizq; c += 2){
        if(num % c == 0)
            return N_PRIMO;
    }
 
    return PRIMO;
}
 
//funçções para teste
void maior_primo(int intervalo){
    unsigned long int count;
    count = 3;
    unsigned int start = clock()/CLOCKS_PER_SEC;
    unsigned int stop = 0;

    printf("2\n");
 
    do{
        if(isprime(count))
            printf("%li\n", count);
        count += 2;
        stop = clock()/CLOCKS_PER_SEC;
    }while((stop-start) < intervalo);
}