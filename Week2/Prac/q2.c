#include <stdio.h>
int main(void) {
    int i = 100, j=0;
    if (i < 3) puts("true"); else puts("false");
    if (!j < 1) puts("true"); else puts("false");
    if (i > 0 || j > 50) puts("true"); else puts("false");
    if (j < i && i<=10) puts("true"); else puts("false");
}