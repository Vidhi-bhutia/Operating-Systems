#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int pageFaults(int pages[], int n, int capacity)
{
    int *frame = (int *)malloc(capacity * sizeof(int));
    int *indexes = (int *)malloc(n * sizeof(int));
    int *lru_indexes = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        indexes[i] = -1;
        lru_indexes[i] = INT_MAX;
    }

    int page_faults = 0;
    for (int i = 0; i < n; i++)
    {
        if (i < capacity)
        {
            if (indexes[pages[i]] == -1)
            {
                frame[i] = pages[i];
                indexes[pages[i]] = i;
                lru_indexes[pages[i]] = i;
                page_faults++;
            }
        }
        else
        {
            if (indexes[pages[i]] == -1)
            {
                int lru = INT_MAX;
                int val;
                for (int j = 0; j < capacity; j++)
                {
                    if (lru_indexes[frame[j]] < lru)
                    {
                        lru = lru_indexes[frame[j]];
                        val = j;
                    }
                }

                indexes[frame[val]] = -1;
                indexes[pages[i]] = val;
                frame[val] = pages[i];
                lru_indexes[pages[i]] = i;
                page_faults++;
            }
            lru_indexes[pages[i]] = i;
        }
    }

    free(frame);
    free(indexes);
    free(lru_indexes);
    return page_faults;
}

int main()
{
    int n;
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page sequence:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    int capacity;
    printf("Enter the capacity of the page frame: ");
    scanf("%d", &capacity);

    printf("Number of page faults: %d\n", pageFaults(pages, n, capacity));

    return 0;
}
