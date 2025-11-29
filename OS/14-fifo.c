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

int isPageInFrames(int frames[], int n, int page) {
  for (int i = 0; i < n; i++) 
    if (frames[i] == page) return 1;
  return 0;
}

int main() {
  assert(FRAME_NUM > 0);
  fprintf(stdout, "[INFO] No of frames: %" PRIu32 "\n", FRAME_NUM);
  
  int frames[FRAME_NUM];
  for (int i = 0; i < FRAME_NUM; i++) frames[i] = -1;
  
  int ref_len;
  printf("Enter length of reference string: ");
  scanf("%d", &ref_len);
  
  int ref_string[100];
  printf("Enter reference string (page numbers):\n");
  for (int i = 0; i < ref_len; i++) {
    scanf("%d", &ref_string[i]);
  }
  
  int page_faults = 0, hits = 0, fifo_index = 0;
  
  for (int i = 0; i < ref_len; i++) {
    int page = ref_string[i];
    
    if (isPageInFrames(frames, FRAME_NUM, page)) {
      hits++;
      printf("Page %d → HIT\n", page);
    } else {
      page_faults++;
      printf("Page %d → FAULT: ", page);
      
      frames[fifo_index] = page;
      fifo_index = (fifo_index + 1) % FRAME_NUM;
      
      printf("Frames: ");
      for (int j = 0; j < FRAME_NUM; j++) {
	if (frames[j] == -1) printf("[ ] ");
	else printf("[%d] ", frames[j]);
      }
      printf("\n");
    }
  }
  
  printf("\nTotal Hits: %d\n", hits);
  printf("Total Faults: %d\n", page_faults);

  fprintf(stdout, "Programmed by Pierce Neupane\n");
  return 0;
}
