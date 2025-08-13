#include <stdio.h>
#include <string.h>

#define MAX_STATES 4
#define MAX_LEN 100

enum { q0, q1, q2, qd };

int transitions[MAX_STATES][2][MAX_STATES] = {
    { {q1, -1, -1}, {qd, -1, -1} }, 
    { {qd, -1, -1}, {q2, -1, -1} }, 
    { {q2, -1, -1}, {q2, -1, -1} }, 
    { {qd, -1, -1}, {qd, -1, -1} }
};

int simulate_nfa(const char *input) {
    int current_states[MAX_STATES] = {0};
    int next_states[MAX_STATES];
    int state_count, i, j, sym;

    current_states[0] = q0;
    state_count = 1;

    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] != '0' && input[i] != '1') return 0; // invalid char
        sym = input[i] - '0';

        int next_count = 0;
        for (j = 0; j < state_count; j++) {
            int st = current_states[j];
            for (int k = 0; transitions[st][sym][k] != -1; k++) {
                next_states[next_count++] = transitions[st][sym][k];
            }
        }

        memcpy(current_states, next_states, next_count * sizeof(int));
        state_count = next_count;
    }

    for (i = 0; i < state_count; i++) {
        if (current_states[i] == q2) return 1;
    }
    return 0;
}

int main() {
    char str[MAX_LEN];
    printf("Enter a binary string: ");
    scanf("%s", str);

    if (simulate_nfa(str))
        printf("Accepted: string starts with 01\n");
    else
        printf("Rejected: string does not start with 01\n");

    return 0;
}
