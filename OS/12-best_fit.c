#include <stdio.h>

#define MAX_BLOCKS 20
#define MAX_PROCS 20

void bestFit(int blockSize[], int numBlocks, int processSize[], int numProcesses) {
  int allocation[MAX_PROCS];
  
  for (int i = 0; i < numProcesses; i++) allocation[i] = -1;

  for (int i = 0; i < numProcesses; i++) {
    int bestIdx = -1;
    for (int j = 0; j < numBlocks; j++) {
      if (blockSize[j] >= processSize[i]) {
	if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
	  bestIdx = j;
	}
      }
    }
    
    if (bestIdx != -1) {
      allocation[i] = bestIdx;
      blockSize[bestIdx] -= processSize[i];
    }
  }
  
  // Print results
  printf("\nProcess No.\tProcess Size\tBlock No.\n");
  for (int i = 0; i < numProcesses; i++) {
    printf("%d\t\t%d\t\t", i + 1, processSize[i]);
    if (allocation[i] != -1)
      printf("%d\n", allocation[i] + 1);
    else
      printf("Not Allocated\n");
  }
}

int main() {
  int blockSize[MAX_BLOCKS], processSize[MAX_PROCS];
  int numBlocks, numProcesses;
  
  // Input memory blocks
  printf("Enter number of memory blocks: ");
  scanf("%d", &numBlocks);
  
  printf("Enter size of each block:\n");
  for (int i = 0; i < numBlocks; i++) {
    printf("Block %d size: ", i + 1);
    scanf("%d", &blockSize[i]);
  }
  
  // Input processes
  printf("\nEnter number of processes: ");
  scanf("%d", &numProcesses);
  
  printf("Enter size of each process:\n");
  for (int i = 0; i < numProcesses; i++) {
    printf("Process %d size: ", i + 1);
    scanf("%d", &processSize[i]);
  }
  
  // Call Best-Fit function
  bestFit(blockSize, numBlocks, processSize, numProcesses);
  
  return 0;
}
