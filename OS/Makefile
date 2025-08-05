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
q6a: 6-preemptive_scheduling/round_robin.c
	$(CC) $^ -o $@ $(LD)
q6b: 6-preemptive_scheduling/priority.c
	$(CC) $^ -o $@ $(LD)
q7: 7-bankers_dl_avoidance.c
	$(CC) $^ -o $@ $(LD)
q8: 8-bankers_dl_prevent.c
	$(CC) $^ -o $@ $(LD)
q9: 9-mvt_mft.c
	$(CC) $^ -o $@ $(LD)

clean:
	rm *~ q2a q2b q3 q4 fcfs sjf priority q6a q6b q7 q8 q9
