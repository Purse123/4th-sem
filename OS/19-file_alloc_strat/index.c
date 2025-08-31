#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 50
#define MAX_FILES  20

int disk[MAX_BLOCKS];

typedef struct {
  char name[20];
  int indexBlock;
  int blocks[10];
  int size;
} File;

File files[MAX_FILES];
int fileCount = 0;

int findFreeBlock() {
  for (int i = 0; i < MAX_BLOCKS; i++) {
    if (disk[i] == 0) {
      disk[i] = 1;
      return i;
    }
  }
  return -1;
}

void createFile(char *name, int size) {
  if (fileCount >= MAX_FILES) {
    printf("File limit reached!\n");
    return;
  }

  int indexBlock = findFreeBlock();
  if (indexBlock == -1) {
    printf("No free block available for index!\n");
    return;
  }

  int allocated[size];
  int count = 0;
  for (int i = 0; i < size; i++) {
    int b = findFreeBlock();
    if (b == -1) {
      printf("Not enough free blocks for file!\n");
      disk[indexBlock] = 0;
      for (int j = 0; j < count; j++) disk[allocated[j]] = 0;
      return;
    }
    allocated[count++] = b;
  }

  // Save file info
  strcpy(files[fileCount].name, name);
  files[fileCount].indexBlock = indexBlock;
  files[fileCount].size = size;
  for (int i = 0; i < size; i++)
    files[fileCount].blocks[i] = allocated[i];
  fileCount++;

  printf("File %s created. Index block: %d\n", name, indexBlock);
}

void displayFiles() {
  if (fileCount == 0) {
    printf("No files found\n");
    return;
  }

  for (int i = 0; i < fileCount; i++) {
    printf("File: %s\n", files[i].name);
    printf("Index Block: %d\n", files[i].indexBlock);
    
    printf("Data Blocks: ");
    for (int j = 0; j < files[i].size; j++)
      printf("%d ", files[i].blocks[j]);
    printf("\n");
  }
}

void deleteFile(char *name) {
  for (int i = 0; i < fileCount; i++) {
    if (strcmp(files[i].name, name) == 0) {
      disk[files[i].indexBlock] = 0;
      for (int j = 0; j < files[i].size; j++)
        disk[files[i].blocks[j]] = 0;
      
      for (int k = i; k < fileCount - 1; k++)
        files[k] = files[k + 1];
      fileCount--;
      
      printf("File %s deleted.\n", name);
      return;
    }
  }
  printf("File not found!\n");
}

int main() {
  int choice, size;
  char fname[20];

  while (1) {
    printf("\nIndexed File Allocation Menu\n");
    printf("1. Create File\n");
    printf("2. Display Files\n");
    printf("3. Delete File\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter file name: ");
      scanf("%s", fname);
      printf("Enter file size (blocks): ");
      scanf("%d", &size);
      createFile(fname, size);
      break;
    case 2:
      displayFiles();
      break;
    case 3:
      printf("Enter file name to delete: ");
      scanf("%s", fname);
      deleteFile(fname);
      break;
    case 4:
      printf("Exiting...\n");
      return 0;
    default:
      printf("Invalid choice!\n");
    }
  }
  return 0;
}
