#include <stdlib.h>
#include <stdio.h>

int main (void){
    printf("%d",RAND_MAX);
    float median = RAND_MAX/2;
    int plus_count=0, minus_count=0;
    int temp;
    for (int i=0; i<100; i++){
        temp = rand();
        if(temp>median && temp!=median){
            plus_count++;
        }else{
            minus_count++;
        }
        printf("\n%d.    %d / %d,    %d",i+1,plus_count,minus_count,plus_count-minus_count);
    }
    return 0;
}
/**
 * the difference does not oscillate around 0,
 * the psuedorandomness of the numbers may be
 * lacking or the sample size is too small.
 * 
 */