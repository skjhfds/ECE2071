/**
 * @file ece2071_asg1.c
 * @author Harry CHOI 32464223
 * @brief  Find palindromes of different lengths within the first 50M digits of pi: https://drive.google.com/file/d/1Egm6tIuC_1Wa8pfCKRkN2k2B6thqU0yr/view
 * @date 2022-03-25
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#define fileLen 50000002    // Length of pi_50m.txt
#define maxPLen 15          // Assume no palindromes exceed length 16
#define maxCount 5001644    // Assume no more than 5001645 palindromes of each length

/* Output Variables */
char *p = NULL;                 // Pointer to array of pi digits
unsigned int c[maxPLen] = {0},  // Number of palindromes starting at length 2
a[maxPLen] = {0},               // Anterior (previous) palindrome index for each length
d[maxPLen][maxCount-1] = {0};   // Digit distances for each length

/* Function Prototypes */
void G(unsigned int s, char o);         // Grow palindromes from seed
void P(void);                           // Print output
int C(const void * a, const void * b);  // Compare function for qsort

int main(void){
    /* Save file as array */
    FILE *file = fopen("pi_50m.txt", "r");  // Open file as instructed
    p = malloc(sizeof(char) * fileLen);     // Allocate buffer
    fread(p, sizeof(char), fileLen, file);  // Read file to memory
    fclose(file);                           // Close file

    /* Find seed palindromes */
    for(unsigned int i=2; i<fileLen; i++){
        /* Find Even Palindromes */
        if(p[i]==p[i+1]){                   // Find indices of even seeds "AA"
            if (a[0]) d[0][c[0]] = i-a[0]-1;// Calculate and store distance
            a[0] = i;                       // Update last index found
            G(i, 0);                        // Grow even seeds
            c[0]++;                         // Add seed itself to count
        }
        /* Find Odd Palindromes */
        if(p[i]==p[i+2]){                   // Find indices of odd seeds "ABA"
            if (a[1]) d[1][c[1]] = i-a[1]-1;// Calculate and store distance
            a[1] = i;                       // Update last index found
            G(i,1);                         // Grow odd seeds
            c[1]++;                         // Add seed itself to count
        }
    }

    /* Print output and return */
    P();
    return 0;
}

/* Grow palindromes from seed */
void G(unsigned int s, char o){
    unsigned int g = 1;                     // Growth (indices away) from seed
    unsigned int l;                         // Length of grown palindrome
    while (p[s-g] == p[s+1+g+o]){           // Loop if successive outer numbers equal
        l = g*2+o;                          // Calculate new length
        if (a[l]) d[l][c[l]] = s-g-a[l]-1;  // Calculate and store distance
        a[l] = s-g;                         // Update last index found
        c[l]++;                             // Add to count
        g++;                                // Grow
    }
    return;
}

/* Print Output */
void P(void){
    // Print headings (hard-coded for speed)
    printf("Palindrome    Number of      Median Digit\nLength        Palindromes    Distance\n----------    -----------    ------------");
    for(unsigned int i=0; i<maxPLen; i++){
        qsort(d[i],c[i],sizeof(unsigned int),C); // Sort distances as instructed
        if(c[i]) printf("\n%10d    %11d    %12d", i+2, c[i], d[i][c[i]/2]); // Print data for each length of palindrome
        else {printf("\n%10d    %11d    %12c", i+2, 0, '-'); break;} // Stop printing after first 0 c as instructed, but it's silly because there might be a non-zero c after it as it swaps between even and odd lengths
    }
    return;
}

/* Compare function for qsort */
int C (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}