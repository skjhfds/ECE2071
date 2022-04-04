#include <stdio.h>
#include <stdlib.h>

#define fileLen 50000002    // Length of pi_50m.txt
#define maxPLen 15          // Assume no palindromes exceed length 16
#define maxCount 5001644    // Assume no more than 5001645 palindromes of each length

/* Output Variables */
char *piDigits = NULL;              // Pointer to array of pi digits
unsigned int pCount[maxPLen] = {0}, // Number of palindromes starting at 2
pLastI[maxPLen] = {0},              // Indices of last found palindrome
digitDist[maxPLen][maxCount-1] = {0};   // Digit distances

/* Function Prototypes */
void growPalindrome(unsigned int seed, char isOdd);
void printOutput(void);
int cmpfunc (const void * a, const void * b);

int main(void){
    /* Save file as array */
    FILE *file = fopen("pi_50m.txt", "r");      // Open file
    piDigits = malloc(sizeof(char) * fileLen);  // allocate buffer
    fread(piDigits, sizeof(char), fileLen, file);   // read file into memory
    fclose(file);                               // close file

    for(unsigned int i=2; i<fileLen; i++){
        /* Find Even Palindromes */
        if(piDigits[i]==piDigits[i+1]){     // Find indices of double numbers "AA"
            if (pLastI[0]) digitDist[0][pCount[0]] = i-pLastI[0]-1; // Calc and store distance
            pLastI[0] = i;                  // Update last index found
            growPalindrome(i, 0);           // Grow double numbers
            pCount[0]++;
        }
        /* Find Odd Palindromes */
        if(piDigits[i]==piDigits[i+2]){     // Find indices of gapped numbers "ABA"
            if (pLastI[1]) digitDist[1][pCount[1]] = i-pLastI[1]-1; // Calc and store distance
            pLastI[1] = i;                  // Update last index found
            growPalindrome(i,1);            // Grow gapped numbers
            pCount[1]++;
        }
    }

    /* Print output and finish */
    printOutput();
    return 0;
}

void growPalindrome(unsigned int seed, char isOdd){
    unsigned int i = 1;         // Growth from seed
    unsigned int pLen;
    while (piDigits[seed-i] == piDigits[seed+1+i+isOdd]){
        pLen = i*2+isOdd;       // Length of palindrome
        if (pLastI[pLen]) digitDist[pLen][pCount[pLen]] = seed-i-pLastI[pLen]-1;    // Calc and store distance
        pLastI[pLen] = seed-i;  // Update last index found
        pCount[pLen]++;         // Add to count
        i++;
    }
    return;
}

void printOutput(void){
    // Headings
    printf("Palindrome    Number of      Median Digit\nLength        Palindromes    Distance\n----------    -----------    ------------");
    for(unsigned int i=0; i<maxPLen; i++){
        qsort(digitDist[i],pCount[i],sizeof(unsigned int),cmpfunc); // Sort distances
        if(pCount[i]) printf("\n%10d    %11d    %12d", i+2, pCount[i], digitDist[i][pCount[i]/2]);
        else {printf("\n%10d    %11d    %12c", i+2, 0, '-'); break;}// Stop printing after first 0 pCount as instructed, but it's silly because there might be a non-zero pCount after it as it swaps between even and odd lengths
    }
    return;
}

int cmpfunc (const void * a, const void * b) {  // Compare function for qsort
   return ( *(int*)a - *(int*)b );
}