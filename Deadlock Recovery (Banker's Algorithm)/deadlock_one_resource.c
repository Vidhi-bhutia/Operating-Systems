#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100
#define MAX_RESOURCES 100

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

int num_processes, num_resources;

bool is_safe(int process_sequence[], int n)
{
    int work[MAX_RESOURCES];
    bool finish[n];
    for (int i = 0; i < num_resources; ++i)
        work[i] = available[i];

    for (int i = 0; i < n; ++i)
        finish[i] = false;

    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (int i = 0; i < n; ++i)
        {
            if (!finish[i])
            {
                bool possible = true;
                for (int j = 0; j < num_resources; ++j)
                {
                    if (need[i][j] > work[j])
                    {
                        possible = false;
                        break;
                    }
                }
                if (possible)
                {
                    for (int j = 0; j < num_resources; ++j)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    process_sequence[count++] = i;
                    found = true;
                }
            }
        }
        if (!found)
            break;
    }
    return count == n;
}

int main()
{
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter maximum resource allocation for each process:\n");
    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j)
            scanf("%d", &max[i][j]);

    printf("Enter resource allocation for each process:\n");
    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j)
            scanf("%d", &allocation[i][j]);

    printf("Enter available resources: ");
    for (int i = 0; i < num_resources; ++i)
        scanf("%d", &available[i]);

    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j)
            need[i][j] = max[i][j] - allocation[i][j];

    int process_sequence[MAX_PROCESSES];
    if (is_safe(process_sequence, num_processes))
    {
        printf("Safe sequence: ");
        for (int i = 0; i < num_processes; ++i)
            printf("%d ", process_sequence[i]);
        printf("\n");

        // Ask for additional resources
        char response;
        printf("Do you have any additional resource requests? (y/n): ");
        scanf(" %c", &response);
        if (response == 'y' || response == 'Y') {
            int process_id;
            printf("Enter the process ID requesting additional resources: ");
            scanf("%d", &process_id);

            int request[MAX_RESOURCES];
            printf("Enter the additional resource request for process %d:\n", process_id);
            for (int i = 0; i < num_resources; ++i)
                scanf("%d", &request[i]);

            // Check if request <= need
            bool valid_request = true;
            for (int i = 0; i < num_resources; ++i) {
                if (request[i] > need[process_id][i]) {
                    valid_request = false;
                    break;
                }
            }

            if (!valid_request) {
                printf("Request cannot be fulfilled as it exceeds the maximum need.\n");
            } else {
                // Check if request <= available
                bool safe_to_allocate = true;
                for (int i = 0; i < num_resources; ++i) {
                    if (request[i] > available[i]) {
                        safe_to_allocate = false;
                        break;
                    }
                }

                if (!safe_to_allocate) {
                    printf("Request cannot be fulfilled due to insufficient available resources.\n");
                } else {
                    // Allocate resources
                    for (int i = 0; i < num_resources; ++i) {
                        available[i] -= request[i];
                        allocation[process_id][i] += request[i];
                        need[process_id][i] -= request[i];
                    }

                    // Check if system is still in a safe state
                    if (is_safe(process_sequence, num_processes)) {
                        printf("Safe sequence after resource allocation: ");
                        for (int i = 0; i < num_processes; ++i)
                            printf("%d ", process_sequence[i]);
                        printf("\n");
                    } else {
                        printf("Resource allocation resulted in an unsafe state.\n");
                    }
                }
            }
        }
    }
    else
    {
        printf("No safe sequence exists.\n");
    }

    return 0;
}
