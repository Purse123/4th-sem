#include <stdio.h>

#define MAX 100

void simulateMVT() {
  int memorySize, allocated = 0;
  int n, processSize;

  printf("\n MVT Memory Management \n");
  printf("Enter total memory available (in KB): ");
  scanf("%d", &memorySize);

  printf("Enter number of processes: ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    printf("Enter memory required for process %d (in KB): ", i + 1);
    scanf("%d", &processSize);

    if (processSize <= (memorySize - allocated)) {
      allocated += processSize;
      printf("Process %d allocated. Memory used: %d KB\n", i + 1, allocated);
    } else {
      printf("Not enough memory to allocate process %d. Remaining: %d KB\n", i + 1, memorySize - allocated);
    }
  }

  printf("Total memory allocated: %d KB\n", allocated);
  printf("Total external fragmentation: %d KB\n", memorySize - allocated);
}

void simulateMFT() {
  int memorySize, blockSize, n, allocated = 0;
  int numBlocks, processSize, internalFrag = 0;
  
  printf("\nMFT Memory Management\n");
  printf("Enter total memory available (in KB): ");
  scanf("%d", &memorySize);

  printf("Enter block (partition) size (in KB): ");
  scanf("%d", &blockSize);

  numBlocks = memorySize / blockSize;

  printf("Total blocks available: %d\n", numBlocks);

  printf("Enter number of processes: ");
  scanf("%d", &n);

  if (n > numBlocks) {
    printf("Not enough blocks to allocate all processes.\n");
    n = numBlocks;
    printf("Only first %d processes will be considered.\n", n);
  }

  for (int i = 0; i < n; i++) {
    printf("Enter memory required for process %d (in KB): ", i + 1);
    scanf("%d", &processSize);
    
    if (processSize <= blockSize) {
      allocated++;
      internalFrag += blockSize - processSize;
      printf("Process %d allocated to block %d\n", i + 1, allocated);
    } else {
      printf("Process %d too big for block (%d KB > %d KB)\n", i + 1, processSize, blockSize);
    }
  }

  printf("Total processes allocated: %d\n", allocated);
  printf("Total internal fragmentation: %d KB\n", internalFrag);
  printf("Total external fragmentation: %d KB\n", memorySize - (numBlocks * blockSize));
}

int main() {
  int choice;

  while (1) {
    printf("\n====== MEMORY MANAGEMENT SIMULATOR ======\n");
    printf("1. Simulate MVT (Variable Partitions)\n");
    printf("2. Simulate MFT (Fixed Partitions)\n");
    printf("3. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      simulateMVT();
      break;
    case 2:
      simulateMFT();
      break;
    case 3:
      return 0;
    default:
      printf("Invalid choice. Try again.\n");
    }
  }
}
