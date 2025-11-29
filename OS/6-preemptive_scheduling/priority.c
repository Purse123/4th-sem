#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TRUE  1
#define FALSE 0
typedef int8_t boolean;

typedef struct process {
  int pid;
  int arrivalTime, burstTime, priority, remainingTime;
  int completionTime, tat, waitTime;
  boolean isCompleted;
} process;

void inputProcesses(process *p, int n) {
  for (int i = 0; i < n; i++) {
    p[i].pid = i + 1;
    printf("Enter arrival time, burst time, and priority for PID %d: ", p[i].pid);
    scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
    p[i].remainingTime = p[i].burstTime;
    p[i].isCompleted = FALSE;
  }
}

void printProcessTable(process *p, int n) {
  printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime,
	   p[i].priority, p[i].completionTime, p[i].tat, p[i].waitTime);
  }
}

void schedulePreemptivePriority(process *p, int n) {
  int currentTime = 0, completed = 0;
  
  while (completed < n) {
    int idx = -1;
    // max int: (2 ** (4 * 8 - 1) - 1)
    //          ~(1 << (4 * 8 - 1)
    int minPriority = 2147483647;
    
    for (int i = 0; i < n; i++) {
      if (p[i].arrivalTime <= currentTime && !p[i].isCompleted && p[i].remainingTime > 0) {
	if (p[i].priority < minPriority) {
	  minPriority = p[i].priority;
	  idx = i;
	} else if (p[i].priority == minPriority) {
	  if (p[i].arrivalTime < p[idx].arrivalTime) {
	    idx = i;
	  }
	}
      }
    }
    
    if (idx != -1) {
      p[idx].remainingTime--;
      currentTime++;
      
      if (p[idx].remainingTime == 0) {
	p[idx].completionTime = currentTime;
	p[idx].tat = p[idx].completionTime - p[idx].arrivalTime;
	p[idx].waitTime = p[idx].tat - p[idx].burstTime;
	p[idx].isCompleted = TRUE;
	completed++;
      }
    } else {
      currentTime++;
    }
  }
}

void calculateAverageTimes(process *p, int n) {
  float totalTAT = 0, totalWT = 0;
  for (int i = 0; i < n; i++) {
    totalTAT += p[i].tat;
    totalWT += p[i].waitTime;
  }
  printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
  printf("Average Waiting Time: %.2f\n", totalWT / n);
}

int main() {
  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  process *p = malloc(n * sizeof(process));
  if (!p) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  inputProcesses(p, n);
  schedulePreemptivePriority(p, n);
  printProcessTable(p, n);
  calculateAverageTimes(p, n);

  fprintf(stdout, "Programmed by Pierce Neupane\n");
  free(p);
  return 0;
}
