#include <stdio.h>
int main(void){
    int k=10,a,b,c,d,e;
    a=b=c=d=e=0;
    for(int i=1; i<=3;i=i+1){printf(" # ");}    //Answer = 3
    for(int i=1; i<=90; i=i+1){
        printf("\n%d",i);
        for(int j=7; j>-4; j--){
            printf(" %d",j);
            if(j%2){
                a++;                  //Answer =
            }
            b++;                      //Answer =
        }
        c++;                          //Answer =
    }
    printf("\na=%d b=%d c=%d",a,b,c);
    return 0;

    while(k){
        printf("\n%d",k);
        switch(k){
            case 9: k=0; break;
            case 10: k++; break;
            case 11: k--; break;
            default: break;
        }
        d++;                          //Answer = 0
    }
    e++;                              //Answer = 0
    printf("\na=%d b=%d c=%d d=%d e=%d",a,b,c,d,e);
    return 0;
}