#include <stdio.h>  // needed for size_t
#include <sys/mman.h> // needed for mmap
#include <assert.h> // needed for asserts
#include "dmm.h"

/*
 * Project 0: Heap Manager
 * Duke CompSci 310 Spring 2019 - Lebeck
 * Date Created: 1/27/2019
 * Date Last Modified: 1/30/2019
 * @author Brian J. Jordan (bjj17)
 */

/* You can improve the below metadata structure using the concepts from Bryant
 * and OHallaron book (chapter 9).
 */

typedef struct metadata {
  /* size_t is the return type of the sizeof operator. Since the size of an
   * object depends on the architecture and its implementation, size_t is used
   * to represent the maximum size of any object in the particular
   * implementation. size contains the size of the data object or the number of
   * free bytes
   */
  size_t size;
  struct metadata* next;
  struct metadata* prev; 
} metadata_t;

/* freelist maintains all the blocks which are not in use; freelist is kept
 * sorted to improve coalescing efficiency 
 */

static metadata_t* freelist = NULL;
static metadata_t* endFreeList = NULL;

/* for debugging; can be turned off through -NDEBUG flag*/
void print_freelist() {
  metadata_t *freelist_head = freelist;
  while(freelist_head != NULL) {
    DEBUG("\tFreelist Size:%zd, Head:%p, Prev:%p, Next:%p\t",
    freelist_head->size,
    freelist_head,
    freelist_head->prev,
    freelist_head->next);
    freelist_head = freelist_head->next;
  }
  DEBUG("\n");
}

/*
 * Iterates through free list coelescing adjacent blocks
 */
void coalesce(){
  metadata_t* cIterator = freelist->next;

  while(cIterator != endFreeList && cIterator->next != endFreeList){
    if(cIterator->next == ((metadata_t*)(((void*)(cIterator)) + METADATA_T_ALIGNED + cIterator->size))){
      cIterator->size = cIterator->size + METADATA_T_ALIGNED + cIterator->next->size;
      cIterator->next->size = NULL;
      cIterator->next = cIterator->next->next;
      cIterator->next->prev->prev = NULL;
      cIterator->next->prev->next = NULL;
      cIterator->next->prev = cIterator;
    }
    else{
      cIterator = cIterator->next;
    }
  }
}

/*
 * Returns pointer to beginning of data in new data block.
 */
void* getNewPtr(metadata_t* iter, size_t bytes){
  iter->size = ALIGN(bytes);
  iter->prev = NULL;
  iter->next = NULL;
  void* returnPtr = ((void*)(((void*)iter) + METADATA_T_ALIGNED));
  return returnPtr;
}

/*
 * Creates new header for remaining free memory space and adds it to the freelist.
 */
void getNewHeader(metadata_t* iter, size_t bytes){
    metadata_t* newHeader = ((metadata_t*)(((void*)iter) + ALIGN(bytes) + METADATA_T_ALIGNED));
    newHeader->prev = iter->prev;
    newHeader->next = iter->next;
    newHeader->size = iter->size - (METADATA_T_ALIGNED + ALIGN(bytes));
    iter->prev->next = newHeader;
    iter->next->prev = newHeader;
}

/*
 * Allocates specified size of block in memory for data and returns pointer to the beginning of the data.
 */
void* dmalloc(size_t numbytes) {
  /* initialize through mmap call first time */
  if(freelist == NULL) {
    printf("Initiating Free List\n"); 			
    if(!dmalloc_init())
      return NULL;
  }
  assert(numbytes > 0);

  metadata_t* malIterator = freelist->next;

  while(malIterator < endFreeList){
    // Case when free block is bigger than space requested
    if (malIterator->size > ALIGN(numbytes) + METADATA_T_ALIGNED){
      getNewHeader(malIterator, numbytes);
      return getNewPtr(malIterator, numbytes);
    }
    // Case when free block is as big as space requested
    else if (malIterator->size >= ALIGN(numbytes)){
      malIterator->prev->next = malIterator->next;
      malIterator->next->prev = malIterator->prev;
      return getNewPtr(malIterator, malIterator->size);
    }
    // Case when block is smaller than space requested
    else{
      malIterator = malIterator->next;
    }
  }
  return NULL;
}

/*
 * Adds freed data block back into freelist and calls method to coelesce freelist.
 */
void dfree(void* ptr) {
  metadata_t* freeIterator = freelist->next;

  metadata_t* refPointer = ((metadata_t*)(ptr - METADATA_T_ALIGNED));

  while(freeIterator <= endFreeList){
    if(refPointer < freeIterator){
      refPointer->prev = freeIterator->prev;
      refPointer->next = freeIterator;
      freeIterator->prev->next = refPointer;
      freeIterator->prev = refPointer;
      break;
    }
    else{
      freeIterator = freeIterator->next;
    }
  }

  coalesce();
}

bool dmalloc_init() {

  /* Two choices: 
   * 1. Append prologue and epilogue blocks to the start and the
   * end of the freelist 
   *
   * 2. Initialize freelist pointers to NULL
   *
   * Note: We provide the code for 2. Using 1 will help you to tackle the 
   * corner cases succinctly.
   */

  size_t max_bytes = ALIGN(MAX_HEAP_SIZE);
  /* returns heap_region, which is initialized to freelist */
  freelist = (metadata_t*) mmap(NULL, max_bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  /* Q: Why casting is used? i.e., why (void*)-1? */
  if (freelist == (void *)-1)
    return false;
  freelist->prev = NULL;
  freelist->size = 0;

  metadata_t* nextFreeSpace = ((metadata_t*)(((void*)freelist) + METADATA_T_ALIGNED));
  freelist->next = nextFreeSpace;
  nextFreeSpace->prev = freelist;
  nextFreeSpace->size = max_bytes - (3 * METADATA_T_ALIGNED);

  endFreeList = ((metadata_t*)(((void*)nextFreeSpace) + METADATA_T_ALIGNED + nextFreeSpace->size));
  nextFreeSpace->next = endFreeList;
  endFreeList->next = NULL;
  endFreeList->prev = nextFreeSpace;
  endFreeList->size = 0;

  return true;
}
