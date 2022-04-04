#include <stdio.h>

int main(void) {
    double answer;
    answer = 9%3-1+22/7.;   printf("answer = %f\n",answer);
    answer = 8%3-1;         printf("answer = %f\n",answer);
    answer = 2 - 5%2 -7/2;  printf("answer = %f\n",answer);
    answer = 2-8%3;         printf("answer = %f\n",answer);
    return 0;
}