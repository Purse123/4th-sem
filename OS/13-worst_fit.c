#include <stdio.h>

#define MAX_BLOCKS 20
#define MAX_PROCS  20

void worstFit(int blockSize[], int numBlocks, int processSize[], int numProcesses) {
  int alloc[MAX_PROCS];

  for (int i = 0; i < numProcesses; i++)
    alloc[i] = -1;

  for (int i = 0; i < numProcesses; i++) {
    int worstIdx = -1;
    for (int j = 0; j < numBlocks; j++)
      if (blockSize[j] >= processSize[i])
	if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) 
	  worstIdx = j;

    if (worstIdx != -1) {
      alloc[i] = worstIdx;
      blockSize[worstIdx] -= processSize[i];
    }
  }

  printf("\nProcess No.\tProcess Size\tBlock No.\n");
  for (int i = 0; i < numProcesses; i++) {
    printf("%d\t\t%d\t\t", i + 1, processSize[i]);
    if (alloc[i] != -1)
      printf("%d\n", alloc[i] + 1);
    else
      printf("Not Allocated\n");
  }
}

int main() {
  int blockSize[MAX_BLOCKS], processSize[MAX_PROCS];
  int numBlocks, numProcesses;

  printf("Enter number of memory blocks: ");
  scanf("%d", &numBlocks);
  printf("Enter size of each block:\n");
  for (int i = 0; i < numBlocks; i++) {
    printf("Block %d size: ", i + 1);
    scanf("%d", &blockSize[i]);
  }

  printf("\nEnter number of processes: ");
  scanf("%d", &numProcesses);
  printf("Enter size of each process:\n");
  for (int i = 0; i < numProcesses; i++) {
    printf("Process %d size: ", i + 1);
    scanf("%d", &processSize[i]);
  }

  worstFit(blockSize, numBlocks, processSize, numProcesses);

  fprintf(stdout, "Programmed by Pierce Neupane\n");
  return 0;
}
