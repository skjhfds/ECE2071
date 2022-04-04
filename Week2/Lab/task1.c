#include <stdio.h>
int main(void){
    int a,b,c,abc=0;
    a=b=c=40;
    if (b>20){
        int abc;
        abc = a*c;
        abc = abc + b;
    }
    printf("abc = %d\n",abc);
    return 0;
}

/**
 * For some reason the a b and c are initialised
 * with seemingly random values.
 * abc is declared twice. The debugger indicates
 * both local and global abc are updated by line 7,
 * but when the if statement closes, the local variable
 * is deleted while the global one reverts back to 0.
 * We cannot trust the debugger.
 * 
 */