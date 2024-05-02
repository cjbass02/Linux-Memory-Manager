/**
 * @file test_large_heap.c
 *
 * @brief (Single thread) This file tests lots of allocations with a large heap
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 10000

int main() {
    char my_heap[MY_HEAP_SIZE];
	mm_init(my_heap, MY_HEAP_SIZE);

    char* ptrs[100];
    for(int i = 0; i < 100; i++) {
        ptrs[i] = mymalloc_bf(100);
        printf("Allocated ptrs[%d] = %p\n", i, ptrs[i]);
    }

    //free all those pointers
    for(int i = 0; i < 100; i++) {
        myfree(ptrs[i]);
        printf("Freed ptrs[%d]\n", i);
    }
    mm_destroy(my_heap);
    return 0;



    
}