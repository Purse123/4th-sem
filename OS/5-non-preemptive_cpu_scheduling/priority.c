#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TRUE  1
#define FALSE 0

typedef uint8_t boolean;
typedef struct process {
  int pid;
  int arrivalTime, burstTime, priority;
  int completionTime, tat, waitTime;
  boolean isCompleted;
} process;

int main() {
  int n, completed = 0, currentTime = 0;
  fprintf(stdout, "Enter number of processes: ");
  scanf("%d", &n);

  process* p = (process*)malloc(n * sizeof(process));

  for (int i = 0; i < n; i++) {
    p[i].pid = i + 1;
    fprintf(stdout, "Enter arrival time, burst time, and priority for PID %d: ", p[i].pid);
    scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
    p[i].isCompleted = FALSE;
  }

  while (completed < n) {
    int idx = -1;
    int highestPriority = 1e9;

    for (int i = 0; i < n; i++) {
      if (!p[i].isCompleted && p[i].arrivalTime <= currentTime) {
	if (p[i].priority < highestPriority) {
	  highestPriority = p[i].priority;
	  idx = i;
	} else if (p[i].priority == highestPriority) {
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
      currentTime++;
    }
  }

  printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime,
	   p[i].priority, p[i].completionTime, p[i].tat, p[i].waitTime);
  }
  
  free(p);
  return 0;
}
