#include <stdio.h>
int main(void){
    char *format = "%p %d %d %d\n";
    int i = 3;
    int *p = &i;
    printf(format, p, *p + 7, 3 * **&p + 1, 5 * (p - (p - 2)));
    return 0;
}