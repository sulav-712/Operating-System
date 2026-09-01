#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread1(void *arg) {
    printf("Thread 1: Started\n");
    for (int i = 1; i <= 2; i++) {
        printf("Thread 1: Working on step %d\n", i);
        sleep(1);
    }
    printf("Thread 1: Task Completed\n");
    return NULL;
}

void *thread2(void *arg) {
    printf("Thread 2: Started\n");
    for (int i = 1; i <= 2; i++) {
        printf("Thread 1: Working on step %d\n", i);
        sleep(1);
    }
    printf("Thread 2: Task Completed\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;

    printf("Main Process: Started\n");

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main Process: All threads completed\n");
    printf("Main Process: Ended\n");

    return 0;
}

