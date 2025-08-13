CC = gcc
CFLAGS = -Wall -Wextra -g

all: q1

q1: 1-pre_suf_sub.c
	$(CC) $^ -o $@
q2: 2-dfa_start_01.c
	$(CC) $^ -o $@
q3: 3-dfa_end_10.c
	$(CC) $^ -o $@
q4: 4-dfa_contain_010.c
	$(CC) $^ -o $@
q5: 5-single_comment.c
	$(CC) $^ -o $@
q6: 6-multi_comment.c
	$(CC) $^ -o $@
q7: 7-identifier_keyword.c
	$(CC) $^ -o $@
q8: 8-nfa_start_01.c
	$(CC) $^ -o $@
q9: 9-nfa_end_10.c
	$(CC) $^ -o $@
q10: 10-npa_contain_010.c
	$(CC) $^ -o $@
q11: 11-pda-equal_01.c
	$(CC) $^ -o $@

clean:
	rm *~ q1 q2 q3 q4 q5 q6 q7 q8 q9 q10 q11
