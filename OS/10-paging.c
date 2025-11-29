#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>

typedef uint32_t u32;

#define KB2BIT(x) ((x) * (1024 * 8))
#define BIT2KB(x) ((x) / (1024 * 8))

#define MEM_SIZE   KB2BIT(32)  // 32 KB
#define FRAME_SIZE KB2BIT(4)   // 4 KB
#define PAGE_SIZE  KB2BIT(4)   // 4 KB

#define FRAME_NUM  (MEM_SIZE / FRAME_SIZE)

void inject2_pageTable(u32* ptable, u32 page_n, u32 frame_n) {
  for (u32 i = 0; i < page_n; i++) {
    printf("Enter frame no for page[%d]: ", i);
    scanf("%d", &ptable[i]);
    
    if (ptable[i] >= frame_n) {
      fprintf(stderr, "[ERROR] Invalid frame number.\n");
      exit(-1);
    }
  }
}

int logical2physical(int logicalAddress, u32* ptable, int page_n) {
  int pageNumber = logicalAddress / FRAME_SIZE;
  int offset = logicalAddress % FRAME_SIZE;

  if (pageNumber >= page_n) {
    fprintf(stderr, "[ERROR] Invalid logical address\n");
    exit(-1);
  }

  return (ptable[pageNumber] * FRAME_SIZE) + offset;
}

int main() {
  u32 page_num;
  u32 pageTable[100];
  
  assert(FRAME_NUM > 0);
  fprintf(stdout, "[INFO] No of frames: %" PRIu32 "\n", FRAME_NUM);

  fprintf(stdout, "Enter number of pages process: ");
  scanf("%" SCNu32, &page_num);
  
  if (page_num > FRAME_NUM) {
    fprintf(stderr, "[WARNING] More pages than frames\n");
    return -1;
  }

  inject2_pageTable(pageTable, page_num, FRAME_NUM);

  /*
    logical address:
     - vpn `4 bits`
     - offset `12 bits`
  */
  u32 logicalAddress, physicalAddress;
  fprintf(stdout, "Enter logical address in bytes (0 to %"PRIu32"):", (page_num * PAGE_SIZE) - 1);
  scanf("%" SCNu32, &logicalAddress);

  if (logicalAddress >= page_num * FRAME_SIZE) {
    fprintf(stderr, "[ERROR] Invalid logical address.\n");
    return -1;
  }

  physicalAddress = logical2physical(logicalAddress, pageTable, page_num);
  printf("Logical Address %d -> Physical Address %d\n", logicalAddress, physicalAddress);

  fprintf(stdout, "Programmed by Pierce Neupane\n");
  return 0;
}
