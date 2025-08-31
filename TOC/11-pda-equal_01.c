#include <stdio.h>
#include <string.h>

#define STACK_MAX 1024

typedef struct {
  char data[STACK_MAX];
  int top;
} Stack;

void stack_init(Stack *st) {
  st->top = -1;
}

int stack_empty(Stack *st) {
  return st->top < 0;
}

int stack_full(Stack *st) {
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

int pda_equal_zeros_ones(const char *s) {
  Stack st; stack_init(&st);
  stack_push(&st, '$');

  for (size_t i = 0; s[i] != '\0'; i++) {
    char ch = s[i];
    if (ch != '0' && ch != '1') {
      return 0;
    }
    
    char t = stack_top(&st);
    if (ch == '0') {
      if (t == 'B') {
	stack_pop(&st);
      } else {
	if (!stack_push(&st, 'A')) return 0;
      }
    } else {
      if (t == 'A') {
	stack_pop(&st);
      } else {
	if (!stack_push(&st, 'B')) return 0;
      }
    }
  }
  
  return (stack_top(&st) == '$' && st.top == 0);
}

int main(void) {
  char s[1024];
  printf("Enter a binary string: ");
  if (scanf("%s", s) != 1) return 1;
  
  if (pda_equal_zeros_ones(s))
    printf("Accepted\n");
  else
    printf("Rejected: counts are not equal\n");

  printf("Programmed by: Pierce Neupane\n");
  return 0;
}
