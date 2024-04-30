#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define NUM_READS 1
#define NUM_WRITES 1

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource_lock = PTHREAD_MUTEX_INITIALIZER;
int readers_count = 0;
int reads_complete = 0;
int writes_complete = 0;

void *reader(void *arg) {
    int id = *((int *)arg);
    
    while(reads_complete < NUM_READS) {
        // Entry section
        pthread_mutex_lock(&mutex);
        readers_count++;
        if (readers_count == 1) {
            pthread_mutex_lock(&resource_lock); // First reader locks the resource
        }
        pthread_mutex_unlock(&mutex);
        
        // Critical section (reading)
        printf("Reader %d is reading...\n", id);
        sleep(1); // Simulating reading
        
        // Exit section
        pthread_mutex_lock(&mutex);
        readers_count--;
        if (readers_count == 0) {
            pthread_mutex_unlock(&resource_lock); // Last reader unlocks the resource
        }
        pthread_mutex_unlock(&mutex);
        
        // Remainder section
        sleep(2); // Simulating non-critical section
        if (reads_complete == 0) {
            reads_complete++;
        }
    }
    
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *)arg);
    
    while(writes_complete < NUM_WRITES) {
        // Entry section
        pthread_mutex_lock(&resource_lock);
        
        // Critical section (writing)
        printf("Writer %d is writing...\n", id);
        sleep(2); // Simulating writing
        
        // Exit section
        pthread_mutex_unlock(&resource_lock);
        
        // Remainder section
        sleep(3); // Simulating non-critical section
        if (writes_complete == 0) {
            writes_complete++;
        }
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];
    
    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    
    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    
    return 0;
}
