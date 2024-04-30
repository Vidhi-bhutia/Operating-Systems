#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, head, i, disk_size, seek_time = 0;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the disk requests: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    int direction;

    if (head < (disk_size / 2))
    {
        direction = 0;
    }
    else
    {
        direction = 1;
    }

    // Sort the requests in ascending order using Bubble Sort
    for (i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("Sequence of disk requests: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", requests[i]);
    }
    printf("\n");

    int index = -1; // Initialize index to -1
    for (i = 0; i < n; i++)
    {
        if (requests[i] >= head)
        {
            index = i;
            break;
        }
    }

    if (direction == 0)
    {
        // Move left
        for (i = index - 1; i >= 0; i--)
        {
            if (requests[i] < head)
            { // Skip moving to 0th disk if next request is greater
                seek_time += abs(requests[i] - head);
                printf("Moved from %d to %d\n", head, requests[i]);
                head = requests[i];
            }
        }
        for (i = index; i < n; i++)
        {
            seek_time += abs(requests[i] - head);
            printf("Moved from %d to %d\n", head, requests[i]);
            head = requests[i];
        }
    }
    else
    {
        // Move right
        for (i = index; i < n; i++)
        {
            seek_time += abs(requests[i] - head);
            printf("Moved from %d to %d\n", head, requests[i]);
            head = requests[i];
        }
    }
    printf("Total seek time: %d\n", seek_time);

    return 0;
}
