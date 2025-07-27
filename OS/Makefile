CC = gcc
CFLAGS = -Wall -Wextra -g

all: q2

q2a: 2-thread_proc/thread.c
	$(CC) $^ -o $@
q2b: 2-thread_proc/process.c
	$(CC) $^ -o $@

clean:
	rm *~ q2a q2b
