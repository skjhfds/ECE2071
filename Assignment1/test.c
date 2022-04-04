#include <stdio.h>
#define len 20
#define heapLen len/2

int test[len] = {1,42,623,76,32,43,23,76,22,1,
1,8,56,9,234,345,456,567,1,3},
heaps[2][heapLen] = {0},
heapLens[2] = {0};

// Function Prototypes
void pushToFront(int input, int heap);
void pushToEnd(int input, int heap);
void maxToFront(void);
void minToFront(void);

int main(void){
    double median;
    for (int i = 0; i<len; i++){
        printf("%d ",test[i]);
    }
    for (int i = 0; i<len; i++){
        // Fill from left
        if (heapLens[0]==0){
            heaps[0][0] = test[i];
            heapLens[0]++;
            printf("\nmaxHeap: ");
            for (int i = 0; i<heapLen; i++){
                printf("%d ",heaps[0][i]);
            }
            printf("\nminHeap: ");
            for (int i = 0; i<heapLen; i++){
                printf("%d ",heaps[1][i]);
            }                
            continue;
        }

        // Calc Median
        switch (heapLens[1]-heapLens[0])
        {
        case 0: // Equal
            median = (heaps[0][0]+heaps[1][0])/2.;
            break;
        case -1: // maxHeap larger
            median = heaps[0][0];
            break;
        case 1: // minHeap Larger
            median = heaps[1][0];
            break;        
        default:
            break;
        }
        printf("\nMedian = %.1f ------------------------------------------- input = %d",median,test[i]);

        // Choose heap to send to
        if (test[i] > median){ // send to minHeap
            if (test[i] < heaps[1][0]){
                printf(" ptFRONT min");
                pushToFront(test[i],1);
            } else {
                printf(" ptEND min");
                pushToEnd(test[i],1);
            }
        } else { // If same as mean, send to maxHeap
            if (test[i] > heaps[0][0]){
                printf(" ptFRONT max");
                pushToFront(test[i],0);
            } else {
                pushToEnd(test[i],0);
                printf(" ptEND max");
            }
        }
        
        // Check balance
        switch (heapLens[1]-heapLens[0])
        {
            case -2: // maxHeap heavy
                pushToFront(heaps[0][0],1);
                maxToFront();
                break;
            case 2: // minHeap heavy
                pushToFront(heaps[1][0],0);
                minToFront();
                break;
            default:
                break;
        }

        char flag = ' ';
        printf("\nmaxHeap: ");
        for (int i = 0; i<heapLens[0]; i++){
            printf("%d ",heaps[0][i]);
            if (heaps[0][i]>heaps[0][0]){
                flag = 'F';
            }
        }
        printf("  heapLens[0] = %d  %c\nminHeap: ",heapLens[0],flag);
        flag = ' ';
        for (int i = 0; i<heapLens[1]; i++){
            printf("%d ",heaps[1][i]);
            if (heaps[1][i]<heaps[1][0]){
                flag = 'F';
            }
        }
        printf("  heapLens[1] = %d  %c",heapLens[1],flag);
        if (flag == 'F'){
            break;
        }
        
    }
    // Calc Median
    switch (heapLens[1]-heapLens[0])
    {
    case 0: // Equal
        median = (heaps[0][0]+heaps[1][0])/2.;
        break;
    case -1: // maxHeap larger
        median = heaps[0][0];
        break;
    case 1: // minHeap Larger
        median = heaps[1][0];
        break;        
    default:
        break;
    }
    printf("\nMedian = %.1f",median);
    
    return 0;
}

void pushToFront(int input, int heap){
    heaps[heap][heapLens[heap]] = heaps[heap][0];
    heaps[heap][0] = input;
    heapLens[heap]++;
}
void pushToEnd(int input, int heap){
    heaps[heap][heapLens[heap]] = input;
    heapLens[heap]++;
}
void maxToFront(void){
    printf("\nmaxHeap: ");
    for (int i = 0; i<heapLens[0]; i++){
        printf("%d ",heaps[0][i]);
    }
    printf("  heapLens[0] = %d\nminHeap: ",heapLens[0]);
    for (int i = 0; i<heapLens[1]; i++){
        printf("%d ",heaps[1][i]);
    }
    printf("  heapLens[1] = %d",heapLens[1]);


    int *max = &heaps[0][1];
    for(int i = 2; i<heapLens[0]; i++){
        if (heaps[0][i]>*max){
            max = &heaps[0][i];
        }
    }
    heaps[0][0] = *max;
    *max = heaps[0][heapLens[0]-1];
    heapLens[0]--;
    printf("\n    maxToFront(%d)",*max);
    return;
}
void minToFront(void){
    int *min = &heaps[1][1];
    for(int i = 2; i<heapLens[1]; i++){
        if (heaps[1][i]<*min){
            min = &heaps[1][i];
        }
    }
    heaps[1][0] = *min;
    *min = heaps[1][heapLens[1]-1];
    heapLens[1]--;
    printf("\n    minToFront(%d)",*min);
    return;
}