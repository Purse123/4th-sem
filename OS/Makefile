CC = gcc
CFLAGS = -Wall -Wextra -g
LD = -pthread
all: q2a q2b q3 q4 fcfs sjf priority q6a q6b q7 q8 q9 q10 q11 q12 q13 q14 q15 q16 q17 singleFile twoLevel multiLevel sequential indexed linked q20

q2: 2-thread_proc/proc_thread.c
	$(CC) $^ -o $@ $(LD) $(CFLAGS)
q2a: 2-thread_proc/thread.c
	$(CC) $^ -o $@ $(CFLAGS)
q2b: 2-thread_proc/process.c
	$(CC) $^ -o $@ $(CFLAGS)
q3: 3-producer-consumer.c
	$(CC) $^ -o $@
q4: 4-Dining-philosopers.c
	$(CC) $^ -o $@ $(CFLAGS)
fcfs: 5-non-preemptive_cpu_scheduling/fcfs.c
	$(CC) $^ -o $@ $(CFLAGS)
sjf: 5-non-preemptive_cpu_scheduling/sjf.c
	$(CC) $^ -o $@ $(CFLAGS)
priority: 5-non-preemptive_cpu_scheduling/priority.c
	$(CC) $^ -o $@ $(CFLAGS)
q6a: 6-preemptive_scheduling/round_robin.c
	$(CC) $^ -o $@ $(CFLAGS)
q6b: 6-preemptive_scheduling/priority.c
	$(CC) $^ -o $@ $(CFLAGS)
q7: 7-bankers_dl_avoidance.c
	$(CC) $^ -o $@ $(CFLAGS)
q8: 8-bankers_dl_prevent.c
	$(CC) $^ -o $@ $(CFLAGS)
q9: 9-mvt_mft.c
	$(CC) $^ -o $@ $(CFLAGS)
q10: 10-paging.c
	$(CC) $^ -o $@ $(CFLAGS)
q11: 11-first_fit.c
	$(CC) $^ -o $@ $(CFLAGS)
q12: 12-best_fit.c
	$(CC) $^ -o $@ $(CFLAGS)
q13: 13-worst_fit.c
	$(CC) $^ -o $@ $(CFLAGS)
q14: 14-fifo.c
	$(CC) $^ -o $@ $(CFLAGS)
q15: 15-leastRecentUsed.c
	$(CC) $^ -o $@ $(CFLAGS)
q16: 16-leastFrequentlyUsed.c
	$(CC) $^ -o $@ $(CFLAGS)
q17: 17-optimal_replacement.c
	$(CC) $^ -o $@ $(CFLAGS)
singleFile: 18-fileOrganize/single_level.c
	$(CC) $^ -o $@ $(CFLAGS)
twoLevel: 18-fileOrganize/two_level.c
	$(CC) $^ -o $@ $(CFLAGS)
multiLevel: 18-fileOrganize/hierarchical.c
	$(CC) $^ -o $@ $(CFLAGS)
sequential: 19-file_alloc_strat/sequential.c
	$(CC) $^ -o $@ $(CFLAGS)
indexed: 19-file_alloc_strat/index.c
	$(CC) $^ -o $@
linked: 19-file_alloc_strat/linked.c
	$(CC) $^ -o $@
q20: 20-disk_scheduling/disk_scheduling.c 20-disk_scheduling/main.c
	$(CC) $^ -o $@

clean:
	rm *~ q2 q2a q2b q3 q4 fcfs sjf priority q6a q6b q7 q8 q9 q10 q11 q12 q13 q14 q15 q16 q17 singleFile twoLevel multiLevel sequential indexed linked q20
