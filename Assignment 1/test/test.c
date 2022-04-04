#include <stdio.h>
#include <stdlib.h>
#define temp_length 15

int compare(const void *p1, const void *p2);
int median_finder(int array[], int array_length);

int main (void){
    int a[7] = {1,2,123,533,4,234,2};
    printf("%D",median_finder(a, 7));
}

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
int median_finder(int array[], int array_length) {
    int *intermedians = (int*) malloc((array_length/temp_length-1) * sizeof(int));
    int temp[temp_length];

    // find medians of sub-arrays of chosen length
    for (int i=0; i<array_length/temp_length - 1; i++) {
        // find sub-arrays of chosen length
        for (int j=1; j<temp_length+1; j++) {
            temp[j-1] = array[temp_length*i + j - 1];
        }

        // find and store median of sub-array
        qsort(temp, temp_length, sizeof(int), compare);
        intermedians[i] = temp[temp_length/2];
    }
    
    // find median of intermedians
    qsort(intermedians, array_length/temp_length, sizeof(int), compare);
    return intermedians[(array_length/temp_length)/2];
}