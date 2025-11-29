// there are 5 philosophers sitting around circular table.
// each philosophers needs two forks (one on left and one on right) to eat.
// forks are shared between neighboring philosophers.
// philosophers alternate between thinking and eating.
// Avoid: - everyone hold fork and wait forever,
//        - some philosophers never get chance to eat.

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 5
#define TRUE 1
#define FALSE 0
#define EAT_LIMIT 2

pthread_mutex_t forks[NUM];
pthread_t philosophers[NUM];

void think(int id) {
  printf("philosopher %d is thinking.\n", id);
  sleep(2);
}

void eat(int id) {
  printf("philosopher %d is eating.\n", id);
  sleep(1);
}

void* routine(void* arg) {
  int id = *(int *)arg;
  int left = id;
  int right = (id + 1) % NUM;

  for (int i = 0; i < EAT_LIMIT; i++) {
    think(id);

    if (id % 2 == 0) {
      pthread_mutex_lock(&forks[left]);
      pthread_mutex_lock(&forks[right]);
    } else {
      pthread_mutex_lock(&forks[right]);
      pthread_mutex_lock(&forks[left]);
    }
    eat(id);

    pthread_mutex_unlock(&forks[left]);
    pthread_mutex_unlock(&forks[right]);
  }
  printf("Philosopher %d has finished eating.\n", id);
  return NULL;
}

int main() {
  int i;
  int ids[NUM];

  for (i = 0; i < NUM; i++)
    pthread_mutex_init (&forks[i], NULL);

  for (i = 0; i < NUM; i++) {
    ids[i] = i;
    pthread_create (&philosophers[i], NULL, routine, &ids[i]);
  }

  for (i = 0; i < NUM; i++)
    pthread_join (philosophers[i], NULL);

  for (i = 0; i < NUM; i++)
    pthread_mutex_destroy (&forks[i]);
  
  fprintf(stdout, "Programmed by Pierce Neupane\n");  
  return 0;
}
