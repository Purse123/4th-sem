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

int pda_0n1n(const char *input) {
  Stack st;
  stack_init(&st);
  int i, n = strlen(input);
  int seen_one = 0;
  
  for (i = 0; i < n; i++) {
    char ch = input[i];

    switch (ch) {
    case '0':
      if (seen_one) return FALSE;
      stack_push(&st, '0');
      break;
    case '1':
      seen_one = 1;
      if (!stack_pop(&st)) return FALSE;
      break;
    default:
      printf("Invalid input\n");
      return FALSE;
    }
  }
  return stack_empty(&st);
}
    
int main() {
  char str[20];
  printf("Enter binary string: ");
  scanf("%s", str);

   if (pda_0n1n(str))
     printf("Accepted\n");
   else
     printf("\nRejected\nString not in form 0^n1^n\n");

   printf("Programmed by: Pierce Neupane\n");
  return 0;
}
