#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {
  "int", "return", "#include", "main"
};
#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

int is_keyword(const char *word) {
  for (int i = 0; i < NUM_KEYWORDS; i++) {
    if (strcmp(word, keywords[i]) == 0) return 1;
  }
  return 0;
}

int is_identifier(const char *word) {
  if (!(isalpha(word[0]) || word[0] == '_')) return 0;
  for (int i = 1; word[i]; i++) {
    if (!(isalnum(word[i]) || word[i] == '_')) return 0;
  }
  return 1;
}

int main() {
  FILE *fp = fopen("sample.c", "r");
  if (!fp) {
    printf("Error: could not open test.c\n");
    return 1;
  }
  
  char token[50];
  int idx = 0;
  char ch;
  
  while ((ch = fgetc(fp)) != EOF) {
    if (isalnum(ch) || ch == '_') {
      token[idx++] = ch;
    } else {
      if (idx > 0) {
	token[idx] = '\0';
	if (is_keyword(token))
	  printf("Keyword: %s\n", token);
	else if (is_identifier(token))
	  printf("Identifier: %s\n", token);
	idx = 0;
      }
    }
  }
  
  fclose(fp);
  return 0;
}
