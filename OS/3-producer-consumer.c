#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_BUFFER 5

int buffer[MAX_BUFFER];
int in = 0, out = 0;

/* typedef union { */
  /* char __size[__SIZEOF_SEM_T]; */
  /* long int __align; */
/* } sem_t; */
sem_t empty, full;
pthread_mutex_t mutex;		/* It is also union */

void* producer(void* arg) {
  int count;
  for (int i = 0; i < 10; i++) {
    count = i + 1;

    sem_wait(&empty);		/* lock semaphore */
    pthread_mutex_lock(&mutex);

    buffer[in] = count;
    printf("Produced: %d\n", count);
    in = (in + 1) % MAX_BUFFER;
    
    pthread_mutex_unlock(&mutex);
    // wait if buffer is full (empty == 0)
    sem_post(&full);
    sleep(1);
  }
  return NULL;
}

void* consumer(void* arg) {
  int item;
  for (int i = 0; i < 10; i++) {
    sem_wait(&full);		/* lock semaphore */
    pthread_mutex_lock(&mutex);

    item = buffer[out];
    printf("Consumed: %d\n", item);
    out = (out + 1) % MAX_BUFFER;
    
    pthread_mutex_unlock(&mutex);
    // wait if buffer is empty (full == 0)
    sem_post(&empty);
    sleep(2);
  }
  return NULL;
}

int main() {
  pthread_t p, c;

  // int pshared -> 0 semaphore is hared between threads of process, and locate at visible address
  // pshared != 0 semaphore is shared between process and should be locate in region of memory
  sem_init(&empty, 0, MAX_BUFFER);
  sem_init(&full, 0, 0);
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&p, NULL, producer, NULL);
  pthread_create(&c, NULL, consumer, NULL);
  pthread_join(p, NULL);
  pthread_join(c, NULL);

  sem_destroy(&empty);
  sem_destroy(&full);
  pthread_mutex_destroy(&mutex);
  return 0;
}
