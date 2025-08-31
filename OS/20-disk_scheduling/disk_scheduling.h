#ifndef DISK_SCHEDULING_H
#define DISK_SCHEDULING_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void fcfs(int requests[], int n, int head);
void scan(int requests[], int n, int head, int disk_size);
void look(int requests[], int n, int head);

#endif
