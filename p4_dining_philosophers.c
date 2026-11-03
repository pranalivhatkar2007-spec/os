
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t room, fork[5];

void *eat(void *arg)
{
    int i = *(int *)arg;

    sem_wait(&room);
    sem_wait(&fork[i]);
    sem_wait(&fork[(i+1)%5]);

    printf("Philosopher %d is eating\n", i+1);

    sem_post(&fork[i]);
    sem_post(&fork[(i+1)%5]);
    sem_post(&room);

    return NULL;
}

int main()
{
    pthread_t t[5];
    int i, id[5];

    sem_init(&room, 0, 4);

    for(i=0; i<5; i++)
        sem_init(&fork[i], 0, 1);

    for(i=0; i<5; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, eat, &id[i]);
    }

    for(i=0; i<5; i++)
        pthread_join(t[i], NULL);

    return 0;
}

op
gcc p4_dining_philosophers.c -o p4 -pthread
./p4