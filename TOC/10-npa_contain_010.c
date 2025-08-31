#include <stdio.h>
#include <string.h>

enum State { q0, q1, q2, q3 };

int simulate_nfa(const char *str) {
    int states[4] = {0}; // current active states
    int count = 1;
    states[0] = q0;

    for (int i = 0; str[i]; i++) {
        int sym = str[i] - '0';
        int next[4], next_count = 0;

        for (int j = 0; j < count; j++) {
            int s = states[j];
            switch(s) {
                case q0:
                    if (sym == 0) { next[next_count++] = q0; next[next_count++] = q1; }
                    else next[next_count++] = q0;
                    break;
                case q1:
                    if (sym == 0) next[next_count++] = q1;
                    else if (sym == 1) next[next_count++] = q2;
                    break;
                case q2:
                    if (sym == 0) next[next_count++] = q3;
                    else if (sym == 1) next[next_count++] = q0;
                    break;
                case q3:
                    next[next_count++] = q3;
                    break;
            }
        }

        memcpy(states, next, next_count * sizeof(int));
        count = next_count;
    }

    for (int i = 0; i < count; i++)
        if (states[i] == q3) return 1;

    return 0;
}

int main() {
    char str[100];
    printf("Enter binary string: ");
    scanf("%s", str);

    if (simulate_nfa(str))
        printf("Accepted\n");
    else
        printf("Rejected\ndoesnot contain 010\n");

    printf("Programmed by: Pierce Neupane\n");
    return 0;
}
