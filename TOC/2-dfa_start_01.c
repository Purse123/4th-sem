#include <stdio.h>
#include <string.h>

typedef enum STATE {
  q0 = 0,
  q1,
  q2,
  qd
} STATE;

STATE dfa_prefix(const char* s, const char* pattern) {
  STATE state = q0;
  size_t len = strlen(s);
  for (size_t i = 0; i < len; i++) {
    char ch = s[i];
    switch (state) {
    case q0:
      state = (ch == pattern[0]) ? q1 : qd;
      break;
    case q1:
      state = (ch == pattern[1]) ? q2 : qd;
      break;
    case q2:
      state = (ch == '0' || ch == '1') ? q2 : qd;
      break;
    case qd:
      return qd;
    }
  }
  return state;
}

int main() {
  char str[20], p[20] = "01";
  printf("Enter string: ");
  scanf("%s", str);

  STATE res = dfa_prefix(str, p);
  if (res == q2) printf("String is accepted via DFA\n");
  else printf("String is rejected via DFA\n");

  printf("Programmed by: Pierce Neupane\n");
  return 0;
}
