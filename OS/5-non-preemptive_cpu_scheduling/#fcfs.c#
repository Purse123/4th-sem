#include <stdio.h>
#include <stdlib.h>

typedef struct process {
  int pid;
  int arrivalTime, burstTime;
  int completionTime, tat, waitTime;
} process;

void sortFCFS (process *p, int n) {
  process temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if ((p + i)->arrivalTime > (p + j)->arrivalTime) {
	temp = *(p + i);
	*(p + i) = *(p + j);
	*(p + j) = temp;
      }
    }
  }
}

int main() {
  int n, currentTime = 0;
  fprintf(stdout, "Enter no of processes: ");
  scanf("%d", &n);

  process* p = (process*)malloc(n * sizeof(process));
  if (!p) {
    fprintf(stderr, "Buy more RAM its 2025!!!\n");
    return -1;
  }

  for (int i = 0; i < n; i++) {
    p[i].pid = i + 1;
    fprintf(stdout, "Enter arrival and burst time for pid %d: ", i + 1);
    scanf("%d%d", &p[i].arrivalTime, &p[i].burstTime);
  }

  sortFCFS(p, n);
  
  for (int i = 0; i < n; i++) {
    if (currentTime < p[i].arrivalTime)
      currentTime = p[i].arrivalTime;

    // calculations
    p[i].completionTime = currentTime + p[i].burstTime;
    p[i].tat = p[i].completionTime - p[i].arrivalTime;
    p[i].waitTime = p[i].tat - p[i].burstTime;
    currentTime = p[i].completionTime;
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
