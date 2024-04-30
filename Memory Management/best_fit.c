#include <stdio.h>

void bestFit(int blockSize[], int m, int processSize[], int n) 
{ 
    int allocation[n]; 

    for (int i = 0; i < n; i++) 
        allocation[i] = -1; 

    for (int i = 0; i < n; i++) 
    { 
        int bestIdx = -1; 
        for (int j = 0; j < m; j++) 
        { 
            if (blockSize[j] >= processSize[i]) 
            { 
                if (bestIdx == -1) 
                    bestIdx = j; 
                else if (blockSize[bestIdx] > blockSize[j]) 
                    bestIdx = j; 
            } 
        } 

        if (bestIdx != -1) 
        { 
            allocation[i] = bestIdx; 
            blockSize[bestIdx] -= processSize[i]; 
        } 
    } 

    printf("\nProcess No.\tProcess Size\tBlock no.\n"); 
    for (int i = 0; i < n; i++) 
    { 
        printf(" %d\t\t%d\t\t", i+1, processSize[i]); 
        if (allocation[i] != -1) 
            printf("%d", allocation[i] + 1); 
        else
            printf("Not Allocated"); 
        printf("\n"); 
    } 
} 

int main() 
{ 
    int m, n;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    int blockSize[m];
    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i+1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processSize[n];
    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d", &processSize[i]);
    }

    bestFit(blockSize, m, processSize, n); 

    return 0 ; 
}
