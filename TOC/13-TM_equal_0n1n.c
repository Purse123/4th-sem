#include <stdio.h>

typedef enum State {
  q0, q1, q2, q3, q4, qr
} State;

int main() {
  char input[100];
  State curr = q0;
  int i;
  for (i = 0; i < 100; i++)
    input[i] = '\0';

  printf("Enter binary string: ");
  scanf("%s", input);
  i = 0;

  while (1) {
    switch(curr) {
    case q0:
      if (input[i] == '0') {
	curr = q1;
	input[i] = 'x';
	i++;
      } else if (input[i] == 'y') {
	curr = q3;
	i++;
      }
      else curr = qr;
      break;

    case q1:
      if (input[i] == '0' || input[i] == 'y') {
	curr = q1;
	i++;
      } else if (input[i] == '1') {
	curr = q2;
	input[i] = 'y';
	i--;
      }
      else curr = qr;
      break;

    case q2:
      if (input[i] == '0' || input[i] == 'y') {
	curr = q2;
	i--;
      } else if (input[i] == 'x') {
	curr = q0;
	i++;
      }
      else curr = qr;
      break;

    case q3:
      if (input[i] == 'y') {
	curr = q3;
	i++;
      }
      else if (input[i] == '\0')
	curr = q4;
      else curr = qr;
      break;
    }

    if (curr == qr || curr == q4)
      break;
  }

  if (curr == q4) printf("Accepted\n");
  else printf("String rejected\n");

  printf("Programmed by: Pierce Neupane\n");
  return 0;
}
