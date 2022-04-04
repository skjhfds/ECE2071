#include <stdio.h>
#define maxPLen 15

void pArray(int c);

int arr[maxPLen] = {3, 13, 7, 5, 21, 23, 39, 23, 40, 23, 14, 12, 56, 23, 29};


unsigned int medianHeaps[maxPLen][2] = {0};      // Max Heap and Min Heap
float pMedians[maxPLen] = {0};      // Median digit distance starting at 2
char medianLER[maxPLen];

void updateMedian(unsigned int dist, char pLen);

int main (void){
    for (int i = 0;i<maxPLen;i++){
        updateMedian(arr[i],0);
        printf("\n%3d  [%3d  %3.1f %3d] %c",arr[i],medianHeaps[0][0],pMedians[0],medianHeaps[0][1],medianLER[0]);
    }
    return 0;
}
void updateMedian(unsigned int dist, char pLen){
    // Initialise values
    if (!medianLER[pLen]) {
        medianHeaps[pLen][0] = dist;
        pMedians[pLen] = dist;
        medianLER[pLen] = 'L';
        return;
    }
    if (dist > pMedians[pLen]){
        medianHeaps[pLen][1] = !medianHeaps[pLen][1] ? dist : dist < medianHeaps[pLen][1] ? dist : medianHeaps[pLen][1];
        medianLER[pLen] = medianLER[pLen] == 'L' ? 'E' : 'R';
    }
    if (dist < pMedians[pLen]){
        medianHeaps[pLen][0] = dist > medianHeaps[pLen][0] ? dist : medianHeaps[pLen][0];
        medianLER[pLen] = medianLER[pLen] == 'R' ? 'E' : 'L';
    }
    switch (medianLER[pLen]) {
        case 'L':
            pMedians[pLen] = medianHeaps[pLen][0];
            break;
        case 'E':
            pMedians[pLen] = (medianHeaps[pLen][0]+medianHeaps[pLen][1])/2;
            break;    
        case 'R':
            pMedians[pLen] = medianHeaps[pLen][1];
            break;    
        default:
            break;
    }
    return;
}