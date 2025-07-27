#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int main() {
  int64_t ret;
  __asm__ __volatile__ (
	"mov $0x39, %%rax;"
	"syscall\n\t"
	"mov %%rax, %0\n\t"
	: "=r" (ret)
	:
	: "%rax", "memory"		/* clobbered register */
  );

  if (ret == 0) {
    printf("Child process: PID = %d\n", getpid());
    _exit(0);			/* for child terminationI */
  }
  else if (ret > 0) {
    printf("Parent process: PID = %d, Child PID = %ld\n", getpid(), ret);
  } else {
    perror("fork failed");
  }
  printf("Programmed by Pierce Neupane\n");
  return 0;
}
