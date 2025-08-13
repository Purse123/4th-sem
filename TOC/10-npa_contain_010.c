#include <stdio.h>
#include <string.h>

#define MAX_STATES 4
#define MAX_STR_LEN 100

enum { q0, q1, q2, q3 };

int transitions[MAX_STATES][2][MAX_STATES] = {
  { {q1, -1}, {q0, -1} },
  { {q1, -1}, {q2, -1} },
  { {q3, -1}, {q0, -1} },
  { {q3, -1}, {q3, -1} }
};

int simulate_nfa(const char *input) {
  int current[MAX_STATES], next[MAX_STATES];
  int curr_count = 1, next_count, i, j, k;
  current[0] = q0;
  
  for (i = 0; input[i] != '\0'; i++) {
    int sym = input[i] - '0';
    if (sym != 0 && sym != 1) return 0;
    
    next_count = 0;
    for (j = 0; j < curr_count; j++) {
      int state = current[j];
      for (k = 0; transitions[state][sym][k] != -1; k++) {
	next[next_count++] = transitions[state][sym][k];
      }
    }
    
    memcpy(current, next, next_count * sizeof(int));
    curr_count = next_count;
  }
  
  for (i = 0; i < curr_count; i++) {
    if (current[i] == q3) return 1;
  }
  return 0;
}

int main() {
  char str[MAX_STR_LEN];
  printf("Enter a binary string: ");
  scanf("%s", str);
  
  if (simulate_nfa(str))
    printf("Accepted: contains substring 010\n");
  else
    printf("Rejected: does not contain substring 010\n");
  
  return 0;
}
