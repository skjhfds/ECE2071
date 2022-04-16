#include <stdio.h>
#include <stdlib.h>

/* Function prototypes */
void print(int mSize, char maze[mSize][mSize+1]);
void findST(int mSize, char maze[mSize][mSize+1], int ST[2][2]);
// Solution in stack
// visited in queue

typedef struct queueNode {
    int coords[2];
    qNode *next;
}qNode;
typedef struct stackNode {
    int coords[2];
    sNode *next
}sNode;

void enqueue(qNode **end, int coords[2]){
    qNode *newNode = (qNode*)malloc(sizeof(qNode));
    *newNode->coords = coords;
    newNode->next = *end;
    *end = newNode;
    return;
}
void dequeue(qNode **end,int *coords){
    qNode *temp = *end;
    while (end != NULL) *end = temp->next;
    coords = temp->coords;
    free(temp);
    return;
}


int main(int argc, char *argv[])
{
    /* Import file as 2D array */
    FILE *file = fopen(argv[1],"r");
    /* Get maze size */
    int mSize = 0;
    while (fgetc(file) != '\n') mSize++;
    rewind(file);
    /* Text to 2d array */
    char maze[mSize][mSize+1];
    fread(maze, 4, mSize*mSize, file);
    fclose(file);
    /* Find Start & Target */
    int ST[2][2]={0};
    findST(mSize, maze, ST);
    //print(mSize, maze);
    //printf("S={%d,%d}\nT={%d,%d}\n",ST[0][0],ST[0][1],ST[1][0],ST[1][1]);
    return 0;
}
void print(int mSize, char maze[mSize][mSize+1]){
    for (int y = 0; y < mSize; y++){
        for (int x = 0; x < mSize+1; x++){
            printf("%c",maze[y][x]);
        }
    }
}
void findST(int mSize, char maze[mSize][mSize+1], int ST[2][2]){
    int flag = 0;
    for (int y = 0; y < mSize; y++){
        for (int x = 0; x < mSize+1; x++){
            if(maze[y][x]=='S'){
                flag++;
                ST[0][0]=x;
                ST[0][1]=y;
                continue;
            }
            if(maze[y][x]=='T'){
                flag++;
                ST[1][0]=x;
                ST[1][1]=y;
                continue;
            }
            if(flag>1) return;
        }
    }
}
void wave(char i){}