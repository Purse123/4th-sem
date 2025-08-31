#include "disk_scheduling.h"

void fcfs(int requests[], int n, int head) {
  int total_movement = 0;
  printf("\nFCFS Disk Scheduling\n");
  printf("Head movement order: %d", head);

  for (int i = 0; i < n; i++) {
    total_movement += abs(requests[i] - head);
    head = requests[i];
    printf(" -> %d", head);
  }

  printf("\nTotal Head Movement: %d\n", total_movement);
}

// SCAN Disk Scheduling (Elevator)
void scan(int requests[], int n, int head, int disk_size) {
  int total_movement = 0;
  int temp, pos;

  // Sort requests
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (requests[j] > requests[j + 1]) {
        temp = requests[j];
        requests[j] = requests[j + 1];
        requests[j + 1] = temp;
      }
    }
  }

  // Find position of head
  for (pos = 0; pos < n; pos++) {
    if (requests[pos] > head)
      break;
  }

  printf("\nSCAN Disk Scheduling\n");
  printf("Head movement order: %d", head);

  // Move right
  for (int i = pos; i < n; i++) {
    total_movement += abs(requests[i] - head);
    head = requests[i];
    printf(" -> %d", head);
  }

  // Go to end of disk
  total_movement += abs((disk_size - 1) - head);
  head = disk_size - 1;

  // Move left
  for (int i = pos - 1; i >= 0; i--) {
    total_movement += abs(requests[i] - head);
    head = requests[i];
    printf(" -> %d", head);
  }

  printf("\nTotal Head Movement: %d\n", total_movement);
}

// LOOK Disk Scheduling
void look(int requests[], int n, int head) {
  int total_movement = 0;
  int temp, pos;

  // Sort requests
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (requests[j] > requests[j + 1]) {
        temp = requests[j];
        requests[j] = requests[j + 1];
        requests[j + 1] = temp;
      }
    }
  }

  // Find position of head
  for (pos = 0; pos < n; pos++) {
    if (requests[pos] > head)
      break;
  }

  printf("\nLOOK Disk Scheduling\n");
  printf("Head movement order: %d", head);

  // Move right
  for (int i = pos; i < n; i++) {
    total_movement += abs(requests[i] - head);
    head = requests[i];
    printf(" -> %d", head);
  }

  // Move left
  for (int i = pos - 1; i >= 0; i--) {
    total_movement += abs(requests[i] - head);
    head = requests[i];
    printf(" -> %d", head);
  }

  printf("\nTotal Head Movement: %d\n", total_movement);
}
