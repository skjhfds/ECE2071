#include <stdio.h>
int main (void) {
    int arr[] = {1,3,2,5,734,2};
    printf("%d", maxVal(arr));
    return 0;
}
int maxVal(int a[]) {
    int output=a[0];
    for(int i=1; i<sizeof(a)/sizeof(int);i++){
        output = output<a[i] ? a[i] : output;
    }
    return output;
}