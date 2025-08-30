#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILD 20

typedef struct Node {
  char name[20];
  int isFile;                     
  struct Node *child[MAX_CHILD];
  int childCount;
  struct Node *parent; // pointer to parent for "cd .."
} Node;

Node* createNode(char *name, int isFile, Node *parent) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->name, name);
  newNode->isFile = isFile;
  newNode->childCount = 0;
  newNode->parent = parent;
  return newNode;
}

void addChild(Node *parent, char *name, int isFile) {
  if (parent->isFile) {
    printf("Cannot add inside a file.\n");
    return;
  }
  if (parent->childCount >= MAX_CHILD) {
    printf("Directory full.\n");
    return;
  }
  parent->child[parent->childCount++] = createNode(name, isFile, parent);
  printf("%s created under %s\n", name, parent->name);
}

void display(Node *root, int depth) {
  for (int i = 0; i < depth; i++) printf("  "); // 2 spaces per level
  printf("%s%s\n", root->name, root->isFile ? "" : "/");
  for (int i = 0; i < root->childCount; i++) {
    display(root->child[i], depth + 1);
  }
}

Node* changeDir(Node *curr, char *dirname) {
  if (strcmp(dirname, "..") == 0) {
    if (curr->parent != NULL) return curr->parent;
    printf("Already at root directory.\n");
    return curr;
  }
  for (int i = 0; i < curr->childCount; i++) {
    if (!curr->child[i]->isFile && strcmp(curr->child[i]->name, dirname) == 0) {
      return curr->child[i];
    }
  }
  printf("Directory not found.\n");
  return curr;
}

void printPath(Node *curr) {
  if (curr->parent != NULL) {
    printPath(curr->parent);
    printf("/%s", curr->name);
  } else {
    printf("%s", curr->name);  // root
  }
}

int main() {
  Node *root = createNode("root", 0, NULL);
  Node *curr = root;  // current directory
  int choice;
  char name[20];

  while (1) {
    printf("\n--- Hierarchical File System ---\n");
    printf("Current Dir: ");
    printPath(curr);
    printf("\n");
    printf("1. Create Directory\n");
    printf("2. Create File\n");
    printf("3. Change Directory (cd)\n");
    printf("4. Display Full Structure\n");
    printf("5. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        printf("Enter directory name: ");
        scanf("%s", name);
        addChild(curr, name, 0);
        break;

      case 2:
        printf("Enter file name: ");
        scanf("%s", name);
        addChild(curr, name, 1);
        break;

      case 3:
        printf("Enter directory name (.. for parent): ");
        scanf("%s", name);
        curr = changeDir(curr, name);
        break;

      case 4:
        printf("\nFile System Structure:\n");
        display(root, 0);
        break;

      case 5:
        printf("Exiting...\n");
        return 0;

      default:
        printf("Invalid choice.\n");
    }
  }
}
