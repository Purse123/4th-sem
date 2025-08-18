#include <stdio.h>
#include <string.h>

typedef enum { q0, q1, q2 } STATE;

int simulate_nfa(const char *input) {
  STATE state = q0;
  for (int i = 0; i < strlen(input); i++) {
    char ch = input[i];
    switch (state) {
    case q0:
      if (ch == '1') state = q1;
      else state = q0;
      break;
    case q1:
      if (ch == '0') state = q2;
      else state = q1;
      break;
    case q2:
      if (ch == '1') state = q1;
      else state = q0;
      break;
    }
  }
  return state == q2;
}

int main() {
  char str[100];
  printf("Enter a binary string: ");
  scanf("%s", str);
  
  if (simulate_nfa(str))
    printf("Accepted\n");
  else
    printf("Rejected: string does not end with 10\n");
  
  return 0;
}
