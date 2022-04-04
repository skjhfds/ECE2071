#include <stdio.h>
#include <stdlib.h>

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

int median_finder(int array[], int array_length, int length) {
    int *intermedians = (int*) malloc((array_length/length-1) * sizeof(int));
    int *temp = (int*) malloc(length * sizeof(int));

    printf("\nintermedians: ");
    for (int i =0; i<array_length/length;i++) printf("%d ",intermedians[i]);

    // find medians of sub-arrays of chosen length
    for (int i=0; i<array_length/length; i++) {
        // find sub-arrays of chosen length
        for (int j=1; j<length+1; j++) {
            temp[j-1] = array[length*i + j - 1];
        }

        printf("\ntemp[%d]: ",i);
        for (int k =0; k<length;k++) printf("%d ",temp[k]);

        // find and store median of sub-array
        qsort(temp, length, sizeof(int), compare);

        printf("\ntemp[%d]: ",i);
        for (int k =0; k<length;k++) printf("%d ",temp[k]);

        intermedians[i] = temp[length/2];
    }
    
    // find median of intermedians
    printf("\nintermedians: ");
    for (int i =0; i<array_length/length;i++) printf("%d ",intermedians[i]);
    qsort(intermedians, array_length/length, sizeof(int), compare);
    printf("\nintermedians: ");
    for (int i =0; i<array_length/length;i++) printf("%d ",intermedians[i]);
    return intermedians[(array_length/length)/2];
}

int main (void){
    int test[12] = {1,213,4,2,23,5,2,654,8,46,43,1};
    printf("\n%d\n",median_finder(test, 12, 6));
}