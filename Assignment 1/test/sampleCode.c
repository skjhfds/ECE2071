#include <stdio.h>
/*
Compile with:
gcc -std=c17 -pedantic -Werror count_pi.c -o count_pi -lm
*/
int main(void)
{
    int c;
    unsigned int count = 0;

    /* Do NOT change the filename! Otherwise your assignment will fail. */
    FILE *file = fopen("pi_50m.txt", "r");
    if (file == 0) {
        printf("I can’t open the file for reading.\n");
        return -1;
    }

    while ((c = fgetc(file)) != EOF) {
        /* Your palindrome number hunting routines could start here */
        count++;
    }

    printf("The file is %d characters long.\n", count);
    fclose(file);
    return 0;
}