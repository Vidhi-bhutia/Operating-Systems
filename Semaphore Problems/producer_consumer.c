#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 11
#define NUM_PRODUCERS 5
#define NUM_CONSUMERS 6

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int produced_count = 0, consumed_count = 0;
sem_t empty, full, mutex;

void *producer(void *arg) {
    int item;
    int id = *((int *)arg);

    while (produced_count < BUFFER_SIZE) {
        item = rand() % 100; // Produce random item
        sem_wait(&empty); // Wait for an empty slot
        sem_wait(&mutex); // Acquire the mutex to access the buffer
        buffer[in] = item; // Put the item into the buffer
        printf("Producer %d produced item: %d\n", id, item);
        in = (in + 1) % BUFFER_SIZE; // Update the in pointer
        produced_count++;
        sem_post(&mutex); // Release the mutex
        sem_post(&full); // Signal that buffer is no longer empty
        sleep(rand() % 2); // Simulate varying production time
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    int id = *((int *)arg);

    while (consumed_count < BUFFER_SIZE) {
        sem_wait(&full); // Wait for a full slot
        sem_wait(&mutex); // Acquire the mutex to access the buffer
        item = buffer[out]; // Get item from the buffer
        printf("Consumer %d consumed item: %d\n", id, item);
        out = (out + 1) % BUFFER_SIZE; // Update the out pointer
        consumed_count++;
        sem_post(&mutex); // Release the mutex
        sem_post(&empty); // Signal that buffer is no longer full
        sleep(rand() % 3); // Simulate varying consumption time
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Buffer starts as empty
    sem_init(&full, 0, 0); // Buffer starts as empty
    sem_init(&mutex, 0, 1); // Mutex for buffer access

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    // Join producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    // Join consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
