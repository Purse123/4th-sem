#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define TRUE  1
#define FALSE 0
#define STACK_MAX 1024

typedef int8_t boolean;

typedef struct {
  char data[STACK_MAX];
  int top;
} Stack;

void stack_init(Stack *st) {
  st->top = -1;
}

boolean stack_empty(Stack *st) {
  return st->top < 0;
}

boolean stack_full(Stack *st) {
  return st->top + 1 >= STACK_MAX;
}

char stack_top(Stack *st) {
  return stack_empty(st) ? '\0' : st->data[st->top];
}

int stack_push(Stack *st, char c) {
  if (stack_full(st)) return 0;
  st->data[++st->top] = c;
  return 1;
}

int stack_pop(Stack *st) {
  if (stack_empty(st)) return 0;
  st->top--;
  return 1;
}

int pda_equal_01(const char *input) {
  Stack st;
  stack_init(&st);

  for (int i = 0; i < strlen(input); i++) {
    char ch = input[i];

    switch (ch) {
    case '0':
      (stack_top(&st) == '1') ? stack_pop(&st) : stack_push(&st, '0');
      break;
    case '1':
      (stack_top(&st) == '0') ? stack_pop(&st) : stack_push(&st, '1');
      break;
    default:
      printf("Invalid input\n");
      return 0;
    }
  }
  return stack_empty(&st);
}
    
int main() {
  char str[20];
  printf("Enter binary string: ");
  scanf("%s", str);

   if (pda_equal_01(str))
     printf("\nAccepted\nString has equal number of 0's and 1's\n");
   else
     printf("\nRejected\nString doesnot have equal number of 0's and 1's\n");

  return 0;
}
