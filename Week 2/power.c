#include <stdio.h>
int main(void){
    int M,N,out=1;
    printf("M: ",M);
    scanf("%d",&M);
    printf("N: ",N);
    scanf("%d",&N);
    if((M|N)<0){
        printf("ERROR: M or N is negative");
        return 1;
        }
    for(N;N>0;N--){out*=M;}
    printf("%d",out);
    return 0;
}