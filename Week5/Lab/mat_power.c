#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxLineLen 100

int d = 2;

void copyArray(double *A, double *B);@

int main(int argc, char *argv[]){ 
    if(argc!=3){
        printf("use <executable> <n> <filename> \n");
        return 0;
    }

    FILE *file = fopen(argv[2], "r");

    char c;
    c = getc(file);
    while (getc(file)!=EOF){
        if (c == '\n') d++;
        c = getc(file);
    }
    rewind(file);

    char row[maxLineLen], *token;
    double *M0,*M1,*M2;
    M0 = malloc(d*d*sizeof(double));
    M1 = malloc(d*d*sizeof(double));
    M2 = malloc(d*d*sizeof(double));

    int i=0;
    char f = 't';
    while (fgets(row, maxLineLen, file)){
        row[strlen(row)-1]='\0';
        token = strtok(row," ");
        while (token != NULL){
            M0[i++] = strtod(token,NULL);
            token = strtok(NULL," ");
        }
        if (f=='t'){
            if(i!=d){
                printf("Error! M0atrix read from file is not a square matrix\n");
                return 1;
            }
            f = 'f';
        }
    }
    fclose(file);

    copyArray(M1,M0);
    double tot=0;
    //atoi(argv[1])
    for (int n = 1; n > 0; n--){
        for (i = 0; i < d; i++){
            for (int j = 0; j < d; j++){
                for (int k = 0; k < d; k++){
                    tot += M0[i*d+k] * M1[k*d+j];
                }
                M2[i*d+j] = tot;
                tot = 0;
            }
        }
    }
    // Display the result.
    for (i = 0; i < d*d; i++){
        printf("%6.2f",M0[i]);
        if ((i+1)%d==0) printf("\n");
    }
    
    //printf("n=%d\nfilename=%s\n", n,argv[2]);
    return 0;
}

void copyArray(double *A, double *B){
    for (int i = 0; i < d*d; i++) A[i] = B[i];
}