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
double finalMedian(unsigned int pLen);

int compare(const void *p1, const void *p2) {
    int a = *(const int*) p1; 
    int b = *(const int*) p2;

    if (a > b) {
        return 1;
    } else {
        if (a == b) {
            return 0;
        } else {
            return -1;
        }
    }
}

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
    printOutput();
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
        if(pCount[i]) printf("\n%10d    %11d    %12.1f", i+2, pCount[i], finalMedian(i));
    }
    return;
}

void addDist(unsigned int dist, unsigned int pLen){
       digitDist[pLen][pCount[pLen]-1]=dist;
       return;
}
double finalMedian(unsigned int pLen){    
    qsort(digitDist[pLen], pCount[pLen], sizeof(int), compare);
    return digitDist[pLen][pCount[pLen]/2]; 
}
