#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>

typedef uint32_t u32;

#define KB2BIT(x) ((x) * (1024 * 8))
#define BIT2KB(x) ((x) / (1024 * 8))

#define MEM_SIZE   KB2BIT(32)  // 32 KB
#define FRAME_SIZE KB2BIT(4)   // 4 KB
#define PAGE_SIZE  KB2BIT(4)   // 4 KB

#define FRAME_NUM  (MEM_SIZE / FRAME_SIZE)

int isPageInFrames(int frames[], int n, int page) {
  for (int i = 0; i < n; i++)
    if (frames[i] == page) return i;
  return -1;
}

int main() {
  assert(FRAME_NUM > 0);
  fprintf(stdout, "[INFO] No of frames: %" PRIu32 "\n", FRAME_NUM);

  int frames[FRAME_NUM];
  int last_used[FRAME_NUM];
  for (int i = 0; i < FRAME_NUM; i++) {
    frames[i] = -1;
    last_used[i] = -1;
  }

  int ref_len;
  fprintf(stdout, "Enter length of reference string: ");
  scanf("%d", &ref_len);

  int ref_string[100];
  fprintf(stdout, "Enter reference string (page numbers):\n");
  for (int i = 0; i < ref_len; i++)
    scanf("%d", &ref_string[i]);

  int page_faults = 0, hits = 0;
  int time = 0;

  for (int i = 0; i < ref_len; i++) {
    int page = ref_string[i];
    time++;

    int idx = isPageInFrames(frames, FRAME_NUM, page);

    if (idx != -1) {
      hits++;
      last_used[idx] = time;
      printf("Page %d → HIT\n", page);
    } else {
      page_faults++;

      int empty = -1;
      for (int j = 0; j < FRAME_NUM; j++) {
        if (frames[j] == -1) {
          empty = j;
          break;
        }
      }

      if (empty != -1) {
        frames[empty] = page;
        last_used[empty] = time;
      } else {
        int lru_index = 0;
        for (int j = 1; j < FRAME_NUM; j++) {
          if (last_used[j] < last_used[lru_index]) {
            lru_index = j;
          }
        }
        frames[lru_index] = page;
        last_used[lru_index] = time;
      }

      printf("Page %d → FAULT: Frames: ", page);
      for (int j = 0; j < FRAME_NUM; j++) {
        if (frames[j] == -1) printf("[ ] ");
        else printf("[%d] ", frames[j]);
      }
      printf("\n");
    }
  }

  printf("\nTotal Hits: %d\n", hits);
  printf("Total Faults: %d\n", page_faults);

  return 0;
}
