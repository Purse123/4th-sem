#include <stdio.h>
#include <string.h>

void prefix(char* str) {
  printf("NULL\n");
  for (int i = 0; i <= strlen(str); i++) {
    for (int j = 0; j <= i; j++) {
      printf("%c", str[j]);
    }
    printf("\n");
  }
}

void suffix(char* str) {
  printf("NULL\n");
  for (int i = 0; i <= strlen(str); i++) {
    for (int j = i; j <= strlen(str); j++) {
      printf("%c", str[j]);
    }
    printf("\n");
  }
}

void substring(char* str) {
  printf("NULL\n");
  for (int i = 0; i < strlen(str); i++) {
    for (int j = i; j < strlen(str); j++) {
      int k;
      for (k = i; k <= j; k++) {
	printf("%c", str[k]);
      }
      printf("\n");
    }
  }
}

int main() {
  char text[3] = "abc";
  printf("String: %s\n", text);
  
  printf("\nPrefix: \n");
  prefix(text);

  printf("\nSuffix: \n");
  suffix(text);

  printf("\nSubstring: \n");
  substring(text);

  return 0;
}
