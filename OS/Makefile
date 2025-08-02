CC = gcc
CFLAGS = -Wall -Wextra -g
LD = -pthread
all: q2

q2a: 2-thread_proc/thread.c
	$(CC) $^ -o $@ $(LD)
q2b: 2-thread_proc/process.c
	$(CC) $^ -o $@ $(LD)
q3: 3-producer-consumer.c
	$(CC) $^ -o $@ $(LD)
q4: 4-Dining-philosopers.c
	$(CC) $^ -o $@ $(LD)
fcfs: 5-non-preemptive_cpu_scheduling/fcfs.c
	$(CC) $^ -o $@ $(LD)
sjf: 5-non-preemptive_cpu_scheduling/sjf.c
	$(CC) $^ -o $@ $(LD)
priority: 5-non-preemptive_cpu_scheduling/priority.c
	$(CC) $^ -o $@ $(LD)

clean:
	rm *~ q2a q2b q3 q4 fcfs sjf priority
