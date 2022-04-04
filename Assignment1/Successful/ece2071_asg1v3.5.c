#include <stdio.h>
#include <stdlib.h>

#define fileLen 50000002    // Length of pi_50m.txt
#define maxe 15          // Assume no palindromes exceed length 16
#define maxCount 5001644    // Assume no more than 5001645 palindromes of each length

/* Output Variables */
char *p = NULL;              // Pointer to array of pi digits
unsigned int c[maxe] = {0}, // Number of palindromes starting at 2
l[maxe] = {0},              // Indices of last found palindrome
d[maxe][maxCount-1] = {0};   // Digit distances

/* Function Prototypes */
void g(unsigned int s, char o); //Grow palindrome from seed
void r(void);
int f(const void * a, const void * b);  // Compare function for qsort

int main(void){
    /* Save file as array */
    FILE *file = fopen("pi_50m.txt", "r");      // Open file
    p = malloc(sizeof(char) * fileLen);  // allocate buffer
    fread(p, sizeof(char), fileLen, file);   // read file into memory
    fclose(file);                               // close file

    for(unsigned int i=2; i<fileLen; i++){
        /* Find Even Palindromes */
        if(p[i]==p[i+1]){     // Find indices of double numbers "AA"
            if (l[0]) d[0][c[0]] = i-l[0]-1; // Calc and store distance
            l[0] = i;                  // Update last index found
            g(i, 0);           // Grow double numbers
            c[0]++;
        }
        /* Find Odd Palindromes */
        if(p[i]==p[i+2]){     // Find indices of gapped numbers "ABA"
            if (l[1]) d[1][c[1]] = i-l[1]-1; // Calc and store distance
            l[1] = i;                  // Update last index found
            g(i,1);            // Grow gapped numbers
            c[1]++;
        }
    }

    /* Print output and finish */
    r();
    return 0;
}

void g(unsigned int s, char o){ //Grow palindrome from seed
    unsigned int i = 1;         // Growth from s
    unsigned int e;             // Length of palindrom being tested
    while (p[s-i] == p[s+1+i+o]){
        e = i*2+o;       // Length of palindrome
        if (l[e]) d[e][c[e]] = s-i-l[e]-1;    // Calc and store distance
        l[e] = s-i;  // Update last index found
        c[e]++;         // Add to count
        i++;
    }
    return;
}

void r(void){
    // Headings
    printf("Palindrome    Number of      Median Digit\nLength        Palindromes    Distance\n----------    -----------    ------------");
    for(unsigned int i=0; i<maxe; i++){
        qsort(d[i],c[i],sizeof(unsigned int),f); // Sort distances
        if(c[i]) printf("\n%10d    %11d    %12d", i+2, c[i], d[i][c[i]/2]);
        else {printf("\n%10d    %11d    %12c", i+2, 0, '-'); break;}// Stop printing after first 0 c as instructed, but it's silly because there might be a non-zero c after it as it swaps between even and odd lengths
    }
    return;
}

int f (const void * a, const void * b) {  // Compare function for qsort
   return ( *(int*)a - *(int*)b );
}