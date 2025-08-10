#include <stdio.h>
#include <stdlib.h>

void inputMemoryDetails(int* mem_size, int* frame_size, int* frame_num) {
  printf("Enter total memory size (in bytes): ");
  scanf("%d", mem_size);
  
  printf("Enter frame/page size (in bytes): ");
  scanf("%d", frameSize);
  
  if (*frameSize <= 0) {
    printf("Frame size must be greater than 0.\n");
    exit(1);
  }
  
  *numFrames = *memSize / *frameSize;
  printf("Total frames in physical memory: %d\n", *numFrames);
}

// Function to input page table
void inputPageTable(int* pageTable, int numPages, int numFrames) {
  printf("Enter frame number for each page:\n");
  
  for (int i = 0; i < numPages; i++) {
    printf("Page %d → Frame: ", i);
    scanf("%d", &pageTable[i]);
    
    if (pageTable[i] < 0 || pageTable[i] >= numFrames) {
      printf("Invalid frame number. Must be between 0 and %d.\n", numFrames - 1);
      exit(1);
    }
  }
}

// Function to translate logical address to physical address
int translateAddress(int logicalAddress, int frameSize, int* pageTable, int numPages) {
  int pageNumber = logicalAddress / frameSize;
  int offset = logicalAddress % frameSize;
  
  if (pageNumber >= numPages) {
    printf("Invalid logical address. Page number %d does not exist.\n", pageNumber);
    exit(1);
  }
  
  return (pageTable[pageNumber] * frameSize) + offset;
}

int main() {
  int mem_size, frame_size, frame_num;
  int page_num, logicalAddress, physicalAddress;
  int pageTable[100];
  
  inputMemoryDetails(&memSize, &frameSize, &numFrames);
  
  printf("Enter number of pages in process: ");
  scanf("%d", &numPages);
  
  if (numPages > numFrames) {
    printf("Not enough frames for all pages. Maximum pages allowed: %d\n", numFrames);
    return 1;
  }
  
  inputPageTable(pageTable, numPages, numFrames);
  
  printf("Enter a logical address (0 to %d): ", (numPages * frameSize) - 1);
  scanf("%d", &logicalAddress);
  
  if (logicalAddress < 0 || logicalAddress >= numPages * frameSize) {
    printf("Invalid logical address.\n");
    return 1;
  }
  
  physicalAddress = translateAddress(logicalAddress, frameSize, pageTable, numPages);
  printf("Logical Address %d → Physical Address %d\n", logicalAddress, physicalAddress);
  
  return 0;
}
