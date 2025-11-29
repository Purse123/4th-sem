#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef int Err;
Err errno;

#define STACK_SIZE 1048576
#define handle_error_en(en, msg)        \
  do {                                  \
    errno = en;                         \
    perror(msg);                        \
    exit(EXIT_FAILURE);                 \
  } while (0)

int count = 0;

// Thread function
void* incrementer(void* arg) {
  char *msg = (char *)arg;
  for (int i = 0; i < 100; i++) {
    count++;   // no mutex, race condition possible
  }
  fprintf(stdout, "Thread finished: %s\n", msg);
  return NULL;
}

int main() {
  pthread_t t1;
  Err s;

  // Thread attributes
  pthread_attr_t attr;
  s = pthread_attr_init(&attr);
  if (s != 0)
    handle_error_en(s, "pthread_attr_init error");

  s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  if (s != 0)
    handle_error_en(s, "pthread_attr_setdetachstate error");

  s = pthread_attr_setstacksize(&attr, STACK_SIZE);
  if (s != 0)
    handle_error_en(s, "pthread_attr_setstacksize error");

  // Create thread
  s = pthread_create(&t1, &attr, incrementer, "thread 1");
  if (s != 0)
    handle_error_en(s, "pthread_create error");

  pthread_attr_destroy(&attr);

  // Wait for thread to finish
  pthread_join(t1, NULL);

  // Print counter from main thread
  fprintf(stdout, "Final counter: %d\n", count);

  // -------- PROCESS DEMO --------
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork failed");
    exit(1);
  }

  if (pid == 0) {
    // Child process
    printf("Child process: PID=%d, PPID=%d\n", getpid(), getppid());
    for (int i = 1; i <= 3; i++) {
      printf("Child working... step %d\n", i);
      sleep(1);
    }
    printf("Child exiting.\n");
    exit(0);
  } else {
    // Parent process
    printf("Parent process: PID=%d, spawned child PID=%d\n", getpid(), pid);
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      printf("Parent: child exited with code %d\n", WEXITSTATUS(status));
    }
    printf("Parent exiting.\n");
  }

  fprintf(stdout, "Programmed by Pierce Neupane\n");
  return 0;
}
