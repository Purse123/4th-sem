#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TAPE_SIZE 100

enum states {
    q0, q1, q2, q3, q_accept, q_reject
};

struct TM {
    char tape[MAX_TAPE_SIZE];
    int head;
    enum states current_state;
};

void initialize_TM(struct TM *tm, const char *input) {
    strncpy(tm->tape + 1, input, MAX_TAPE_SIZE - 2);
    tm->tape[0] = 'B'; // Blank symbol at start
    tm->tape[strlen(input) + 1] = 'B'; // Blank symbol at end
    tm->head = 1;
    tm->current_state = q0;
}

int process_TM(struct TM *tm) {
    while (1) {
        char current_symbol = tm->tape[tm->head];
        
        switch (tm->current_state) {
            case q0:
                if (current_symbol == '0') {
                    tm->tape[tm->head] = 'X';
                    tm->head++;
                    tm->current_state = q1;
                } else if (current_symbol == 'Y') {
                    tm->head++;
                    tm->current_state = q3;
                } else {
                    tm->current_state = q_reject;
                }
                break;
                
            case q1:
                if (current_symbol == '0') {
                    tm->head++;
                } else if (current_symbol == 'Y') {
                    tm->head++;
                } else if (current_symbol == '1') {
                    tm->tape[tm->head] = 'Y';
                    tm->head--;
                    tm->current_state = q2;
                } else {
                    tm->current_state = q_reject;
                }
                break;
                
            case q2:
                if (current_symbol == '0') {
                    tm->head--;
                } else if (current_symbol == 'X') {
                    tm->head++;
                    tm->current_state = q0;
                } else if (current_symbol == 'Y') {
                    tm->head--;
                } else {
                    tm->current_state = q_reject;
                }
                break;
                
            case q3:
                if (current_symbol == 'Y') {
                    tm->head++;
                } else if (current_symbol == 'B') {
                    tm->current_state = q_accept;
                } else {
                    tm->current_state = q_reject;
                }
                break;
                
            case q_accept:
                return 1;
                
            case q_reject:
                return 0;
        }
        
        if (tm->current_state == q_accept) return 1;
        if (tm->current_state == q_reject) return 0;
    }
}

int main() {
    char input[MAX_TAPE_SIZE];
    printf("Enter binary string: ");
    scanf("%s", input);
    
    // Basic input validation
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != '0' && input[i] != '1') {
            printf("Invalid input. Only 0s and 1s allowed.\n");
            return 1;
        }
    }
    
    struct TM tm;
    initialize_TM(&tm, input);
    
    int result = process_TM(&tm);
    
    if (result)
        printf("Accepted\n", input);
    else 
      printf("Rejected: string not in form 0^n1^n\n");
    
    
    return 0;
}
