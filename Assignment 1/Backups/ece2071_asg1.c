#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fileLen 50000002    // Length of pi_50m.txt
#define testMax fileLen
#define maxPLen 15          // Assume no palindromes exceed length 15
#define maxCount 5001645    // Assume no more than 5001645 palindromes of each length
#define halfCount maxCount/2+1

/* Output Variables */
char *piDigits = NULL;              // Pointer to array of pi digits
unsigned int pCount[maxPLen] = {0}, // Number of palindromes starting at 2
pLastI[maxPLen] = {0},              // Indices of last found palindrome
// Heap sorting variables
digitDist[maxPLen][maxCount] = {0},
ddMaxHeap[maxPLen][halfCount] = {0},// Digit distances in max heap
ddMinHeap[maxPLen][halfCount] = {0},// Digit distances in min heap
ddHeapLen[maxPLen][2] = {0};        // Digit distances heap lengths

/* Function Prototypes */
void growPalindrome(unsigned int seed, char isOdd);
void printOutput(void);
// Heap sorting functions
void addDist(unsigned int dist, unsigned int pLen);
int finalMedian(unsigned int pLen);
double calcMedian(unsigned int pLen);
void pushToFront(unsigned int input, unsigned char heap, unsigned int pLen);
void pushToEnd(unsigned int input, unsigned char heap, unsigned int pLen);
void maxToFront(unsigned int pLen);
void minToFront(unsigned int pLen);

int zeroCount = 0;

int main(void)
{
    /* Save file as array */
    FILE *file = fopen("pi_50m.txt", "r");  // Open file
    piDigits = malloc(4 * (fileLen + 1));   // allocate buffer
    fread(piDigits, 4, fileLen, file);      // read file into memory
    fclose(file);                           // close file

    /* Find Even Palindromes */
    for(unsigned int i=2; i<testMax; i++){
        if(piDigits[i]==piDigits[i+1]){     // Find indices of double numbers "AA"
            if (pLastI[0]) addDist(i-pLastI[0]-1, 0);
            if (i-pLastI[0]-1 == 0) zeroCount++;
            pLastI[0] = i;
            growPalindrome(i, 0);           // Grow double numbers
            pCount[0]++;
        }
    }
    /* Find Odd Palindromes */
    for(unsigned int i=2; i<testMax; i++){
        if(piDigits[i]==piDigits[i+2]){     // Find indices of gapped numbers "ABA"
            if (pLastI[1]) addDist(i-pLastI[1]-1, 1);
            pLastI[1] = i;
            growPalindrome(i,1);            // Grow gapped numbers
            pCount[1]++;
        }
    }

    /* Print output and finish */
    //printOutput();
    printf("%d",zeroCount);
    int distcount=0;
    for (int c = 0; c<maxCount; c++){
        if (digitDist[0][c]==0){
            printf("%d %d",c,digitDist[0][c]);
            exit(5);
            if (zeroCount){
                zeroCount--;
                break;
            }
        } else distcount++;
    }
    printf("\n%d %d",pCount[0], distcount);
    return 0;
}

void growPalindrome(unsigned int seed, char isOdd){
    unsigned int i = 1;
    unsigned int pLen;
    while (piDigits[seed-i] == piDigits[seed+1+i+isOdd]){
        pLen = i*2+isOdd;
        // Calc distance
        if (pLastI[pLen]) addDist(seed-i-pLastI[pLen]-1, pLen);
        pLastI[pLen] = seed-i;
        pCount[pLen]++; // Add to count
        i++;
    }
    return;
}

void printOutput(void){
    // Titles
    printf("Palindrome    Number of      Median Digit\nLength        Palindromes    Distance\n----------    -----------    ------------");
    // Print line of data if not 0;
    for(unsigned int i=0; i<maxPLen; i++){
        if(pCount[i]) printf("\n%10d    %11d    %12d", i+2, pCount[i], finalMedian(i));
    }
    return;
}

void addDist(unsigned int dist, unsigned int pLen){
       digitDist[pLen][pCount[pLen]-1]=dist;
       return;
}
int finalMedian(unsigned int pLen){    
    for (unsigned int i = 0; i<pCount[pLen]-1; i++){
        unsigned int dist = digitDist[pLen][i];
        // Fill in ddMaxHeap first
        if (!ddHeapLen[pLen][0]){
            ddMaxHeap[pLen][0] = dist;
            ddHeapLen[pLen][0]++;
            continue;
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
    }
    if (ddHeapLen[pLen][0]<ddHeapLen[pLen][1]) return ddMinHeap[pLen][0];  // ddMinHeap larger
    else return ddMaxHeap[pLen][0];
}
double calcMedian(unsigned int pLen){
    double median;
    switch (ddHeapLen[pLen][1]-ddHeapLen[pLen][0]){
        case 0: // Equal
            median = ddMaxHeap[pLen][0]; break;
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