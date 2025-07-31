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


