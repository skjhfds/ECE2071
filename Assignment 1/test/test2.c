#include <stdio.h>
#define pCount 20

unsigned int pDist[pCount] = {3, 13, 7, 5, 21, 23, 39, 23, 40, 23, 14, 12, 56, 23, 29, 8,8,8,8,8};  // Digit distances
unsigned int pDistHeap[2][pCount/2];

float medianUpdate(unsigned int dist);

int main (void){
    for (unsigned int i = 0;i<pCount;i++){
        printf("%d ",pDist[i]);
        medianUpdate(pDist[i]);
    }
    return 0;
}

float medianUpdate(unsigned int dist){
    if 
    return;
}