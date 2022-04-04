#include <stdio.h>
#include <stdlib.h>
#define file_length 50000002

// Comparative function used in median finding method
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

// Main
int main(void) {
    char *data = NULL;
    FILE *file = fopen("pi_50m.txt", "r");
    data = malloc(sizeof(char) * (file_length + 1));
    fread(data, sizeof(char), file_length, file);
    fclose(file);

    int count = 0; // palindrome length counter

    // array to store number of palindromes per length {...}
    int length;
    int num_pal[15] = {0}; // assuming there is no palindrome with length greater than 15

    // array to store distances per length {{}{}...}
    int *distances[15];
    for (int i=0; i<15; i++) {
        distances[i] = (int*) malloc(file_length * sizeof(int));
    }
    int previous[15] = {0}; // previous end indices

    // FIND PALINDROMES ==============================================
    for (int i = 0; i<file_length; i++) {
        // EVEN PALINDROME CASE ==================================
        if (data[i] == data[i+1]) {
            count = 0; // reset count
            while (data[i-count] == data[i+1+count]) {
                length = 2 + count*2; // palindrome length
                length--; // for indexing

                // store palindrome length  
                num_pal[length]++;

                // store palindrome distance
                distances[length][num_pal[length]-1] = i - previous[length] - 1;
                previous[length] = i;

                count++;
            }
                
        } 
        if (data[i] == data[i+2]) {
            // ODD PALINDROME CASE ===================================
            count = 0; // reset count 
            while (data[i-count] == data[i+2+count]) {
                length = 3 + count*2; // palindrome length
                length--; // for indexing
                                
                // store palindrome length  
                num_pal[length]++;    
                  
                // store palindrome distance
                distances[length][num_pal[length]-1] = i - previous[length] - 1;
                previous[length] = i;

                count++;
            }
        }
    }

    // SORT DISTANCES AND FIND MEDIANS =========================
    // find median of each length
    int medians[15] = {0};
    for (int i=0; i<15; i++) {
        // medians[i] = median_finder(distances[i], num_pal[i], 15);
        qsort(distances[i], num_pal[i], sizeof(int), compare);
        medians[i] = distances[i][num_pal[i]/2];
    }

    // PRINT OUTPUT =============================================
    printf("Palindrome   Number of     Median Digit\n");
    printf("Length       Palindromes   Distance\n");
    printf("----------   -----------   ------------\n");
    for (int i=1; i<15; i++) {
        printf("%10i%14i%15i\n", i+1, num_pal[i], medians[i]);
    }

    free(data);
    for (int i=0; i<15; i++) {
        free(distances[i]);
    }

    return 0;
}