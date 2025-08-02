#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TRUE  1
#define FALSE 0

typedef uint8_t boolean;
typedef struct process {
  int pid;
  int arrivalTime, burstTime;
  int completionTime, tat, waitTime;
  boolean isCompleted;
} process;

int main() {
  int n, completed = 0, currentTime = 0;
  fprintf(stdout, "Enter no of processes: ");
  scanf("%d", &n);

  process* p = (process*)malloc(n * sizeof(process));
  if (!p) {
    fprintf(stderr, "Buy more RAM its 2025!!!\n");
    return -1;
  }

  for (int i = 0; i < n; ++i) {
    p[i].pid = i + 1;
    fprintf(stdout, "Enter arrival and burst time for pid %d: ", i + 1);
    scanf("%d%d", &p[i].arrivalTime, &p[i].burstTime);
    p[i].isCompleted = FALSE;
  }

  while (completed < n) {
    int idx = -1, minBT = 1e9;

    // sjf
    for (int i = 0; i < n; i++) {
      if (!p[i].isCompleted && p[i].arrivalTime <= currentTime) {
	if (p[i].burstTime < minBT) {
	  minBT = p[i].burstTime;
	  idx = i;
	} else if (p[i].burstTime == minBT) {
	  if (p[i].arrivalTime < p[idx].arrivalTime) {
	    idx = i;
	  }
	}
      }
    }
    
    if (idx != -1) {
      p[idx].completionTime = currentTime + p[idx].burstTime;
      p[idx].tat = p[idx].completionTime - p[idx].arrivalTime;
      p[idx].waitTime = p[idx].tat - p[idx].burstTime;
      currentTime = p[idx].completionTime;
      p[idx].isCompleted = TRUE;
      completed++;
    } else {
      currentTime++;		/* no process ready */
    }
  }
  
  fprintf(stdout, "PID\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime,
	   p[i].completionTime, p[i].tat, p[i].waitTime);
  }

  free(p);
  fprintf(stdout, "Programmed by Pierce Neupane\n");
  return 0;
}
