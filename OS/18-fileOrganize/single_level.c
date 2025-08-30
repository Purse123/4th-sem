#include <stdio.h>
#include <string.h>

#define MAX_FILE 50

typedef struct File {
  char name[20];
  int size;
}File;

typedef struct Dir {
  File fp[MAX_FILE];
  int fileCount;
}Dir;

Dir d;

void create_file(char *name, int size){
  if (d.fileCount >= MAX_FILE) {
    fprintf(stderr, "Directory is full\n");
    return;
  }
  for (int i = 0; i < d.fileCount; i++) {
    if (strcmp(d.fp[i].name, name) == 0) {
      fprintf(stderr, "File already exits\n");
      return;
    }
  }

  strcpy(d.fp[d.fileCount].name, name);
  d.fp[d.fileCount++].size = size;
  fprintf(stdout, "%s created\n", name);
}

void delete_file(char* name){
  for (int i = 0; i < d.fileCount; i++) {
    if (strcmp(d.fp[i].name, name) == 0) {
      for (int j = i; j < d.fileCount - 1; j++) 
	d.fp[j] = d.fp[j + 1];
      d.fileCount--;
      printf("%s deleted\n", name);
      return;
    }
  }
  printf("%s not found\n", name);
}

void list_file(){
  if (d.fileCount == 0) {
    fprintf(stdout, "Directory is empty\n");
    return;
  }

  printf("Files:\n");
  for (int i = 0; i < d.fileCount; i++)
    printf("%d. %s (%d KB)\n", i + 1, d.fp[i].name, d.fp[i].size);
}

int main() {
  int choice = 0, size;
  char name[20];

  printf("Single Level Directory Menu\n");
  printf("1. Create File\n");
  printf("2. Delete File\n");
  printf("3. List Files\n");
  printf("4. Exit\n");

  while (choice != 4) {
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter file name: ");
      scanf("%s", name);
      printf("Enter file size: ");
      scanf("%d", &size);
      create_file(name, size);
      break;
    case 2:
      printf("Enter file name to delete: ");
      scanf("%s", name);
      delete_file(name);
      break;
    case 3:
      list_file();
      break;
    case 4:
      printf("Exiting...\n");
      break;
    default:
      fprintf(stderr, "Invalid choice\n");
    }
  }
  return 0;
}
