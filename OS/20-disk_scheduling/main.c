#include "disk_scheduling.h"

int main() {
  int n, head, disk_size, choice;
  int requests[MAX];

  printf("Enter number of requests: ");
  scanf("%d", &n);

  printf("Enter the request sequence: ");
  for (int i = 0; i < n; i++) {
    scanf("%d", &requests[i]);
  }

  printf("Enter initial head position: ");
  scanf("%d", &head);

  printf("Enter total disk size (for SCAN): ");
  scanf("%d", &disk_size);

  while (1) {
    printf("\nDisk Scheduling Menu\n");
    printf("1. FCFS\n");
    printf("2. SCAN\n");
    printf("3. LOOK\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        fcfs(requests, n, head);
        break;
      case 2:
        scan(requests, n, head, disk_size);
        break;
      case 3:
        look(requests, n, head);
        break;
      case 4:
        printf("Exiting...\n");
        return 0;
      default:
        printf("Invalid choice!\n");
    }
  }
}
