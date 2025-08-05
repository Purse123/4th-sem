#include <stdio.h>

#define MAX_P 10
#define MAX_R 10

int main() {
  int n, m;
  int allocation[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R];
  int available[MAX_R], finish[MAX_P] = {0};
  int safeSequence[MAX_P];
  int count = 0;

  printf("Enter number of processes: ");
  scanf("%d", &n);
  printf("Enter number of resource types: ");
  scanf("%d", &m);

  printf("Enter Allocation Matrix:\n");
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &allocation[i][j]);

  printf("Enter Max Matrix:\n");
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &max[i][j]);
  
  printf("Enter Available Resources:\n");
  for (int i = 0; i < m; i++)
    scanf("%d", &available[i]);

  // Calculate Need Matrix
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      need[i][j] = max[i][j] - allocation[i][j];

  // Safety Algorithm
  while (count < n) {
    int found = 0;
    for (int i = 0; i < n; i++) {
      if (!finish[i]) {
	int j;
	for (j = 0; j < m; j++) {
	  if (need[i][j] > available[j])
	    break;
	}

	if (j == m) {
	  for (int k = 0; k < m; k++)
	    available[k] += allocation[i][k];
	  
	  safeSequence[count++] = i;
	  finish[i] = 1;
	  found = 1;
	}
      }
    }
    
    if (!found) {
      printf("\nSystem is in UNSAFE state! Deadlock may occur.\n");
      return 1;
    }
  }

  // Safe State
  printf("\nSystem is in SAFE state.\nSafe Sequence: ");
  for (int i = 0; i < n; i++) {
    printf("P%d", safeSequence[i]);
    if (i != n - 1) printf(" -> ");
  }
  printf("\n");
  
  return 0;
}
