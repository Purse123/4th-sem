## OS
3. producer-consumer problem using Semaphores.
- synchronization problem
- demonstrate how multiple threads or process share common, fixed-size buffer without conflicts.
- **producers** generate data and add it to buffer
- **consumer** take data from buffer and process it

- buffer have limited capacity
> producer must wait if buffer is full
> consumer must wait if buffer is empty

## Commmon Solution Using Semaphores 
- semaphore 
  `empty`: tracks empty slots in buffer
  `full`: tracks filled slots
  `mutex`: ensure mutual exclusion when accessing buffer

## Mutual Exclusion 
- also known as mutex
- It ensures that only one process or thread can access a critical section (shared resource) at a time
- It prevents race condition and ensuring data consistency.

***

## Banker's algorithm
- It is a deadlock avoidance algorithm.
- It ensures system never enter an unsafe safe ensure deadlock by keeping sufficient resource available for all processes.

**Step**
- take no of processes and no of resource type
- `max[n][m]`: max demand of each process
- `Allocation[n][m]`: currently allocated resource

**Safety Check Algorithm**
We determine if a system is in a safe state:
- Initialize:
	Work       = Available
	Finish[i]  = false for all processes
- Find a process i such that:
	Finish[i] == false
	Need[i]   <= Work
- If such a process is found:
	Work      += Allocation[i]
	Finish[i]  = true
- Repeat
	If all processes are finished (Finish[i] == true), system is in a safe state
