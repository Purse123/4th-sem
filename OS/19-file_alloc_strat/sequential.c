#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BLOCKS 50
#define MAX_FILES  20

int disk[MAX_BLOCKS];

typedef struct {
  char name[20];
  int start;
  int size;
} File;

File files[MAX_FILES];
int fileCount = 0;

int findFreeBlock(void) {
  for (int i = 0; i < MAX_BLOCKS; i++) {
    if (disk[i] == -1) {
      return i;
    }
  }
  return -1;
}

int countFreeBlocks(void) {
  int cnt = 0;
  for (int i = 0; i < MAX_BLOCKS; i++)
    if (disk[i] == -1) cnt++;
  return cnt;
}

bool nameExists(const char *name) {
  for (int i = 0; i < fileCount; i++)
    if (strcmp(files[i].name, name) == 0) return true;
  return false;
}

void createFile(char *name, int size) {
  if (size <= 0) {
    printf("Invalid file size. Must be > 0.\n");
    return;
  }

  if (fileCount >= MAX_FILES) {
    printf("File limit reached!\n");
    return;
  }

  if (nameExists(name)) {
    printf("File with name '%s' already exists.\n", name);
    return;
  }

  int freeBlocks = countFreeBlocks();
  if (freeBlocks < size) {
    printf("Not enough free blocks. Required: %d, Available: %d\n",
           size, freeBlocks);
    return;
  }

  int start = findFreeBlock();
  if (start == -1) {
    printf("No free block available!\n");
    return;
  }

  int prev = start;
  disk[start] = -2; 
  int count = 1;

  for (int i = 1; i < size; i++) {
    int b = findFreeBlock();
    if (b == -1) {  
      int temp = start;
      while (temp != -2) {
        int next = disk[temp];
        disk[temp] = -1;
        if (next == -2) break;
        temp = next;
      }
      printf("Unexpected allocation error (rollback performed).\n");
      return;
    }
    disk[prev] = b;
    disk[b] = -2;
    prev = b;
    count++;
  }

  strncpy(files[fileCount].name, name, sizeof(files[fileCount].name) - 1);
  files[fileCount].name[sizeof(files[fileCount].name) - 1] = '\0';
  files[fileCount].start = start;
  files[fileCount].size = count;
  fileCount++;

  printf("File %s created. Start block: %d (blocks used: %d)\n",
         name, start, count);
}

void displayFiles(void) {
  if (fileCount == 0) {
    printf("No files present.\n");
    return;
  }

  printf("\nFiles:\n");
  for (int i = 0; i < fileCount; i++) {
    printf("File: %s\n", files[i].name);
    printf(" Start Block: %d\n", files[i].start);
    printf(" Blocks: ");
    int temp = files[i].start;
    while (temp != -2) {
      printf("%d ", temp);
      int next = disk[temp];
      if (next == -2) break;
      temp = next;
    }
    printf("\n");
  }
}

void deleteFile(char *name) {
  for (int i = 0; i < fileCount; i++) {
    if (strcmp(files[i].name, name) == 0) {
      int temp = files[i].start;
      while (temp != -2) {
        int next = disk[temp];
        disk[temp] = -1;
        if (next == -2) break;
        temp = next;
      }

      for (int k = i; k < fileCount - 1; k++)
        files[k] = files[k + 1];
      fileCount--;

      printf("File %s deleted.\n", name);
      return;
    }
  }
  printf("File not found!\n");
}

int main(void) {
  int choice, size;
  char fname[20];

  for (int i = 0; i < MAX_BLOCKS; i++)
    disk[i] = -1;

  while (1) {
    printf("\nLinked File Allocation Menu\n");
    printf("1. Create File\n");
    printf("2. Display Files\n");
    printf("3. Delete File\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) {
      int c;
      while ((c = getchar()) != '\n' && c != EOF) {}
      printf("Invalid input. Try again.\n");
      continue;
    }

    switch (choice) {
    case 1:
      printf("Enter file name: ");
      scanf("%19s", fname);
      printf("Enter file size (blocks): ");
      if (scanf("%d", &size) != 1) {
        printf("Invalid size.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        break;
      }
      createFile(fname, size);
      break;
    case 2:
      displayFiles();
      break;
    case 3:
      printf("Enter file name to delete: ");
      scanf("%19s", fname);
      deleteFile(fname);
      break;
    case 4:
      printf("Exiting...\n");
      printf("Programmed by Pierce Neupane\n");
      return 0;
    default:
      printf("Invalid choice!\n");
    }
  }
}
