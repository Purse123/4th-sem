#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int n, m; // n = processes, m = resources
int Allocation[MAX_P][MAX_R], Max[MAX_P][MAX_R], Need[MAX_P][MAX_R], Available[MAX_R];

// Utility to calculate Need matrix
void calculateNeed() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      Need[i][j] = Max[i][j] - Allocation[i][j];
}

// Safety algorithm to check if system is in a safe state
bool isSafe() {
  int Work[MAX_R];
  bool Finish[MAX_P] = {false};
  
  for (int i = 0; i < m; i++)
    Work[i] = Available[i];
  
  int count = 0;
  while (count < n) {
    bool found = false;
    for (int i = 0; i < n; i++) {
      if (!Finish[i]) {
	bool canFinish = true;
	for (int j = 0; j < m; j++) {
	  if (Need[i][j] > Work[j]) {
	    canFinish = false;
	    break;
	  }
	}
	
	if (canFinish) {
	  for (int j = 0; j < m; j++)
	    Work[j] += Allocation[i][j];
	  Finish[i] = true;
	  count++;
	  found = true;
	}
      }
    }
    if (!found)
      return false;
  }
  return true;
}

// Attempt to request resources for a process
bool requestResources(int pid, int request[]) {
  for (int i = 0; i < m; i++) {
    if (request[i] > Need[pid][i]) {
      printf("Error: Request exceeds process max need.\n");
      return false;
    }
    if (request[i] > Available[i]) {
      printf("Process must wait: resources not available.\n");
      return false;
    }
  }
  
  // Try allocating temporarily
  for (int i = 0; i < m; i++) {
    Available[i] -= request[i];
    Allocation[pid][i] += request[i];
    Need[pid][i] -= request[i];
  }
  
  if (isSafe()) {
    printf("Request granted. System remains in safe state.\n");
    return true;
  } else {
    // Rollback
    for (int i = 0; i < m; i++) {
      Available[i] += request[i];
      Allocation[pid][i] -= request[i];
      Need[pid][i] += request[i];
    }
    printf("Request denied. System would enter unsafe state.\n");
    return false;
  }
}

// Print system state
void printState() {
  printf("\nProcess\tAllocation\tMax\t\tNeed\n");
  for (int i = 0; i < n; i++) {
    printf("P%d\t", i);
    for (int j = 0; j < m; j++)
      printf("%d ", Allocation[i][j]);
    printf("\t");
    
    for (int j = 0; j < m; j++)
      printf("%d ", Max[i][j]);
    printf("\t");
    
    for (int j = 0; j < m; j++)
      printf("%d ", Need[i][j]);
    printf("\n");
  }
  
  printf("Available: ");
  for (int i = 0; i < m; i++)
    printf("%d ", Available[i]);
  printf("\n");
}

int main() {
  printf("Enter number of processes: ");
  scanf("%d", &n);
  printf("Enter number of resource types: ");
  scanf("%d", &m);
  
  printf("Enter Allocation Matrix:\n");
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &Allocation[i][j]);
  
  printf("Enter Max Matrix:\n");
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &Max[i][j]);
  
  printf("Enter Available Resources:\n");
  for (int i = 0; i < m; i++)
    scanf("%d", &Available[i]);
  
  calculateNeed();
  
  int choice;
  while (1) {
    printState();
    printf("\nMenu:\n");
    printf("1. Make a resource request\n");
    printf("2. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    if (choice == 2)
      break;
    else if (choice == 1) {
      int pid;
      int request[MAX_R];
      printf("Enter process number (0 to %d): ", n - 1);
      scanf("%d", &pid);
      
      printf("Enter request for %d resources:\n", m);
      for (int i = 0; i < m; i++)
	scanf("%d", &request[i]);
      
      requestResources(pid, request);
    } else {
      printf("Invalid choice!\n");
    }
  }
  
  return 0;
}
