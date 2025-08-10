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

## Paging
1. logical/virtual memory: 
   - memory address space used by programs.
   - divided into fixed-size blocks called pages.
2. Physical memory:
   - Acutual RAM.
   - divided into blocks of same size as page called frames.
3. Page Table:
   - Data structure used by OS to map logical pages to physical frames.

**How does it work**
1. Program is divided into pages by OS.
2. Pages are loaded into available frames in physical memory.
3. When CPU access memory address, Memory Management Unit:
   - Looks up page number in page table.
   - Finds corresponding frame number.
   - Combine frame number with offset to access the exact physical address.

**Example:**
suppose:
- page size       = 4kb
- logical address = 10kb
then 
- page number = 10kb / 4kb = 2
- offset      = 10kb % 4kb = 2 kb
if page 2 is in frame 5:
physical address = (frame 5) * 4 kb + 2 kb = 22 kb
