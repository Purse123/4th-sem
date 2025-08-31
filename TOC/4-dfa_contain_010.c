#include <stdio.h>
#include <string.h>

typedef enum STATE {
  q0 = 0,
  q1,
  q2,
  q3
} STATE;

STATE dfa_prefix(const char* s, const char* pattern) {
  STATE state = q0;
  size_t len = strlen(s);
  for (size_t i = 0; i < len; i++) {
    char ch = s[i];
    switch (state) {
    case q0:
      state = (ch == pattern[0]) ? q1 : q0;
      break;
    case q1:
      state = (ch == pattern[1]) ? q2 : q1;
      break;
    case q2:
      state = (ch == pattern[2]) ? q3 : q0;
      break;
    case q3:
      state = q3;
      break;
    }
  }
  return state;
}

int main() {
  char str[20], p[20] = "010";
  printf("Enter string: ");
  scanf("%s", str);

  STATE res = dfa_prefix(str, p);
  if (res == q3) printf("String is accepted via DFA\n");
  else printf("String is rejected via DFA\n");

  printf("Programmed by: Pierce Neupane\n");
  return 0;
}
