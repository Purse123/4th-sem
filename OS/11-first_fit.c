#include <stdio.h>
#include <stdint.h>

#define MAX_BLOCKS 20
#define MAX_PROCS  20

void ffa(int numb, int nump, int* block, int* proc, int* alloc) {
  for (int i = 0; i < nump; i++) {
    for (int j = 0; j < numb; j++) {
      if (block[j] >= proc[i]) {
	alloc[i] = j;
	block[j] -= proc[i];
	break;
      }
    }
  }
}

int main() {
  int block[MAX_BLOCKS], proc[MAX_PROCS], alloc[MAX_PROCS];
  int numBlocks, numProcs;

  printf("Enter number of memory blocks: ");
  scanf("%d", &numBlocks);

  printf("Enter size of blocks:\n");
  for (int i = 0; i < numBlocks; i++) {
    printf("Block %d size: ", i + 1);
    scanf("%d", &block[i]);
  }

  printf("Enter size of process: ");
  scanf("%d", &numProcs);
  for (int i = 0; i < numProcs; i++) {
    printf("Process %d size: ", i + 1);
    scanf("%d", &proc[i]);
    alloc[i] = -1;
  }

  ffa(numBlocks, numProcs, block, proc, alloc);

  printf("\nProcess No.\tProcess Size\tBlock No.\n");
  for (int i = 0; i < numProcs; i++) {
    printf("%d\t\t%d\t\t", i + 1, proc[i]);
    if (alloc[i] != -1)
      printf("%d\n", alloc[i] + 1);
    else
      printf("Not Allocated\n");
  }

  fprintf(stdout, "Programmed by Pierce Neupane\n");
  return 0;
}
