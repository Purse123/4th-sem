CC = gcc
CFLAGS = -Wall -Wextra -g
LD = -pthread
all: q2a q2b q3 q4 fcfs sjf priority q6a q6b q7 q8 q9 q10 q11 q12 q13 q14 q15 q16 q17 singleFile twoLevel multiLevel sequential indexed linked q20

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
q10: 10-paging.c
	$(CC) $^ -o $@ $(LD)
q11: 11-first_fit.c
	$(CC) $^ -o $@ $(LD)
q12: 12-best_fit.c
	$(CC) $^ -o $@ $(LD)
q13: 13-worst_fit.c
	$(CC) $^ -o $@ $(LD)
q14: 14-fifo.c
	$(CC) $^ -o $@ $(LD)
q15: 15-leastRecentUsed.c
	$(CC) $^ -o $@ $(LD)
q16: 16-leastFrequentlyUsed.c
	$(CC) $^ -o $@ $(LD)
q17: 17-optimal_replacement.c
	$(CC) $^ -o $@ $(LD)
singleFile: 18-fileOrganize/single_level.c
	$(CC) $^ -o $@ $(LD)
twoLevel: 18-fileOrganize/two_level.c
	$(CC) $^ -o $@ $(LD)
multiLevel: 18-fileOrganize/hierarchical.c
	$(CC) $^ -o $@ $(LD)
sequential: 19-file_alloc_strat/sequential.c
	$(CC) $^ -o $@ $(LD)
indexed: 19-file_alloc_strat/index.c
	$(CC) $^ -o $@
linked: 19-file_alloc_strat/linked.c
	$(CC) $^ -o $@
q20: 20-disk_scheduling/disk_scheduling.c 20-disk_scheduling/main.c
	$(CC) $^ -o $@

clean:
	rm *~ q2a q2b q3 q4 fcfs sjf priority q6a q6b q7 q8 q9 q10 q11 q12 q13 q14 q15 q16 q17 singleFile twoLevel multiLevel sequential indexed linked q20
