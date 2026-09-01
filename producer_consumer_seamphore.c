#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS   10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full;

void *producer(void *arg)
{
    int i;
    for (i = 1; i <= NUM_ITEMS; i++)
    {
        sem_wait(&empty);

        buffer[in] = i;
        printf("Producer produced: %d (at index %d)\n", i, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int i;
    for (i = 1; i <= NUM_ITEMS; i++)
    {
        sem_wait(&full);

        int item = buffer[out];
        printf("Consumer consumed: %d (from index %d)\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&empty);
    }
    return NULL;
}

int main()
{
    pthread_t prod_thread, cons_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
