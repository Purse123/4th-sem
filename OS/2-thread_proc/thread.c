#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

typedef int Err;
Err errno;

#define STACK_SIZE 1048576
#define handle_error_en(en, msg)		\
  do {						\
    errno = en;					\
    perror(msg);				\
    exit(EXIT_FAILURE);				\
  } while (0)

int count = 0;

// For race condition
pthread_mutex_t lock;

void* incrementer (void* arg) {
  char *msg = (char *)arg;
  for (int i = 0; i < 100; i++) {
    pthread_mutex_lock(&lock);
    count++;
    pthread_mutex_unlock(&lock);
  }
  
  fprintf(stdout, "Thread finished: %s\n", msg);
  return NULL;
}

int main() {
  pthread_t t1;
  Err s;
  
  s = pthread_mutex_init(&lock, NULL);
  if (s != 0)
    handle_error_en(s, "pthread_mutex_init error");

  /*
    union pthread_attr_t
    {
        char __size[__SIZEOF_PTHREAD_ATTR_T];
        long int __align;
    };
  */
  // Structure that holds attributes for creating a thread.
  // POSIX doesn't want to see __size array, it includes:
  // Detach state, stack size, stack address, scheduling policy and priority.
  pthread_attr_t attr;

  // Setting pthread_attr_t attribute
  // it is an union
  s = pthread_attr_init(&attr);
  if (s != 0)
    handle_error_en(s, "pthread_attr_init error");

  // unlike join it auto release resources
  s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  if (s != 0)
    handle_error_en(s, "pthread_attr_detached error");
  
  s = pthread_attr_setstacksize(&attr, STACK_SIZE);
  if (s != 0)
    handle_error_en(s, "pthread_attr_setstacksize error");

  s = pthread_create(&t1, &attr, incrementer, "thread 1");
  if (s != 0)
    handle_error_en(s, "pthread_create error");

  s = pthread_attr_destroy(&attr);
  if (s != 0)
    handle_error_en(s, "pthread_attr_destroy error");

  fprintf(stdout, "thread 1 is working...\n");
  sleep(2);
  
  
  pthread_mutex_lock(&lock);
  // printed by main thread
  fprintf(stdout, "Final counter: %d\n", count);
  pthread_mutex_unlock(&lock);

  pthread_mutex_destroy(&lock);
  fprintf(stdout, "Programmed by Pierce Neupane\n");

  return 0;
}
