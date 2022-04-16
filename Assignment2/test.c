#include <stdio.h>
typedef struct queueNode {
    int coords[2];
    qNode *next;
} qNode;
typedef struct stackNode {
    int coords[2];
    sNode *next
} sNode;

void enqueue(qNode **end, int coords[2]){
    qNode *newNode = (qNode*)malloc(sizeof(qNode));
    *newNode->coords = coords;
    newNode->next = *end;
    *end = newNode;
    return;
}
void dequeue(qNode **end,int *coords){
    qNode *temp = *end;
    while (temp != NULL) *temp = temp -> next;
    coords = temp->coords;
    free(temp);
    return;
}
void printQ(qNode *end){
    qNode * temp = end;
    while (temp!= NULL){
        printf("[%d,%d]\n", temp->coords[0],temp->coords[1]);
        temp = temp -> next;
    }
    puts("done!");
}

int main(){
    qNode *end = NULL;
    int first[2] = {0,0};
    enqueue(&end, first);
    for (int i = 1; i < 20; i++){
        int temp[2] = {i,i};
        enqueue(&end, temp);
    }
    printQ(end);

    return 1;
}