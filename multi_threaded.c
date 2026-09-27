#include <stdio.h>
#include <pthread.h>

void *thread1_func(void *arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Thread 1: %d\n", i);
        sleep(1);
    }

    return NULL;
}

void *thread2_func(void *arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Thread 2: %d\n", i);
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have completed.\n");

    return 0;
}


