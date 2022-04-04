#include <stdio.h>
#include <math.h>
int main (void){
    printf("   -1                            0                             1\n  0 ---------+---------+---------o---------+---------+---------+\n");
    for (int i = 5; i <= 360; i+=5){
        int y = sin(i/180.*3.14)*30+31;
        printf("%3d ",i);
        for (int j = 1; j <= 60; j++){
            if (j==y){
                printf("o");
            } else if (i%45) {
                if(j%10==0){
                    printf("|");
                } else {
                    printf(" ");
                }
            } else {
                if(j%10==0){
                    printf("+");
                } else {
                    printf("-");
                }
            }
                
        }
        printf("\n");        
    }
}