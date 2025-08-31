#include <stdio.h>
#include <string.h>

// block = total number of blocks on the disk
#define MAX_BLOCKS 50
#define MAX_FILES  20

typedef struct {
  char name[20];
  int start, length;
} File;

int disk[MAX_BLOCKS];
File files[MAX_FILES];
int fileCount = 0;

int allocate(int size) {
  // i use (MAX_BLOCKS - size) method                        -> Sequential 
  // rather than chunking, chunk = MAX_BLOCKS / size       -> Partitioned
  // chunking has memory leaks and is used rarely
  for (int i = 0; i <= MAX_BLOCKS - size; i++) {
    int freeCount = 0;

    for (int j = i; j <= i + size; j++) {
      if (disk[j] == 0) freeCount++;
      else break;
    }
    
    if (freeCount == size) return i;
  }
  return -1;
}

void createFile(char* name, int size) {
  if (fileCount >= MAX_FILES) {
    printf("File table full\n");
    return;
  }

  int start = allocate(size);
  if (start == -1) {
    printf("Contiguous Space not enough\n");
    return;
  }

  for (int i = start; i < start + size; i++)
    disk[i] = 1;

  strcpy(files[fileCount].name, name);
  files[fileCount].start = start;
  files[fileCount].length = size;
  fileCount++;
  printf("%s created from block %d to %d\n", name, start, start + size - 1);
}

void deleteFile(char* name) {
  for (int i = 0; i < fileCount; i++) {
    if (strcmp(files[i].name, name) == 0) {
      for (int j = files[i].start; j < files[i].start + files[i].length; j++)
	disk[j] = 0;

      printf("%s is deleted\n", name);
      
      for (int k = i; k < fileCount - 1; k++)
	files[k] = files[k + 1];
      fileCount--;
      return;
    }
  }

  printf("File not found\n");
}

void displayFiles() {
  if (fileCount == 0) {
    printf("No files found\n");
    return;
  }

  printf("File\tStart\tLength\n");
  for (int i = 0; i < fileCount; i++) 
    printf("%s\t%d\t%d\n", files[i].name, files[i].start, files[i].length);
}

void displayDisk() {
  printf("\nDisk Blocks:\n");
  for (int i = 0; i < MAX_BLOCKS; i++)
    printf("%d", disk[i]);
  printf("\n");
}

int main() {
  int choice, size;
  char name[20];

  while (1) {
    printf("Sequential File Allocation\n");
    printf("1. Create File\n");
    printf("2. Delete File\n");
    printf("3. Display File Table\n");
    printf("4. Display Disk\n");
    printf("5. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter file name: ");
      scanf("%s", name);
      printf("Enter file size (blocks): ");
      scanf("%d", &size);
      createFile(name, size);
      break;
    case 2:
      printf("Enter file name to delete: ");
      scanf("%s", name);
      deleteFile(name);
      break;
    case 3:
      displayFiles();
      break;
    case 4:
      displayDisk();
      break;
    case 5:
      printf("Exiting...\n");
      return 0;
    default:
      printf("Invalid choice.\n");
    }
  }
}
