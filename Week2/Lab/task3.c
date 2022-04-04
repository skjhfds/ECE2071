#include <stdio.h>
int main(void){
    int input_value, hours, minutes, seconds;

    printf("Input the number of seconds:  ");
    scanf("%d", &input_value);
    hours = input_value/3600;
    minutes = input_value%3600/60;
    seconds = input_value%3600%60;
    printf("\n%d seconds is equivalent to %d hours %d minutes and %d seconds", input_value, hours, minutes, seconds);
    return 0;
}