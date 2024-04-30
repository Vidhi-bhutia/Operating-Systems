#include <stdio.h>
#include <math.h>

void FCFS(int arr[], int head, int size)
{
	int seek_count = 0;
	int cur_track, distance;

	for (int i = 0; i < size; i++)
	{
		cur_track = arr[i];

		// calculate absolute distance
		distance = fabs(head - cur_track);

		// increase the total count
		seek_count += distance;

		// accessed track is now new head
		head = cur_track;
	}

	printf("Total number of seek operations: %d\n", seek_count);

	// Seek sequence would be the same
	// as request array sequence
	printf("Seek Sequence is\n");

	for (int i = 0; i < size; i++)
	{
		printf("%d\n", arr[i]);
	}
}

// Driver code
int main()
{
	int n;
	printf("Enter the number of requests: ");
	scanf("%d", &n);

	int proc[n];
	printf("Enter the requests: ");
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &proc[i]);
	}

	int start_head;
	printf("Enter the starting head position: ");
	scanf("%d", &start_head);

	FCFS(proc, start_head, n);

	return 0;
}
