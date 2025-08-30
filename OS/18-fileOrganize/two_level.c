#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 50

struct File {
  char name[20];
  int size;
};

struct UserDirectory {
  char user[20];
  struct File files[MAX_FILES];
  int file_count;
};

struct RootDirectory {
  struct UserDirectory users[MAX_USERS];
  int user_count;
} root;

void create_user(char *username) {
  if (root.user_count >= MAX_USERS) {
    printf("User limit reached!\n");
    return;
  }
  for (int i = 0; i < root.user_count; i++) {
    if (strcmp(root.users[i].user, username) == 0) {
      printf("User already exists!\n");
      return;
    }
  }
  strcpy(root.users[root.user_count].user, username);
  root.users[root.user_count].file_count = 0;
  root.user_count++;
  printf("User %s created.\n", username);
}

void create_file(char *username, char *filename, int size) {
  for (int i = 0; i < root.user_count; i++) {
    if (strcmp(root.users[i].user, username) == 0) {
      if (root.users[i].file_count >= MAX_FILES) {
	printf("Directory full for user %s!\n", username);
	return;
      }
      for (int j = 0; j < root.users[i].file_count; j++) {
	if (strcmp(root.users[i].files[j].name, filename) == 0) {
	  printf("File already exists!\n");
	  return;
	}
      }
      strcpy(root.users[i].files[root.users[i].file_count].name, filename);
      root.users[i].files[root.users[i].file_count].size = size;
      root.users[i].file_count++;
      printf("File %s created under user %s.\n", filename, username);
      return;
    }
  }
  printf("User not found!\n");
}

void delete_file(char *username, char *filename) {
  for (int i = 0; i < root.user_count; i++) {
    if (strcmp(root.users[i].user, username) == 0) {
      for (int j = 0; j < root.users[i].file_count; j++) {
	if (strcmp(root.users[i].files[j].name, filename) == 0) {
	  for (int k = j; k < root.users[i].file_count - 1; k++) {
	    root.users[i].files[k] = root.users[i].files[k + 1];
	  }
	  root.users[i].file_count--;
	  printf("File %s deleted from user %s.\n", filename, username);
	  return;
	}
      }
      printf("File not found!\n");
      return;
        }
  }
  printf("User not found!\n");
}

void list_files(char *username) {
  for (int i = 0; i < root.user_count; i++) {
    if (strcmp(root.users[i].user, username) == 0) {
      if (root.users[i].file_count == 0) {
	printf("No files for user %s\n", username);
	return;
      }
      printf("Files of user %s:\n", username);
      for (int j = 0; j < root.users[i].file_count; j++) {
	printf("%d. %s (%d KB)\n", j + 1, root.users[i].files[j].name, root.users[i].files[j].size);
      }
      return;
    }
  }
  printf("User not found!\n");
}

int main() {
  int choice, size;
  char username[20], filename[20];
  
  while (1) {
    printf("Two Level Directory Menu\n");
    printf("1. Create User\n");
    printf("2. Create File\n");
    printf("3. Delete File\n");
    printf("4. List Files of User\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
    case 1:
      printf("Enter username: ");
      scanf("%s", username);
      create_user(username);
      break;
      
    case 2:
      printf("Enter username: ");
      scanf("%s", username);
      printf("Enter file name: ");
      scanf("%s", filename);
      printf("Enter file size: ");
      scanf("%d", &size);
      create_file(username, filename, size);
      break;
      
    case 3:
      printf("Enter username: ");
      scanf("%s", username);
      printf("Enter file name to delete: ");
      scanf("%s", filename);
      delete_file(username, filename);
      break;
      
    case 4:
      printf("Enter username: ");
      scanf("%s", username);
      list_files(username);
      break;
      
    case 5:
      printf("Exiting...\n");
      return 0;
      
    default:
      printf("Invalid choice!\n");
    }
  }
}
