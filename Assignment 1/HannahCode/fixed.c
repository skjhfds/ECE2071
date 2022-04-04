#include <stdio.h>
#include <stdlib.h>
#define file_length 50000002






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


    for (int i=0; i<array_length/length; i++) { // DELETE -1

        for (int j=1; j<length+1; j++) {
            temp[j-1] = array[length*i + j - 1];
        }


        qsort(temp, length, sizeof(int), compare);
        intermedians[i] = temp[length/2];
    }
    

    qsort(intermedians, array_length/length, sizeof(int), compare);
    return intermedians[(array_length/length)/2];
}


int main(void) {
    char *data = NULL;
    FILE *file = fopen("pi_50m.txt", "r");
    data = malloc(sizeof(char) * (file_length + 1));
    fread(data, sizeof(char), file_length, file);
    fclose(file);

    int count = 0; 


    int length;
    int num_pal[15] = {0};


    int *distances[15];
    for (int i=0; i<15; i++) {
        distances[i] = (int*) malloc(file_length * sizeof(int));
    }
    int previous[15] = {0}; 


    for (int i = 0; i<file_length; i++) {

        if (data[i] == data[i+1]) {
            count = 0; 
            while (data[i-count] == data[i+1+count]) {
                length = 2 + count*2; 
                length--;


                num_pal[length]++;


                distances[length][num_pal[length]-1] = i - previous[length];
                previous[length] = i;

                count++;
            }
                
        } 
        if (data[i] == data[i+2]) {

            count = 0; 
            while (data[i-count] == data[i+2+count]) {
                length = 3 + count*2;
                length--;
                                

                num_pal[length]++;    
                  
  
                distances[length][num_pal[length]-1] = i - previous[length];
                previous[length] = i;

                count++;
            }
        }
    }



    for (int i=0; i<15; i++) {
        distances[i] = realloc(distances[i], num_pal[i] * sizeof(int));
    }


    int medians[15] = {0};
    for (int i=0; i<15; i++) {
        medians[i] = median_finder(distances[i], num_pal[i], 15);
    }


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