#include <stdio.h>
#include <stdlib.h>
#define file_length 50000002

// NOTE:
// Something wrong with the columns of distance[][] is causing the program to fail
// Error code: 3221225477 (recursion/stack overflow)

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

// Median of Medians algorithm implemented in a function 
int median_finder(int array[], int array_length, int length) {
    int *intermedians = (int*) malloc((array_length/length-1) * sizeof(int));
    int *temp = (int*) malloc(length * sizeof(int));

    // find medians of sub-arrays of chosen length
    for (int i=0; i<array_length/length - 1; i++) {
        // find sub-arrays of chosen length
        for (int j=1; j<length+1; j++) {
            temp[j-1] = array[length*i + j - 1];
        }

        // find and store median of sub-array
        qsort(temp, length, sizeof(int), compare);
        intermedians[i] = temp[length/2];
    }
    
    // find median of intermedians
    qsort(intermedians, array_length/length, sizeof(int), compare);
    return intermedians[(array_length/length)/2];
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
                distances[length][num_pal[length]-1] = i - previous[length];
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
                distances[length][num_pal[length]-1] = i - previous[length];
                previous[length] = i;

                count++;
            }
        }
    }

    // SORT DISTANCES AND FIND MEDIANS =========================
    // resize distance arrays
    for (int i=0; i<15; i++) {
        distances[i] = realloc(distances[i], num_pal[i] * sizeof(int));
    }

    // find median of each length
    int medians[15] = {0};
    for (int i=0; i<15; i++) {
        medians[i] = median_finder(distances[i], num_pal[i], 15);
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