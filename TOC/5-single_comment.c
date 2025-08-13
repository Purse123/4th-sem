#include <stdio.h>
#include <string.h>

typedef enum {
  Q0,
  Q1,
  Q2,
  Q3
} STATE;

void extract_single_line_comments(const char *program) {
  STATE state = Q0;
  char comment[200];
  int idx = 0;

  size_t len = strlen(program);
  
  for (size_t i = 0; i < len; i++) {
    char ch = program[i];
    
    switch (state) {
    case Q0:
      state = (ch == '/') ? Q1 : Q0;
      break;
      
    case Q1:
      if (ch == '/') {
	state = Q2;
	idx = 0;   
      } else {
	state = Q0;
      }
      break;
      
    case Q2:
      if (ch == '\n') {
	comment[idx] = '\0';
	printf("Single-line comment: %s\n", comment);
	state = Q0;
      } else {
	if (idx < sizeof(comment) - 1) {
	  comment[idx++] = ch;
	}
      }
      break;
      
    case Q3:
      state = Q0;
      break;
    }
  }
  
  if (state == Q2) {
    comment[idx] = '\0';
    printf("Single-line comment: %s\n", comment);
  }
}

int main() {
  const char *program =
    "#include <stdio.h>\n"
    "int main() {\n"
    "    printf(\"Hello world\"); // print hello world\n"
    "}\n";
  
  extract_single_line_comments(program);
  return 0;
}
