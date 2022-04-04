#include <stdio.h>
#include <stdlib.h>
#define maxPLen 15          // Assume no palindromes exceed length 15
#define maxCount 37    // Assume no more than 5001645 palindromes of each length
#define halfCount maxCount/2+1
// Heap sorting variables
unsigned int
digitDist[maxPLen][maxCount] = {0},
ddMaxHeap[maxPLen][halfCount] = {0},// Digit distances in max heap
ddMinHeap[maxPLen][halfCount] = {0},// Digit distances in min heap
ddHeapLen[maxPLen][2] = {0};        // Digit distances heap lengths
// Heap sorting functions
void addDist(unsigned int dist, unsigned int pLen);
int finalMedian(unsigned int pLen);
double calcMedian(unsigned int pLen);
void pushToFront(unsigned int input, unsigned char heap, unsigned int pLen);
void pushToEnd(unsigned int input, unsigned char heap, unsigned int pLen);
void maxToFront(unsigned int pLen);
void minToFront(unsigned int pLen);

int main(void){
    printf("%d,", 0);
    addDist(0,0);
    for (int i = 1; i<maxCount; i++){
        int temp = rand();
        printf("%d,", temp);
        addDist(temp,0);
    }
    printf("\nmedian = %d",finalMedian(0));
    return 0;
}

void addDist(unsigned int dist, unsigned int pLen){
    // Fill in ddMaxHeap first
    if (!ddHeapLen[pLen][0]){
        ddMaxHeap[pLen][0] = dist;
        ddHeapLen[pLen][0]++;
        return;
    }
    // Choose heap to send to
    if (dist > calcMedian(pLen)){
        // Send to ddMinHeap if greater than median
        if (dist < ddMinHeap[pLen][0]) pushToFront(dist, 1, pLen);
        else pushToEnd(dist, 1, pLen);
    } else {
        // Send to ddMaxHeap if equal to or less than median
        if (dist > ddMaxHeap[pLen][0]) pushToFront(dist, 0, pLen);
        else pushToEnd(dist, 0, pLen);
    }
    // Check balance of heaps
    switch (ddHeapLen[pLen][1]-ddHeapLen[pLen][0]){
        case -2:    // ddMaxHeap heavy
            pushToFront(ddMaxHeap[pLen][0], 1, pLen);
            maxToFront(pLen); break;
        case 2:     // ddMinHeap heavy
            pushToFront(ddMinHeap[pLen][0], 0, pLen);
            minToFront(pLen); break;
        default: break;
    }
    return;
}
int finalMedian(unsigned int pLen){    
    if (ddHeapLen[pLen][0]<ddHeapLen[pLen][1]) return ddMinHeap[pLen][0];  // ddMinHeap larger
    else return ddMaxHeap[pLen][0];
}
double calcMedian(unsigned int pLen){
    double median;
    switch (ddHeapLen[pLen][1]-ddHeapLen[pLen][0]){
        case 0: // Equal
            median = (ddMaxHeap[pLen][0]+ddMinHeap[pLen][0])/2.; break;
        case -1: median = ddMaxHeap[pLen][0]; break;    // ddMaxHeap larger
        case  1: median = ddMinHeap[pLen][0]; break;    // ddMinHeap larger
        default: break;
    }
    return median;
}
void pushToFront(unsigned int input, unsigned char heap, unsigned int pLen){
    if(heap){
        ddMinHeap[pLen][ddHeapLen[pLen][heap]] = ddMinHeap[pLen][0];
        ddMinHeap[pLen][0] = input;
    } else {
        ddMaxHeap[pLen][ddHeapLen[pLen][heap]] = ddMaxHeap[pLen][0];
        ddMaxHeap[pLen][0] = input;
    }
    ddHeapLen[pLen][heap]++;
}
void pushToEnd(unsigned int input, unsigned char heap, unsigned int pLen){
    if(heap) ddMinHeap[pLen][ddHeapLen[pLen][heap]] = input;
    else ddMaxHeap[pLen][ddHeapLen[pLen][heap]] = input;
    ddHeapLen[pLen][heap]++;
}
void maxToFront(unsigned int pLen){
    // Find pointer to maximum value
    unsigned int *max = &ddMaxHeap[pLen][1];
    for(unsigned int i = 2; i<ddHeapLen[pLen][0]; i++)
    if (ddMaxHeap[pLen][i]>*max) max = &ddMaxHeap[pLen][i];
    // Move maximum value to front, fill in memory with last value
    ddMaxHeap[pLen][0] = *max;
    *max = ddMaxHeap[pLen][ddHeapLen[pLen][0]-1];
    ddHeapLen[pLen][0]--;
    return;
}
void minToFront(unsigned int pLen){
    // Find pointer to minimum value
    unsigned int *min = &ddMinHeap[pLen][1];
    for(unsigned int i = 2; i<ddHeapLen[pLen][1]; i++)
    if (ddMinHeap[pLen][i]<*min) min = &ddMinHeap[pLen][i];
    // Move maximum value to front, fill in memory with last value
    ddMinHeap[pLen][0] = *min;
    *min = ddMinHeap[pLen][ddHeapLen[pLen][1]-1];
    ddHeapLen[pLen][1]--;
    return;
}