#include <stdio.h>
int main(void){
    int i,j;
    for(i=1;i<=5;++i){
        for(j=0;j<i;++j){
            printf("%3d \n",j);
        }
    }
    for(i=4; i>0; --i){
        for (j=0; j<i; ++j){
            printf("%3d \n",j);
        }
    }
}