#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // Include for sleep function
#define NUM_PHILOSOPHERS 5
#define NUM_CHOPSTICKS 5

void *dine(void *arg); // Adjusted the function signature to match pthread_create
pthread_t philosopher[NUM_PHILOSOPHERS];
pthread_mutex_t chopstick[NUM_CHOPSTICKS];

int main()
{
    int i, status_message;
    void *msg;

    // Initialize the chopstick Mutex array
    for (i = 0; i < NUM_CHOPSTICKS; i++)
    {
        status_message = pthread_mutex_init(&chopstick[i], NULL);
        if (status_message != 0)
        {
            printf("\n Mutex initialization failed");
            exit(1);
        }
    }

    // Run the philosopher Threads using dine() function
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        status_message = pthread_create(&philosopher[i], NULL, dine, (void *)(intptr_t)i); // Cast i to intptr_t and then to void* to pass it as argument
        if (status_message != 0)
        {
            printf("\n Thread creation error \n");
            exit(1);
        }
    }

    // Wait for all philosophers threads to complete executing (finish dining) before closing the program
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        status_message = pthread_join(philosopher[i], &msg);
        if (status_message != 0)
        {
            printf("\n Thread join failed \n");
            exit(1);
        }
    }

    // Destroy the chopstick Mutex array
    for (i = 0; i < NUM_CHOPSTICKS; i++)
    {
        status_message = pthread_mutex_destroy(&chopstick[i]);
        if (status_message != 0)
        {
            printf("\n Mutex destruction failed \n");
            exit(1);
        }
    }
    return 0;
}

void *dine(void *arg)
{
    int n = (int)(intptr_t)arg; // Cast void* to intptr_t and then to int
    printf("Philosopher %d is thinking\n", n);

    // Philosopher picks up the left chopstick (wait)
    pthread_mutex_lock(&chopstick[n]);

    // Philosopher picks up the right chopstick (wait)
    pthread_mutex_lock(&chopstick[(n + 1) % NUM_CHOPSTICKS]);

    // After picking up both the chopsticks, philosopher starts eating
    printf("Philosopher %d is eating\n", n);
    sleep(3);

    // Philosopher places down the left chopstick (signal)
    pthread_mutex_unlock(&chopstick[n]);

    // Philosopher places down the right chopstick (signal)
    pthread_mutex_unlock(&chopstick[(n + 1) % NUM_CHOPSTICKS]);

    // Philosopher finishes eating
    printf("Philosopher %d Finished eating\n", n);

    pthread_exit(NULL); // Terminate the thread
}
