#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TRUE  1
#define FALSE 0
typedef int8_t boolean;

typedef struct process {
  int pid;
  int arrivalTime, burstTime, remainingTime;
  int completionTime, tat, waitTime;
  boolean isCompleted;
} process;

void inputProcesses(process *p, int n) {
  for (int i = 0; i < n; i++) {
    p[i].pid = i + 1;
    printf("Enter arrival and burst time for PID %d: ", p[i].pid);
    scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
    p[i].remainingTime = p[i].burstTime;
    p[i].isCompleted = FALSE;
  }
}

void printProcessTable(process *p, int n) {
  printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime,
	   p[i].completionTime, p[i].tat, p[i].waitTime);
  }
}

void scheduleRoundRobin(process *p, int n, int quantum) {
  int currentTime = 0, completed = 0;
  int *queue = malloc(n * sizeof(int));
  int front = 0, rear = 0;

  int *visited = calloc(n, sizeof(int));

  for (int i = 0; i < n; i++) {
    if (p[i].arrivalTime == 0) {
      queue[rear++] = i;
      visited[i] = 1;
    }
  }

  while (completed < n) {
    if (front == rear) {
      currentTime++;
      for (int i = 0; i < n; i++) {
	if (!visited[i] && p[i].arrivalTime <= currentTime) {
	  queue[rear++] = i;
	  visited[i] = 1;
	}
      }
      continue;
    }
    
    int idx = queue[front++ % n];
    
    if (p[idx].remainingTime > 0) {
      int execTime = (p[idx].remainingTime > quantum) ? quantum : p[idx].remainingTime;
      p[idx].remainingTime -= execTime;
      currentTime += execTime;

      for (int i = 0; i < n; i++) {
	if (!visited[i] && p[i].arrivalTime <= currentTime) {
	  queue[rear++ % n] = i;
	  visited[i] = 1;
	}
      }

      if (p[idx].remainingTime == 0) {
	p[idx].completionTime = currentTime;
	p[idx].tat = p[idx].completionTime - p[idx].arrivalTime;
	p[idx].waitTime = p[idx].tat - p[idx].burstTime;
	p[idx].isCompleted = TRUE;
	completed++;
      } else {
	queue[rear++ % n] = idx;
      }
    }
  }

  free(queue);
  free(visited);
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
  int n, quantum;
  printf("Enter number of processes: ");
  scanf("%d", &n);
  
  process *p = malloc(n * sizeof(process));
  
  inputProcesses(p, n);
  
  printf("Enter time quantum: ");
  scanf("%d", &quantum);

  scheduleRoundRobin(p, n, quantum);
  printProcessTable(p, n);
  calculateAverageTimes(p, n);
  
  free(p);
  fprintf(stdout, "Programmed by Pierce Neupane\n");
  return 0;
}
