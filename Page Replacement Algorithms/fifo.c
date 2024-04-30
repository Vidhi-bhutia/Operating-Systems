#include <stdio.h>
#include <stdbool.h>

int pageFaults(int pages[], int n, int capacity)
{
    int current_page = 0;
    int next_page = 0;
    int page_faults = 0;
    int *frame = (int *)malloc(capacity * sizeof(int));
    bool *isPresent = (bool *)calloc(n, sizeof(bool));

    for (int i = 0; i < n; i++)
    {
        if (current_page < capacity)
        {
            if (!isPresent[pages[i]])
            {
                frame[current_page++] = pages[i];
                isPresent[pages[i]] = true;
                page_faults++;
            }
        }
        else
        {
            if (!isPresent[pages[i]])
            {
                isPresent[frame[next_page]] = false;
                frame[next_page] = pages[i];
                isPresent[pages[i]] = true;
                page_faults++;
                next_page = (next_page + 1) % capacity;
            }
        }
    }

    free(frame);
    free(isPresent);
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
