#include <stdio.h>
#include <string.h>

typedef enum {
  Q0,
  Q1,
  Q2,
  Q3 
} STATE;

void extract_multiline_comments(const char *program) {
  STATE state = Q0;
  char comment[500];
  int idx = 0;
  
  size_t len = strlen(program);
  
  for (size_t i = 0; i < len; i++) {
    char ch = program[i];
    
    switch (state) {
    case Q0:
      state = (ch == '/') ? Q1 : Q0;
      break;
      
    case Q1:
      if (ch == '*') {
	state = Q2;
	idx = 0;
      } else {
	state = Q0;
      }
      break;
      
    case Q2:
      if (ch == '*') {
	state = Q3;
      } else {
	if (idx < sizeof(comment) - 1) {
	  comment[idx++] = ch;
	}
      }
      break;
      
    case Q3:
      if (ch == '/') {
	comment[idx] = '\0';
	printf("Multi-line comment:\n%s\n", comment);
	state = Q0;
      } else {
	if (idx < sizeof(comment) - 1) {
	  comment[idx++] = '*';
	  comment[idx++] = ch; 
	}
	state = Q2;
      }
      break;
    }
  }
}

int main() {
  const char *program =
    "#include <stdio.h>\n"
    "int main() {\n"
    "    /* This is a\n"
    "       multi-line comment */\n"
    "    printf(\"Hello\");\n"
        "    /* Another comment */\n"
    "}\n";
  
  extract_multiline_comments(program);
  return 0;
}
